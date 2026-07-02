================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了通过PA6引脚唤醒MCU的功能。下载程序并运行后，LED灯处于常亮状态；按下
用户按键后，LED灯处于常暗状态，且MCU进入STOP模式；拉低PA6引脚后，MCU唤醒，LED灯
处于闪烁状态。

Function descriptions:
This sample demonstrates the function to wake up the MCU via the PA6 pin. After
downloading the program and running, the LED remains on; After pressing the user
button, the LED remains off, and the MCU enters the STOP mode; After pulling 
down the PA6 pin, the MCU wakes up and the LED light is toggling.
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
2. 小灯处于常亮状态，按下用户按键，LED灯处于常暗状态，且MCU进入STOP模式
3. 拉低PA6引脚后，MCU唤醒，LED灯处于闪烁状态

Example execution steps:
1. compile and download the program to MCU and run it;
2. press the user button when the led is on, the LED will be off and the MCU 
will enter the STOP mode
3. After pulling down the PA6 pin, the MCU will be woke up and the LED will 
be toggled
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