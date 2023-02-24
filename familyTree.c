#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CHANGE                 200
#define REGISTERATION       300
#define REMOVE	               400
#define FAMILY_TREE     500
#define END	            		999

#define MAX_FAMILY_TREE_LENGTH 30000
#define MAX_NAME_LENGTH 12

extern void parse(char orgFamilyTree[MAX_FAMILY_TREE_LENGTH], int size);
extern void change(char name[MAX_NAME_LENGTH], char bfName[MAX_NAME_LENGTH]);
extern void registeration(char parent[MAX_NAME_LENGTH], char child[MAX_NAME_LENGTH], char childBfName[MAX_NAME_LENGTH]);
extern void remove(char name[MAX_NAME_LENGTH]);
extern int familyTree(char name[MAX_NAME_LENGTH], char newFamilyTree[MAX_FAMILY_TREE_LENGTH]);

static char orgFamilyTree[MAX_FAMILY_TREE_LENGTH];
static char newFamilyTree[MAX_FAMILY_TREE_LENGTH];

static int point;

static int calcHash(char* data, int len) {
	int ret = 0;
	for (register int i = 1; i < len; ++i) {
		ret += (data[i] * i + i);
		ret &= 0xFFFF;
	}
	return ret;
}

static inline int ch2num(char ch) {
	return ch >= 'A' ? 10 + ch - 'A' : ch - '0';
}

int testcase;
#define SOLOTYPE         (0x01)
#define MARRIEDTYPE            (0x02)
static int len;

static void run() {
	char buf[80];
	scanf("%d", &len);
	for (register int p = 0; p < len;) {
		scanf("%s", buf);
		for (register int i = 0; i < 64 && p < len; i += 2, ++p)
			orgFamilyTree[p] = (ch2num(buf[i]) << 4) | ch2num(buf[i + 1]);
	}
	parse(orgFamilyTree, len);

	while (1) {
		int command;
		char name[MAX_NAME_LENGTH], bfName[MAX_NAME_LENGTH];
		char parent[MAX_NAME_LENGTH], child[MAX_NAME_LENGTH], childBfName[MAX_NAME_LENGTH];
		int hash, length, resultlength, resulthash;

		scanf("%d", &command);
		switch (command) {
		case CHANGE:
			scanf("%s %s", name, bfName);
			change(name, bfName);
			break;
		case REGISTERATION:
			scanf("%s %s %s", parent, child, childBfName);
			registeration(parent, child, childBfName);
			break;
		case REMOVE:
			scanf("%s", name);
			remove(name);
			break;
		case FAMILY_TREE:
			scanf("%s %d %d", name, &length, &hash);
			resultlength = familyTree(name, newFamilyTree);
			if (length == resultlength) {
				resulthash = calcHash(newFamilyTree, length);
				if (resulthash == hash) point += length;
			}
			break;
		}
		if (command == END) break;
	}
}

int main() {
	int T, total_score;
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);

	total_score = 0;
	for (testcase = 1; testcase <= 1; ++testcase) {
		int score;
		point = 0;
		run();
		scanf("%d", &score);
		total_score += (point / score) * 100;
	}

	printf("#total score : %d\n", total_score / T);
	if (total_score / T < 100) return -1;
	return 0;
}

#define NULL 0
#define MAX_CHILD_NUM 100
struct NODE
{
	int type;
	int name_len[2];
	char name[MAX_NAME_LENGTH];
	int bf_name_len[2];
	char bf_name[MAX_NAME_LENGTH];
	int child_cnt[2];
	int real_cnt;
	int flag;
	NODE *parent = NULL;
	NODE *pre_node = NULL;
	NODE *next_node = NULL;
	NODE *child_head = NULL;
	NODE* child_tail = NULL;
	NODE *brother = NULL;
};
NODE *node_data[MAX_FAMILY_TREE_LENGTH + 1];
NODE *root = NULL;
int node_num;

