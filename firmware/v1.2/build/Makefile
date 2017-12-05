PROJECT_NAME := blue_plant_1.0
OUTPUT_FILENAME := blue_plant_1.0

export OUTPUT_FILENAME
#MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE_NAME := $(MAKEFILE_LIST)
MAKEFILE_DIR := $(dir $(MAKEFILE_NAME) ) 

# RUTA DEL SDK
SDK_PATH = /opt/nRF51_SDK_10

# RUTA DONDE SE ENCUENTRA EL ARCHIVO Makefile.posix
TEMPLATE_PATH = $(SDK_PATH)/components/toolchain/gcc


ifeq ($(OS),Windows_NT)
include $(TEMPLATE_PATH)/Makefile.windows
else
include $(TEMPLATE_PATH)/Makefile.posix
endif

MK := mkdir
RM := rm -rf

#echo suspend
ifeq ("$(VERBOSE)","1")
NO_ECHO := 
else
NO_ECHO := @
endif

# Toolchain commands
CC       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc"
AS       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as"
AR       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar" -r
LD       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld"
NM       		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm"
OBJDUMP  		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump"
OBJCOPY  		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy"
SIZE    		:= "$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size"

#function for removing duplicates in a list
remduplicates = $(strip $(if $1,$(firstword $1) $(call remduplicates,$(filter-out $(firstword $1),$1))))


#########################################################################################
# AQUI SE AGREGAN LOS ARCHIVOS FUENTE NECESARIOS PARA LA COMPILACIÓN
# DE LA APLICACIÓN.

# Archivos fuente a compilar

C_SOURCE_FILES =  ../main.c
C_SOURCE_FILES += ../include/ble/ble_inits.c
C_SOURCE_FILES += ../include/ble/ble_events.c 
C_SOURCE_FILES += ../include/drivers/onewire.c 
C_SOURCE_FILES += ../include/drivers/ds18b20.c
C_SOURCE_FILES += ../include/drivers/light_sensor.c 
C_SOURCE_FILES += ../include/drivers/soil_sensor.c 
#C_SOURCE_FILES += ../include/services/ble_custom_service.c

C_SOURCE_FILES += $(SDK_PATH)/components/libraries/timer/app_timer.c 
C_SOURCE_FILES += $(SDK_PATH)/components/libraries/timer/app_timer_appsh.c 

C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/delay/nrf_delay.c 
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/common/nrf_drv_common.c 
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/pstorage/pstorage.c 

C_SOURCE_FILES += $(SDK_PATH)/components/ble/common/ble_advdata.c 
C_SOURCE_FILES += $(SDK_PATH)/components/ble/ble_advertising/ble_advertising.c 
C_SOURCE_FILES += $(SDK_PATH)/components/ble/common/ble_conn_params.c 
C_SOURCE_FILES += $(SDK_PATH)/components/ble/common/ble_srv_common.c 

C_SOURCE_FILES += $(SDK_PATH)/components/toolchain/system_nrf51.c 
C_SOURCE_FILES += $(SDK_PATH)/components/softdevice/common/softdevice_handler/softdevice_handler.c 
C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/hal/nrf_adc.c 

#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/button/app_button.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/util/app_error.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/trace/app_trace.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/fifo/app_fifo.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/gpiote/app_gpiote.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/scheduler/app_scheduler.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/uart/retarget.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/uart/app_uart.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/uart/app_uart_fifo.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/crc16/crc16.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/ic_info/nrf51_ic_info.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/led_softblink/led_softblink.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/low_power_pwm/low_power_pwm.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/pwm/app_pwm.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/libraries/twi/app_twi.c 

#C_SOURCE_FILES += $(SDK_PATH)/components/ble/ble_error_log/ble_error_log.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/ble/ble_debug_assert_handler/ble_debug_assert_handler.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/ble/device_manager/device_manager_peripheral.c
#C_SOURCE_FILES += $(SDK_PATH)/components/ble/ble_radio_notification/ble_radio_notification.c

#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/ble_flash/ble_flash.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/gpiote/nrf_drv_gpiote.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/uart/nrf_drv_uart.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/ppi/nrf_drv_ppi.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/qdec/nrf_drv_qdec.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/radio_config/radio_config.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/rng/nrf_drv_rng.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/sdio/sdio.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/spi_master/nrf_drv_spi.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/spi_slave/nrf_drv_spis.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/swi/nrf_drv_swi.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/timer/nrf_drv_timer.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/twi_master/nrf_drv_twi.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/clock/nrf_drv_clock.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/lpcomp/nrf_drv_lpcomp.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/lpcomp/nrf_drv_lpcomp.c 
#C_SOURCE_FILES += $(SDK_PATH)/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c 

