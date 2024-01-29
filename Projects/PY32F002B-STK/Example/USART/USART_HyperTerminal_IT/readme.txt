================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USART的中断方式发送和接收数据，USART配置为115200，数据位8，停止位1，
校验位None,下载并运行程序后，上位机通过USART会接收到0x1-0xC,然后通过上位机下
发12个数据，例如0x1~0xC,则，MCU会把接收到的数据再次发送到上位机。

Function descriptions:
This example demonstrates the interrupt method of USART to send and receive
data. USART is configured as 115200, with data bit 8, stop bit 1, and check
bit None. After downloading and running the program, the upper computer will
receive 0x1-0xC through USART, and then send 12 data through the upper computer,
such as 0x1-0xC. The MCU will send the received data to the upper computer again.
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
1. 编译并下载程序到MCU；
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PB04(TX) --> RX
PB05(RX) --> TX
GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为115200；
4. MCU会发送0x1~0xc到PC端
5  上位机接收后. 上位机发送12个数据，MCU会反馈同样的12个数据给上位机

Example execution steps:
1.Compile and download the program to MCU;
2.Connect the PC to the STK board through the USB to TTL module, and the
connection method between the STK board and the USB to TTL module is as follows:
STK board    USB to TTL module
PB04(TX) ---> RX
PB05(RX) ---> TX
GND      ---> GND
3.On the PC end, open the serial port debugging assistant, connect the
communication COM port correctly, and set the Baud to 115200;
4.MCU will send 0x1~0xc to the PC end;
5.After receiving by the upper computer The upper computer sends 12 data, and
the MCU will feedback the same 12 data to the upper computer.
================================================================================
注意事项：

Notes:

================================================================================