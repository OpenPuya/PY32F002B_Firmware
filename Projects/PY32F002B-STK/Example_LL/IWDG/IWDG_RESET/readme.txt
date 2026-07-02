================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了IWDG看门狗功能，配置看门狗重载计数值，计数1s后复位，然后通过调整每次
喂狗的时间（main函数while循环中代码），可以观察到，如果每次喂狗时间小于1s，程序
能一直正常运行（LED灯闪烁），如果喂狗时间超过1s，程序会一直复位（LED灯不亮）。

Function descriptions:
This sample demonstrates the IWDG watchdog function.Configure the watchdog to
count for 1s and then reset.By adjusting the time of each feed dog(code in the
while loop of the main function), it can be observed following situation:
if each dog feeding time is less than 1s, the program can always run normally(
LED toggle).
if the dog feeding time is more than 1s, the program will always reset (LED off)
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
2. 观察到LED灯闪烁；
3. 修改程序（main函数while循环中注释代码），配置喂狗时间为1.1s；
4. 重新编译下载程序到MCU，并运行；
5. 观察到LED灯不亮。

Example execution steps:
1. compile and download the program to MCU and run it;
2. Observed LED toggle
3. modify the program (comment code in the while loop of the main function) to
configure the dog feeding time to 1.1s;
4. recompile and download the program to the MCU and run it;
5. Observe that the LED is off.
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