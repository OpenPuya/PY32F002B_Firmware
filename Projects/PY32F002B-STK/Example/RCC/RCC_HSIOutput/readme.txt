================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例配置系统时钟为HSI，并通过MCO（PA07）引脚输出。

Function descriptions:
This example configures the system clock as HSI and outputs it through the 
MCO (PA07) pin.
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
2. 用示波器监测PA07引脚上的频率，观察是否和配置的HSI频率一致。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.Use an oscilloscope to monitor the frequency on the PA07 pin and observe if 
it matches the configured HSI frequency.
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