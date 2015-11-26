CFLAGS = -o -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -lSDL2
TARGET = combat
SOURCES =  Newcombat.c
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
