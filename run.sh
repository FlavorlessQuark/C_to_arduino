avr-gcc -c -DF_CPU=36000000UL -mmcu=atmega328p -std=gnu99 main.c -o main.o -O1
avr-gcc -c -DF_CPU=36000000UL -mmcu=atmega328p -std=gnu99 other.c -o other.o -O1
avr-gcc -c -DF_CPU=36000000UL -mmcu=atmega328p -std=gnu99 thing.c -o thing.o -O1

avr-gcc -DF_CPU=36000000UL -mmcu=atmega328p -std=gnu99 main.o other.o thing.o -o main.elf -O1
avr-objcopy -O ihex -j .text -j .data main.elf main.hex
# sudo avrdude -p atmega32u4 -c avr109 -P usb  -B 125kHz -U flash:w:main.hex
sudo avrdude  -p atmega328p -c arduino -b 115200 -P/dev/ttyACM0 -D -U flash:w:main.hex -v
