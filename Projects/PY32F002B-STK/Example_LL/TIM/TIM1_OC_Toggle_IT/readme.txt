================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了TIM1的输出比较模式。将捕获/比较通道1（CH1）的输出映射到PA5，开启捕获
/比较通道1（CH1）并设置为比较输出翻转模式，并使能比较中断，在中断中翻转LED。

Function descriptions:
This sample demonstrates the output compare function of TIM1.CH1 map to PA5,and
set CH1 as output compare channel and in toggle mode.Enable compare interrupt 
and toggle LED in interrupt callback.

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
2. 使用示波器观察PA5，频率为0.5Hz
3. LED的翻转频率为0.5Hz

Example execution steps:
1. compile and download the program to MCU and run it;
2. Observe PA5 with an oscilloscope ,toggle frequency is 0.5 Hz
3. LED is toggled at 0.5Hz frequency
================================================================================
注意事项：

Notes:

================================================================================