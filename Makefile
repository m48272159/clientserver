#!/usr/bin/bash
.PHONY: all docs clean rebuild

BOOST_ROOT ?= $(HOME)/software/boost

SOURCES:= tcpapplication.cpp
TARGET:= tcpapplication
DOCSDIR:= htmldocs
CC:= g++
CPPFLAGS:= -std=c++11

# -lboost_program_options HAS to be be placed after sources
$(TARGET):$(SOURCES)
	$(CC) $(CPPFLAGS) -I$(BOOST_ROOT)/include -L$(BOOST_ROOT)/lib $< -lboost_program_options -o $@

all:$(TARGET) docs

docs:
	@doxygen

clean:
	@rm -rf $(TARGET) $(DOCSDIR)

rebuild:
	make clean all

