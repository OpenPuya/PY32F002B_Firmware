================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了CRC校验功能，通过对一个数组里的数据进行校验，得到的校验值与理论校验
值进行比较，相等则LED灯亮，否则LED灯熄灭。

Function descriptions:
This example demonstrates the CRC verification function. By verifying the data 
in an array, the obtained verification value is compared with the theoretical 
verification value. If it is equal, the LED light will be on, otherwise the LED
light will be off.
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
2. 观察LED灯是否亮起，如果灯亮表示运行成功，否则运行失败。

Example execution steps:
1. Compile and download the program to MCU and run it;
2. Observe whether the LED light is on. If it is on, it indicates successful 
operation, otherwise it fails.
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