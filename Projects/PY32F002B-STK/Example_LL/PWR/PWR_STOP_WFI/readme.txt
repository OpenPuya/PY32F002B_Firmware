================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了在stop模式下，使用GPIO中断唤醒。

Function descriptions:
This sample demonstrates waking up from stop mode using GPIO interrupt.
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
2. LED灯亮，按下按键，LED灯灭，进入stop模式；
3. 在PA06上产生一个下降沿，程序退出stop模式；
4. LED以200ms的间隔进行翻转。

Example execution steps:
1. compile and download the program to MCU and run it;
2. When the LED is on press the key,the LED goes off and enters stop mode;
3. generate a falling edge on PA06 and the program exits stop mode;
4. the LED are toggled in 200ms intervals.
================================================================================
注意事项：
1.演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。
2.注意关闭systick中断，防止该中断唤醒MCU。
3.如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
1.to demonstrate this sample function, you need to disconnect the swd 
connection wire and re-power,because by default, the emulator will set the 
DBGMCU_CR.DBG_STOP.
2.Be careful to turn off the systick interrupt to avoid this interrupt waking 
up the MCU.
3.If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required
================================================================================