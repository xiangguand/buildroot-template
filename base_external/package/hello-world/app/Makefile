CC ?= $(CROSS_COMPILE)gcc
CFLAGS ?= -Wall -Wextra
LDFLAGS ?= -lpthread
APP_NAME ?= hello_linux

SRC := app_hello.c
TARGET = $(APP_NAME)
OBJS := $(SRC:.c=.o)

all: $(TARGET)


$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	-rm -f *.o $(TARGET)

# Phony targets
.PHONY: all clean
