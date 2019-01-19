CC=cc
CFLAGS=-std=c90 -pedantic -Wall -Wextra -g

all: linkedLists105 binaryTrees110

linkedLists105: linkedLists105.c
	$(CC) $(CFLAGS) -c -o linkedLists105 linkedLists105.c

binaryTrees110: binaryTrees110.c
	$(CC) $(CFLAGS) -c -o binaryTrees110 binaryTrees110.c
