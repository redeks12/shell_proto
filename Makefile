#var
FLAGS = -Wall -Werror -Wextra -pedantic -g 

#default
all: main 

main:
	gcc $(FLAGS) shellHeader.h memoryFunc.c stringFunc.c stringFunc2.c customFunc.c printFunc.c helperFunc.c specialFunc.c history.c main.c
test: 
	gcc -g shellHeader.h memoryFunc.c stringFunc.c stringFunc2.c customFunc.c printFunc.c helperFunc.c specialFunc.c history.c main.c
tr: test
	./a.out
tb: test
	gdb ./a.out
