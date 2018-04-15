#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

struct Polynomial
{
	int coeff;
	int expo;
};

struct Node
{
	struct Polynomial *data;
	int height;
	struct Node *left;
	struct Node *right;
};

struct PolynomialSeries
{
	struct Polynomial *data;
	struct PolynomialSeries *next;
};

typedef struct Polynomial Polynomial;
typedef struct Node Node;
typedef struct PolynomialSeries PolynomialSeries;

PolynomialSeries *series1, *series2, *series;

void Inorder(Node *root)
{
	if(root!= NULL)
	{
		Inorder(root->left);

		PolynomialSeries *seriesNode = (PolynomialSeries*) malloc (sizeof(PolynomialSeries));
		seriesNode->data = root->data;
		seriesNode->next = NULL;
		series->next = seriesNode;
		series = seriesNode;

		Inorder(root->right);
	}
}

int max(int leftHeight, int rightHeight)
{
	return (leftHeight>rightHeight ? leftHeight : rightHeight);
}

int Height(Node *node)
{
	return (node == NULL? 0:node->height);
}

Node* rightRotate(Node *node)					// left-left case
{
	Node *leftNode = node->left;
	node->left = leftNode->right;
	node->height = 1 + max(Height(node->left), Height(node->right));
	leftNode->right = node;
	leftNode->height = 1 + max(Height(leftNode->left), Height(leftNode->right));
	return leftNode;
}

Node* leftRotate(Node *node)					// right-right case
{
	Node *rightNode = node->right;
	node->right = rightNode->left;
	node->height = 1 + max(Height(node->left), Height(node->right));
	rightNode->left = node;
	rightNode->height = 1 + max(Height(rightNode->left), Height(rightNode->right));
	return rightNode;
}

Node* InsertNode(Node *root, Node *node)
{
	if(root == NULL)
		return node;
	else if(root->data->expo > node->data->expo)
		root->left = InsertNode(root->left, node);
	else
		root->right = InsertNode(root->right, node);

	root->height = 1 + max(Height(root->left), Height(root->right));

	if(abs(Height(root->left) - Height(root->right)) > 1)
	{
		if(Height(root->left) > Height(root->right))
		{
			if(root->left->data->expo > node->data->expo)				// Single right rotation
				root = rightRotate(root);
			else														// First rotate left the rotate right once
			{
				root->left = leftRotate(root->left);
				root = rightRotate(root);
			}
		}
		else if(Height(root->left) < Height(root->right))
		{
			if(root->right->data->expo > node->data->expo)				// First rotate right then rotate left
			{
				root->right = rightRotate(root->right);
				root = leftRotate(root);
			}
			else													// Single right rotation
				root = leftRotate(root);
		}
	}
	return root;
}

PolynomialSeries* storePolynomial(int size)
{
	Node *root = NULL;
	int i = 0, coeff, expo;
	printf("Enter the terms of Polynomial (first coefficient then exponent) : \n");
	for(i = 0; i<size; i++)
	{
		scanf("%d %d", &coeff, &expo);
		Polynomial *p = (Polynomial*) malloc (sizeof(Polynomial));
		p->coeff = coeff;
		p->expo = expo;
		Node *node = (Node *) malloc (sizeof(Node));
		node->data = p;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;

		root = InsertNode(root, node);
	}
	series = (PolynomialSeries*) malloc (sizeof(PolynomialSeries));
	PolynomialSeries *temp = series;
	Inorder(root);
	return temp->next;
}

void printPolynomial(PolynomialSeries *series)
{
	while(series != NULL)
	{
		if(series->next == NULL)
			printf("%dX%d", series->data->coeff, series->data->expo);	
		else
			printf("%dX%d-->", series->data->coeff, series->data->expo);
		series = series->next;
	}
}

void addPolynomial(PolynomialSeries *series1, PolynomialSeries *series2)         // Adds two sorted polynomials
{
	printf("\n Addition of two polynomials is : \n");

	while(series1 != NULL && series2 != NULL)
	{
		if(series1->data->expo < series2->data->expo)
		{
			printf("%dX%d-->", series1->data->coeff, series1->data->expo);
			series1 = series1->next;
		}
		else if(series1->data->expo > series2->data->expo)
		{
			printf("%dX%d-->", series2->data->coeff, series2->data->expo);
			series2 = series2->next;
		}
		else
		{
			if(series1->next == NULL && series2->next == NULL)
				printf("%dX%d", (series1->data->coeff+series2->data->coeff), series1->data->expo);
			else
				printf("%dX%d-->", (series1->data->coeff+series2->data->coeff), series1->data->expo);
			series1 = series1->next;
			series2 = series2->next;
		}
	}
	while(series1 != NULL)
	{
		if(series1->next == NULL)
			printf("%dX%d", series1->data->coeff, series1->data->expo);	
		else
			printf("%dX%d-->", series1->data->coeff, series1->data->expo);
		series1 = series1->next;
	}
	while(series2 != NULL)
	{
		if(series2->next == NULL)
			printf("%dX%d", series2->data->coeff, series2->data->expo);	
		else
			printf("%dX%d-->", series2->data->coeff, series2->data->expo);
		series2 = series2->next;
	}
}

int main()
{
	printf("\n\n%s", "Enter the number of terms in 1st Polynomial : ");
	int size;
	scanf("%d",&size);
	series1 = storePolynomial(size);
	printPolynomial(series1);

	printf("\n\n%s", "Enter the number of terms in 2nd Polynomial : ");
	scanf("%d",&size);
	series2 = storePolynomial(size);
	printPolynomial(series2);

	addPolynomial(series1, series2);
}