================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例配置系统时钟为LSE，并通过MCO（PA07）引脚输出。

Function descriptions:
This example configures the system clock as LSE and outputs it through the 
MCO (PA07) pin.
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
2. 按下用户按键；
3. 用示波器监测PA07引脚上的频率，观察是否和配置的LSE频率一致。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.Press the user button;
3.Use an oscilloscope to monitor the frequency on the PA07 pin and observe if
it matches the configured LSE frequency.
================================================================================
注意事项：
1. 样例中默认启动的系统时钟是HSI，只有按下用户按键后，系统时钟才会切换到LSE。
2. 注意系统时钟切换为LSE之前，要求把systick中断关闭掉，因为systick中断默认是1ms
一次中断，由于LSE时钟频率过低，systick中断会导致程序无法正常运行。

Notes:
1.The default startup system clock in the example is HSI, and the system clock
will only switch to LSE after pressing the user button.
2.Before switching the system clock to LSE, it is required to turn off the
systick interrupt, as the systick interrupt defaults to a 1ms interrupt.
Due to the low LSE clock frequency, the systick interrupt can cause the program
to not run properly.
================================================================================