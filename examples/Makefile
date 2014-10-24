TARGET = iplookup
OBJECTS = iplookup.o
CFLAGS = -c -g
LDFLAGS = -liploc

CC = gcc
LD = $(CC)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^  $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -o  $@ $^

clean:
	rm $(TARGET) $(OBJECTS)

install:
	cp $(TARGET) /usr/bin

uninstall:
	rm /usr/bin/$(TARGET)

.PHONY: all clean install uninstall
