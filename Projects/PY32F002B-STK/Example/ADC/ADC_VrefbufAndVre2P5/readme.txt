================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的通道4采样功能和VREFBUF的功能，通过VREFBUF推算出通道4的输入电压。

Function descriptions:
This sample demonstrates the channel 4 sampling function of the ADC and the 
function of VREFBUF, from which the input voltage of channel 4 is deduced.
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
1. 编译并下载程序；
2. 串口每隔1s打印一次通道4的输入电压值。

Example execution steps:
1. Compile and download the program;
2. The serial port prints the input voltage value for channel 4 every 1s.
================================================================================
注意事项：
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND

Notes:
Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:

STK board USB to TTL module
PB4 (TX) -->RX
PB5 (RX) -->TX
GND -->GND
================================================================================