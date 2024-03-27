================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了通过软件方式将RESET引脚改为普通GPIO。

Function descriptions:
This sample demonstrates the change of the RESET pin to a normal GPIO by 
software.
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
2. 请将MCU断电并重新上电；
3. 按下按键，RST键变为GPIO功能，再次按下按键，LED亮；
4. 注释掉"MODE_PC0 OB_SWD_PB6_GPIO_PC0",打开"MODE_PC0 OB_SWD_PB6_NRST_PC0",
编译重新下载到MCU;
5. 将MCU断电并重新上电；
6. 按下按键，RST键变为RESET功能，再次按下按键，LED亮；

Example execution steps:
1. compile and download the program to the MCU and run it;
2. power off and re-power the MCU;
3. Press the button,the RST key changes to GPIO function and the LED lights up;
4. Comment out "MODE_PC0 OB_SWD_PB6_GPIO_PC0" and turn on "MODE_PC0 OB_SWD_PB6_
NRST_PC0".Compile and re-download to MCU.
5. power off and re-power the MCU;
6. Press the button,the RST key changes to RESET function and the LED lights up;
================================================================================
注意事项：

Notes:

================================================================================