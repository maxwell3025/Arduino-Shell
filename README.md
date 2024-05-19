# Arduino-Shell
My attempt at getting a basic shell running an an arduino uno

## How To Run
Install the necessary libraries
```bash
sudo apt install gcc-avr binutils-avr avr-libc gdb-avr avrdude
```
Plug your arduino uno into your computer
Make sure that it is connected at `/dev/ttyACM0`
Run
```bash
make run
```