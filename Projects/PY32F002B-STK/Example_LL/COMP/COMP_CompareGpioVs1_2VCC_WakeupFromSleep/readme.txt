================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器唤醒功能，PA04作为比较器负端输入，1/2VCC作为比较器正端输
入，上完电LED灯会常亮，用户点击按钮，LED灯灭，进入sleep模式，通过调整PA04上的输入
电压，产生中断唤醒sleep模式。

Function descriptions:
This example demonstrates the wake-up function of the COMP comparator, with PA04
as the negative input and 1/2VCC as the positive input. After power on, the LED
light will remain on. When the user clicks the button, the LED light will go out
and enter sleep mode. By adjusting the input voltage on PA04, an interrupt
wake-up sleep mode is generated.
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
1. PA04上输入大于1.65V的电压;
2. 编译下载程序到MCU，并运行，发现LED灯常亮；
3. 用户点击按钮，LED灯熄灭，进入sleep模式；
4. PA04上输入小于1.65V的电压，产生中断唤醒；
5. 接下来LED每隔200ms进行翻转，程序正常运行。

Example execution steps:
1. Input voltage greater than 1.65V on PA04;
2. Compile and download the program to MCU, and run it. It is found that the LED
light is constantly on;
3. When the user clicks the button, the LED light goes out and enters sleep mode;
4. When a voltage less than 1.65V is input on PA04, an interrupt wake-up is
generated;
5. Next, the LED flips every 200ms and the program runs normally.
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