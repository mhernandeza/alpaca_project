CFLAGS = -O3 -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm -lSDL2
TARGET = AL_driver
SOURCES = AL_player.c kraken_encounters.c AL_combat.c $(TARGET).c
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET)
