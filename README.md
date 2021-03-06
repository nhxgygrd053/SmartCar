
#### 介绍
```
2018全国大学生第13th“恩智浦“杯智能汽车竞赛 
双车会车组——【高斯洛必达队】
仅此纪念我们的共同努力及那无数个日日夜夜。
```
# 1.智能车控制中心

| 硬件 | 描述 |
| -- | -- |
|芯片型号| K60N512 |
|CPU| Cortex-M4 |
|FLASH| 512K |
|SRAM| 128K |
|主频| 180MHz |
|单元| FPU |

![competition](/docs/competition.gif)

# 2.目录说明
```
+——SmartCar
|--------+ docs: 【一些方法与调试文档】
|--------+ hardware:【相关电路设计】      
|            └──MOS_Motor_drive 【驱动电路】
|            └──... 【...】
|--------+ software:【相关软件设计】
|            └──2018.08.21(The end) 【程序】
|            └──... 【...】
|--------+ video:【纪念视频】      
|-----README.md

```


# 3.硬件结构
![car](/docs/双车.jpg)
```
+——Smart_Car
|--------+──K60N512 【Center Control】                  
|        |       └──【Normal Peripheral】
|        |       ├── LED [GPIO]   
|        |       ├── KEY [GPIO]     
|        |       ├── OLED [Software SPI]                   
|        |       └──......  
|        |       └── 【Important Peripheral】
|        |       ├── Electromagnetic Induction [ADC] 
|        |       ├── 鹰眼OV7725 [DMA]   
|        |       ├── Bluetooth to Debug [UART]
|        |       ├── Zigbee to Debug [UART]
|        |       └──...... 
|        +──Vehicle Devices
|        ├── Motor [PWM]
|        └──...... 
```



# 4.软件结构
```
+——Smart_Car
|    └──Peripherals Init 【系统内核初始化】                  
|    ├──Flash Read 【读取FLASH参数】
|    ├── Mode 【选择模式】 
|           └── Image Processing 【图像处理】 
|           └── Electromagnetic data processing 【电磁数据处理】 
|           └── Speed control 【速度控制】 
|           ├── Steering control 【方向控制】 
|           ├── Communication control 【通讯逻辑控制】 
|    		└──...... 
```


### 赞赏
![赞赏](/docs/给赞.png "赞赏")


