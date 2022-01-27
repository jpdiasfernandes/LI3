CC = gcc

EXEC = program

CFLAGS = -O2 -Wall -std=c99 
RL = -L/usr/local/lib -I/usr/local/include -lreadline
PKG = `pkg-config --cflags --libs glib-2.0`
NCS = -lncurses
STRDUP = -D_DEFAULT_SOURCE

SRCS_MODELS = $(wildcard model/table/src/*.c) $(wildcard model/sgr/src/*.c) 
SRCS_CONTROLLER = $(wildcard controller/interpreter/src/*.c) 
SRCS_VIEW = $(wildcard view/pagination/src/*.c) $(wildcard view/messages/src/*.c) 

program: $(SRCS_MODELS) $(SRCS_VIEW) $(SRCS_CONTROLLER)
	$(CC) -o $(EXEC) $(STRDUP) $(PKG) $(CFLAGS) $(RL) $(NCS) $(SRCS_VIEW) $(SRCS_CONTROLLER) $(SRCS_MODELS) main.c

clean:
	rm program
