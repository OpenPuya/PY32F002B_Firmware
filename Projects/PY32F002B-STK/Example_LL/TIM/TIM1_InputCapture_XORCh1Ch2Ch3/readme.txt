================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了TIM1的三通道异或输入捕获功能。配置PA0、PA3、PA4为通道1、通道2、通道3
的输入引脚。每当有一个引脚电平变化时会触发捕获中断，并在中断处理中翻转LED。

Function descriptions:
This sample demonstrates the 3 channels XOR input capture function of TIM1.Configure
PA0 、PA3 、PA4 as CH1 、CH2 、CH3 input pin.Whenever pin of any of the three pin
(PA0\PA3\PA4) detects a polarity change it triggers a capture interrupt and toggle
the LED in the capture interrupt callback function.

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
1. 编译下载程序到MCU，并运行
2. 保持任意两个引脚电平不变，当剩下一引脚电平变化时LED翻转

Example execution steps:
1. compile and download the program to MCU and run it;
2. Keep any two pin polarity unchanged, and the LED toggle when the remaining third
pin polarity changes
================================================================================
注意事项：

Notes:

================================================================================