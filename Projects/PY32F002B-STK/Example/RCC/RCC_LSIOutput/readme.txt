================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例配置系统时钟为LSI，并通过MCO（PA07）引脚输出。

Function descriptions:
This example configures the system clock as LSI and outputs it through the
MCO (PA07) pin.
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
2. 按下用户按键；
3. 用示波器监测PA07引脚上的频率，观察是否和配置的LSI频率一致。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.Press the user button;
3.Use an oscilloscope to monitor the frequency on the PA07 pin and observe
if it matches the configured LSI frequency.
================================================================================
注意事项：
1. 样例中默认启动的系统时钟是HSI，只有按下按键后，系统时钟才会切换到LSI。
2. 注意系统时钟切换为LSI之前，要求把systick中断关闭掉，因为systick中断默认是1ms
一次中断，由于LSI时钟频率过低，systick中断会导致程序无法正常运行。

Notes:
1.The default startup system clock in the example is HSI, and the system clock
will only switch to LSI after pressing the button.
2.Before switching the system clock to LSI, it is required to turn off the
systick interrupt, as the systick interrupt defaults to a 1ms interrupt. Due to
the low clock frequency of the LSI, the systick interrupt can cause the program
to not run properly.
================================================================================