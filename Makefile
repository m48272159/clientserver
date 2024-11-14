#!/usr/bin/bash
.PHONY: all docs clean rebuild

SOURCES:= tcpapplication.cpp
TARGET:= tcpapplication
DOCSDIR:= htmldocs
CC:= g++
CPPFLAGS:= -std=c++11

$(TARGET):$(SOURCES)
	$(CC) $(CPPFLAGS) $< -o $@

all:$(TARGET) docs

docs:
	@doxygen

clean:
	@rm -rf $(TARGET) $(DOCSDIR)

rebuild:
	make clean all

