# Name of the executable
TARGET = app

# Compiler
CC = gcc

# Compiler Options
CFLAGS = -W -Wall -pedantic

# Driver library
LIBS = drv_api.a libs/data_lib/data_management.a

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