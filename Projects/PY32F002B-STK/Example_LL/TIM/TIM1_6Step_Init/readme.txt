================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了使用TIM1产生“六步PWM信号”，每间隔1ms在SysTick中断中触发换向，实现无刷
电机的换向。

Function descriptions:
This sample demonstrates how TIM1 can be used to generate a "six-step PWM signal."
The commutation is triggered in the SysTick interrupt every 1ms to realize the
commutation of the brushless motor.

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
2. 使用逻辑分析仪观察引脚PA5/PB2/PA3/PB1/PA4/PB0的波形

Example execution steps:
1. compile and download the program to MCU and run it;
2. Observe PA5/PB2/PA3/PB1/PA4/PB0 waveforms with logic analyzer
================================================================================
注意事项：
换向步骤和波形如下所示：
                第一步  第二步  第三步  第四步  第五步  第六步
CH1               1       0       0      0        0       1
CH1N              0       0       1      1        0       0
CH2               0       0       0      1        1       0
CH2N              1       1       0      0        0       0
CH3               0       1       1      0        0       0
CH3N              0       0       0      0        1       1

CH1  (PA05)   |||||||_________________________________|||||||
CH1N (PB02)   _______________||||||||||||||||________________

CH2  (PA03)   _______________________||||||||||||||||________
CH2N (PB01)   |||||||||||||||________________________________

CH3  (PA04)   _______||||||||||||||||________________________
CH3N (PB00)   ________________________________|||||||||||||||

Notes:
The commutation steps and waveforms are shown below:
                step 1  step 2  step 3 step 4   step 5  step 6
CH1               1       0       0      0        0       1
CH1N              0       0       1      1        0       0
CH2               0       0       0      1        1       0
CH2N              1       1       0      0        0       0
CH3               0       1       1      0        0       0
CH3N              0       0       0      0        1       1

CH1  (PA05)   |||||||_________________________________|||||||
CH1N (PB02)   _______________||||||||||||||||________________

CH2  (PA03)   _______________________||||||||||||||||________
CH2N (PB01)   |||||||||||||||________________________________

CH3  (PA04)   _______||||||||||||||||________________________
CH3N (PB00)   ________________________________|||||||||||||||
================================================================================