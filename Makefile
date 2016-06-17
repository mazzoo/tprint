CFLAGS=-Wall -Os -I.
CFLAGS+=-g
TARGET=test

OBJ+=$(TARGET).o
OBJ+=tprint.o

all:$(TARGET)

$(TARGET):$(OBJ)

clean:
	$(RM) $(OBJ)
	$(RM) $(TARGET)
