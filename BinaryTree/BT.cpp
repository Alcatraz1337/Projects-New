#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
#define MAX 50
 
typedef struct BTNode
{
	char *word;
	unsigned long count;
	struct BTNode *lchild;
	struct BTNode *rchild;
}BTNode;
 
void GetWord(FILE *fp,int lim,char word[])//获取一个单词
{
	char *w=word;
	int c;
	while(isspace(c=getc(fp)))//跳过空格
		;
	if(c!=EOF)
		*word++=c;
	if(!isalpha(c))//单词第一个不是字母，退出
	{
		*word='\0';
		return ;
	}
	for( ;--lim>0;word++)
		if(!isalnum(*word=getc(fp)))//不是字母或数字，退出
			break;
	*word='\0';
	word=w; //返回单词的头
}
 
BTNode *AddTree(BTNode *root,char *w)
{
    //这个里面的root就是指当前的这个结点
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
	else if(strcmp(w,root->word)==0)
		root->count++;
	else if(strcmp(w,root->word)>0)
		root->rchild=AddTree(root->rchild,w);
	else
		root->lchild=AddTree(root->lchild,w);
 
	return root;
}
 
void TreePrint(BTNode *root,FILE *fp)
{
	if(root)
	{
		TreePrint(root->lchild,fp);
		fprintf(fp,"%4ld %s\n",root->count,root->word);
		TreePrint(root->rchild,fp);
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
	BTNode *root=NULL;
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
			root=AddTree(root,word);
			sumwords++;
		}
	}
	TreePrint(root,out);
    printf("The all words are: %d\n",sumwords);
	fclose(fp);
	fclose(out);
	DTree(root);
	return 0;
}