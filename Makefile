FILENAME=arm
MCU=atmega328p
LINK=libservo.a

SRCS=srcs/IK.cpp\
	 srcs/main.cpp\
	 srcs/MT/MT.cpp\
	 srcs/MT/MT_v2.cpp

PORT=/dev/ttyACM0

OBJS = $(SRCS:.cpp=.o)

all:$(OBJS)
	avr-gcc -DF_CPU=36000000UL -mmcu=$(MCU) -std=gnu++14  $(OBJS) -o main.elf -O1
	avr-objcopy -O ihex -j .text -j .data main.elf main.hex
	sudo avrdude  -p $(MCU) -c arduino -b 115200 -P$(PORT) -D -U flash:w:main.hex -v

servo:
	ar-rc libservo.a /home/jjosephi/.arduino15/libraries/Servo.cpp
%.o: %.cpp
	avr-gcc -mmcu=$(MCU) -std=gnu++14 -I includes/ -I /home/jjosephi/.arduino15/libraries/ -I /home/jjosephi/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino/ -c $< -o $@
