================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了ADC的模拟看门狗功能，当开启模拟看门狗通道的电压值超过上下限时，会进
入看门狗中断。

Function descriptions:
This sample demonstrates the analog watchdog function of the ADC, which enters
the watchdog interrupt when the voltage value of the channel that opens the
analog watchdog exceeds the upper and lower limit.
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
1. 编译并下载程序
2. 通道4(PA7)的电压值小于1.65V，LED灯不会被点亮
3. 通道4(PA7)的电压值大于1.65V，LED灯被点亮。

Example execution steps:
1. Compile and download the program and run it
2. the voltage value of channel 4 (PA7) is lower than 1.65V, the LED off
3. the voltage value of channel 4 (PA7) is higher than 1.65V, the LED on
================================================================================
注意事项：

Notes:

================================================================================