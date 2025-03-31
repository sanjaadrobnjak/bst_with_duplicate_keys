#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct NODE {
	int key;
	struct NODE* left;
	struct NODE* right;
	struct NODE* parent;
}Node;

typedef struct queue
{
	void** content;
	int front, rear;
	int max_size;
} Queue;

typedef struct st
{
	void** content;
	int top;
	int max_size;
} Stack;

Stack* createStack(int initial_size)
{
	if (initial_size < 1) return 0;
	else
	{
		Stack* ret = (Stack*)calloc(1, sizeof(Stack));
		if (!ret) return 0;
		ret->content = calloc(initial_size, sizeof(void*));
		if (!ret->content)
		{
			free(ret);
			return 0;
		}
		ret->max_size = initial_size;
		return ret;
	}
}

int push(Stack* s, void* dat)
{
	if (!s) return 0;
	if (s->top == s->max_size * 9 / 10)
	{
		Stack** tmp = (Stack**)realloc(s->content, sizeof(void*) * s->max_size * 2);
		if (!tmp) return 0;
		s->content = tmp;
		s->max_size *= 2;
	}
	s->content[s->top++] = dat;
	return 1;
}
void* pop(Stack* s)
{
	if (!s) return 0;
	if (s->top == 0) return 0;
	return s->content[--s->top];
}
int isEmptyStack(Stack* s)
{
	if (!s) return 1;
	return s->top == 0;
}


Queue* createQueue(int initial_size)
{
	Queue* ret = (Queue*)calloc(1, sizeof(Queue));
	if (!ret) return 0;
	ret->content = calloc(initial_size, sizeof(void*));
	if (!ret->content)
	{
		free(ret);
		return 0;
	}
	ret->max_size = initial_size;
	return ret;
}

void eraseQueue(Queue* q)
{
	if (q)
	{
		free(q->content);
		free(q);
	}
}

int insertIntoQueue(Queue* q, void* dat)
{
	if (!q) return 0;
	if ((q->rear + 1) % q->max_size == q->front)
	{
		void** c = (void**)calloc(q->max_size * 2, sizeof(void*));
		int i, j;
		if (!c) return 0;
		for (i = 0, j = q->front; j != q->rear; j = (j + 1) % q->max_size, i++)
			c[i] = q->content[j];
		q->front = 0; q->rear = i;
		free(q->content);
		q->content = c;
		q->max_size *= 2;
	}
	q->content[q->rear++] = dat;
	q->rear = q->rear % q->max_size;
	return 1;
}

void* removeFromQueue(Queue* q)
{
	void* ret = 0;
	if (!q) return 0;
	if (q->front == q->rear) return 0;
	ret = q->content[q->front++];
	q->front = q->front % q->max_size;
	return ret;
}


Node* newNode(int item) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		printf("Neuspela alokacija!\n");
		exit(1);
	}

	tmp->key = item;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->parent = NULL;

	return tmp;
}

Node* createBT(int* K, int low, int high) {
	if (low <= high) {
		int mid = (low + high) / 2;
		Node* root = newNode(K[mid]);
		root->left = createBT(K, low, mid - 1);
		root->right = createBT(K, mid + 1, high);
		return root;
	}
	else
	{
		return NULL;
	}
}



Node* createBintree(int* K, int k) {
	int low = 0;
	int high = k - 1;
	return createBT(K, low, high);
}

void freeTree(Node* r) {
	Node* stack[1000];
	int s, e = 0;
	if (r != NULL) {
		stack[e++] = r;
		for (s = 0; s < e; s++)
		{
			if (stack[s]->left) {
				stack[e++] = stack[s]->left;
			}
			if (stack[s]->right) {
				stack[e++] = stack[s]->right;
			}
			free(stack[s]);
		}
	}
}

int treeHeight(Node* node) {
	if (!node) return -1;
	return 1 + max(treeHeight(node->left), treeHeight(node->right));
}

void printTree(Node* root) {
	if (!root) return;
	else {
		int height = treeHeight(root);
		Queue* q = createQueue((int)pow(2, height));
		int i, line_len = 62;
		int first_skip = line_len, in_between_skip;
		if (!q) return;
		insertIntoQueue(q, root);
		for (i = 0; i <= height; i++) {
			int j = 1 << i, k, l;
			in_between_skip = first_skip;
			first_skip = (first_skip - 2) / 2;
			for (k = 0; k < first_skip; k++) putchar(' ');
			for (k = 0; k < j; k++) {
				Node* btn = (Node*)removeFromQueue(q);
				if (btn) {
					insertIntoQueue(q, btn->left);
					insertIntoQueue(q, btn->right);
				}
				else {
					insertIntoQueue(q, 0);
					insertIntoQueue(q, 0);
				}

				if (btn) printf("%2d", btn->key);

				else printf(" ");
				for (l = 0; l < in_between_skip; l++) putchar(' ');
			}
			putchar('\n');
			putchar('\n');
		}
		eraseQueue(q);
	}
}

