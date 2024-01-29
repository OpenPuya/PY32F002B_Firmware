================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了I2C通过中断方式进行通讯，主机先向从机发送15byte数据，然后再接收从机
发送的15byte数据,主机、从机接收数据成功后，主机和从机板上的小灯处于“常亮”状态。

Function descriptions:
This example demonstrates I2C communication through interrupt mode. The master
first sends 15byte data to the slave, and then receives the 15byte data sent
by the slave. After the master and slave successfully receive the data, the small
lights on the master and slave boards are in a "constant on" state.
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
2. 先复位从机，然后再复位主机
3. 复位完成后，按下主机user按键，主从开始通讯
4. 观察主从机的LED灯，当主机和从机LED灯由常暗转为常亮状态，则表明主机、从机收发数
据成功；当主机或从机LED灯处于闪烁状态，则表明主机、从机收发数据失败。

Example execution steps:
1.Compile and download the program to MCU and run it;
2.First reset the slave, then reset the master
3.After resetting, press the master user button to start communication between the
master and slave
4.Observe the LED lights of the master and slave machines. When the LED lights
of the master and slave machines change from normally dark to normally on, it
indicates that the master and slave machines have successfully transmitted and
received data; When the LED light of the master or slave is in a flashing state,
it indicates that the master or slave has failed to transmit and receive data.
================================================================================
注意事项：
PB03     ------> I2C_SCL
PB04    ------> I2C_SDA 
主机程序为I2C_TwoBoard_CommunicationMaster_IT
从机程序为I2C_TwoBoard_CommunicationSlave_IT
如需修改速率，直接修改I2C_SPEEDCLOCK即可

Notes:
PB03     ------> I2C_SCL
PB04    ------> I2C_SDA 
The master program is I2C_TwoBoard_CommunicationMaster_IT
Slave program is I2C_TwoBoard_CommunicationSlave_IT
If you need to modify the rate, directly modify I2C_SPEEDCLOCK is sufficient.
================================================================================