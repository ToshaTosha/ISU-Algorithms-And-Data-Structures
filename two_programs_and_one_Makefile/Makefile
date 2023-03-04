CC = g++
CFLAGS = -std=c++11 -Wall -pedantic
FIRST_SOURCES = angles.cpp
SECOND_SOURCES = grad.cpp

number = 5
name = data

ifeq ($(OS), Windows_NT)
	RM = del
	FIRST_TARGET = angles.exe
	SECOND_TARGET = grad.exe
else
	RM = rm
	FIRST_TARGET = first
	second_TARGET = second
endif

first:
	$(CC) $(CFLAGS) -o $(FIRST_TARGET) $(FIRST_SOURCES)

second:
	$(CC) $(CFLAGS) -o $(SECOND_TARGET) $(SECOND_SOURCES)

clean:
	echo $(OS)
	$(RM) $(FIRST_TARGET)
	$(RM) $(SECOND_TARGET)

run: first second
	$(FIRST_TARGET) $(number) $(name)
	$(SECOND_TARGET) $(name)
