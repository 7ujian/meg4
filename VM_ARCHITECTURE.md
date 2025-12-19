# MEG-4 虚拟机架构分析

## 1. 概述

MEG-4是一个高性能的虚拟游戏控制台，内置多语言编辑器（C/BASIC/Assembly/Lua）并支持跨平台执行。本文档详细分析MEG-4虚拟机的核心架构，包括虚拟CPU、内存布局、执行流程、内存管理和系统调用机制。

## 2. 虚拟CPU架构

### 2.1 指令集定义

MEG-4虚拟机实现了一个16位的虚拟CPU，支持92+条指令。指令集在`src/cpu.h`中定义，主要分为以下几类：

- **控制流指令**：BC_RET（函数返回）、BC_SCALL（系统调用）、BC_CALL（函数调用）、BC_JMP（跳转）、BC_JZ（零跳转）等
- **算术运算指令**：BC_ADDI（整数加法）、BC_SUBI（整数减法）、BC_MULI（整数乘法）、BC_DIVI（整数除法）等
- **浮点运算指令**：BC_ADDF（浮点加法）、BC_SUBF（浮点减法）、BC_MULF（浮点乘法）、BC_DIVF（浮点除法）等
- **内存访问指令**：BC_LOAD（加载）、BC_STORE（存储）、BC_LDIP（从指针加载）等

每条指令使用32位格式存储：8位操作码 + 24位操作数。

### 2.2 CPU执行流程

CPU的执行流程在`src/cpu.c`的`cpu_run()`函数中实现：

```c
void cpu_run(void) {
    int lim = 1048576; // 每帧指令执行限制
    do { cpu_fetch(); } while(meg4.pc && !(meg4.flg & ~1) && meg4.mode == MEG4_MODE_GAME && --lim);
}
```

指令的获取和执行在`cpu_fetch()`函数中实现，采用循环的方式逐条处理指令：

```c
void cpu_fetch(void) {
    uint32_t pc = meg4.pc + 1;
    int i = meg4.code[meg4.pc];
    switch(i & 0xff) { // 提取8位操作码
        case BC_RET: // 函数返回处理
            // ...
        case BC_SCALL: // 系统调用处理
            // ...
        // 其他指令处理
    }
    meg4.pc = pc; // 更新程序计数器
}
```

## 3. 图形处理单元（GPU）

### 3.1 GPU概述

MEG-4的图形处理单元（GPU）负责所有图形渲染任务，在`src/gpu.c`中实现。它支持2D和3D图形渲染，使用高效的算法实现各种图形原语的绘制。

### 3.2 2D图形渲染

GPU使用Bresenham算法实现2D图形原语的绘制：

- **点绘制**：`pset()`函数用于绘制单个像素
- **线绘制**：使用Bresenham算法绘制直线
- **矩形绘制**：`rect()`（空心）和`frect()`（实心）函数
- **圆形绘制**：`circ()`（空心）和`fcirc()`（实心）函数
- **椭圆绘制**：`ellip()`（空心）和`fellip()`（实心）函数
- **贝塞尔曲线**：使用重入式中点法实现二次和三次贝塞尔曲线绘制

### 3.3 3D图形渲染

GPU支持3D图形渲染，实现了以下功能：

- **3D三角形绘制**：支持梯度填充和纹理映射
- **顶点处理**：顶点坐标转换、裁剪和透视变换
- **深度缓冲**：使用z-buffer实现深度测试
- **透视投影**：支持透视变换和相机控制

3D三角形绘制函数`draw_triangle_grd()`实现了梯度填充的三角形渲染：

```c
static void draw_triangle_grd(vert_t* v0, vert_t* v1, vert_t* v2) {
    // 实现3D三角形的梯度填充渲染
}
```

### 3.4 坐标系统和变换

GPU支持多种坐标变换：

```c
static float prj[16],  // 投影矩阵
             cam[16],  // 相机矩阵
             cami[16], // 逆相机矩阵
             camp[3];  // 相机位置
```

这些矩阵用于实现3D场景的视图变换和透视投影。

### 3.5 纹理和精灵处理

GPU支持纹理映射和精灵绘制：

- **精灵绘制**：`spr()`函数用于绘制精灵
- **纹理映射**：支持将纹理应用到3D模型上
- **精灵排序**：实现了精灵的深度排序

### 3.6 GPU性能优化

GPU采用了多种性能优化技术：

- **Bresenham算法**：高效的直线、圆和椭圆绘制算法
- **中点法贝塞尔曲线**：比传统方法更快的曲线绘制
- **深度缓冲优化**：使用16位z-buffer减少内存占用
- **裁剪优化**：高效的多边形裁剪算法

## 4. 内存布局

### 4.1 统一内存映射

