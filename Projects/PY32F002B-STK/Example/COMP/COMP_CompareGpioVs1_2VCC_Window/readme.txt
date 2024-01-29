================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了COMP比较器的window功能，比较器1的Plus端用比较器2的IO2(1/2VCCA)作为输
入，PB0作为比较器负端输入，当PB0的电压值大于1.65V时,LED灯灭，小于1.65V时,LED灯亮。


Function descriptions:
This example demonstrates the window function of the COMP comparator. The Plus
end of comparator 1 uses the IO2 (1/2VCCA) of comparator 2 as the input, and PB0
as the negative end input. When the voltage value of PB0 is greater than 1.65V,
the LED light turns off, and when it is less than 1.65V, the LED light turns on

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
2. 配置PB0输入大于1.65V电压，LED灯灭；
3. 配置PB0输入小于1.65V电压，LED灯亮。

Example execution steps:
1. Compile and download the program to MCU and run it;
2. Configure PB0 input voltage greater than 1.65V and LED light off;
3. If the input voltage of PB0 is less than 1.65V, the LED light will be on.
================================================================================
注意事项：

Notes:
================================================================================