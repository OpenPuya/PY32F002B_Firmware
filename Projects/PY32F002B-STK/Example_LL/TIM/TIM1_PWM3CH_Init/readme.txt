================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了使用TIM1 PWM2模式输出三路频率为10Hz占空比分别为25%、50%、75%的PWM波
形。

Function descriptions:
This sample demonstrates how to use TIM1 PWM2 mode to output three 10Hz 
frequency PWM waveform with duty cycles of 25%, 50% and 75% separately

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
2. 按下按键
3. 使用逻辑分析仪观察引脚PA5/PB0/PA4的波形

Example execution steps:
1. compile and download the program to MCU and run it;
2. Press the button
3. Observe PA5/PB0/PA4 waveforms with logic analyzer
================================================================================
注意事项：
1.
PA5------>CH1 75%
PB0------>CH2 50%
PA4------>CH3 25%
2.如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
1.
PA5------>CH1 75%
PB0------>CH2 50%
PA4------>CH3 25%
2.If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required
================================================================================