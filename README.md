# pb-5300-keyboard-controller
A controller to connect a keyboard for the Apple Powerbook 5300 to a USB based computer.

The purpose of this project is to enable the reuse of the keyboard in a Powerbook 5300 laptop without the logic board. Specifically, it provides a controller with a USB HID interface that enables connecting it to modern computers.

## Hardware
The project hardware consists of a PCB that is hosting an Arduino Leonardo capable microcontroller board. The board used in the development of this project is the Sparkfun Pro Micro. That board was chosen because it was readily at hand in the component cupboard, but in hindsight it might have been better to go with a microcontroller with a higher number of I/O pins. That would have reduced the need for external chips like the demuxers and the shift registers. An idea for a future improvement would be to reimplement it using a larger PIC microcontroller.

## Firmware
The firmware implements a basic keyboard matrix scan and uses a library for USB HID functionality. The Atmel32u4 microcontroller used in Leonardo class boards has built in USB functionality. The library just makes it easier to deal with USB HID, without getting into the details of USB HID protocols. The choice fell on [NicoHood's HID libary](https://github.com/NicoHood/HID). It is very similar to the built in Keyboard of Arduino development tools, and it was chosen over the Arduino library for the simple reason that it provides handling of a keyboard's LED status without diving deep. An added bonus of the chosen library is that it supports the HID boot protocol, which may help with some BIOS implementations, but it is not the reason why it was chosen.

## Credits

During this project I relied heavily on the [excellent post about keyboard design by Michal Trybus](http://blog.komar.be/how-to-make-a-keyboard-the-matrix/) and I stole the idea of using shift registers for working around limited I/O pin numbers from [mehmedbasic.dk](https://mehmedbasic.dk/post/74hc595-keyboard/).
