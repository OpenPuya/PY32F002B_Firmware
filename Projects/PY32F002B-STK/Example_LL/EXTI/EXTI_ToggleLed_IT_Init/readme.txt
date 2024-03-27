================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了GPIO外部中断功能，PA0引脚上的每一个下降沿都会产生中断，中断函数中
LED灯会翻转一次。

Function descriptions:
This example demonstrates the GPIO external interrupt function, each falling 
edge on the PA0 pin will generate an interrupt, and the LED will toggle once in 
the interrupt handle function.
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
1. compile and download the program to MCU and run it;
2. Every time the user presses the key, the LED is observed to toggle;
================================================================================
注意事项：
用户按键所对应的引脚为PA0

Notes:
PA0 pin is used as user key
================================================================================