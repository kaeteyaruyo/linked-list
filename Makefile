CC = gcc
CFLAGS = -O0 -g -Wall -Werror
EXE = sort-singly sort-circular-doubly sort-optimize sort-linux sort-iterative sort-xor

GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) $(EXE)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

bench-size: rand $(EXE)
	./test/bench-size.sh

test-optimize: rand sort-optimize
	./test/optimize-minsize.sh

$(EXE): % : sort-list.o %.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c sort-list.h
	$(CC) $(CFLAGS) -c $<

rand: rand.c
	$(CC) $(CFLAGS) rand.c -o rand

clean:
	rm -f $(EXE) rand *.o *.png **/*.txt