MEG-4采用统一的内存映射，在`src/meg4.h`中定义了完整的内存布局：

| 地址范围      | 大小     | 用途                    |
|-------------|---------|------------------------|
| 0x00000-0x1FFFF | 128KB | 通用MMIO（内存映射I/O）   |
| 0x20000-0x2FFFF | 64KB  | 动态映射内存             |
| 0x30000-0xBFFFF | 576KB | 用户可用RAM             |

### 4.2 MMIO区域

MMIO区域包含各种设备寄存器和状态信息，包括：

- **固件和性能**：固件版本、性能计数器、定时器
- **输入设备**：键盘、鼠标、游戏手柄状态
- **GPU控制**：调色板、裁剪区域、屏幕偏移
- **DSP控制**：音频通道状态、音效参数

### 4.3 动态映射内存

动态映射区域根据选择器的值映射不同的资源：

- 波形库（wavesel）
- 音乐轨道库（tracksel）
- 字体库（fontsel）

### 4.4 用户RAM

用户RAM区域（0x30000-0xBFFFF）是程序可自由使用的内存空间，通过宏定义：

```c
#define MEG4_MEM_USER  0x30000      /* 用户RAM起始地址 */
#define MEG4_MEM_LIMIT 0xC0000      /* 内存上限 */
```

## 5. 执行流程

### 5.1 程序初始化

程序启动时，CPU会进行初始化：

```c
meg4_init_len = meg4.code_len = meg4.flg = meg4.tmr = meg4.cp = meg4.pc = meg4.dp = meg4.ac = 0; meg4.af = 0.0f;
memset(meg4.data, 0, sizeof(meg4.data));
meg4.bp = meg4.sp = sizeof(meg4.data) - 256;
```

### 5.2 指令执行循环

CPU在`cpu_run()`函数中执行指令，每条指令的执行包括：

1. 从代码内存获取指令
2. 解析操作码和操作数
3. 执行指令操作
4. 更新程序计数器和寄存器

### 5.3 系统调用处理

当执行BC_SCALL指令时，会调用MEG4_DISPATCH宏分发到对应的API函数：

```c
case BC_SCALL:
    i = val;
    if(i < 0 || i >= MEG4_NUM_API) { MEG4_DEBUGGER(ERR_BADSYS); } else {
        // ...
        switch(i) {
            MEG4_DISPATCH
        }
        // ...
    }
```

## 6. 内存管理机制

### 6.1 内存访问API

MEG-4提供了完整的内存访问API函数，在`src/mem.c`中实现：

- **字节访问**：`meg4_api_inb()`/`meg4_api_outb()`
- **字访问**：`meg4_api_inw()`/`meg4_api_outw()`
- **整数访问**：`meg4_api_ini()`/`meg4_api_outi()`
- **内存操作**：`meg4_api_memcpy()`、`meg4_api_memset()`、`meg4_api_memcmp()`

### 6.2 内存地址转换

内存地址转换由`meg4_memaddr()`函数处理，将虚拟地址映射到实际内存区域：

```c
uint8_t *meg4_memaddr(addr_t src) {
    if(src < sizeof(meg4.mmio)) return (uint8_t*)&meg4.mmio + src;
    if(src < sizeof(meg4.mmio) + 0x4000) return meg4.waveforms[meg4.mmio.wavesel && meg4.mmio.wavesel < 32 ? meg4.mmio.wavesel - 1 : 0] +
        src - sizeof(meg4.mmio); else
    if(src < sizeof(meg4.mmio) + 0x8000) return meg4.tracks[meg4.mmio.tracksel < 8 ? meg4.mmio.tracksel : 0] + src - sizeof(meg4.mmio) - 0x4000; else
    if(src < MEG4_MEM_USER) return meg4.font + (meg4.mmio.fontsel < 16 ? meg4.mmio.fontsel * 32768 : 0) + src - sizeof(meg4.mmio) - 0x8000; else
    if(src < MEG4_MEM_LIMIT) return meg4.data + src - MEG4_MEM_USER;
    return NULL;
}
```

### 6.3 内存保护

MEG-4实现了内存保护机制，防止程序访问非法内存区域：

- 对MMIO区域的关键寄存器进行写保护
- 对用户RAM区域进行边界检查
- 对栈溢出进行检测

### 6.4 栈管理

MEG-4使用用户RAM的高地址部分作为栈空间：

```c
meg4.bp = meg4.sp = sizeof(meg4.data) - 256;
```

栈从高地址向低地址增长，栈顶指针为`meg4.sp`，基址指针为`meg4.bp`。

## 7. 系统调用和API

### 7.1 API结构

MEG-4定义了171个系统API函数，在`src/api.h`中声明。每个API函数的结构如下：

