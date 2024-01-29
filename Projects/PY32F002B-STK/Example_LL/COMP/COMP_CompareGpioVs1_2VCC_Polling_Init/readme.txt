================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器轮询功能，PA04作为比较器负端输入，1/2VCCA 作为正端输入，通
过调整PA04上的输入电压，当检测到比较器输出状态为高时，LED灯亮，比较器输出状态为
低时，LED灯灭。

Function descriptions:
This sample demonstrates the COMP polling function, with PA04 as the negative
comparator input and 1/2VCCA as the positive input. Adjust the input voltage
on PA04 , the LED will be on when the comparator output state is detected as high
and be off when the comparator output state is low.
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
1. 编译下载程序到MCU，并运行；
2. 配置PA04输入大于1.65V电压，LED灯灭；
3. 配置PA04输入小于1.65V电压，LED灯亮。


Example execution steps:
1. Compile and download the program and run it
2. when the PA04 input is larger than 1.65V,LED off
3. When PA04 input is less than 1.65V,LED on
================================================================================
注意事项：

Notes:
================================================================================