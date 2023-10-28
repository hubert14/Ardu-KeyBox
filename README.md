<details>
  <summary>Builded Project (Images)</summary>
  
  # How it looks like:
  ![Outside](https://github.com/hubert14/Ardu-KeyBox/github/outside.jpg)

  # How the buttons looks like inside:
  ![Inside](https://github.com/hubert14/Ardu-KeyBox/github/inside.jpg)
  
</details>


# Install
This project doesn`t have the libraries included in the project. 
Need to install it by yourself.

### Used libraries:
- [Joystick](https://github.com/MHeironimus/ArduinoJoystickLibrary) v2.1.1
- [EncButton](https://github.com/GyverLibs/EncButton) v2.0 (!  need to install exactly this version)

### How to install libraries
- Joystick:
  - Download zip archive with code (from repository)
  - In the Arduino IDE, select `Sketch` > `Include Library` > `Add .ZIP Library`
- EncButton:
  - Download it from the Library Manager inside the Arduino IDE `Tools` > `Manage Libraries` or `CTRL+SHIFT+I`


# Schema
- ### Buttons
`D2`-`D6`

- ### Encoders

##### Left encoder

| Pin  | Pin   |
| ---- | ----  |
| **CLK** | D9   |
| **DT**   | D8   |
| **SW**  | D10 |

##### Right encoder

| Pin  | Pin   |
| ---- | ----  |
| **CLK** | D15   |
| **DT**   | D14   |
| **SW**  | D16 |

- ### Potentiometers
`A0`, `A1`

# Renaming device
**(works only on Arduino IDE 1.x)**

1. Open Arduino IDE folder (i.e. `C:\Program Files (x86)\Arduino`)
2. Open `hardware\arduino\avr` folder
3. Open `boards.txt` (possible require admin rights)
4.  Add this after `Arduino Leonardo`:

	```
	#############################################################

	menu.build_variant=Build Variant
	leonardo.menu.build_variant.leonardo=Leonardo

	leonardo.menu.build_variant.leonardo_switch=VitasyaKeyBox

	leonardo.menu.build_variant.leonardo_switch.name=VitasyaKeyBox
	leonardo.menu.build_variant.leonardo_switch.vid.0=0x0F0D
	leonardo.menu.build_variant.leonardo_switch.pid.0=0x8092
	leonardo.menu.build_variant.leonardo_switch.vid.1=0x0F0D
	leonardo.menu.build_variant.leonardo_switch.pid.1=0x0092

	leonardo.menu.build_variant.leonardo_switch.upload.tool=avrdude
	leonardo.menu.build_variant.leonardo_switch.upload.protocol=avr109
	leonardo.menu.build_variant.leonardo_switch.upload.maximum_size=28672
	leonardo.menu.build_variant.leonardo_switch.upload.maximum_data_size=2560
	leonardo.menu.build_variant.leonardo_switch.upload.speed=57600
	leonardo.menu.build_variant.leonardo_switch.upload.disable_flushing=true
	leonardo.menu.build_variant.leonardo_switch.upload.use_1200bps_touch=true
	leonardo.menu.build_variant.leonardo_switch.upload.wait_for_upload_port=true

	leonardo.menu.build_variant.leonardo_switch.bootloader.tool=avrdude
	leonardo.menu.build_variant.leonardo_switch.bootloader.low_fuses=0xff
	leonardo.menu.build_variant.leonardo_switch.bootloader.high_fuses=0xd8
	leonardo.menu.build_variant.leonardo_switch.bootloader.extended_fuses=0xcb
	leonardo.menu.build_variant.leonardo_switch.bootloader.file=caterina/Caterina-Leonardo.hex
	leonardo.menu.build_variant.leonardo_switch.bootloader.unlock_bits=0x3F
	leonardo.menu.build_variant.leonardo_switch.bootloader.lock_bits=0x2F

	leonardo.menu.build_variant.leonardo_switch.build.mcu=atmega32u4
	leonardo.menu.build_variant.leonardo_switch.build.f_cpu=16000000L
	leonardo.menu.build_variant.leonardo_switch.build.vid=0x0F0D
	leonardo.menu.build_variant.leonardo_switch.build.pid=0x0092
	leonardo.menu.build_variant.leonardo_switch.build.usb_product="VITASYA KEYBOX"
	leonardo.menu.build_variant.leonardo_switch.build.board=AVR_LEONARDO
	leonardo.menu.build_variant.leonardo_switch.build.core=arduino
	leonardo.menu.build_variant.leonardo_switch.build.variant=leonardo
	leonardo.menu.build_variant.leonardo_switch.build.extra_flags={build.usb_flags}

	leonardo.menu.build_variant.leonardo_switch.build.usb_manufacturer="Vitasya Tech"

	#############################################################
	```
5. After that you will see the `Build Variant` after board selector
