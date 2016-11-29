NAME := progName
TARGET := $(NAME)
DISTFILES := $(TARGET) ClearSans-Medium.ttf resources
OBJS := *.cpp
OPTS := -g -O2 -Wall
LIB := -lSDL2 -lGLEW
CC := $(CROSS_COMPILE)g++

SDL2CONF = $(shell which sdl2-config)
CFLAGS += $(shell $(SDL2CONF) --cflags)
LDFLAGS += $(shell $(SDL2CONF) --libs)

$(TARGET): $(OBJS)
	    $(CC) $(OPTS) $(CFLAGS) $^ -o $(NAME) $(LIB)
