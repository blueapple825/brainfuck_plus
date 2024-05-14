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

$(TARGET): main.o tokenizer.o
	gcc main.o tokenizer.o -o $(TARGET)

main.o: main.c
	gcc main.c -c -o main.o

$(TEST): test.o tokenizer.o
	gcc test.o tokenizer.o -o $(TEST)

test.o: test.c
	gcc test.c -c -o test.o

test: $(TEST)
	$()

tokenizer.o: tokenizer.c tokenizer.h
	gcc tokenizer.c -c -o tokenizer.o

clean:
	$(RM) *.o $(TARGET) $(TEST)
