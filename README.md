# studyAssistant（健康学习助手）


## 作品简介

学生近视与脊柱侧弯等问题中有很大一部分是因为长期错误的学习坐姿导致的。由此，我们制作了一台健康学习助手，它能够实时监测学习者头部位置，一旦发现不良坐姿就会给予提醒，从而有效缓解坐姿不良所造成的问题。相对于目前市面上已经存在的坐姿矫正设备，该系统的优势在于体积小，造价低，便携性强，舒适度较高，适用于各年龄段的学生在日常学习中使用。

![index](https://mmbiz.qpic.cn/mmbiz_jpg/QnbW8Viao1X5sqp7AENa7zS5daAicIp8WOsXNcFmVmM3UocD7h0e0VI3b820tAzY9WkXr000IxOB5koAYuuN6UbQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

## 研究背景

人们在认识到不良坐姿对学生健康所产生的重要影响后，开发了不同类型的坐姿矫正器。在市面上支架式、穿戴式与感应式电子坐姿矫正器比较常见，然而这三类坐姿矫正器都存在一定的缺陷。支架式坐姿矫正器中，书写板组合局限性较大；坐姿矫正杆部分体积较大，不易拆卸、携带；穿戴式坐姿矫正器主要分为坐姿矫正背带和坐姿矫正衣，背带宽松程度受衣服影响，矫正衣较为昂贵；感应式矫正器主要包括正姿笔、耳挂式矫正器等，几种方式的灵敏度、舒适度的缺陷容易引起用户的反感，也会导致书写困难。

![image-20200913193427434](https://mmbiz.qpic.cn/mmbiz_png/QnbW8Viao1X5sqp7AENa7zS5daAicIp8WO1lC3gtnMPRQ5PoiazRQ1ia4g4niaeHWytF1Ka6PXm4hyRp727TNxkWC9w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

通过分析以上几种方案中所存在缺点，我们所设计的健康学习助手通过超声波与舵机云台的组合可以巧妙地避免大部分问题，局限性小，体积小，造价低，便携，舒适度较高。

## 研究计划

### 功能设计

作品预期实现的主要功能包括：

1. 坐姿检测：系统能够检测低头和歪头等不良坐姿；
2. 报警提醒：根据应用场景设计了显示屏提醒、指示灯提醒和语音提醒功能；
3. 辅助功能：自动恢复、按键重置、音量调节等功能；

### 技术方案

作品总体设计上可分为软件编程、硬件电路、作品外观三个部分的设计。

1. 软件部分：使用Arduino IDE作为主要编程工具，调用u8glib库实现OLED屏幕的显示驱动，自行编写语音模块的头文件，采用PWM信号控制的方法控制舵机，使用NewPing文件控制超声波传感器。
2. 电路部分：计划使用体积小巧的 Arduino NANO作为主控制器，控制超声波和舵机云台进行头部定位和姿态监测，选用质量轻，造价低的9g舵机，精确度较高的US-015超声波传感器，语音部分采用TTS语音合成模块。
3. 外观设计：使用Tinkercad进行三维建模，通过3D打印机打印形成作品的外壳。

![image-20200913195442660](https://mmbiz.qpic.cn/mmbiz_png/QnbW8Viao1X5sqp7AENa7zS5daAicIp8WOEDcuYqznADlT6wEzOLhChYAUaibmhTfqRnM920xnVUJAlg2okPFTOvQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

## 作品制作

### 功能流程图

系统工作主要包括开机自检、云台定位、循环监测、以及错误坐姿报警等流程。

![流程图](https://mmbiz.qpic.cn/mmbiz_png/QnbW8Viao1X5sqp7AENa7zS5daAicIp8WOibNSibqGBJgFke5I9cD2Ya6bN8UNyJt7uM4BRtjE0UbInInicScROb1cw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 绘制电路图

我们根据系统的功能设计选定相关的硬件型号，学习研究硬件电路的连线方法，绘制电路连接图，根据连接图再具体完成电路的连接工作。健康学习助手采用Arduino NANO作为主控制器，设备成本较低，运算性能良好，体积小巧；监测部分则由超声波模块与舵机云台构成；报警部分由OLED显示屏、LED灯、TTS语音合成模块构成。内部电路采用洞洞板焊接的方式，增强了稳定性、易用性。使用Fritzing软件绘制电路连接图如下：

![Study Assistant_bb](https://mmbiz.qpic.cn/mmbiz_png/QnbW8Viao1X5sqp7AENa7zS5daAicIp8WO52EMickrFXQfuibHj8NkxP6OibuTLhzu19eicrdjHktDLNt8D5NLLrfEJg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)


### 程序编写

程序主要采用Arduino IDE进行编写，调用U8glib库控制OLED显示屏，计划使用NewPing库控制超声波模块，由于在程序编写时调用了Servo库，其中所用的 timer0 定时器与串口通信冲突，故舵机云台采用PWM控制的方式，TTS语音模块利用串口通信，自行封装了相关头文件。


### 三维设计

三维设计采用Tinkercad在线3D建模，外壳的设计更加人性化，几个面均加有圆角设计，为方便更换电池，顶盖还设计了方便掀开的凸起。

![3D设计过程](https://mmbiz.qpic.cn/mmbiz_png/QnbW8Viao1X5sqp7AENa7zS5daAicIp8WOiapS4lDpVOXpxQPGkyic3kDVa3DMLZJTRJGe7arwgOoSteOXThtPtywA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 组合调试

将搭建好的电路放入预先打印的模型中，最后进行组合调试。

## 使用方法

在使用健康学习助手时，只需将设备放置在前方桌面上，打开开关，调整坐姿，学习助手会自动从上下、左右两个方面锁定头部位置；头部定位成功后进入巡航监测模式，实时对低头、歪头等不良坐姿进行检测识别；当发现不良坐姿时进入报警模式，屏幕显示具体的提醒内容，LED灯开始闪烁，并由语音合成模块进行语音提示；当处于自习室、图书馆等场景时，使用者还可通过音量旋钮调整音量；当恢复标准坐姿时，提示报警自动取消。

![image-20200913201312412](https://mmbiz.qpic.cn/mmbiz_png/QnbW8Viao1X5sqp7AENa7zS5daAicIp8WOtaicgqdvr55ice85gibK60YvEABr8Yia6wdHKzhqgEwyrMAYDXFuKo3ib7A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

## 改进方向

在制作该项目的过程中，我们还产生了新的改进计划，包括：

1. 增强系统的稳定性，自主设计PCB电路板，改善布线方式；
2. 改用摄像头进行视觉识别，基于AI人脸检测或姿态检测来进行坐姿监测；
3. 采集用户数据并进行科学分析，使产品个性化，提出改善用户学习状态的更优方案。
