CC = gcc
CFLAGS = -O0 -g -Wall -Werror
EXE = sort-singly sort-circular-doubly sort-optimize sort-linux sort-iterative sort-xor

GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) $(EXE)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

$(EXE): % : sort-list.o %.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c sort-list.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXE) *.o
