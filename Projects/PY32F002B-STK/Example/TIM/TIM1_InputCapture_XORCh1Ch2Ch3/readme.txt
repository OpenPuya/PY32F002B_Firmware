================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的三通道异或输入捕获功能。配置PA0、PA3、PA4为通道1、通道2、通道3
的输入引脚。每当有一个引脚电平变化时会触发捕获中断，并在中断处理中翻转LED。

Function descriptions:
This example demonstrates the three channel XOR input capture function of TIM1.
Configure PA0, PA3, and PA4 as input pins for channels 1, 2, and 3. Whenever a 
pin level changes, a capture interrupt is triggered and the LED is flipped during
interrupt processing.
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
1. 编译下载程序到MCU，并运行
2. 保持任意两个引脚电平不变，当剩下一引脚电平变化时LED翻转

Example execution steps:
1. Compile and download the program to MCU and run it
2. Keep the level of any two pins unchanged, and flip the LED when the level of
the remaining pin changes
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