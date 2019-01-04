#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

void print(struct node *head);
void push(struct node **head, int data);
int count(struct node *head, int data);
int getNth(struct node *head, int n);
void delete(struct node **head);
int pop(struct node **head);
void sortedInsert(struct node **head, struct node *new);
void insertSort(struct node **head);
void append(struct node **a, struct node **b);
void frontBackSplit(struct node *head, struct node **front, struct node **back);
void removeDuplicates(struct node *head);
void moveNode(struct node **dst, struct node **src);

int
main(void)
{
	struct node *head = NULL;

	print(head);

	return (EXIT_SUCCESS);
}

void print(struct node *head)
{
	struct node *node;

	for (node = head; node != NULL; node = node->next) {
		printf("%p %d %p\n", (void *)node, node->data, (void *)node->next);
	}
}

void push(struct node **head, int data)
{
	struct node *node = malloc(sizeof(struct node));
	node->data = data;
	node->next = *head;
	*head = node;
}

int count(struct node *head, int data)
{
	struct node *node;
	int i = 0;

	for (node = head; node != NULL; node = node->next) {
		if (node->data == data) {
			i++;
		}
	}

	return (i);
}

int getNth(struct node *head, int n)
{
	struct node *node;
	int i = 0;

	assert(n >= 0);

	for (node = head; node != NULL; node = node->next) {
		if (i == n) {
			return (node->data);
		}

		i++;
	}

	assert(0);
}

void delete(struct node **head)
{
	struct node *node = *head;
	struct node *next;

	while (node != NULL) {
		next = node->next;
		free(node);
		node = next;
	}

	*head = NULL;
}

int pop(struct node **head)
{
	struct node *node;
	int data;

	assert(*head != NULL);

	node = *head;
	data = node->data;
	*head = node->next;
	free(node);

	return (data);
}

void insertNth(struct node **head, int n, int data)
{
	struct node **node;
	int i = 0;

	assert(n > 0);

	for (node = head; *node != NULL; node = &((*node)->next)) {
		if (i == n) {
			break;
		}

		i++;
	}

	assert(n == i);

	push(node, data);
}

void sortedInsert(struct node **head, struct node *new)
{
	struct node **node;

	for (node = head; *node != NULL; node = &((*node)->next)) {
		if ((*node)->data > new->data) {
			break;
		}
	}

	new->next = *node;
	*node = new;
}

void insertSort(struct node **head)
{
	struct node *sortedHead = NULL;
	struct node *node = *head;

	while (node != NULL) {
		struct node *nextNode = node->next;

		sortedInsert(&sortedHead, node);
		node = nextNode;
	}

	*head = sortedHead;
}

void append(struct node **a, struct node **b)
{
	struct node *node;

	if (*a == NULL) {
		*a = *b;
		return;
	}

	if (*b == NULL) {
		return;
	}

	for (node = *a; node != NULL; node = node->next)
		;

	node->next = *b;
	*b = NULL;
}

void frontBackSplit(struct node *head, struct node **front, struct node **back)
{
	struct node *slowp, *fastp;

	if (head != NULL || head->next != NULL) {
		*front = head;
		*back = NULL;
	}

	slowp = fastp = head;

	for (;;) {
		fastp = fastp->next;
		if (fastp == NULL) {
			break;
		}

		fastp = fastp->next;
		if (fastp == NULL) {
			break;
		}

		slowp = slowp->next;
	}

	*front = head;
	*back = slowp->next;
	slowp->next = NULL;
}

void removeDuplicates(struct node *head)
{
	struct node *uniqueNode = head;

	while (uniqueNode != NULL) {
		struct node *node = uniqueNode->next;

		while (node != NULL && node->data == uniqueNode->data) {
			struct node *nextNode = node->next;

			free(node);
			node = nextNode;
		}

		uniqueNode->next = node;
		uniqueNode = uniqueNode->next;
	}
}

void moveNode(struct node **dst, struct node **src)
{
	struct node *node;

	node = *src;
	*src = (*src)->next;
	node->next = *dst;
	*dst = node;
}

void alternatingSplit(struct node *head, struct node **a, struct node **b)
{
}
