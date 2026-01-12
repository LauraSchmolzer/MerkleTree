# Compiler
CC = clang

# OpenSSL paths (macOS Homebrew, modify if necessary but I use macOS)
OPENSSL_INCLUDE = /opt/homebrew/opt/openssl@3/include
OPENSSL_LIB     = /opt/homebrew/opt/openssl@3/lib

# Compiler flags
CFLAGS = -I$(OPENSSL_INCLUDE) -Wall -O2
LDFLAGS = -L$(OPENSSL_LIB) -lssl -lcrypto

# Source files
SRCS = main.c structure_tree.c
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = merkle_tree

# Default rule
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Compile .c files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJS) $(TARGET)
