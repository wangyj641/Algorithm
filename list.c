
#include <stdio.h>
#include <stdlib.h>

typedef struct DATA
{
	int id;
	char name[20];
}DATA;

typedef struct NODE
{
	DATA data;
	int next;
}NODE;

NODE node[101] = {0};
int use = 1;
int head[10] = {0};
int index[100] = {0};

void insert(int a, DATA b)
{
	node[use].data = b;
	node[use].next = head[a];
	head[a] = use++;
}

void del(int a, int id)
{
	int prev = 0;
	for (int index = head[a]; index != 0; prev = index, index = node[index].next)
	{
		if (node[index].data.id == id)
		{
			if (prev == 0)head[a] = node[index].next;
			else node[prev].next = node[index].next;
		}
	}
}

char * find(int a, int id)
{
	int prev = 0;
	for (int index = head[a]; index != 0; index = node[index].next)
	{
		if (node[index].data.id == id)
		{
			return node[index].data.name;
		}
	}
	return NULL;
}

void main()
{
	for (int i = 0; i < 100; i++)
	{
		DATA temp = { i, };
		for (int j = 0; j < 10; j++)
		{
			temp.name[j] = rand() % 57 + 65;
		}
		index[i] = rand() % 10;
		insert(index[i], temp);
	}

	for (int i = 0; i < 10; i++)
	{
		int id = rand() % 100;
		del(index[id], id);
	}

	for (int i = 0; i < 10; i++)
	{
		int id = rand() % 100;
		printf("%s\n", find(index[id], id));
	}
}
