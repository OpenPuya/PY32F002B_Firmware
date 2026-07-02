================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了LPTIM单次模式事件唤醒STOP模式。

Function descriptions:
This sample demonstrates waking up from stop mode by LPTIM(single mode) event
request.
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
2. 按下按键进入stop模式；
3. 200ms后唤醒stop模式；
4. LED保持闪烁状态；

Example execution steps:
1. compile and download the program to MCU and run it;
2. Press the button and enter stop mode
3. Woke up from stop mode after 200ms
4. you can see LED toggle
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