================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例使能LSI，并通过MCO（PA07）引脚输出。

Function descriptions:
This sample enables the LSI and is output via the MCO (PA07) pin.
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

Notes:
================================================================================