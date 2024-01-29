================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了LPTIM连续模式事件唤醒STOP模式。

Function descriptions:
This example demonstrates the LPTIM continuous mode event wake-up STOP mode.
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
2. 按下按键进入stop模式；
3. 200ms后唤醒stop模式并循环进入stop模式再唤醒；
4. LED保持2.5Hz频率闪烁；

Example execution steps:
1. Compile and download the program to MCU and run it;
2. Press the button to enter stop mode;
3. Wake up the stop mode after 200ms and cycle into the stop mode before waking up;
4. LED flashes at a frequency of 2.5Hz;
================================================================================
注意事项：

Notes:
================================================================================