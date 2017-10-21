#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

all: find generate a

find: find.c helpers.c helpers.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o find find.c helpers.c -lcs50 -lm

generate: generate.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o generate generate.c
a: a.c
	clang -fsanitize=integer -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow    a.c  -lcrypt -lcs50 -lm -o a

clean:
	rm -f *.o a.out core find generate