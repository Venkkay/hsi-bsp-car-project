# Name of the executable
TARGET = app

# Compiler
CC = gcc

# Compiler Options
CFLAGS = -W -Wall -pedantic -Wextra -O2

# Driver library
LIBS = drv_api.a libs/data_lib/libdata.a

# Source files
SRC = app.c

# Default rules
all: libs/data_lib/libdata.a $(TARGET)

libs/data_lib/libdata.a:
	$(MAKE) -C libs/data_lib

# Compilation
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Cleaning generated files
clean:
	rm -f $(TARGET)
	$(MAKE) -C libs/data_lib clean