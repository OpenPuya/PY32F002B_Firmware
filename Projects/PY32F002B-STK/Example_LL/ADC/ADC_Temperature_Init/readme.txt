================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了ADC的Tempsensor功能。

Function descriptions:
This sample demonstrates the Tempsensor function of the ADC.
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
2. 串口打印出当前温度值。

Example execution steps:
1. Compile and download the program and run it
2. USART printf current temperaure value
================================================================================
注意事项：
1.请检查芯片的高温校准值，如果是85，选择HighTemp_85，如果是105，选择HighTemp_105

2.通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
@PrintfConfigStart
STK板        USB转TTL模块
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
UART配置为波特率115200，数据位8，停止位1，校验位None
@PrintfConfigEnd
3.如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
1.Please check the high temperature calibration value of the chip. If it is 85, 
select HighTemp_85. If it is 105, select HighTemp_105

2.Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:
@PrintfConfigStart
STK board USB to TTL module
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
UART is configured as BaudRate 115200, data bit 8, stop bit 1, and parity None.
@PrintfConfigEnd
3.If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required
================================================================================