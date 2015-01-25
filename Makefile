#--------------------------------------------------------
# system
#--------------------------------------------------------
UNAME = $(shell uname)

#--------------------------------------------------------
# target
#--------------------------------------------------------
TARGET = shmpr_minesweeper

#--------------------------------------------------------
# directories
#--------------------------------------------------------
GIT_DIR = ./
SRC_DIR = $(GIT_DIR)src/
INC_DIR = $(GIT_DIR)include/
INT_DIR = $(GIT_DIR)

BIN_DIR = ./

OBJ_DIR = ./obj/$(UNAME)/
OBJ32_DIR = $(OBJ_DIR)32bit/
OBJ64_DIR = $(OBJ_DIR)64bit/

#--------------------------------------------------------
# compilation configuration
#--------------------------------------------------------
CXX = gcc

ifeq ($(UNAME), Linux)
INCLUDE   = -I$(INT_DIR) -I$(INC_DIR)
LFLAGS    = 
else
INCLUDE32 = -I$(INT_DIR) -I$(INC_DIR)
INCLUDE64 = -I$(INT_DIR) -I$(INC_DIR)
LFLAGS32  = -lm -lmingw32
LFLAGS64  = -lm -lmingw32
endif

ifeq ($(UNAME), Linux)
CFLAGS    = -MD -MP -Wall -Werror -pedantic -std=c99 -fPIC
else
CFLAGS    = -MD -MP -Wall -Werror -pedantic -std=c99
endif
CFLAGS32  = -m32 $(CFLAGS)
CFLAGS64  = -m64 $(CFLAGS)

#--------------------------------------------------------
# sources
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
else
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES = $(call rwildcard,$(SRC_DIR),*.c)
endif

#--------------------------------------------------------
# objects ans dependencies
#--------------------------------------------------------
OBJECTS32 = $(patsubst $(SRC_DIR)%.c, $(OBJ32_DIR)%.o, $(SOURCES))
OBJECTS64 = $(patsubst $(SRC_DIR)%.c, $(OBJ64_DIR)%.o, $(SOURCES))

DEPS32	= $(OBJECTS32:.o=.d)
DEPS64	= $(OBJECTS64:.o=.d)

#--------------------------------------------------------
# make all rule
#--------------------------------------------------------
all: app64

#--------------------------------------------------------
# hypnos rules
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
app32: $(BIN_DIR)$(TARGET).l32
app64: $(BIN_DIR)$(TARGET).l64
else
app32: $(BIN_DIR)$(TARGET).w32.exe
app64: $(BIN_DIR)$(TARGET).w64.exe
endif

#--------------------------------------------------------
# cleaning rule
#--------------------------------------------------------
clean:
	rm -rf $(OBJ32_DIR)
	rm -rf $(OBJ64_DIR)
ifeq ($(UNAME), Linux)
	rm -rf $(BIN_DIR)$(TARGET).l32
	rm -rf $(BIN_DIR)$(TARGET).l64
else
	rm -rf $(BIN_DIR)$(TARGET).w32.exe
	rm -rf $(BIN_DIR)$(TARGET).w64.exe
endif

#--------------------------------------------------------
# hypnos objects and target rules
#--------------------------------------------------------

ifeq ($(UNAME), Linux)
$(BIN_DIR)$(TARGET).l32: $(OBJECTS32)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS32) $(LFLAGS)
$(BIN_DIR)$(TARGET).l64: $(OBJECTS64)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS64) $(LFLAGS)
else
$(BIN_DIR)$(TARGET).w32.exe: $(OBJECTS32)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS32) $(LFLAGS32)
$(BIN_DIR)$(TARGET).w64.exe: $(OBJECTS64)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS64) $(LFLAGS64)
endif

-include $(DEPS32)
-include $(DEPS64)

ifeq ($(UNAME), Linux)
$(OBJ32_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS32) $(INCLUDE) $< -o $@
else
$(OBJ32_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS32) $(INCLUDE32) $< -o $@
endif

ifeq ($(UNAME), Linux)
$(OBJ64_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS64) $(INCLUDE) $< -o $@
else
$(OBJ64_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS64) $(INCLUDE64) $< -o $@
endif
