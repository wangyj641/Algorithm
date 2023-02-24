#include <stdio.h>
#include <stdlib.h>


//数据结构
//定义一个大的质数，例如10007 100003 1000003
const int mode = 10007;                  //选个跟数据量差不多的
//定义一个hash头
int hash[mode] = {0};
//真正存放数据的地方，为题目中给定的大小
typedef struct NODE
{
	int next;//链表 next指向下一个数组下标
	int value;
}NODE;

NODE node[10001];
int use = 1;//第一个不用，因为我们要判断next==0时为空
unsigned int hashf(int data[8]) {
	unsigned int h = 0;
	for(int i=0;i<8;i++)
		h = h * 31 + data[i];
	return h%mode;
}

void insert(int a)//插入一个数据
{ 
	int id = a % mode;//计算出插入到hash表哪个位置
	node[use].value = a;
	//过程如下图所示，hash已有节点node1，将当前节点node2插入hash表头
	//hash-->node1
	//node2-->node1
	//hash-->node2-->node1
	node[use].next = hash[id];
	hash[id] = use;
	use++;
}

void del(int a)//在表中删除一个节点
{
	int id = a % mode;
	int prev = 0;
	//删除节点，在找的过程中，记录当前节点的前一个节点
	for (int index = hash[id]; index != 0; prev = index, index = node[index].next)
	{
		if (node[index].value == a)
		{
			if (prev == 0)
				hash[id] = node[index].next;
			else 
				node[prev].next = node[index].next;
		}
		
	}
}

bool check(int a)//查找一个节点
{
	int id = a % mode;
	for (int index = hash[id]; index != 0; index = node[index].next)
	{
		if (node[index].value == a)
		{
			return true;
		}
	}
	return false;
}

//有1万个小于1000万的数，删除若干之后，查询每个数是否存在
void main()
{
	int value[10000] = {0};

	for (int i = 0; i < 10000; i++)
	{
		value[i] = (rand() * 10000 + rand()) % 10000000;
		insert(value[i]);
	}

	for (int i = 0; i < 1000; i++)
	{
		del(value[rand()%10000]);
	}

	for (int i = 0; i < 10000; i++)
	{
		check(value[i]);
	}
}
