================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了使用TIM1 PWM2模式输出三路频率为10Hz占空比分别为25%、50%、75%的PWM波
形。

Function descriptions:
This sample demonstrates how to use TIM1 PWM2 mode to output three 10Hz frequency
PWM waveform with duty cycles of 25%, 50% and 75% separately

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
2. 按下按键
3. 使用逻辑分析仪观察引脚PA5/PB0/PA4的波形

Example execution steps:
1. compile and download the program to MCU and run it;
2. Press the button
3. Observe PA5/PB0/PA4 waveforms with logic analyzer
================================================================================
注意事项：
PA5------>CH1 75%
PB0------>CH2 50%
PA4------>CH3 25%

Notes:
PA5------>CH1 75%
PB0------>CH2 50%
PA4------>CH3 25%
================================================================================