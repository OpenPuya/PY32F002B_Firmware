================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了STK板上的按键、LED灯、打印等功能。

Function descriptions:
This example demonstrates how to use the button and LED on the STK board,and 
printf debug information.
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
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
3. 按下按键，调试助手打印：print test；并且LED灯闪烁

Example execution steps:
1. compile and download the program to MCU and run it;
2. Connect PC and STK board through USB to TTL module and the connection method
is as follows
STK board    USB to TTL moudle
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
3. Press the button,serial assistant will printf:print test and LED will blink.
================================================================================
注意事项：

Notes:

================================================================================