int* createArr(int k, int upper, int lower) {
	int* K;
	K = (int*)malloc(k * sizeof(int));
	if (K == NULL) {
		printf("Neuspela alokacija!\n");
		exit(1);
	}

	srand(time(NULL));
	int i;
	for (i = 0; i < k; i++) {
		K[i] = rand() % (upper - lower + 1) + lower;
	}

	int pom, j;
	for (i = 0; i < k - 1; i++) {
		for (j = i + 1; j < k; j++) {
			if (K[i] > K[j]) {
				pom = K[i];
				K[i] = K[j];
				K[j] = pom;
			}
		}
	}
	return K;
}

Node* insert(Node* root, int key) {
	Node* newnode = newNode(key);
	Node* x = root;
	Node* y = NULL;

	while (1) {
		if (x == NULL)
		{
			break;
		}
		y = x;
		if (x->key < key)
			x = x->right;
		else
			x = x->left;
	}


	if (key > y->key) {
		y->right = newnode;
	}

	else if (key < y->key) {
		y->left = newnode;
	}

	else if (y == NULL) {
		y = newnode;
	}

	return y;
}


int findK(Node* root, int key)
{
	int level = 0;
	Node* parent = 0;
	if (!root) return -1;
	Node* node = root;

	while (node)
	{
		if ((node)->key == key) break;
		level++;
		parent = node;
		if ((node)->key > key) {
			node = (node)->left;
		}
		else {
			node = (node)->right;
		}
	}
	return level;
}

void menu() {

	printf("[1] Formiranje stabla na osnovu uredjenog niza kljuceva K \n");
	printf("[2] Umetanje novog kljuca u stablo \n");
	printf("[3] Pretraga stabla za zadati kljuc \n");
	printf("[4] Ispis stabla \n");
	printf("[5] Evaluacija performansi pretrazivanja u BST nad nizom kljuceva \n");
	printf("[6] Brisanje stabla \n");
	printf("[7] Kraj programa \n");

}

int numberOfComparing(Node* root, int key) {
	int level = 0;
	if (!root) return -1;
	Node* node = root;
	//int br = 1;
	int br = 0;


	while (node)
	{
		if ((node)->key == key) {
			br++;
			break;
		}

		if ((node)->key > key) {
			node = (node)->left;
			br = br + 2;
		}

		else {
			node = (node)->right;
			br = br + 3;
		}
	}


	return br;
}

int main() {
	Node* root = NULL;
	int k, upper, lower;

	while (1) {
		menu();
		printf("\n");
		printf("Izaberite opciju : ");
		int choice;
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("\nIzaberite kako zelite da unesete opseg i duzinu niza:\n");
			printf("1) Preko datoteke\n");
			printf("2) Preko standarnog ulaza\n");
			int izbor;
			scanf("%d", &izbor);
			if (izbor == 1)
			{
				FILE* fp = fopen("unos.txt", "r");
				if (fp == NULL) {
					printf("Ne postoji datoteka pod tim nazivom");
					exit(1);
				}
				fscanf(fp, "%d", &k);
				fscanf(fp, "%d", &lower);
				fscanf(fp, "%d", &upper);

				fclose(fp);
			}
			else
			{
				printf("Unesite duzinu niza: ");
				scanf("%d", &k);
				printf("\nUnesite donju granicu niza: ");
				scanf("%d", &lower);
				printf("\nUnesite gornju granicu niza: ");
				scanf("%d", &upper);
				printf("\n");
			}

			int* K = createArr(k, upper, lower);
			if (K == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}

			printf("\nGenerisan niz: ");
			for (int i = 0; i < k; i++)
			{
				printf("%d ", K[i]);
			}

			root = createBintree(K, k);
			break;

		case 2:
			printf("Unesite kljuc koji zelite da dodamo : ");
			int kljuc;
			scanf("%d", &kljuc);
			printf("\n");
			insert(root, kljuc);
			break;

		case 3:
			printf("Unesite kljuc: ");
			int kk;
			scanf("%d", &kk);
			int nivo = findK(root, kk);
			printf("\nTrazeni kljuc se nalazi na visini %d", nivo);
			break;

		case 4:
			printf("Stablo izgleda ovako: \n");
			printTree(root);
			break;

		case 5:
			printf("\nUnesite broj kljuceva: ");
			int brk;
			scanf("%d", &brk);

			int* arr = (int*)malloc(brk * sizeof(int));
			if (arr == NULL) {
				printf("Neuspela alokacija!\n");
				exit(1);
			}

			printf("\nUnesite vrednosti kljuceva: ");
			for (int i = 0; i < brk; i++)
			{
				scanf("%d", &arr[i]);
			}

			//for (int i = 0; i < brk; i++)
			//{
				//printf("\n broj koraka poredjenja je %d", numberOfComparing(root, arr[i]));
			//}

			double averageNumOfComp;
			int sum = 0;
			for (int i = 0; i < brk; i++)
			{
				sum = sum + numberOfComparing(root, arr[i]);
			}

			double z = (double)sum;
			double b = (double)brk;
			averageNumOfComp = z / b;

			printf("\nProsecan broj poredjenja je %f\n", averageNumOfComp);
			break;

		case 6:
			freeTree(root);
			break;

		case 7:
			printf("Kraj programa!\n");
			exit(1);

		default:
			printf("Izabrali ste pogresnu opciju. Ponovo unesite broj");
			break;
		}
	}
	return 0;
}