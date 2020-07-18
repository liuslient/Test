#include<iostream>
#include <sstream>
#include <string>
using namespace std;

//结构体
typedef struct treeNode
{
	int data;
	struct treeNode *left;
	struct treeNode *right;
}Node;

//创建二叉树
Node *creat()
{
	Node *p;
	int n;
	cin>>n;
	if(n==0)
	{
		p=NULL;
	}
	else
	{
		p=(Node*)malloc(sizeof(Node));
		p->data=n;
		p->left=creat();
		p->right=creat();
	}
	return p;
}

//先序遍历
void firsttraverse(Node* root)
{
	if(root)
	{
		cout<<root->data;
		firsttraverse(root->left);
		firsttraverse(root->right);
	}
}
//中序遍历
void middletraverse(Node* root)
{
	if(root)
	{
		middletraverse(root->left);
		cout<<root->data;
		middletraverse(root->right);
	}
}
//后序遍历
void lasttraverse(Node* root)
{
	if(root)
	{
		lasttraverse(root->left);
		lasttraverse(root->right);
		cout<<root->data;
	}
}

//二叉树节点数目
int num(Node *root)
{
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		return num(root->left)+num(root->right)+1;
	}
}
//二叉树深度
int depth(Node *root)
{
	if(root==NULL)
	{
		return 0;
	}
	if(root)
	{
		return depth(root->left)>depth(root->right)?depth(root->left)+1:depth(root->right)+1;
	}
}
//二叉树叶子节点数
int leaf(Node *root)
{
	if(!root)
	{
		return 0;
	}
	else if((root->left==NULL)&&(root->right==NULL))
	{
		return 1;
	}
	else
	{
		return (leaf(root->left)+leaf(root->right));
	}
}
//主函数
int main()
{
	Node *root=NULL;
	root=creat();
	printf("二叉树建立成功");
	cout<<endl;
	cout<<"节点"<<num(root) <<endl;
	cout<<"深度"<<depth(root)<<endl;
	cout<<"叶子数"<<leaf(root)<<endl;

	cout<<"前序遍历结果"<<endl;
	firsttraverse(root);
	cout<<endl;

	cout<<"中序遍历结果"<<endl;
        middletraverse(root);
        cout<<endl;

	cout<<"后序遍历结果"<<endl;
        lasttraverse(root);
        cout<<endl;

	return 0;
}
