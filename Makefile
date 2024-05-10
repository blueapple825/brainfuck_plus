ifeq ($(OS), Windows_NT)
	UNAME := Windows_NT
else
	UNAME := $(shell uname)
endif

ifeq ($(UNAME), Windows_NT)
    TARGET := bfp.exe
	RM := del
else
    TARGET := exe
	RM := rm
endif

$(TARGET): bfp.o
	gcc bfp.o -o $(TARGET)

bfp.o: bfp.c
	gcc bfp.c -c -o bfp.o

clean:
	$(RM) *.o $(TARGET)
