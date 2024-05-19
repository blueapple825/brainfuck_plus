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

$(TARGET): main.o tokenizer.o bytecode.o stack.o bfp.o
	gcc main.o tokenizer.o bytecode.o stack.o bfp.o -o $(TARGET)

$(TEST): test.o tokenizer.o bytecode.o stack.o bfp.o
	gcc test.o tokenizer.o bytecode.o stack.o bfp.o -o $(TEST)

test: $(TEST)
	$()

main.o: main.c
	gcc main.c -c -o main.o

test.o: test.c
	gcc test.c -c -o test.o

tokenizer.o: tokenizer.c tokenizer.h
	gcc tokenizer.c -c -o tokenizer.o

bytecode.o: bytecode.c bytecode.h
	gcc bytecode.c -c -o bytecode.o

stack.o: stack.c stack.h
	gcc stack.c -c -o stack.o

bfp.o: bfp.c bfp.h
	gcc bfp.c -c -o bfp.o

clean:
	$(RM) *.o $(TARGET) $(TEST)
