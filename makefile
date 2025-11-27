# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 
LDFLAGS =

# Target executable name
TARGET = png_reader

# Source files
SRCS = main.c Convert_IM_B64.c

# Object files (automatically generated from SRCS)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = Convert_IM_B64.h

# Default target - builds the executable
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile .c files to .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean run