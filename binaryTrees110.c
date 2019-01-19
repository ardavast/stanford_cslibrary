#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

struct node *newNode(int data);
int lookup(struct node *node, int data);
void insert(struct node **node, int data);
int size(struct node *node);
int maxDepth(struct node *node);
int minValue(struct node *node);
void printTree(struct node *node);
void printPostorder(struct node *node);
int hasPathSum(struct node *node, int sum);
void printPaths(struct node *node);
void printPathsRecur(struct node *node, int path[], int pathLen);
void mirror(struct node *node);
void doubleTree(struct node *node);
int sameTree(struct node *a, struct node *b);

struct node *newNode(int data)
{
	struct node *node = malloc(sizeof(struct node));

	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

int lookup(struct node *node, int data)
{
	if (node == NULL) {
		return (0);
	} else if (data == node->data) {
		return (1);
	} else {
		if (data <= node->data) {
			return (lookup(node->left, data));
		} else {
			return (lookup(node->right, data));
		}
	}

	return (0);
}

void insert(struct node **node, int data)
{
	assert(node != NULL);

	if (*node == NULL) {
		*node = newNode(data);
		return;
	} else {
		if (data <= (*node)->data) {
			insert(&((*node)->left), data);
		} else {
			insert(&((*node)->right), data);
		}
	}
}

int size(struct node *node)
{
	if (node == NULL) {
		return (0);
	} else {
		return (size(node->left) + 1 + size(node->right));
	}
}

int maxDepth(struct node *node)
{
	int depthLeft, depthRight;

	if (node == NULL) {
		return (0);
	} else {
		depthLeft = maxDepth(node->left);
		depthRight = maxDepth(node->left);

		if (depthLeft > depthRight) {
			return (1 + depthLeft);
		} else {
			return (1 + depthRight);
		}
	}
}

int minValue(struct node *node)
{
	assert(node != NULL);

	if (node->left != NULL) {
		return minValue(node->left);
	} else {
		return (node->data);
	}
}

void printTree(struct node *node)
{
	if (node == NULL) {
		return;
	} else {
		printTree(node->left);
		printf("%d\n", node->data);
		printTree(node->right);
	}
}

void printPostorder(struct node *node)
{
	if (node == NULL) {
		return;
	} else {
		printPostorder(node->left);
		printPostorder(node->right);
		printf("%d\n", node->data);
	}
}

int hasPathSum(struct node *node, int sum)
{
	if (node == NULL) {
		return (node->data == 0);
	} else {
		return (hasPathSum(node->left, sum - node->data) ||
		        hasPathSum(node->right, sum - node->data));
	}
}

void printPaths(struct node *node)
{
	int *path = malloc(sizeof(int) * maxDepth(node));

	printPathsRecur(node, path, 0);
}

void printPathsRecur(struct node *node, int path[], int pathLen)
{
	int i;

	if (node == NULL) {
		return;
	}

	path[pathLen] = node->data;
	pathLen++;

	if (node->left ==  NULL && node->right == NULL) {
		for (i = 0; i < pathLen - 1; i++) {
			printf("%d ", path[i]);
		}
		printf("%d\n", path[i]);
	} else {
		printPathsRecur(node->left, path, pathLen);
		printPathsRecur(node->right, path, pathLen);
	}
}

void mirror(struct node *node)
{
	struct node *tmp;

	if (node == NULL) {
		return;
	}

	mirror(node->left);
	mirror(node->right);

	tmp = node->left;
	node->left = node->right;
	node->right = tmp;

}

void doubleTree(struct node *node)
{
	struct node *tmp;

	if (node == NULL) {
		return;
	}

	doubleTree(node->left);
	doubleTree(node->right);

	tmp = node->left;
	node->left = newNode(node->data);
	node->left->left = tmp;
}

int sameTree(struct node *a, struct node *b)
{
	if (a == NULL && b == NULL) {
		return (1);
	} else if (a != NULL && b != NULL) {
		return (a->data == b->data &&
			sameTree(a->left, b->left) &&
			sameTree(a->right, b->right));
	} else {
		return (0);
	}
}
