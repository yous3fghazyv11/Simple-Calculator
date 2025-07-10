CC = g++
CFLAGS = -Wall -Wextra -std=c++23
TARGET = calc
SRCS = calc.cpp parser.cpp token.cpp var.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean run install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

install: all
	sudo cp $(TARGET) /usr/bin/

clean:
	rm -f $(TARGET) $(OBJS)
