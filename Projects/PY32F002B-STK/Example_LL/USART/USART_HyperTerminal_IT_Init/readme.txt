================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了USART的中断方式发送和接收数据，USART配置为9600，数据位8，停止位1，
校验位None,下载并运行程序后，打印提示信息，然后通过上位机下发12个数据，例如
0x1~0xC,则MCU会把接收到的数据再次发送到上位机，然后打印结束信息。

Function descriptions:
This example demonstrates how to use USART to send an amount of data in interrupt 
mode. USART configuration is 9600 baud rate, data bit 8, stop bit 1, check bit 
None. After download and run the program,Print the prompt message, and then send
12 data through the upper computer, such as 0x1~0xC, the MCU will send the 
received data to the upper computer again, Then print the end message.
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
1. 编译并下载程序到MCU；
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
@PrintfConfigStart
STK板        USB转TTL模块
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
UART配置为波特率9600，数据位8，停止位1，校验位None
@PrintfConfigEnd
3. PC端打开串口调试助手，正确连接上通讯COM口。
4. 按下复位按键，MCU会发送aTxStartMessage数组内的数据到上位机，提示输入12个数据。
5. 上位机发送12个数据到MCU，MCU会反馈同样的12个数据给上位机。同时发送aTxEndMessage
   数组内数据到上位机，提示样例执行结束。
6. 观察开发板上的指示灯，长亮表示通信正常，反之通信异常。

Example execution steps:
1. compile and download the program to MCU and run it;
2. Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:
@PrintfConfigStart
STK board USB to TTL module
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
UART is configured as BaudRate 9600, data bit 8, stop bit 1, and parity None.
@PrintfConfigEnd
3. Open the serial port Assistant on the PC, connect the COM port correctly.
4. When the reset button is pressed, the MCU sends the data in the aTxStartMessage
   array to the host computer, prompting for 12 data inputs.
5. The host computer sends 12 data to the MCU and the MCU feeds back the same 12
   data to the host computer. Also send the data in the aTxEndMessage array to the
   host computer to signal the end of the sample execution.
6. Observe the indicator light on the development board, a long light means that
   the communication is normal, and vice versa, the communication is abnormal.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required

================================================================================