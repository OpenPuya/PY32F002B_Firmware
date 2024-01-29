================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的VREFINT采样功能和VREFBUF的功能，通过VREFINT推算出VREFBUF的电压。

Function descriptions:
This example demonstrates the VREFINT sampling function and VREFBUF function of 
ADC, and calculates the voltage of VREFBUF through VREFINT.
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
1. 编译并下载程序；
2. 串口每隔1s打印一次VrefBuf值。

Example execution steps:
1. Compile and download the program;
2. The serial port prints the VrefBuf value every 1 second
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