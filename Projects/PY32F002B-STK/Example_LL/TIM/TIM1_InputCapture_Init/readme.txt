================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了TIM1的输入捕获功能，配置PA0作为输入捕获引脚，PA0每检测到一个下降沿触
发捕获中断在捕获中断回调函数中翻转LED灯。

Function descriptions:
This sample demonstrates the input capture function of TIM1.Configure PA0 as 
input capture pin,Whenever PA0 detects a falling edge it triggers a capture 
interrupt and toggle the LED in the capture interrupt callback function.
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
1. compile and download the program to MCU and run it;
2. LED will toggled once per the button is pressed
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