================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在stop模式下，使用GPIO事件唤醒。

Function descriptions:
This example demonstrates using GPIO event wake-up in stop mode.
================================================================================
测试环境：
测试用板：PY32F002B_STK
MDK版本： 5.28
IAR版本： 9.20

Test environment:
Test board: PY32F002B_STK
MDK Version: 5.28
IAR Version: 9.20
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. LED灯亮，按下按键，LED灯灭，进入stop模式；
3. 在PA06上产生一个下降沿，程序退出stop模式；
4. LED以200ms的间隔进行翻转。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.The LED light is on, press the button, the LED light goes out, and enters
stop mode;
3.Generate a falling edge on PA06, and the program exits stop mode;
4.The LED flips at 200ms intervals.
================================================================================
注意事项：
1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。
2，注意关闭systick中断，防止该中断唤醒MCU。

Notes:
1.To demonstrate this sample function, it is necessary to disconnect the SWD
cable and power it back on, as by default, the emulator will reset the
DBGMCU_CR.DBG_STOP position.
2.Pay attention to turning off the systick interrupt to prevent it from waking
up the MCU.
================================================================================