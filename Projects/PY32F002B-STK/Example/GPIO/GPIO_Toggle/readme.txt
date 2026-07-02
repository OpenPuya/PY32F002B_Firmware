================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了GPIO输出模式，配置LED引脚为数字输出模式，并且每隔250ms翻转一次LED引
脚电平，运行程序，可以看到LED灯以2Hz的频率闪烁。

Function descriptions:
This example demonstrates the GPIO output mode, configuring the LED pin to be in
 digital output mode, and flipping the LED pin level every 250ms. Running the 
program, you can see that the LED light flashes at a frequency of 2Hz.
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
2. 可观察到STK板上的LED以2Hz的频率闪烁。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.It can be observed that the LED on the STK board flashes at a frequency of 2Hz.
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