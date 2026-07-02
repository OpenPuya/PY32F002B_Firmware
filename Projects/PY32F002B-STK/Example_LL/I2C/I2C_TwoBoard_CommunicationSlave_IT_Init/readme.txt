================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了I2C通过中断方式进行通讯，主机先向从机发送15byte数据，然后再接收从机
发送的15byte数据,主机、从机接收数据成功后，主机和从机板上的小灯处于“常亮”状态。

Function descriptions:
This sample demonstrates that I2C communicates with interrupt mode, the host 
first sends 15byte data to the slave, and then receives 15byte data from the 
slave.After the host and slave successfully receive data, the LEDs on the host 
and slave board are in the state of "steady on".
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
2. 先复位从机，然后再复位主机
3. 复位完成后，按下主机user按键，主从开始通讯
4. 观察主从机的LED灯，当主机和从机LED灯由常暗转为常亮状态，则表明主机、从机收发数
据成功；当主机或从机LED灯处于闪烁状态，则表明主机、从机收发数据失败。

Example execution steps:
1. Compile and download the program and run it
2. Reset the slave and then the host
3. After the reset is complete, press the user button of the host to start
communication between the master and slave
4. Observe the LED of the master and slave. When the LED lights of the master 
and slave turn from off to steady on, it indicates that the master and slave 
receive and send data successfully; When the LED of the host or slave is 
blinking,it indicates that the host or slave fails to receive and or data.
================================================================================
注意事项：
1.
PB3     ------> I2C_SCL
PB4     ------> I2C_SDA
主机程序为I2C_TwoBoard_CommunicationMaster_IT_Init
从机程序为I2C_TwoBoard_CommunicationSlave_IT_Init
如需修改速率，直接修改I2C_SPEEDCLOCK即可
2.如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
1.
PB3     ------> I2C_SCL
PB4     ------> I2C_SDA
Master program name:I2C_TwoBoard_CommunicationMaster_IT_Init
Slave program name:I2C_TwoBoard_CommunicationSlave_IT_Init
I2C_SPEEDCLOCK can be modified to change the communication frequency
2If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required
================================================================================