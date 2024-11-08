#!/usr/bin/bash
.PHONY: all clean rebuild

SOURCES:= tcpapplication.cpp
TARGET:= tcpapplication
CC:= g++
CPPFLAGS:= -std=c++11

$(TARGET):$(SOURCES)
	$(CC) $(CPPFLAGS) $< -o $@

all:$(TARGET)

clean:
	@rm -f $(TARGET)

rebuild:
	make clean all

