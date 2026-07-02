================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了flash page擦除和page写功能。

Function descriptions:
This example demonstrates the flash page erase and page write functions.
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
2. 按下按键，程序进行page擦除和page写功能；
3. page擦除成功和page写成功，LED亮。

Example execution steps:
1. Compile and download the program to MCU and run it;
2. Press the button to perform page erase and page write functions in the
program;
3. The page is successfully erased and the page is successfully written, and the
LED is on.
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