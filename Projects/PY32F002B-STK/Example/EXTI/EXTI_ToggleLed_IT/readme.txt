================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了GPIO外部中断功能，PA0引脚上的每一个下降沿都会产生中断，中断函数中
LED灯会翻转一次。

Function descriptions:
This example demonstrates the GPIO external interrupt function, where each
falling edge on the PA0 pin generates an interrupt, and the LED light in the
interrupt function flips once.
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
2. 每按一次用户按键，观察到LED翻转一次；

Example execution steps:
1.Compile and download the program to MCU and run it;
2.Observe the LED flipping once every time the user presses the button;
================================================================================
注意事项：
1.用户按键对应PA0引脚。
2.如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
1.PA0 pin corresponding to user button.
2.If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required
================================================================================