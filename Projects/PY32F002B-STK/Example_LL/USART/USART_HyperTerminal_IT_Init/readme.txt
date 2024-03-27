================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了通过USART中断收发数据的功能，复位MCU并重新运行，PC端收到字符串：
UART Test；PC端发送12个字符，MCU会反馈同样的12个字符给PC端。

Function descriptions:
This example demonstrates function of USART to send and receive data using
interrupt mode.Reset the MCU and restart,the PC will receive a string:
UART Test;The PC sends 12 characters,then the MCU returns the same 12 characters
to the PC
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
PB4(TX) --> RX
PB5(RX) --> TX
GND     --> GND
3.PC端打开串口调试助手，正确连接上通讯COM口，
    波特率设置为9600，1位停止位，8位数据位，无奇偶校验。
4. 复位MCU并重新运行，PC端收到字符串：UART Test；
5. PC端发送12个字符，MCU会反馈同样的12个字符给PC端。

Example execution steps:
1. compile and download the program to MCU and run it;
2. Connect PC and STK board through USB to TTL module and the connection method
is as follows
STK board    USB to TTL moudle
PB4(TX) -->  RX
PB5(RX) -->  TX
GND     -->  GND
3. Open the serial port Assistant on the PC, connect the COM port correctly, and
set the baud rate to 9600,1 stop bit, and 8 data bit ,without parity check.
4. Reset the MCU and restart,the PC will receive a string:UART Test;
5. The PC sends 12 characters,then the MCU returns the same 12 characters to the
PC
================================================================================
注意事项：

Notes:

================================================================================