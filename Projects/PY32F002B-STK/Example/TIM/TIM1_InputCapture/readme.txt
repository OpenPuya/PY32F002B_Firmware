================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的输入捕获功能，配置PA0作为输入捕获引脚，PA0每检测到一个下降沿触
发捕获中断,在捕获中断回调函数中翻转LED灯。

Function descriptions:
This example demonstrates the input capture function of TIM1, where PA0 is 
configured as the input capture pin. Every time PA0 detects a falling edge, it 
triggers a capture interrupt and flips the LED light in the capture interrupt 
callback function.
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
1. 编译下载程序到MCU，并运行
2. 每次按下按键,LED灯翻转一次。

Example execution steps:
1. Compile and download the program to MCU and run it
2. Each time the button is pressed, the LED light flips once.
================================================================================
注意事项：

Notes:

================================================================================