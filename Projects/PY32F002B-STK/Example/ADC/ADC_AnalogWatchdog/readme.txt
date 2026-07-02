================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的模拟看门狗功能，当开启看门狗的通道的电压值不在设定的上下限中，
会进入看门狗中断。

Function descriptions:
This example demonstrates the analog watchdog function of ADC. When the voltage
value of the channel that opens the watchdog is not within the set upper or 
lower limits,Will enter watchdog interrupt.
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
2. PA7的电压值小于1.65V(供电电压为3.3V),不会进入看门狗中断，LED灯不亮；
3. PA7的电压值大于1.65V(供电电压为3.3V)，进入看门狗中断，LED亮。

Example execution steps:
1. Compile and download the program to MCU and run it;
2. If the voltage value of PA7 is less than 1.65V (with a power supply voltage of
3.3V), it will not enter the watchdog interrupt and the LED light will not light 
up;
3. If the voltage value of PA7 is greater than 1.65V (with a supply voltage of 
3.3V), the watchdog will interrupt and the LED will light up.
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