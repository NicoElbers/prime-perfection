# compiler
CC = g++

# compiler flags
CFLAGS := -std=c++23

# main file
MAIN_FILE = main.cpp

# program name(s)
MAIN_PROGRAM = main
DEBG_PROGRAM = debug_$(MAIN_PROGRAM)
TEST_PROGRAM = tests

# compiler flags
DBGFLAGS := -g
COBJFLAGS := $(CFLAGS) -c

# paths
BIN_PATH  := bin
OBJ_PATH  := obj
SRC_PATH  := src
DBG_PATH  := dbg
SAVE_PATH := save
TEST_PATH := test


# compile logic
ifeq ($OS),Windows_NT)
	MAIN_PROGRAM := $(addsuffix .exe, $(MAIN_PROGRAM))
	DEBG_PROGRAM := $(addsuffix .exe, $(DEBG_PROGRAM))
	TEST_PROGRAM := $(addsuffix .exe, $(TEST_PROGRAM))
endif

TARGET_MAIN := $(BIN_PATH)/$(MAIN_PROGRAM)
TARGET_TEST := $(BIN_PATH)/$(TEST_PROGRAM)
TARGET_DEBG := $(DBG_PATH)/$(DEBG_PROGRAM)

COUNT_SAVE  := $(shell ls $(SAVE_PATH) -1 2>/dev/null | wc -l)
TARGET_SAVE := $(SAVE_PATH)/$(MAIN_PROGRAM)$(COUNT_SAVE)

# source files
MAIN_SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
TEST_SRC := $(foreach x, $(SRC_PATH), $(filter-out $(SRC_PATH)/$(MAIN_FILE), $(wildcard $(addprefix $(x)/*,.c*))))
TEST_SRC += $(foreach x, $(TEST_PATH), $(wildcard $(addprefix $(x)/*,.c*)))

# object files
MAIN_OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(MAIN_SRC)))))
TEST_OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(TEST_SRC)))))
DEBG_OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(MAIN_SRC)))))


# clean files list
DIST_LIST  := $(MAIN_OBJ) \
							$(TEST_OBJ) \
							$(DEBG_OBJ)
CLEAN_LIST := $(TARGET_MAIN) \
							$(TARGET_TEST) \
							$(TARGET_DEBG) \
							$(DIST_LIST) 

# default rule
default: dir main test

# non-phony targets
$(TARGET_MAIN): $(MAIN_OBJ)
	$(CC) -o $@ $(MAIN_OBJ) $(CFLAGS)

$(TARGET_TEST): $(TEST_OBJ)
	$(CC) -o $@ $(TEST_OBJ) $(DBGFLAGS) $(CFLAGS)

$(TARGET_DEBG): $(DEBG_OBJ)
	$(CC) -o $@ $(DEBG_OBJ) $(DBGFLAGS) $(CFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) -o $@ $<

$(OBJ_PATH)/%.o: $(TEST_PATH)/%.c*
	$(CC) $(COBJFLAGS) -o $@ $<

# phony rules
.PHONY: dir
dir: 
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(SRC_PATH) $(DBG_PATH) $(SAVE_PATH) $(TEST_PATH)

.PHONY: main
main: $(TARGET_MAIN)

.PHONY: test
test: $(TARGET_TEST)

.PHONY: debug
debug: $(TARGET_DEBG)

.PHONY: save
save: $(TARGET_MAIN)
	@echo $(TARGET_SAVE)
	@cp -n $(TARGET_MAIN) $(TARGET_SAVE)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	rm -f $(CLEAN_LIST)
