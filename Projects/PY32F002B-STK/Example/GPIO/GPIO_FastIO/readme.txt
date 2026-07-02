================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
本样例主要展示GPIO的FAST IO输出功能,FAST IO速度可以达到单周期翻转速度。

Function descriptions:
This example mainly demonstrates the FAST IO output function of GPIO, which can
achieve a single cycle flip speed.
================================================================================
测试环境：
测试用板：PY32F002B_STK
MDK版本： 5.28
IAR版本： 9.20
GCC 版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F002B_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. GPIO每个时钟周期输出翻转一次，可观测到端口PA1输出波形输出波形频率为12MHz。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.GPIO flips its output once per clock cycle, and it can be observed that the 
output waveform frequency of port PA1 is 12MHz.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required

================================================================================