```c
typedef struct {
    char *name;         /* 函数名称 */
    char ret;           /* 返回类型 (0 void, 1 int, 2 addr, 3 string, 4 float) */
    char narg;          /* 参数数量 */
    char varg;          /* 第一个可变参数的索引或0 */
    uint16_t amsk;      /* 地址参数掩码 */
    uint16_t smsk;      /* 字符串参数掩码 */
    uint16_t fmsk;      /* 浮点参数掩码 */
    uint16_t umsk;      /* 无符号参数掩码 */
} meg4_api_t;
```

### 7.2 系统调用分发

系统调用通过MEG4_DISPATCH宏分发到具体的API函数：

```c
#define MEG4_DISPATCH \
    case  0: meg4_api_putc((uint32_t)cpu_topi(0)); break; \
    case  1: meg4_api_printf((str_t)cpu_topi(0)); break; \
    case  2:  val = meg4_api_getc(); break; \
    // ...
```

### 7.3 关键API函数

主要API函数包括：

- **输入输出**：`putc()`、`printf()`、`getc()`、`gets()`
- **图形处理**：`pset()`、`line()`、`rect()`、`spr()`
- **音频处理**：`sfx()`、`music()`
- **内存操作**：`memcpy()`、`memset()`、`memcmp()`
- **数学函数**：`sin()`、`cos()`、`tan()`、`sqrt()`

## 8. 音频处理系统（DSP）

### 8.1 DSP概述

MEG-4的数字信号处理器（DSP）负责音频生成和处理，在`src/dsp.c`中实现。它支持多种波形生成、音频合成和音效处理功能，为游戏提供丰富的音频体验。DSP基于rombankzero的pocketmod.h（MIT许可证），但经过重写以适应MEG-4的需求。

### 8.2 波形生成

DSP支持8种基本波形类型，在`dsp_genwave()`函数中实现：

```c
static wavefunc_t waves[] = { 
    wave_sine,        /* 正弦波 */
    wave_triangle,    /* 三角波 */
    wave_sawtooth,    /* 锯齿波 */
    wave_square,      /* 方波 */
    wave_pulse,       /* 脉冲波 */
    wave_organ,       /* 管风琴波 */
    wave_noise,       /* 噪声波 */
    wave_phaser       /* 移相波 */
};
```

每个波形通过对应的函数生成，例如正弦波和三角波的实现：

```c
static float wave_sine(float t) { return sinf(t * 360 * 0.01745329252); }
static float wave_triangle(float t) { return t < 0.25 ? t / 0.25 : (t < 0.75 ? 1.0 - (t - 0.25) * 4.0 : -1.0 + (t - 0.75) / 0.25); }
```

### 8.3 音符周期表

DSP定义了完整的音符周期表，用于将音符映射到相应的频率。该表包含从八度0到八度7的所有音符：

```c
uint16_t dsp_periods[MEG4_NUM_NOTE] = { 
    0,                                 /* 无音符 */
    /*   C    C#     D    D#     E     F    F#     G    G#     A    A#     B  */
    6848, 6464, 6096, 5760, 5424, 5120, 4832, 4560, 4304, 4064, 3840, 3624, /* 八度0 */
    3424, 3232, 3048, 2880, 2712, 2560, 2416, 2280, 2152, 2032, 1920, 1812, /* 八度1 */
    // ... 其他八度周期值
};
```

### 8.4 音频处理API

DSP提供了一系列音频处理API函数，供程序使用：

- **音效播放**：`sfx()`函数用于播放音效
- **音乐播放**：`music()`函数用于播放音乐
- **波形生成**：通过MMIO寄存器控制波形生成

这些API在系统调用中通过MEG4_DISPATCH宏进行分发。

### 8.5 音频上下文

DSP使用全局音频上下文管理音频状态：

```c
meg4_dsp_t *dsp = &meg4.dram;
```

该上下文包含音频通道状态、波形数据、音乐轨道等信息，用于管理整个音频系统的运行。

## 9. 结论

MEG-4虚拟机采用了高效的设计，具有以下特点：

1. **简洁高效的指令集**：92+条指令，32位指令格式，支持整数和浮点运算
2. **统一的内存映射**：清晰的内存布局，包括MMIO、动态映射内存和用户RAM
3. **安全的内存管理**：内存保护机制，防止非法访问和栈溢出
4. **丰富的API支持**：171个系统API函数，提供完整的硬件访问能力
5. **灵活的执行环境**：支持多语言（C/BASIC/Assembly/Lua），跨平台执行
6. **完整的多媒体支持**：强大的GPU用于图形渲染，DSP用于音频处理

MEG-4虚拟机的设计兼顾了性能和易用性，为游戏开发提供了一个强大而灵活的平台，具有与PICO-8/TIC-80类似的功能，但提供了更丰富的API和更强的性能。