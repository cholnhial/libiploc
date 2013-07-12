TARGET = libiploc.so
OBJECTS = src/iploc.o
CFLAGS = -fPIC -c -Wall -I include/
LDFLAGS = -shared -fPIC -lcurl -ljson

CC = gcc
LD = $(CC)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(TARGET) src/*.o


install: $(TARGET)
	cp $(TARGET) /usr/lib
	cp -r include/iploc /usr/include

uninstall: $(TARGET)
	rm /usr/lib/$(TARGET)
	rm -r /usr/include/iploc

.PHONY: all clean install uninstall

