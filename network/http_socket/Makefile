SHELL = /bin/sh

TOP 	= ..
CUR_DIR = $(shell pwd)

CC = gcc
STRIP = strip
AR = ar

INCLUDE			=
SRC				= client_http.c base64.c
AMTAR			= tar
CCFLAGS   = -I$(CUR_DIR)/include -Wall -g -DLINUX
STRIP			= strip

EXECUTABLES = http_get
all: release


release:	CCFLAGS += -DNDEBUG
release:	$(EXECUTABLES)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

http_get: client_http.o base64.o
	$(CC) $(CCFLAGS) client_http.o base64.o -o $@

clean:
	rm -f *.o http_get
