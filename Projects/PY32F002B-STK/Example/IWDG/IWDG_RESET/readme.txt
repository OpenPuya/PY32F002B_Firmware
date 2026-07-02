================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了IWDG看门狗功能，配置看门狗重载计数值，计数1s后复位，然后通过调整每次
喂狗的时间（main函数while循环中代码），可以观察到，如果每次喂狗时间小于1s钟，程序
能一直正常运行（LED灯闪烁），如果喂狗时间超过1s钟，程序会一直复位（LED灯熄灭）。

Function descriptions:
This example demonstrates the IWDG watchdog function, configuring the watchdog 
overload count value, resetting after counting for 1 second, and then adjusting 
each time The feeding time of the dog (code in the main function while loop)
can be observed that if the feeding time is less than 1 second each time, the 
program Can continue to operate normally (LED flashing), if the dog feeding 
time exceeds 1 second, the program will continue to reset (LED light off).
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
2. 可观察到LED能正常亮起；
3. 修改程序（main函数while循环中注释代码），配置喂狗时间为1.1s；
4. 重新编译下载程序到MCU，并运行；
5. 可观察到LED不能正常亮起；

Example execution steps:
1. Compile and download the program to MCU and run it;
2. It can be observed that the LED can light up normally;
3. Modify the program (comment the code in the main function while loop) and 
configure the dog feeding time to be 1.1 seconds;
4. Recompile and download the program to MCU and run it;
5. It can be observed that the LED cannot light up normally;
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