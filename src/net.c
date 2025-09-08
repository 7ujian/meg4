/*
 * meg4/net.c
 *
 * Copyright (C) 2023 bzt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @brief LAN game functions
 * @chapter Networking
 *
 */

#ifndef __EMSCRIPTEN__
#ifdef __WIN32__
#include <ws2tcpip.h>
#else
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#endif

#include "meg4.h"
#include "lang.h"

#define NUMPEER 16
#define PORT 1025

#ifndef __EMSCRIPTEN__
typedef struct {
    struct sockaddr_in addr;
    uint32_t lastseen;
} peer_t;
peer_t net_peers[NUMPEER] = { 0 };
int _net_sock = 0, _net_role = 0, _net_len = 0, _net_num = 0, _net_max = -1, _net_from = -1;
struct sockaddr_in _net_peer;
char _net_msg[1024], _net_ka[80];
uint32_t _net_lastsent;
#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif
#endif

/**
 * Reset network connection
 */
void net_free(void)
{
#ifndef __EMSCRIPTEN__
#ifdef __WIN32__
    WSADATA WsaData;
    if(_net_max == -1) WSAStartup(MAKEWORD(2,2), &WsaData);
#endif
    if(_net_sock) close(_net_sock);
    _net_sock = _net_role = _net_num = _net_max = _net_lastsent = 0;
    memset(net_peers, 0, sizeof(net_peers));
    memset(&_net_peer, 0, sizeof(_net_peer));
    _net_peer.sin_family = AF_INET;
    _net_peer.sin_port = htons(PORT);
    _net_peer.sin_addr.s_addr = htonl(INADDR_ANY);
    _net_from = -1;
#endif
}

/**
 * Initialize network connection
 */
