Arduino_opencm3  
=============  

##Notice

This software is experimental and a work in progress.
Under no circumstances should these files be used in relation to any critical system(s).
Use of these files is at your own risk.


##Summary:  
This repository is a testbed for combining the libopencm3 libray with Arduino IDE version 1.6.9. This testbed will support boards based on STM32 micro-controllers. 


- **libopencm3** open-source firmware library (https://github.com/libopencm3/libopencm3)
- Arduino IDE (tested on 1.6.9)
  
##Developers
- Vassilis Serasidis (https://github.com/Serasidis)
- Evangelos Arkalis (https://github.com/evark)


  
##Roadmap

`7 July 2016 ` **[ SPI support  ]**
  
* Added SPI support (SPI, SPI1,...,SPI6)

---
`5 July 2016 ` **[ Timing functions ]**

* `delay.c` Added support to **delay()**, **delayMicroseconds()**, **millis()** and **micros()** functions. 

---
`3 July 2016 ` **[ Serial ports ]**

* `Uart.cpp` Added support to hardware **Serial1**, **Serial2** and **Serial3**.

---
`2 July 2016 ` **[ Removed the libmaple files ]**

* Removed some files from the core that have belonged to the old libmaple core.

---
`30 June 2016 ` **[ Initial release ]** 

* Added core files from official Arduino core
* `wiring_digital.c` Added **pinMode()** , **digitalRead()** , **digitalWrite()** and **togglePin()** functions.
