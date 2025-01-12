# Name of the executable
TARGET = app

# Compiler
CC = gcc

# Compiler Options
CFLAGS = -W -Wall -pedantic

# Driver library
LIBS = drv_api.a libs/data_lib/libdata.a

# Source files
SRC = app.c decode.c encode.c fsm_classic_car_lights.c fsm_indicator_light_warning.c fsm_wipers_washer.c

# Default rules
all: $(TARGET)

# Compilation
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Cleaning generated files
clean:
	rm -f $(TARGET)