int meg4_net_conn(int role, int num)
{
#ifndef __EMSCRIPTEN__
    int n = 1;
#ifdef __WIN32__
    DWORD nb;
#endif
    net_free();
    if(num < 0 || role) num = 1;
    if(num < 1 || num > NUMPEER) num = NUMPEER;
    if((_net_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 1) return 0;
    if(setsockopt(_net_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&n, sizeof(n)) ||
#ifdef __WIN32__
       ioctlsocket(_net_sock, FIONBIO, &nb)
#else
       fcntl(_net_sock, F_SETFL, O_NONBLOCK, 1)
#endif
       ) goto err;
    if(role) _net_role = 1; else
    if(bind(_net_sock, (struct sockaddr*)&_net_peer, sizeof(_net_peer))) goto err;
    _net_max = num;
    return 1;
err:close(_net_sock);
    _net_sock = 0;
    return 0;
#else
    (void)role; (void)num;
    return -1;
#endif
}

/**
 * Start listening for client connections, hosting a LAN game. Does not block, [net_conn] reports when the connection is established.
 * @param num maximum number of players, up to 16
 * @return 1 on success, 0 on error, -1 if not supported. With WebAssembly always returns -1.
 * @see [net_join], [net_conn], [net_close]
 */
int meg4_api_net_host(int num) { return meg4_net_conn(0, num); }

/**
 * Indicate that player wants to join the LAN game. Does not block, [net_conn] reports when the connection is established.
 * @return 1 on success, 0 on error, -1 if not supported. With WebAssembly always returns -1.
 * @see [net_host], [net_conn], [net_close]
 */
int meg4_api_net_join(void) { return meg4_net_conn(1, 1); }

/**
 * Return connection status.
 * @return Retuns 0 if no connection started yet, 1 when pending, and 2 if established.
 * @see [net_host], [net_join]
 */
int meg4_api_net_conn(void)
{
#ifndef __EMSCRIPTEN__
    return !_net_sock ? 0 : 1 + (_net_num > 0);
#else
    return 0;
#endif
}

/**
 * Closes the connection.
 * @see [net_host], [net_join]
 */
void meg4_api_net_close(void)
{
#ifndef __EMSCRIPTEN__
    if(_net_sock) {
        close(_net_sock);
        _net_sock = 0;
    }
#endif
}

/**
 * Receives a message from a peer.
 * @param peer sender peer id address, 0x30000 to 0xBFFFC
 * @param msg a 1024 bytes big buffer's address, 0x30000 to 0xBFFFF
 * @return Length of the message and the message in `msg`, 0 means disconnected, `peer` is -1 if there was no message.
 * @see [net_send]
 */
int meg4_api_net_recv(addr_t peer, addr_t msg)
{
#ifndef __EMSCRIPTEN__
    char *buf;
    int i, n = _net_len < 1024 ? _net_len : 1024;

    if(peer < MEG4_MEM_USER || peer + 4 >= MEG4_MEM_LIMIT - 256 ||
       msg < MEG4_MEM_USER || msg >= MEG4_MEM_LIMIT - 1024 - 256) { MEG4_DEBUGGER(ERR_BADARG); return 0; }
    *((int*)((char*)meg4.data + peer - MEG4_MEM_USER)) = -1;
    buf = (char*)meg4.data + msg - MEG4_MEM_USER;
    if(_net_sock && _net_from != -1 && _net_len > 0) {
        *((int*)((char*)meg4.data + peer - MEG4_MEM_USER)) = _net_from;
        memcpy(buf, _net_msg, n);
        if(n != 1024) buf[n] = 0;
    } else {
        n = 0;
        /* housekeeping for timed out peers */
        for(i = 0; i < _net_num; i++)
            if(net_peers[i].lastseen && net_peers[i].lastseen + 1000 < le32toh(meg4.mmio.tick)) {
                net_peers[i].lastseen = 0;
                *((int*)((char*)meg4.data + peer - MEG4_MEM_USER)) = i;
                break;
            }
        while(_net_num > 0 && !net_peers[_net_num - 1].lastseen) _net_num--;
    }
    _net_from = -1;
    _net_len = 0;
    return n;
#else
    if(peer < MEG4_MEM_USER || peer + 4 >= MEG4_MEM_LIMIT - 256) { MEG4_DEBUGGER(ERR_BADARG); return 0; }
    *((int*)((char*)meg4.data + peer - MEG4_MEM_USER)) = -1;
    (void)msg;
    return 0;
#endif
}

/**
 * Sends a message to a peer or to all connected peers if `peer` is -1.
 * @param peer target peer id, or -1 to send it to all connected peers
 * @param msg message, address of at most 1024 bytes big buffer, 0x30000 to 0xBFFFF
 * @param len length of the message, 1 to 1024
 * @return 1 on success, 0 on error.
 * @see [net_recv]
 */
int meg4_api_net_send(int peer, addr_t msg, int len)
{
#ifndef __EMSCRIPTEN__
    char *buf;
    int i;

    _net_lastsent = le32toh(meg4.mmio.tick);
    if(_net_sock && len > 0) {
        if(len > 1024) len = 1024;
        if(!msg) {
            len = strlen(_net_ka + 1) + 2;
            buf = _net_ka;
        } else {
            if(msg < MEG4_MEM_USER || msg >= MEG4_MEM_LIMIT) { MEG4_DEBUGGER(ERR_BADARG); return 0; }
            if(msg + len > MEG4_MEM_LIMIT) len = MEG4_MEM_LIMIT - msg;
            buf = (char*)meg4.data + msg - MEG4_MEM_USER;
        }
        if(peer < 0) {
            if(_net_role) {
                peer = 0;
                if(!_net_num) {
                    /* handle when client started before the host */
                    _net_peer.sin_addr.s_addr = htonl(INADDR_ANY);
                    return sendto(_net_sock, _net_ka, len, 0, (struct sockaddr*)&_net_peer, sizeof(struct sockaddr_in)) >= 0;
                }
            } else {
                /* broadcast from host */
                for(i = 0; i < _net_num; i++)
                    if(net_peers[i].lastseen > 0)
                        sendto(_net_sock, buf, len, 0, (struct sockaddr*)&net_peers[i].addr, sizeof(struct sockaddr_in));
                return _net_num > 0;
            }
        }
        /* normal single message to one peer */
        if(peer < _net_num && net_peers[peer].lastseen > 0)
            return sendto(_net_sock, buf, len, 0, (struct sockaddr*)&net_peers[peer].addr, sizeof(struct sockaddr_in)) >= 0;
    }
    return 0;
#else
    (void)peer; (void)msg; (void)len;
    return 0;
#endif
}

/**
 * Main networking loop
 */
void net_loop(void)
{
#ifndef __EMSCRIPTEN__
    socklen_t sl = sizeof(_net_peer);
    int i, w, len;

    /* handle network messages */
    if(_net_sock) {
        if(meg4_title[0]) strcpy(_net_ka + 1, meg4_title); else strcpy(_net_ka + 1, "noname");
        len = strlen(_net_ka + 1) + 2;
        /* send keep alive */
        if(_net_lastsent + 500 < le32toh(meg4.mmio.tick))
            meg4_api_net_send(-1, 0, len);
        /* incoming message (just one per frame) */
        memset(_net_msg, 0, sizeof(_net_msg));
        if((w = recvfrom(_net_sock, _net_msg, sizeof(_net_msg), MSG_DONTWAIT, (struct sockaddr*)&_net_peer, &sl)) > 0) {
            _net_len = w;
            /* find peer id */
            for(i = 0; i < _net_num && memcmp(&net_peers[i].addr, &_net_peer, sizeof(_net_peer)); i++);
            /* new peer? */
            if(i == _net_num) {
                /* not our client */
                if(!_net_role && (w != len || memcmp(_net_msg, _net_ka, len))) return;
                /* find a free peer slot */
                for(i = 0; i < _net_num && net_peers[i].lastseen; i++);
                if(i == _net_num) {
                    /* ooops, too many peers */
                    if(_net_num == _net_max || _net_num == NUMPEER) return;
                    _net_num++;
                }
                /* save address */
                memcpy(&net_peers[i].addr, &_net_peer, sizeof(_net_peer));
                /* send a reply to the client so that it can record our address in its own peer list */
                if(!_net_role)
                    sendto(_net_sock, _net_ka, len, 0, (struct sockaddr*)&_net_peer, sizeof(_net_peer));
            }
            net_peers[i].lastseen = le32toh(meg4.mmio.tick);
            _net_from = i;
            /* a zero byte, game name and another zero byte message is hello or keep alive */
            if(w == len && !memcmp(_net_msg, _net_ka, len)) { _net_from = -1; _net_len = 0; }
        }
    }
#endif
}
