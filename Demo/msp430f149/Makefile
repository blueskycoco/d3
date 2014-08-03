MCU ?= msp430f149
CROSS_COMPILE ?= msp430-

FREERTOS_ROOT=../../freertos
SOURCE_PATH=$(FREERTOS_ROOT)/Source
PORT_PATH=../../Source/portable/GCC/MSP430
DEMO_PATH=$(FREERTOS_ROOT)/Demo/Common/Minimal
BSP430_PATH=../Common/drivers/MSP430/bsp430
HAL_PATH=MSP-EXP430F5438_HAL

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar

# Can't use -f*-sections until SF 3534425 is fixed
OPT_CFLAGS ?= -Os -ffunction-sections -fdata-sections
WARN_CFLAGS = -Wall -Wno-main
# Turn off warnings related to brokenness in the TI code
# -Wno-unused-function: Headers provide static function declarations
WARN_CFLAGS += -Wno-unused-function
OPT_LDFLAGS ?= -Wl,-gc-sections
CPPFLAGS = -I. -I$(PORT_PATH)
CPPFLAGS += -I$(HAL_PATH)
CPPFLAGS += -I$(SOURCE_PATH)/include
CPPFLAGS += -I$(FREERTOS_ROOT)/Demo/Common/include

# TARGET_FLAGS holds things like -msr20, -md20, -mc20, or -mmemory-model=.
# Like -mmcu, it gets passed in both CFLAGS and LDFLAGS.
ifndef TARGET_FLAGS
ifdef MEMORY_MODEL
TARGET_FLAGS=-mmemory-model=$(MEMORY_MODEL)
endif # MEMORY_MODEL
endif # TARGET_FLAGS

CFLAGS=-mmcu=$(MCU) $(TARGET_FLAGS) $(OPT_CFLAGS)  $(WARN_CFLAGS) $(XCFLAGS)
LDFLAGS=-mmcu=$(MCU) $(TARGET_FLAGS) $(OPT_LDFLAGS)

# Object file derived from assembler source including preprocessor
%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

SRC = \
$(SOURCE_PATH)/tasks.c \
$(SOURCE_PATH)/queue.c \
$(SOURCE_PATH)/list.c \
$(SOURCE_PATH)/timers.c \
$(SOURCE_PATH)/portable/MemMang/heap_1.c \
$(PORT_PATH)/port.c \
$(HAL_PATH)/hal_board.c \
$(HAL_PATH)/hal_buttons.c \
serial.c \
main.c


OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

demo.elf: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJ)
	msp430-size demo.elf
clean:
	-rm -f $(OBJ)

realclean: clean
	-rm -f demo.elf $(DEP)

install: demo.elf
	mspdebug -j uif 'prog demo.elf'

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(DEP)
