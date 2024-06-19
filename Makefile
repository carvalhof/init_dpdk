#!/bin/bash

CC = gcc
LIBS =
CFLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors \
         -Wunused -Wuninitialized -Wfloat-equal -Wshadow \
         -O2 -fstack-protector-strong -fsanitize=address \
         -pthread

DPDK_DIR = $(HOME)/lib/x86_64-linux-gnu
PKG_CONFIG_DIR = $(DPDK_DIR)/pkgconfig

DPDK_CFLAGS = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_DIR) pkg-config --cflags libdpdk)
DPDK_LDFLAGS = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_DIR) pkg-config --libs libdpdk)

INCLUDE_DIRS = $(HOME)/include
LIB_DIRS = $(HOME)/lib

INCFLAGS = $(foreach dir, $(INCLUDE_DIRS), -I$(dir))
LDFLAGS = $(foreach dir, $(LIB_DIRS), -L$(dir))

TARGET = helloworld
SRCS = helloworld.c

all: $(TARGET)

$(TARGET): $(SRCS)
        $(CC) $(CFLAGS) $(DPDK_CFLAGS) $(INCFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS) $(DPDK_LDFLAGS) $(LIBS)

clean:
        rm -f $(TARGET)

distclean: clean
        rm -f *.o *~

run: $(TARGET)
        sudo -E LD_LIBRARY_PATH=$(DPDK_DIR):$$LD_LIBRARY_PATH ./$(TARGET) $(ARGS)

.PHONY: all clean distclean run
