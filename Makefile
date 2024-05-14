ifeq ($(OS), Windows_NT)
	UNAME := Windows_NT
else
	UNAME := $(shell uname)
endif

ifeq ($(UNAME), Windows_NT)
    TARGET := bfp.exe
	TEST := test.exe
	RM := del
else
    TARGET := bfp
	TEST := test.out
	RM := rm
endif

$(TARGET): main.o tokenizer.o bytecode.o
	gcc main.o tokenizer.o bytecode.o -o $(TARGET)

main.o: main.c
	gcc main.c -c -o main.o

$(TEST): test.o tokenizer.o bytecode.o
	gcc test.o tokenizer.o bytecode.o -o $(TEST)

test.o: test.c
	gcc test.c -c -o test.o

test: $(TEST)
	$()

tokenizer.o: tokenizer.c tokenizer.h
	gcc tokenizer.c -c -o tokenizer.o

bytecode.o: bytecode.c
	gcc bytecode.c -c -o bytecode.o

clean:
	$(RM) *.o $(TARGET) $(TEST)