# AGREGAR LOS ARCHIVOS FUENTE NECESSARIOS PARA EL USUARIO

#########################################################################################

#assembly files common to all targets
ASM_SOURCE_FILES  = $(SDK_PATH)/components/toolchain/gcc/gcc_startup_nrf51.s


#########################################################################################
# AQUI SE AGREGAN LOS ARCHIVOS DE CABECERA NECESARIOS PARA LA
# COMPILACIÓN DE LA APLICACIÓN

#includes common to all targets
INC_PATHS  = -I ../
INC_PATHS += -I ../include
INC_PATHS += -I ../include/services
INC_PATHS += -I ../include/drivers
INC_PATHS += -I ../include/ble

#Inclusion de librerias de aplicación.
INC_PATHS += -I $(SDK_PATH)/components/libraries/fds
INC_PATHS += -I $(SDK_PATH)/components/libraries/twi
INC_PATHS += -I $(SDK_PATH)/components/libraries/pwm
INC_PATHS += -I $(SDK_PATH)/components/libraries/fifo
INC_PATHS += -I $(SDK_PATH)/components/libraries/uart
INC_PATHS += -I $(SDK_PATH)/components/libraries/uart
INC_PATHS += -I $(SDK_PATH)/components/libraries/slip
INC_PATHS += -I $(SDK_PATH)/components/libraries/util
INC_PATHS += -I $(SDK_PATH)/components/libraries/trace
INC_PATHS += -I $(SDK_PATH)/components/libraries/timer
INC_PATHS += -I $(SDK_PATH)/components/libraries/crc16
INC_PATHS += -I $(SDK_PATH)/components/libraries/button
INC_PATHS += -I $(SDK_PATH)/components/libraries/gpiote
INC_PATHS += -I $(SDK_PATH)/components/libraries/ic_info
INC_PATHS += -I $(SDK_PATH)/components/libraries/console
INC_PATHS += -I $(SDK_PATH)/components/libraries/scheduler
INC_PATHS += -I $(SDK_PATH)/components/libraries/mem_manager
INC_PATHS += -I $(SDK_PATH)/components/libraries/simple_timer
INC_PATHS += -I $(SDK_PATH)/components/libraries/led_softblink
INC_PATHS += -I $(SDK_PATH)/components/libraries/bootloader_dfu


# Inclusion de los drivers del hardware
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/hal
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/ppi
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/rtc
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/rng
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/swi
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/wdt
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/uart
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/qdec
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/sdio
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/delay
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/timer
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/clock
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/common
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/config
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/gpiote
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/lpcomp
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/pstorage
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/spi_slave
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/spi_master
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/ble_flash
INC_PATHS += -I $(SDK_PATH)/components/drivers_nrf/twi_master

INC_PATHS += -I $(SDK_PATH)/components/toolchain/gcc
INC_PATHS += -I $(SDK_PATH)/components/toolchain

# Inclusion de las librerías BLE.
INC_PATHS += -I $(SDK_PATH)/components/ble/ble_dtm
INC_PATHS += -I $(SDK_PATH)/components/ble/ble_racp
INC_PATHS += -I $(SDK_PATH)/components/ble/ble_services
INC_PATHS += -I $(SDK_PATH)/components/ble/ble_error_log
INC_PATHS += -I $(SDK_PATH)/components/ble/device_manager
INC_PATHS += -I $(SDK_PATH)/components/ble/ble_advertising
INC_PATHS += -I $(SDK_PATH)/components/ble/ble_radio_notification
INC_PATHS += -I $(SDK_PATH)/components/ble/ble_debug_assert_handler
INC_PATHS += -I $(SDK_PATH)/components/ble/common
INC_PATHS += -I $(SDK_PATH)/components/ble/device_manager/config
INC_PATHS += -I $(SDK_PATH)/components/ble/peer_manager


INC_PATHS += -I $(SDK_PATH)/components/softdevice/s110/headers
INC_PATHS += -I $(SDK_PATH)/components/softdevice/common/softdevice_handler
INC_PATHS += -I $(SDK_PATH)/components/device

# AGREGAR LAS CARPETAS DE ARCHIVOS DE CABECERA NECESARIAS PARA EL USUARIO

#########################################################################################



OBJECT_DIRECTORY = _obj
LISTING_DIRECTORY = $(OBJECT_DIRECTORY)
OUTPUT_BINARY_DIRECTORY = bin

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(OBJECT_DIRECTORY) $(OUTPUT_BINARY_DIRECTORY) $(LISTING_DIRECTORY) )

