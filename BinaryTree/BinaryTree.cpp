#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<iostream>
#include<stack>
#include<queue>

using namespace std;

#define MAX 50
 
class BTNode{
	public:
		char *word;
		unsigned long count;
		BTNode *lchild;
		BTNode *rchild;

};


void GetWord(FILE *fp,int lim,char word[])//获取一个单词
{
	char *w=word;
	int c;
	while(isspace(c = tolower(getc(fp))))//跳过空格
		;
	if(c!=EOF)
		*word++=c;
	if(!isalpha(c))//单词第一个不是字母，退出
	{
		*word='\0';
		return ;
	}
	for( ;--lim>0;word++){
		if(!isalnum(*word=getc(fp)))//不是字母或数字，退出
			break;
	}
	*word='\0';
	word=w;
}
 
BTNode* AddNode(BTNode *root,char *w)
{
	BTNode *node;
	if(root==NULL)
	{
		root=(BTNode *)malloc(sizeof(BTNode)*1);
		if(!root)
		{
			printf("No enough memory!\n");
			exit(-1);
		}
		else
		{
			root->word=(char *)malloc(sizeof(char)*MAX);
			if(!root->word)
			{
				printf("No enough memory!\n");
			    exit(-1);
			}
		}
		strcpy(root->word,w);
		root->count=1;
		root->lchild=root->rchild=NULL;
	}
/* 	else{
		while(!nodeQueue.empty()){
			//node = nodeQueue.front();
			nodeQueue.pop();
			node = nodeQueue.front();
			//strcpy(node->word, w);
			if(node->lchild == NULL){
				nodeQueue.push(node->lchild);
			}
			if(node->rchild == NULL){
				nodeQueue.push(node->rchild);
			}
		}
	} */

	else if(strcmp(w,root->word)==0)
		root->count++;
	else if(strcmp(w,root->word)>0)
		root->rchild=AddNode(root->rchild,w);
	else
		root->lchild=AddNode(root->lchild,w);
 
	return root;
}
 
 void PreorderRecusion(BTNode *root, FILE *fp)        //递归前序遍历
{
   if(root!=NULL)
   {
       fprintf(fp,"%4ld %s\n",root->count,root->word);
       PreorderRecusion(root->lchild, fp);
       PreorderRecusion(root->rchild, fp);
   }
}
 
 void PreorderNonRecusion(BTNode *root, FILE *fp)        //非递归前序遍历
{

   stack<BTNode *> nodeStack;       

   BTNode *p = root;
   while(p || !nodeStack.empty())
   {
       if(p)
       {
           	fprintf(fp,"%4ld %s\n",p->count,p->word);
        	if(p->rchild != NULL)
				nodeStack.push(p->rchild);
			p = p->lchild;
	   }
	   else{
		   p = nodeStack.top();
		   nodeStack.pop();
	   }
   }
}
 
void inOrderRecusion(BTNode *root,FILE *fp)
{
	if(root)
	{
		inOrderRecusion(root->lchild,fp);
		fprintf(fp,"%4ld %s\n",root->count,root->word);
		inOrderRecusion(root->rchild,fp);
	}
}

void inOrderNonRecusion(BTNode *root, FILE *fp){
	stack<BTNode *> nodeStack;
	BTNode *pointer = root;
	while(!nodeStack.empty() || pointer){
		if(pointer){
			nodeStack.push(pointer);
			pointer = pointer->lchild;
		}
		else{
			pointer = nodeStack.top();
			fprintf(fp,"%4ld %s\n",pointer->count,pointer->word);
			pointer = pointer->rchild;
			nodeStack.pop();
		}
	}
	fprintf(fp, "\n");
}
 
void PostorderRecusion(BTNode *root, FILE *fp)        //递归后序遍历
{
   if(root!=NULL)
   {
       PostorderRecusion(root->lchild, fp);
       PostorderRecusion(root->rchild, fp);
       fprintf(fp,"%4ld %s\n",root->count,root->word);
   }
}

void PostorderNonRecusion(BTNode *root, FILE *fp){
	stack<BTNode *> nodeStack;
	BTNode *pointer = root;
	BTNode *pre = root;
	while(pointer){
		for (; pointer->lchild != NULL; pointer = pointer->lchild)
			nodeStack.push(pointer);
		while(pointer != NULL && (pointer->rchild == NULL || pointer->rchild == pre)){
			fprintf(fp,"%4ld %s\n",pointer->count,pointer->word);
			pre = pointer;
			if(nodeStack.empty())
				return;
			pointer = nodeStack.top();
			nodeStack.pop();
		}
		nodeStack.push(pointer);
		pointer = pointer->rchild;
	}
}
 
void DTree(BTNode *root)//销毁二叉树
{
	BTNode *p=root;
	if(!p)
		return;
	DTree(p->lchild);
	DTree(p->rchild);
	free(p);
	p=NULL;
}
 
int main(int argc,char *argv[])
{
	queue<BTNode *> nodeQueue;
	BTNode *tree1 = NULL;
	FILE *fp,*out;
	char word[MAX];
	int sumwords=0;
	fp=fopen("text.txt","r");
	out=fopen("out.txt","w");
	if(fp==NULL)
	{
		printf("Can not open the file!\n");
		exit(-1);
	}
	if(out==NULL)
	{
		printf("Can not open the file!\n");
		exit(-1);
	}
	while(!feof(fp))
	{
		GetWord(fp,MAX,word);
		if(isalpha(word[0]))//如果Word第一个是字母，则加入到二叉树中
		{
			tree1 = AddNode(tree1,word);
			sumwords++;
		}
	}

	fprintf(out, "Preorder Recusion: \n");
	PreorderRecusion(tree1, out);
	fprintf(out, "\n");

	fprintf(out, "Preoder Non Recusion: \n");
	PreorderNonRecusion(tree1, out);
	fprintf(out, "\n");

	fprintf(out, "InOrder Recusion: \n");
	inOrderRecusion(tree1, out);
	fprintf(out, "\n");

	fprintf(out, "InOrder Non Recusion: \n");
	inOrderNonRecusion(tree1, out);
	fprintf(out, "\n");

	fprintf(out, "Postorder Recusion:\n");
	PostorderRecusion(tree1, out);
	fprintf(out, "\n");

	fprintf(out, "Postorder Non Recusion: \n");
	PostorderNonRecusion(tree1, out);
	fprintf(out, "\n");

	printf("The all words are: %d\n",sumwords);
	fclose(fp);
	fclose(out);
	DTree(tree1);
	return 0;
}
