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
void deleteList(struct node **head);
int pop(struct node **head);
void sortedInsert(struct node **head, struct node *new);
void insertSort(struct node **head);
void append(struct node **a, struct node **b);
void frontBackSplit(struct node *head, struct node **front, struct node **back);
void removeDuplicates(struct node *head);
void moveNode(struct node **dst, struct node **src);
void alternatingSplit(struct node *head, struct node **a, struct node **b);
struct node *shuffleMerge(struct node *a, struct node *b);
struct node *sortedMerge(struct node *a, struct node *b);
void mergeSort(struct node **head);
struct node *sortedIntersect(struct node *a, struct node *b);
void reverse(struct node **head);

void print(struct node *head)
{
	struct node *node;

	for (node = head; node != NULL; node = node->next) {
		printf("%d\n", node->data);
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

void deleteList(struct node **head)
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
	struct node *node = head;
	struct node *aHead = NULL, *bHead = NULL;
	struct node **aTail = &aHead, **bTail = &bHead;

	for (;;) {
		if (node == NULL) {
			break;
		}
		push(aTail, node->data);
		aTail = &((*aTail)->next);
		node = node->next;

		if (node == NULL) {
			break;
		}
		push(bTail, node->data);
		bTail = &((*bTail)->next);
		node = node->next;
	}

	*a = aHead;
	*b = bHead;
}

struct node *shuffleMerge(struct node *a, struct node *b)
{
	struct node *head = NULL;
	struct node **tail = &head;

	while (a != NULL || b != NULL) {
		if (a != NULL) {
			push(tail, a->data);
			a = a->next;
			tail = &((*tail)->next);
		}

		if (b != NULL) {
			push(tail, b->data);
			b = b->next;
			tail = &((*tail)->next);
		}
	}

	return (head);
}

struct node *sortedMerge(struct node *a, struct node *b)
{
	struct node *head = NULL;
	struct node **tail = &head;

	for (;;) {
		if (a != NULL && b != NULL) {
			if (a->data < b->data) {
				push(tail, a->data);
				a = a->next;
			} else {
				push(tail, b->data);
				b = b->next;
			}
			tail = &((*tail)->next);
		} else if (a != NULL) {
			push(tail, a->data);
			a = a->next;
			tail = &((*tail)->next);
		} else if (b != NULL) {
			push(tail, b->data);
			b = b->next;
			tail = &((*tail)->next);
		} else {
			break;
		}
	}

	return (head);
}

void mergeSort(struct node **head)
{
	struct node *a, *b;

	if (*head == NULL || (*head)->next == NULL) {
		return;
	}

	frontBackSplit(*head, &a, &b);

	mergeSort(&a);
	mergeSort(&b);

	*head = sortedMerge(a, b);
}

struct node *sortedIntersect(struct node *a, struct node *b)
{
	struct node *head = NULL;
	struct node **tail = &head;

	while (a != NULL && b != NULL) {
		if (a->data < b->data) {
			a = a->next;
		} else if (a->data > b->data) {
			b = b->next;
		} else {
			push(tail, a->data);
			a = a->next;
			b = b->next;
		}
	}

	return (head);
}

void reverse(struct node **head)
{
	struct node *node = *head;
	struct node *prev = NULL;
	struct node *next;

	while (node != NULL) {
		next = node->next;
		node->next = prev;
		prev = node;
		node = next;
	}

	*head = prev;
}
