CC      := g++
CFLAGS  := -Wall -Wextra -std=c++23
TARGET  := calc
SRC     := main.cpp
BINDIR  := /usr/bin

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

run: all
	./$(TARGET)

install: $(TARGET)
	@echo "Installing to $(BINDIR)/$(TARGET) …"
	sudo install -Dm755 $(TARGET) $(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run install clean
