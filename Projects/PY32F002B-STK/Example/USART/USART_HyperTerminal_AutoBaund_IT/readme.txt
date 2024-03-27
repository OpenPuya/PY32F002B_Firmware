================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USART的自动波特率检测功能，调试助手发送一个字符0x7F，MCU反馈字符
串：Auto BaudRate Test。

Function descriptions:
This example demonstrates USART's automatic Baud detection function. The
debugging assistant sends a character 0x7F and MCU feedback string: Auto
BaudRate Test.
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
STK板        USB转TTL模块
PB04(TX) --> RX
PB05(RX) --> TX
GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为9600；
4. 调试助手发送一个字符0x7F，MCU反馈字符串：Auto BaudRate Test；

Example execution steps:
1.Compile and download the program to MCU;
2.Connect the PC to the STK board through the USB to TTL module, and the
connection method between the STK board and the USB to TTL module is as follows:
STK board    USB to TTL module
PB04(TX) ---> RX
PB05(RX) ---> TX
GND      ---> GND
3.On the PC side, open the serial port debugging assistant, connect the
communication COM port correctly, and set the Baud to 9600;
4.Debugging assistant sends a character 0x7F, MCU feedback string: Auto
BaudRate Test;
================================================================================
注意事项：
1. 不注释掉宏AUTO_BAUD_MODE0(main.c中)，上位机发送1字节的波特率检测0x7f，如果
MCU检测成功,返回字符：Auto BaudRate Test
2. 注释掉宏AUTO_BAUD_MODE0(main.c中)，上位机发送1字节的波特率检测0x55，如果MCU
检测成功，返回字符：Auto BaudRate Test

Notes:
1.Do not comment out macro AUTO_BAUD_MODE0 (in main.c), the upper computer
sends 1-byte Baud detection 0x7f, if MCU detection is successful, the returned
character: Auto BaudRate Test
2.Comment out macro AUTO_ BAUD_ MODE0 (in main. c), the upper computer sends
1-byte Baud detection 0x55, if MCU detection is successful, the returned
character: Auto BaudRate Test
================================================================================