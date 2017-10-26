# Bootloader for STM32F407 (with SD card support)
This project is part of [Wakaama_Ethernet][1] project.

## Compilation
You need:
+ Linux and Windows:
  + [GNU ARM Embedded Toolchain][2] ([tutorial][3])
+ only Windows:
  + [GNU MCU Eclipse Windows Build Tools][4] ([tutorial][5])

For above packages you should add their `bin` directories to [PATH][6] environment variable, for example:
+ Windows:
```
set PATH=%PATH%;C:\Program Files\GNU Tools ARM Embedded\5.4 2016q3\bin
set PATH=%PATH%;C:\Program Files\GNU ARM Eclipse\Build Tools\2.8-201611221915\bin
```
+ Linux:
```
export PATH=$PATH:/opt/gcc-arm-none-eabi-4_8-2014q1/bin
```

Then, you can use `make` command, for example:
```
make all
```
which compiles project and creates `.hex` and `.bin` files in `obj` directory

## Programming Flash memory
You need:
+ Windows:
  + [STM32 ST-LINK Utility][7]

+ Linux:
  + [GNU MCU Eclipse OpenOCD][8] ([tutorial][9])

Again, you should add paths to [PATH][6] environment variable, for example:
+ Windows:
```
set PATH=%PATH%;C:\Program Files\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility
```
+ Linux:
```
export PATH=$PATH:~/opt/gnuarmeclipse/openocd/0.10.0-201510281129-dev/bin
```

Then use applicable `make` command:
```
make program_windows
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

[6]: https://en.wikipedia.org/wiki/PATH_(variable)

[7]: http://www.st.com/en/development-tools/stsw-link004.html

[8]: https://gnu-mcu-eclipse.github.io/openocd/

[9]: https://gnu-mcu-eclipse.github.io/openocd/install/
