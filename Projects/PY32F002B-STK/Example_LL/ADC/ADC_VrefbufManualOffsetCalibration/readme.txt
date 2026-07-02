================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了ADC在Vrefbuf1.5V的情况下手动校准Offset的功能，通过设置PA3为推挽输出
模式，手动修改Offset值，直到采样PA3的DR值在0-1范围内。

Function descriptions:
This example demonstrates the function of manually calibrating the Offset of ADC
in the case of Vrefluf1.5V, by setting PA3 as a push-pull output Mode, manually
modify the Offset value until the DR value of sampled PA3 is within the range of
0-1.
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
2. 串口每隔1s打印一次通道4(PA7)的转换值.

Example execution steps:
1. Compile and download the program and run it
2. USART printf conversation data of the channel 4(PA7) once per 1s
================================================================================
注意事项：
1.该样例的PA3(ADC通道1)为推挽输出，如果实际使用中需要用到该通道，需修改为别的通道
进行校准操作。
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
1.The PA3 (ADC channel 1) of this example is a push-pull output. If this channel
is needed in actual use, it needs to be modified to a different channel
Perform calibration operations.
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