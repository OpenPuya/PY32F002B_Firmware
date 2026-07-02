================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了主机I2C、从机I2C通过轮询方式进行通讯，当按下从机单板的用户按键，再
按下主机单板的用户按键后，主机I2C向从机I2C发送"LED ON"数据。当主机I2C成功发送数
据，从机I2C成功接收数据时，主机单板和从机单板LED灯分别亮起。

Function descriptions:
This sample demonstrates that I2C(as master and as slave) communicates with 
polling mode.Press the user key of the slave board first and then press the user 
key of the host board,the master I2C will send "LED ON" data to the slave I2C.
When the master I2C successfully sends data and the slave I2C successfully 
receives data, the LED lights on the host board and slave board respectively.
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
1. 注释掉main.h的宏定义“#define SLAVE_BOARD”，编译下载程序到MCU(为主机)，并运行；
   打开main.h的宏定义“#define SLAVE_BOARD”，编译下载程序到MCU(为从机)，并运行；
2. 先复位从机，然后再复位主机
3. 复位完成后，先按下从机单板的用户按键，再按主机单板的用户按键，主从开始通讯
4. 当主机I2C成功发送数据，从机I2C成功接收数据时，主机单板和从机单板LED灯分别亮起；
   否则，LED灯处于闪烁状态。

Example execution steps:
1. Comment out the macro definition of main.h "#define SLAVE_BOARD", compile 
and download the program to MCU(as master), and run it; Release main.h macro 
definition "#define SLAVE_BOARD", compile download program to MCU(as slave), 
and run;
2. Reset the slave and then the master
3. After the reset is completed, first press the user button of the slave board
and then press the user button of the host board, Communication will start
4. When the master I2C successfully sends data and the slave I2C successfully 
receives data, the LED lights on the host board and slave board respectively. 
Otherwise, the LED light is blinking
================================================================================
注意事项：
1.
PB3     ------> I2C_SCL
PB4     ------> I2C_SDA
2.如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
1.
PB3     ------> I2C_SCL
PB4     ------> I2C_SDA
2.If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required
================================================================================