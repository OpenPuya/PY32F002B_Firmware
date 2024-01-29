================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
本例程输出4路PWM，通道1的占空比为20%，通道2为40%，通道3为60%，通道4为80%
本例程周期为24000000/2000/1200=10Hz。

Function descriptions:
This routine outputs 4 PWM channels, with a duty cycle of 20% for channel 1, 
40% for channel 2, 60% for channel 3, and 80% for channel 4
The cycle of this routine is 24000000/2000/1200=10Hz.
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
1. 编译并下载程序；
2. 用逻分或者示波器连接四个通道PA5(TIM1_CH1),PB0(TIM1_CH2),PA4(TIM1_CH3)和
PA7(TIM1_CH4)
3. 查看发现周期为10Hz，占空比分别为20%，40%，60%，80%

Example execution steps:
1. Compile and download the program;
2. Use logic or oscilloscope to connect the four channels PA5 (TIM1_CH1)，
PB0 (TIM1_CH2), PA4 (TIM1_CH3), and PA7 (TIM1_CH4)
3. Upon inspection, it was found that the cycle is 10Hz and the duty cycle is 
20%, 40%, 60%, and 80% respectively

================================================================================
注意事项：
PA5------>CH1 20%
PB0------>CH2 40%
PA4------>CH3 60%
PA7------>CH4 80%

Notes:
PA5------>CH1 20%
PB0------>CH2 40%
PA4------>CH3 60%
PA7------>CH4 80%

================================================================================