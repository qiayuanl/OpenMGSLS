# OpenMGSLS

## Introduction
There have many 3D printing technologies, many of them use the laser to process materials like SLS(Selective Laser Sintering). Move the laser quickly and accurately became an important thing in the 3D printing. Laser galvanometer which widely used in industrial marking has the many advan- tages such as high-speed and high-precision.So this project tries to develop a system which can use laser galvanometer in 3D printing.
## methord
Laser galvanometer works the same as the voltmeter, the volt determines the angle of mirrors which reflect the laser. We use serial to communicate with the computer and receive the GCode(GCode is most widely used nu- merical control programming language), process the GCode and plan, cal- culate the mirrors angle for each movement, use SPI to send the volt data to the DAC module, output the volt and make galvanometer turn to the corresponding angle.Then this poject develop a desktop SLS 3D printer to test the control system.
## date
The galvanometer control system and 3D printer developed in this project are compatible with most 3D printing slicing software(like simplify3D Cura), the laser point movement speed can reach 2,000mm/s, the print accuracy can reach 0.01mm and it can print many complex structures without sup- ports.
## summary
This project develops a system which can use the GCode to control the galvanometer and build a desktop SLS 3D printer base on this system. Rely on this system the printer can do 3D printing faster and more accurately than most of another desktop 3D printer.
![](https://ws4.sinaimg.cn/large/006tKfTcgy1ftzeiuhoxkj30g809caal.jpg)
## 引言
现存的 3D 打印技术中许多使用激光来加工材料，快速且精确地移动激光非常重要。激光振镜广泛应用于工业打标，具有高速、高精度的优点。本项 目是开发了一套可以在选择性激光烧结 3D 打印机上使用激光振镜的系统。

## 方法
激光振镜的工作原理与电压表相同，电压决定偏转激光的反射镜的角度。 这个项目使用串又与计算机通讯并接收 G代码(G 代码是使用最广泛的数 控编程语言)，对其进行处理规划，计算每个运动对应的电压，使用SPI将数据输出到DAC模块，输出电压，使振镜转到相应的角度。后另外开发了一台选择性激光烧结3D打印机来实验开发的控制系统。

## 数据
这个项目开发的振镜控制系统及3D打印机可以兼容大多数3D打印切片软件如:Simplify3D、Cura。激光点移动速度可以达到 2,000mm/s，打印精度可以达到0.01mm。

## 总结
这个项目开发了一个可以使用 GCode 来控制振镜的系统, 并在此基础上开发了一台桌面级选择性激光烧结3D打印机，可以比其他大多数桌面3D打印机更快，更准确地进行 3D 打印。
![](https://ws3.sinaimg.cn/large/006tKfTcgy1ftzen78qmej30mc0hv11x.jpg)
![](https://ws1.sinaimg.cn/large/006tKfTcgy1ftzemoeso0j30s70mkalx.jpg)