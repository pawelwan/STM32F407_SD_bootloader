# Optimization level, can be [0, 1, 2, 3, s].
#     0 = turn off optimization. s = optimize for size.
#

OPT = 2

# Object files directory
# Warning: this will be removed by make clean!
#
OBJDIR = obj

# Target file name (without extension)
TARGET = $(OBJDIR)/STM32F407_bootloader

BOARD = USE_STM32F4_DISCOVERY
CHIP = STM32F4x7

DRV_SRC = drivers/src/crc32.c
DRV_SRC += drivers/src/dbgu.c
DRV_SRC += drivers/src/firmware.c
DRV_SRC += drivers/src/flash.c
DRV_SRC += drivers/src/led.c
DRV_SRC += drivers/src/term_io.c

FAT_SRC = fatfs/ff_io.c
FAT_SRC += fatfs/ff.c

LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/misc.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
LIB_SRC += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c

SD_SRC = sd/sd.c
SD_SRC += sd/stm32f4_sdio_sd.c

SRC_SRC += src/startup_stm32f4xx.s
SRC_SRC += src/system_stm32f4xx.c
SRC_SRC += src/vectors.c

# Define all C source files (dependencies are generated automatically)
#
SOURCES = main.c
SOURCES += $(DRV_SRC)
SOURCES += $(FAT_SRC)
SOURCES += $(LIB_SRC)
SOURCES += $(SD_SRC)
SOURCES += $(SRC_SRC)

OBJECTS  = $(addprefix $(OBJDIR)/,$(addsuffix .o,$(basename $(SOURCES))))

# Place -D, -U or -I options here for C and C++ sources
CPPFLAGS += -D $(BOARD)
CPPFLAGS += -D $(CHIP)

CPPFLAGS += -I .
CPPFLAGS += -I drivers/inc
CPPFLAGS += -I fatfs
CPPFLAGS += -I libs/CMSIS/Include
CPPFLAGS += -I libs/Device/STM32F4xx/Include
CPPFLAGS += -I libs/STM32F4xx_StdPeriph_Driver/inc
CPPFLAGS += -I sd
CPPFLAGS += -I src

#---------------- Compiler Options C ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS  = -O$(OPT)
CFLAGS += -std=gnu99
CFLAGS += -gdwarf-2
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wstrict-prototypes
CFLAGS += -Winline
CFLAGS += -Wunreachable-code
CFLAGS += -Wundef
CFLAGS += -Wa,-adhlns=$(OBJDIR)/$(*F).lst

# Optimize use of the single-precision FPU
#
CFLAGS += -fsingle-precision-constant

# This will not work without recompiling libs
#
# CFLAGS += -fshort-double

#---------------- Compiler Options C++ ----------------
#
CXXFLAGS  = $(CFLAGS)

#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler
#  -adhlns:   create listing
#
ASFLAGS = -Wa,-adhlns=$(OBJDIR)/$(*F).lst


#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS += -lm
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Tsrc/stm32_flash.ld

#============================================================================


# Define programs and commands
TOOLCHAIN = arm-none-eabi
ARM_GCC   = $(TOOLCHAIN)-gcc
OBJCOPY   = $(TOOLCHAIN)-objcopy
OBJDUMP   = $(TOOLCHAIN)-objdump
SIZE      = $(TOOLCHAIN)-size
NM        = $(TOOLCHAIN)-nm
ST_LINK   = ST-LINK_CLI
OPENOCD   = openocd


# Compiler flags to generate dependency files
GENDEPFLAGS = -MMD -MP -MF $(OBJDIR)/$(*F).d


# Combine all necessary flags and optional flags
# Add target processor to flags.
#
#CPU = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft
#CPU = -mcpu=cortex-m4 -mthumb
#

CPU = -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16

CFLAGS   += $(CPU)
CXXFLAGS += $(CPU)
ASFLAGS  += $(CPU)
LDFLAGS  += $(CPU)

# Default target.
all:  gccversion build showsize

build: elf hex bin

elf: $(TARGET).elf
hex: $(TARGET).hex
lss: $(TARGET).lss
sym: $(TARGET).sym
bin: $(TARGET).bin


# Display compiler version information
gccversion:
	@$(ARM_GCC) --version

# Show the final program size
showsize: elf
	@echo
	@$(SIZE) $(TARGET).elf 2>/dev/null


# Flash the device
program_windows: hex
	$(ST_LINK) -HardRst -c SWD -ME -P $(TARGET).hex -Rst

program_linux: elf
	openocd -f board/stm32f4discovery.cfg -c "program $(TARGET).elf verify reset exit"


# Target: clean project
clean:
	@echo Cleaning project:
	rm -rf $(OBJDIR)


# Create extended listing file from ELF output file
%.lss: %.elf
	@echo
	@echo Creating Extended Listing: $@
	$(OBJDUMP) -h -S -z $< > $@


# Create a symbol table from ELF output file
%.sym: %.elf
	@echo
	@echo Creating Symbol Table: $@
	$(NM) -n $< > $@


# Link: create ELF output file from object files
.SECONDARY: $(TARGET).elf
.PRECIOUS:  $(OBJECTS)

$(TARGET).elf: $(OBJECTS)
	@echo
	@echo Linking: $@
	$(ARM_GCC) $^ $(LDFLAGS) --output $@


# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo Creating hex file: $@
	$(OBJCOPY) -O ihex $< $@

%.bin : %.elf
	$(OBJCOPY) -O binary $< $@

# Compile: create object files from C source files
$(OBJDIR)/%.o : %.c
	@echo
	@echo Compiling C: $<
	$(ARM_GCC) -c $(CPPFLAGS) $(CFLAGS) $(GENDEPFLAGS) $< -o $@

# Assemble: create object files from assembler source files
$(OBJDIR)/%.o : %.s
	@echo
	@echo Assembling: $<
	$(ARM_GCC) -c $(CPPFLAGS) $(ASFLAGS) $< -o $@

# Create object file directories
$(shell mkdir -p $(OBJDIR) 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/drivers/src 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/fatfs 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/libs/STM32F4xx_StdPeriph_Driver/src/ 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/sd 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/src 2>/dev/null)

# Include the dependency files
-include $(wildcard $(OBJDIR)/*.d)


# Listing of phony targets
.PHONY: all build clean \
		program_windows program_linux  \
		elf bin hex lss sym \
		showsize gccversion
