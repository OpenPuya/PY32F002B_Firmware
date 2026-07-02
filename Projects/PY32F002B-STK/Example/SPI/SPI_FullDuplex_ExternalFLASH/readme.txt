================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了主机SPI通过轮询方式进行通讯，从机使用FLASH外设芯片P25Q64，按下user
按键，主机先向从机写15bytes数据为0x1~0xf，然后再从FLASH中将写入的数据读出，读取成
功后，通过串口打印信息判定通信是否成功。

Function descriptions:
This sample demonstrates the host SPI communication through polling, the slave 
uses FLASH peripheral chip P25Q64, press the user button, the host first to the 
slave to write 15bytes of data for the 0x1~0xf,and then from the FLASH will be
written to read out the data, read successfully, through the serial port to 
print the information to determine whether the communication is successful.
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
1.编译下载程序到MCU，并运行；
2.按下主机user按键，擦除外接FLASH第一个Sector页；
3.写15bytes数据0x1-0xf到刚擦除的Sector页；
4.从FLASH的第一个Sector页读取15bytes数据；
5.比较读出的数据与写入的数据是否相同。观察串口助手，如果主、从机串口助手均接收到
“SPI transfer succeeded”则通信成功；如果主、从机串口助手接收到“SPI Transfer Error”
则通信失败。

Example execution steps:
1. compile and download the program to MCU and run it;
2. Press the host user button to erase the first Sector of the external FLASH;
3. Write 15bytes of data 0x1-0xf to the Sector that was just erased;
4. read 15bytes of data from the first Sector of FLASH;
5.Compares whether the data read is the same as the data written. Compare whether
the read data and the written data are the same. When the LED of the host turns
from dark to light, it indicates that the host is successful in sending and 
receiving data; when the LED of the host is in flashing state, it indicates that
the host fails to send and receive data.
================================================================================
注意事项:
1.主机与板载FLASH(P25Q64)引脚连接(箭头指向为信号传输方向) 
主机MASTER：         FLASH：
SCK(PB2)   ----->    SCK
MISO(PA1)  <-----    MISO
MOSI(PA7)  ----->    MOSI
NSS(PA6)   ----->    NSS
GND       <----->    GND
2.板子上的LED灯引脚为PA1，与SPI_MISO引脚为同一个，不能再用LED表示通讯成功或失败
的状态。
3.通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
@PrintfConfigStart
STK板         USB转TTL模块
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
UART配置为波特率115200，数据位8，停止位1，校验位None
@PrintfConfigEnd
4.开发板焊接了FLASH器件，使用该样例需要焊接R41/R45/R46/R47/R48五个电阻。没有焊接
FLASH器件，使用该样例需外接FLASH。
5.如果需要使用按键:
StartKit版本为V1.0,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V1.0以上版本,则无需操作

Notes:
1.Host and on-board FLASH (P25Q64) pin connection (the arrow points to the 
direction of signal transmission) 
MASTER：             FLASH：
SCK(PB2)   ----->    SCK
MISO(PA1)  <-----    MISO
MOSI(PA7)  ----->    MOSI
NSS(PA6)   ----->    NSS
GND       <----->    GND
2.The LED light pin on the board is PA1, which matches the SPI_ The MISO pins
are the same, and LED cannot be used to indicate the status of successful or
failed communication.
3.Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:
@PrintfConfigStart
STK board USB to TTL module
PB4(TX)  -->  RX
PB5(RX)  -->  TX
GND      -->  GND
UART is configured as BaudRate 115200, data bit 8, stop bit 1, and parity None.
@PrintfConfigEnd
4.Development board welded FLASH device, the use of the sample need to weld
R41/R45/R46/R47/R48 five resistors. No FLASH device is soldered, using the sample
requires external FLASH.
5.If you need to use buttons:
StartKit version is V1.0, please comment out StartKitVersion 2 in StartKit.h and 
open StartKitVersion 1
If the StartKit version is above V1.0, no operation is required

================================================================================