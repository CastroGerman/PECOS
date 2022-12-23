#PATHS CONFIG
MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKEFILE_DIR := $(dir $(MAKEFILE_PATH))

SRC_DIR = $(MAKEFILE_DIR)/src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
ASM_FILES = $(SRC_FILES:.c=.s)
INC_DIR = $(MAKEFILE_DIR)/src
INC_FILES = $(wildcard $(SRC_DIR)/*.h)
BUILD_DIR = $(MAKEFILE_DIR)/build
BUILD_FILENAME = app

CC = arm-none-eabi-gcc
FLAG_MARCH = -march=armv7e-m
FLAG_MFPU = -mfpu=fpv4-sp-d16
FLAG_MFLOAT_ABI = -mfloat-abi=hard
FLAG_MTHUMB = -mthumb
FLAG_OPTIMIZATION = -O4
FALG_SPECS = --specs=nano.specs
CC_FLAGS = 	$(FLAG_OPTIMIZATION) -ffunction-sections -fdata-sections -fstack-usage \
			$(FALG_SPECS) $(FLAG_MARCH) $(FLAG_MFPU) $(FLAG_MFLOAT_ABI) $(FLAG_MTHUMB) \
			-Wall -I $(INC_DIR)

LD_DIR = $(MAKEFILE_DIR)/ld
LD_FILE = $(wildcard $(LD_DIR)/*.ld)
CLD = arm-none-eabi-ld
CLD_FLAGS = 
EXE_FILENAME = app

COBJDUMP = arm-none-eabi-objdump
COBJDUMP_FLAGS = 

CFG_FILES = $(SRC_FILES:.c=.cfg)


## ------------------------------------------------------------
## Makefile to automate the workflow of GCC
##
## Author: German Castro
## Rev: 10.2022
## ------------------------------------------------------------
.PHONY: clean


all: clean compile assemble link objdump

## clean:	remove build directory.
clean:
	@rm -rf $(BUILD_DIR)

compile:
	@mkdir -p $(BUILD_DIR)
	@$(CC) -c $(CC_FLAGS) -S -o $(BUILD_DIR)/$(notdir $(ASM_FILES)) $(SRC_FILES)

assemble: compile
	@$(CC) -c $(CC_FLAGS) -fdump-tree-cfg -o $(BUILD_DIR)/$(notdir $(OBJ_FILES)) $(SRC_FILES)

link: assemble
	@$(CLD) $(CLD_FLAGS) -T $(LD_FILE) -o $(BUILD_DIR)/$(EXE_FILENAME).o $(BUILD_DIR)/$(notdir $(OBJ_FILES))

objdump: link
	@$(COBJDUMP) $(COBJDUMP_FLAGS) -d $(BUILD_DIR)/$(EXE_FILENAME).o > $(BUILD_DIR)/$(EXE_FILENAME).lst

readelf: link
	readelf -S $(BUILD_DIR)/$(EXE_FILENAME).o