int strcompare(char str1[], char str2[])
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			break;
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0')
		return 1;
	return 0;
}
void strcopy(char from[], char to[])
{
	while (*from != '\0')
	{
		*to = *from;
		from++;
		to++;
	}
	*to = '\0';
}
int cal_hash(char str[])
{
	int ret = 0;
	int i = 0;
	while (str[i])
	{
		ret = (ret * 131 + str[i]) % 30001;
		i++;
	}
	return ret;
}
int get_len(char str[])
{
	int len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}

void init(NODE * nd)
{
	if (nd == NULL)return;
	int i;
	if (nd->type == 2)
	{
		if (nd->child_head != NULL)
		{
			NODE* tmp = nd->child_head;
			while (tmp)
			{
				NODE* next = tmp->brother;
				init(tmp);
				//				tmp = tmp->brother;
				tmp = next;
			}
		}
	}
	delete nd;
	nd = NULL;
	//	delete nd;
}

int add_child(char instr[], int start, int end, NODE * parent, int index)
{
	if (start >= end || parent == NULL)
		return start;
	NODE * nd = new NODE;

	if (nd != NULL)
	{
		nd->type = instr[start++];
		nd->name_len[0] = instr[start++];
		nd->name_len[1] = instr[start++];
		int i;
		for (i = 0; i < nd->name_len[1]; i++)
		{
			nd->name[i] = instr[start++];
		}
		nd->name[i] = '\0';
		nd->flag = 0; // 1: deleted
		nd->parent = parent;

		int hash_index = cal_hash(nd->name);
		if (node_data[hash_index] == NULL)
			node_data[hash_index] = nd;
		else
		{
			NODE *head = node_data[hash_index];
			nd->next_node = head;
			head->pre_node = nd;
			node_data[hash_index] = nd;
		}
		if (nd->type == 1)
		{
			nd->bf_name_len[0] = instr[start++];
			nd->bf_name_len[1] = instr[start++];
			for (i = 0; i < nd->bf_name_len[1]; i++)
				nd->bf_name[i] = instr[start++];
			nd->bf_name[i] = '\0';
		}
		else if (nd->type == 2)
		{
			nd->child_cnt[0] = instr[start++];
			nd->child_cnt[1] = instr[start++];
			nd->real_cnt = nd->child_cnt[1];
			for (i = 0; i < nd->child_cnt[1]; i++)
				start = add_child(instr, start, end, nd, i);
		}
		if (index == 0)
		{
			parent->child_head = nd;

		}
		else
		{
			NODE* tmp = parent->child_head;
			while (tmp->brother)
				tmp = tmp->brother;
			tmp->brother = nd;
		}
		if (index == parent->child_cnt[1] - 1)
			parent->child_tail = nd;
		return start;
	}
	return start;
}
void parse(char orgFamilyTree[MAX_FAMILY_TREE_LENGTH], int size) {
	init(root);
	int i;
	//	for (i = 0; i < size; i++)
	//		printf("%d ", orgFamilyTree[i]);
	//	printf("\n");
	int pos = 0;
	root = new NODE;
	if (root != NULL)
	{
		root->type = orgFamilyTree[pos++];
		root->name_len[0] = orgFamilyTree[pos++];
		root->name_len[1] = orgFamilyTree[pos++];
		int i;
		for (i = 0; i < root->name_len[1]; i++)
		{
			root->name[i] = orgFamilyTree[pos++];
		}
		root->name[i] = '\0';
		root->flag = 0; // 1: deleted
		root->parent = NULL;
		root->pre_node = NULL;
		node_data[cal_hash(root->name)] = root;
		if (root->type == 1)
		{
			root->bf_name_len[0] = orgFamilyTree[pos++];
			root->bf_name_len[1] = orgFamilyTree[pos++];
			for (i = 0; i < root->bf_name_len[1]; i++)
				root->bf_name[i] = orgFamilyTree[pos++];
			root->bf_name[i] = '\0';
		}
		else if (root->type == 2)
		{
			root->child_cnt[0] = orgFamilyTree[pos++];
			root->child_cnt[1] = orgFamilyTree[pos++];
			root->real_cnt = root->child_cnt[1];
			for (i = 0; i < root->child_cnt[1]; i++)
				pos = add_child(orgFamilyTree, pos, size, root, i);
		}
	}
}
int copy_data_to_tree(NODE* parent, char newtree[], int start)
{
	if (parent == NULL)
		return start;
	if (parent->flag == 1)
		return start;
	newtree[start++] = parent->type;
	newtree[start++] = parent->name_len[0];
	newtree[start++] = parent->name_len[1];
	int i;
	for (i = 0; i < parent->name_len[1]; i++)
		newtree[start++] = parent->name[i];
	if (parent->type == 1)
	{
		newtree[start++] = parent->bf_name_len[0];
		newtree[start++] = parent->bf_name_len[1];
		for (i = 0; i < parent->bf_name_len[1]; i++)
			newtree[start++] = parent->bf_name[i];
	}
	else if (parent->type == 2)
	{
		newtree[start++] = parent->child_cnt[0];
		newtree[start++] = parent->real_cnt;
		NODE* tmp = parent->child_head;
		while (tmp)
		{
			start = copy_data_to_tree(tmp, newtree, start);
			tmp = tmp->brother;
		}
	}
	return start;
}
NODE* find_the_node(char name[])
{
	int hash = cal_hash(name);
	NODE *nd = node_data[hash];
	if (nd == NULL)
		return NULL;
	int flg = 0;
	while (nd)
	{
		if (strcompare(nd->name, name))
		{
			flg = 1;
			break;
		}
		nd = nd->next_node;
	}
	return nd;
}
void dfs_remove_child(NODE* parent)
{
	if (parent == NULL)
		return;
	int hash = cal_hash(parent->name);
	parent->flag = 1;
	if (parent->pre_node != NULL)
	{
		parent->pre_node->next_node = parent->next_node;
		if (parent->next_node != NULL)
			parent->next_node->pre_node = parent->pre_node;
	}
	else
	{
		node_data[hash] = parent->next_node;
	}

	if (parent->real_cnt == 0)
		return;
	int i;
	NODE* tmp = parent->child_head;
	while (tmp)
	{
		if (tmp->flag == 0)
			dfs_remove_child(tmp);
		tmp = tmp->brother;
	}
}
void change(char name[MAX_NAME_LENGTH], char bfName[MAX_NAME_LENGTH]){
	NODE *nd = find_the_node(name);
	if (nd == NULL)
		return;
	if (nd->flag == 1)  //this node was deleted
		return;
	int len = get_len(bfName);
	nd->bf_name_len[1] = len;
	strcopy(bfName, nd->bf_name);
}

