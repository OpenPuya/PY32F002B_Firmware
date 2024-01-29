================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述:
此样例是利用中断对串口外设接口（SPI）与外部设备以全双工串行方式进行通信的演示,
此接口设置为主模式，为外部从设备提供通信时钟SCK。主机通过MOSI引脚发送数据,从MISO
引脚接收从机的数据，数据以主机提供的SCK沿同步被移位，完成全双工通信。

Function descriptions:
This example is a demonstration of using interrupts to communicate with the
serial peripheral interface (SPI) and external devices in a full duplex serial
mode. This interface is set as the main mode and provides communication clock
SCK for external slave devices. The master sends data through the MOSI pin and
receives data from the slave through the MISO pin. The data is synchronously
shifted along the SCK provided by the master, completing full duplex communication.
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
NSS(PA6)   ----->    NSS(PA6)
GND        <----->   GND
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
1.Select two PY32F002B blocks_ STK board, one as the master and one as the slave
2.Compile and download master program SPI_TwoBoards_FullDuplexMaster_IT_Init
3.Compile and download slave program SPI_TwoBoards_FullDuplexSlave_IT_Init
4.Connection between the master and slave pins (arrow pointing in the direction
of signal transmission)
MASTER：         SLAVE：
SCK(PB2)   ----->    SCK(PB2)
MISO(PA1)  <-----    MISO(PA1)
MOSI(PA7)  ----->    MOSI(PA7)
NSS(PA6)   ----->    NSS(PA6)
GND        <----->   GND
5.Connect the PC to the STK board through the USB to TTL module, and the
connection method between the STK board and the USB to TTL module is as follows:
STK board        USB to TTL module
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
6.Powering on the master and slave machines
7.Press the slave reset button to run the slave program first, and then press
the master user button to run the master program
8.Observe the serial port assistant, and if both the master and slave serial
port assistants receive "SPI transfer succeeded", the communication is
successful; If the master and slave serial port assistants receive an
"SPI Transfer Error", communication fails.
================================================================================
注意事项:
1.必须先按从机复位按键使从机程序先运行，再按主机用户按键开始运行主机程序，否则会
导致主从机通信失败。
2.NSS引脚只需要在使用NSS硬件方式时连接（本样例使用的是NSS硬件方式）
3.板子上的LED灯引脚为PA1，与SPI_MISO引脚为同一个，不能再用LED表示通讯成功或失败
的状态。

Notes:
1.You must first press the slave reset button to run the slave program first,
and then press the master user button to start running the master program, otherwise
it will cause communication failure between the master and slave machines.
2.The NSS pin only needs to be connected when using NSS hardware mode
(this example uses NSS hardware mode)
3.The LED light pin on the board is PA1, which matches the SPI_ The MISO pins
are the same, and LED cannot be used to indicate the status of successful or
failed communication.
================================================================================