#------------------------------------------------------------------------------
# File: 	Makefile
# Author:	paul dautry
# Date:     2016-10-21
# Purpose:
#		Compile distmatnorm program used to benchmark matrix multiplication 
#       and norm operation implemented with and without pthread
#------------------------------------------------------------------------------
HEADERS=alloc.h init.h debug.h mat_ops.h mat_thd_ops.h time_macro.h
OBJ=alloc.o init.o debug.o mat_ops.o mat_thd_ops.o main.o
CFLAGS=-g -Wall -O2
DEFINES=
LIBS=-pthread
TARGET=distmatnorm
#DEBUG=-v

all: build

build: $(TARGET)

install:

clean:
	rm *.o
	rm $(TARGET)

$(TARGET): $(OBJ)
	gcc $(DEBUG) -o $@ $^ $(LIBS)

%.o: %.c
	gcc $(DEBUG) $(CFLAGS) $(DEFINES) -c $<
