# -std=c99
CFLAGS = -O0 -Wall -g
RL = -L/usr/local/lib -I/usr/local/include -lreadline
PKG = `pkg-config --cflags --libs glib-2.0`
NCS = -lncurses
CC = gcc 

SRCS = $(wildcard ../table/src/*.c) $(wildcard src/*.c) $(wildcard ../pagination/src/*.c) $(wildcard ../data/src/*.c) $(wildcard ../queries/src/*.c) TEST_interpreter.c

all: TEST_interpreter

TEST_interpreter : $(SRCS)
	gcc -o $@ $(PKG) $(CFLAGS) $(RL) $(SRCS) $(NCS)
