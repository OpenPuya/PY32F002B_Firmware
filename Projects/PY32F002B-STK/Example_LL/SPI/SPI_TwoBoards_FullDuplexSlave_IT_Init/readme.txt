================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述:
此样例是利用中断对串口外设接口（SPI）与外部设备以全双工串行方式进行通信 的演示,
此接口设置为主模式，为外部从设备提供通信时钟SCK。主机通过MOSI引脚发送数据,从MISO
引脚接收从机的数据，数据以主机提供的SCK沿同步被移位，完成全双工通信。

Function descriptions:
This sample demonstrates how to use the Serial Peripheral Interface (SPI) to
communicate with an external device in full-duplex serial mode(using interrupts
to process the data).This interface is set as the master mode, providing
communication clock SCK to the external slave device.The host sends data through
the MOSI pin and receives data from the slave through the MISO pin.The data is
shifted synchronously at the SCK edge provided by the host to complete full-duplex
communication.
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
使用步骤:
1.选择两块PY32F002B_STK板，一块作为主机，一块作为从机
2.编译下载主机程序SPI_TwoBoards_FullDuplexMaster_IT_Init
3.编译下载从机程序SPI_TwoBoards_FullDuplexSlave_IT_Init
4.主机与从机引脚连接(箭头指向为信号传输方向)
主机MASTER：         从机SLAVE：
SCK(PB2)   ----->    SCK(PB2)
MISO(PA1)  <-----    MISO(PA1)
MOSI(PA7)  ----->    MOSI(PA7)
GND       <----->    GND
5. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
6.主从机上电
7.按下从机复位按键先运行从机程序，再按下主机用户按键运行主机程序
8.观察串口助手，如果主、从机串口助手均接收到“SPI transfer succeeded”则通信成功；
如果主、从机串口助手接收到“SPI Transfer Error”则通信失败。

Example execution steps:
1. Select two PY32L020_STK boards, one as the host and one as the slave
2. Compile and download the host program SPI_TwoBoards_FullDuplexMaster_IT_Init
3. Compile and download the slave program SPI_TwoBoards_FullDuplexSlave_IT_Init
4. Connect the host and slave pins as follows (the arrows point to indicate the
direction of signal transmission)
MASTER：         SLAVE：
SCK(PB2)   ----->    SCK(PB2)
MISO(PA1)  <-----    MISO(PA1)
MOSI(PA7)  ----->    MOSI(PA7)
GND       <----->    GND
5. connect the PC to the STK board via the USB to TTL module, the connection
between the STK board and the USB to TTL module is as follows:
STK board     USB to TTL module
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
6. Power on the master and slave
7. Press the slave reset button to run the slave program first, then press the
host user button to run the host program
8. Observe the serial assistant, if both master and slave serial assistant receive
"SPI transfer succeeded", the communication is successful;
If the master and slave serial assistant receive "SPI Transfer Error",the
communication fails.
================================================================================
注意事项:
1.必须先按从机复位按键使从机程序先运行，再按主机用户按键开始运行主机程序，否则会
导致主从机通信失败。
2.主机模式可通过程序设置IO控制方式为DMA方式、中断方式和查询方式
3.NSS引脚只需要在使用NSS硬件方式时连接（本样例使用的是NSS软件方式，无需连接NSS引
脚）
4.板子上的LED灯引脚为PA1，与SPI_MISO引脚为同一个，不能再用LED表示通讯成功或失败
的状态。

Notes:
1. You must first press the slave reset button to make the slave program run first,
and then press the host user button to start running the host program, otherwise it
will cause the master-slave communication failure.
2. The IO control mode can be set to DMA mode, interrupt mode and polling mode by
the program in the master mode.
3. NSS pins only need to be connected when using the NSS hardware mode (this sample
uses the NSS software mode, no need to connect the NSS pins)
4. The LED pin on the board is PA1, which is the same as the SPI_MISO pin, and can
no longer use LEDs to indicate the status of communication success or failure.


================================================================================