#flags common to all targets
#CFLAGS  = -DBOARD_BLE400
CFLAGS =  -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF51
CFLAGS += -DS110
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DSWI_DISABLE0
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs --std=gnu99
CFLAGS += -Wall -O3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums

# keep every function in separate section. This will allow linker to dump unused functions
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

# Assembler flags
ASMFLAGS += -x assembler-with-cpp
#ASMFLAGS += -DBOARD_BLE400
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DNRF51
ASMFLAGS += -DS110
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DSWI_DISABLE0




#default target - first one defined
default: clean $(OUTPUT_FILENAME)

#building all targets
all: clean
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e cleanobj
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e $(OUTPUT_FILENAME)

#target for printing all targets
help:
	@echo following targets are available:
	@echo 	$(OUTPUT_FILENAME)
	@echo 	install_softdevice


C_SOURCE_FILE_NAMES = $(notdir $(C_SOURCE_FILES))
C_PATHS = $(call remduplicates, $(dir $(C_SOURCE_FILES) ) )
C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILE_NAMES:.c=.o) )

ASM_SOURCE_FILE_NAMES = $(notdir $(ASM_SOURCE_FILES))
ASM_PATHS = $(call remduplicates, $(dir $(ASM_SOURCE_FILES) ))
ASM_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASM_SOURCE_FILE_NAMES:.s=.o) )

vpath %.c $(C_PATHS)
vpath %.s $(ASM_PATHS)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)


$(OUTPUT_FILENAME): LINKER_SCRIPT=ble_app_gcc_nrf51.ld
$(OUTPUT_FILENAME): $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	$(NO_ECHO)$(MAKE) -f $(MAKEFILE_NAME) -C $(MAKEFILE_DIR) -e finalize

## Create build directories
$(BUILD_DIRECTORIES):
	echo $(MAKEFILE_NAME)
	$(MK) $@

# Create objects from C SRC files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC_PATHS) -c -o $@ $<

# Assemble files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Compiling file: $(notdir $<)
	$(NO_ECHO)$(CC) $(ASMFLAGS) $(INC_PATHS) -c -o $@ $<


# Link
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(NO_ECHO)$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out


## Create binary .bin file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

finalize: genbin genhex echosize

genbin:
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(NO_ECHO)$(OBJCOPY) -O binary $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin

## Create binary .hex file from the .out file
genhex: 
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(NO_ECHO)$(OBJCOPY) -O ihex $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex

echosize:
	-@echo ""
	$(NO_ECHO)$(SIZE) $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	-@echo ""

clean:
	$(RM) $(BUILD_DIRECTORIES)

cleanobj:
	$(RM) $(BUILD_DIRECTORIES)/*.o

install: $(MAKECMDGOALS)
	
	@echo "device nrf51822_xxac" > jlinkscript_s110.jlink
	@echo "w4 4001e504 1" >> jlinkscript_s110.jlink
	@echo "loadfile `pwd`/$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex" >> jlinkscript_s110.jlink
	@echo "r" >> jlinkscript_s110.jlink
	@echo "g" >> jlinkscript_s110.jlink
	@echo "q" >> jlinkscript_s110.jlink
	@JLinkExe jlinkscript_s110.jlink
	@rm jlinkscript_s110.jlink

erase:
	@echo "device nrf51822_xxac" > jlinkscript_s110.jlink
	@echo "w4 4001e504 2" >> jlinkscript_s110.jlink
	@echo "w4 4001e50c 1" >> jlinkscript_s110.jlink
	@echo "w4 4001e514 1" >> jlinkscript_s110.jlink
	@echo "r" >> jlinkscript_s110.jlink
	@echo "q" >> jlinkscript_s110.jlink
	@JLinkExe jlinkscript_s110.jlink
	@rm jlinkscript_s110.jlink

reset:
	@echo "device nrf51822_xxac" > jlinkscript_s110.jlink
	@echo "r" >> jlinkscript_s110.jlink
	@echo "q" >> jlinkscript_s110.jlink
	@JLinkExe jlinkscript_s110.jlink
	@rm jlinkscript_s110.jlink

install-softdevice: erase
	@echo "device nrf51822_xxac" > jlinkscript_s110.jlink
	@echo "w4 4001e504 1" >> jlinkscript_s110.jlink
	@echo "loadfile "`pwd`"/softdevice/nrf51_s110_8.0_softdevice.hex" >> jlinkscript_s110.jlink
	@echo "r" >> jlinkscript_s110.jlink
	@echo "g" >> jlinkscript_s110.jlink
	@echo "q" >> jlinkscript_s110.jlink
	@JLinkExe jlinkscript_s110.jlink
	@rm jlinkscript_s110.jlink