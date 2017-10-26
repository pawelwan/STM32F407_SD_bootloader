# Bootloader for STM32F407 (with SD card support)
This project is part of [Wakaama_Ethernet][1] project.

## Requirements
Project could be compiled both on Windows and Linux.

Firstly, you need to install:
+ for both Windows and Linux:
  + [GNU ARM Embedded Toolchain][2] ([tutorial][3])
+ only for Windows:
  + [GNU MCU Eclipse Windows Build Tools][4] ([tutorial][5])
  + [STM32 ST-LINK Utility][6]
+ only for Linux:
  + [GNU MCU Eclipse OpenOCD][7] ([tutorial][8])

Secondly, you should update the [PATH][9] environment variable.
To accomplish that (only for current command line instance), enter
(with paths adequate to your installation directories):
+ Windows:
```
set PATH=%PATH%;C:\Program Files\GNU Tools ARM Embedded\5.4 2016q3\bin
set PATH=%PATH%;C:\Program Files\GNU ARM Eclipse\Build Tools\2.8-201611221915\bin
set PATH=%PATH%;C:\Program Files\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility
```
+ Linux:
```
export PATH=$PATH:/opt/gcc-arm-none-eabi-6-2017-q2-update/bin
export PATH=$PATH:/opt/gnu-mcu-eclipse/openocd/0.10.0-4-20171004-0812-dev/bin
```

You can also use predefined scripts (but first you need to update them with adequate paths):
+ Windows:
```
set_path.bat
```
+ Linux:
```
source set_path.sh
```

## Compilation
To compile project and create `.hex` and `.bin` files in `obj` directory, enter:
```
make all
```

## Programming Flash memory
+ Windows:
```
make program_windows
```
+ Linux:
```
make program_linux
```

<!---
SD card should contain:
* basic.bin file with basic version of firmware
--->

[1]: https://github.com/WojciechPolnik/Wakaama_Ethernet

[2]: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm

[3]: https://gnu-mcu-eclipse.github.io/toolchain/arm/install/

[4]: https://gnu-mcu-eclipse.github.io/windows-build-tools/

[5]: https://gnu-mcu-eclipse.github.io/windows-build-tools/install/

[6]: http://www.st.com/en/development-tools/stsw-link004.html

[7]: https://gnu-mcu-eclipse.github.io/openocd/

[8]: https://gnu-mcu-eclipse.github.io/openocd/install/

[9]: https://en.wikipedia.org/wiki/PATH_(variable)
