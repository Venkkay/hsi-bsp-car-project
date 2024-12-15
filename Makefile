# Name of the executable
TARGET = app

# Compiler
CC = gcc

# Compiler Options
CFLAGS = -Wall -Wextra -O2

# Driver library
LIBS = drv_api.a

# Source files
SRC = app.c

# Default rules
all: $(TARGET)

# Compilation
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Cleaning generated files
clean:
	rm -f $(TARGET)