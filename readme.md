# UC1698

UC1698是一个彩屏控制器，但是在国内却广泛用于单色液晶显示，所以控制起来比较复杂。尤其是厂家例程都是并口的，没有spi控制例程，所以整理后上传。

## 硬件接线

SPI接线需注意和并口接线完全不同，需要参考手册。具体接线图如下：

![UC1698U SPI接线](https://raw.githubusercontent.com/smartmx/file-storage/pictures/20230219212312.png)

## 移植使用

### 软件spi

需要在`spi_3wire_io.c`中填写spi相关引脚的拉高拉低代码。

### UC1698控制

复位脚等操作需要修改。

### inline修改

根据不同编译器修改inline的编写方式。
