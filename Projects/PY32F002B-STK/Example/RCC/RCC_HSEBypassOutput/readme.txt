================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了时钟输出功能，可输出HSE波形。

Function descriptions:
This example demonstrates the clock output function, which can output HSE 
waveforms.
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
2. PA06引脚接入外部24MHz时钟；
3. 按下用户按键；
4. 可由示波器观察到PA07输出HSE波形（24MHz）。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.PA06 pin is connected to an external 24MHz clock;
3.Press the user button;
4.PA07 output HSE waveform (24MHz) can be observed by an oscilloscope.
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