void registeration(char parent[MAX_NAME_LENGTH], char child[MAX_NAME_LENGTH], char childBfName[MAX_NAME_LENGTH]){
	NODE *nd = find_the_node(parent);
	if (nd == NULL)
		return;
	if (nd->flag == 1)  //this node was deleted
		return;
	NODE *tmp = new NODE;
	tmp->type = 1;
	tmp->name_len[0] = 0;
	int len = get_len(child);
	tmp->name_len[1] = len;
	strcopy(child, tmp->name);
	int bf_len = get_len(childBfName);
	tmp->bf_name_len[0] = 0;
	tmp->bf_name_len[1] = bf_len;
	strcopy(childBfName, tmp->bf_name);
	tmp->parent = nd;
	if (nd->child_cnt[1] > 0)
	{
		nd->child_tail->brother = tmp;
		nd->child_tail = tmp;
	}
	nd->child_cnt[1]++;
	nd->real_cnt++;
}

void remove(char name[MAX_NAME_LENGTH]){

	NODE *nd = find_the_node(name);
	if (nd == NULL)
		return;
	if (nd->flag == 1)  //this node was deleted
		return;
	nd->parent->real_cnt--;
	dfs_remove_child(nd);
}

int familyTree(char name[MAX_NAME_LENGTH], char newFamilyTree[MAX_FAMILY_TREE_LENGTH]) {
	int ret = 0;
	NODE *nd = find_the_node(name);
	if (nd == NULL)
		return 0;
	//start to copy the data to newFamilyTree
	if (nd->flag == 1)  //this node was deleted
		return 0;
	ret = copy_data_to_tree(nd, newFamilyTree, ret);
	return ret;
}
