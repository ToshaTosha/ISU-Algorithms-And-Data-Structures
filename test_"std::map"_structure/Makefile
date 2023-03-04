CC = g++
CFLAGS = -std=c++11 -Wall -pedantic

SOURCE_CPP = main.cpp
TARGET_PY = main.py
VIEW = draw.py

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET_CPP = test.exe
else
	RM = rm
	TARGET_CPP = test
endif

all:
	$(CC) $(CFLAGS) -o $(TARGET_CPP) $(SOURCE_CPP)

clean:
	$(RM) *.exe

run: all
	$(TARGET_CPP)
	python $(TARGET_PY)
	python $(VIEW)