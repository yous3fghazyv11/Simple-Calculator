CC = g++

CFLAGS = -Wall -W -std=c++23

TARGET = calc

all: $(TARGET)

$(TARGET): calc.cpp
	@$(CC) $(CFLAGS) -o $(TARGET) calc.cpp > /dev/null 2>&1

run: all
	@./$(TARGET)

clean:
	@rm -rf $(TARGET)
