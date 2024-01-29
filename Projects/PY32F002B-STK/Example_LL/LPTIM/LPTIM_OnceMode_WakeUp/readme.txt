================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了LPTIM单次模式事件唤醒STOP模式。

Function descriptions:
This sample demonstrates waking up from stop mode by LPTIM(single mode) event request.
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
3. 200ms后唤醒stop模式；
4. LED保持闪烁状态；

Example execution steps:
1. compile and download the program to MCU and run it;
2. Press the button and enter stop mode
3. Woke up from stop mode after 200ms
4. you can see LED toggle
================================================================================
注意事项：

Notes:
================================================================================