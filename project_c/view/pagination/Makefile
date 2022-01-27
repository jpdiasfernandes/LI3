# -std=c99
CFLAGS = -O0 -Wall -g 
RL = -L/usr/local/lib -I/usr/local/include -lreadline -I ../table/includes
PKG = `pkg-config --cflags --libs glib-2.0`
NCS = -lncurses -lmenu 
CC = gcc 

SRCS = TEST_pagination.c $(wildcard ../data/src/*.c) $(wildcard ../queries/src/*.c) $(wildcard ../table/src/*.c) $(wildcard ../pagination/src/*.c)

all: TEST_pagination

TEST_pagination: $(SRCS)
	gcc -o $@ $(CFLAGS) $(RL) $(SRCS) $(PKG) $(NCS)

clean:
	rm TEST_pagination
