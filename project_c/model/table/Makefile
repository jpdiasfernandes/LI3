CC      = gcc
CCFLAGS = -O2 -Wall -Wextra
INCLDS  = -I $(INC_DIR) 
INCLDS += `pkg-config --cflags --libs gmodule-no-export-2.0`
DEBUG   = -g
SRC_DIR = .
INC_DIR = ../includes
BLD_DIR = .
BIN_DIR = .
SRC     = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(SRC))
DEPS    = $(patsubst $(BLD_DIR)/%.o,$(BLD_DIR)/%.d,$(OBJS))
PROGRAM = test_table

vpath %.c $(SRC_DIR)

.DEFAULT_GOAL = build

.PHONY: clean run build debug

$(BLD_DIR)/%.o: %.c
	$(CC) -c $(INCLDS) $(CCFLAGS) $< -o $@

$(BIN_DIR)/$(PROGRAM): $(OBJS)
	$(CC) $(INCLDS) $(CCFLAGS) -o $@ $(OBJS)

build: $(BLD_DIR)/$(PROGRAM)

run: build
	./$(BIN_DIR)/$(PROGRAM) 

debug: CCFLAGS += $(DEBUG)
debug: build
	

clean: 
	rm $(BIN_DIR)/*.o $(PROGRAM)
