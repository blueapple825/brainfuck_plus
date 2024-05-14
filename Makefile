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

$(TARGET): bfp.o tokenizer.o
	gcc bfp.o tokenizer.o -o $(TARGET)

bfp.o: bfp.c
	gcc bfp.c -c -o bfp.o

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
