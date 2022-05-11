#ifndef jc_h
#define jc_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
typedef struct tm timeform;
#define MaxVerNum 10
#define INFINITY 10000


/******************************************************/

typedef struct _Book{

	int id;				//排号
	char name[32]; 		//书名
	long int isbn;		//编号
	float price;		//价格
	char type[32];		//分类
	time_t atime;		//时间
	int sign;			//标记

	char Discount[32];	//成色
	float disprice;		//打折后的价格

	int integral;		//积分

}Book;

typedef struct  _TreeNodeBook{
	Book *data;
	struct _TreeNodeBook *left, *right;
}TreeNode;

typedef struct _TreeBook{
	TreeNode *root;
}Tree;

typedef struct _nodeBook{
	Book  *data;
	struct _nodeBook *next;

}NodeBook;

typedef struct _linkedListBook{
	NodeBook *head;
	NodeBook *tail;
	NodeBook *current;

}List_Book;

/***************************链表***************************/
List_Book *initList_Book();
NodeBook *Find_Book_name_node(List_Book *list,char name[]);

List_Book *Find_Book_name(List_Book *list,char name[]);
List_Book *Find_Book_Isbn(List_Book *list,long int isbn);
List_Book *Find_Book_Type(List_Book *list,char type[]);

NodeBook *PromptFind_Book_name(List_Book *list);

int Order_Number();
Book *PromptInput_Data(List_Book *list);
void addTail_Book(List_Book *list);
void delNode_Book(List_Book *list);
void BookToFile(List_Book *list);
void BookToFile_Del(List_Book *list);
void addTail_Book_File(List_Book *list,Book *data);
void BookFromFile(List_Book *list);
void Free_Booklist(NodeBook *list);
void display_Book(NodeBook *book);

void PromptInput_Type(Book *book);

/****************************树*************************/
void CreateTree(Tree *tree, Book *data);
void displayTree_Book(TreeNode *tree);
void InOrder(TreeNode *tree);
void BookFromFile_Tree(Tree *tree);
void FreeTree_Book(TreeNode *tree);

/****************************图*************************/

typedef struct _VertexType{
	char address[30];
}VertexType;

typedef int EdgeType;

typedef struct _MGraph{
	VertexType vexs[MaxVerNum];
	EdgeType edges[MaxVerNum][MaxVerNum];
	int vnum,enumw;
}MGraph;

void CreateMGraph(MGraph *G,VertexType *data,int edgeData[MaxVerNum][MaxVerNum]);
void initVnum(VertexType *data);
void initEdge(int edgeData[MaxVerNum][MaxVerNum]);
int SelectAddress();
void ShortestPath(MGraph *G, int P[MaxVerNum], int D[MaxVerNum], VertexType *data,int vertex,int end);
void Navigate();


/****************************************************/
void Seek_name();
void Seek_Reward();
void Seek_Type();
void Seek_Menu();
/************************************************/
void Book_MenuCheck();
void Book_MenuAdd();
void Book_MenuDel();
void Book_Menu();
void Money();

void Main_Menu();
/************************************************************/
typedef struct _User{
	long int number;			//用户账号
	char name[20]; 				//用户名
	char password[30];			//密码
	int integral;				//积分

}User;


typedef struct _node
{
	User  *data;
	struct _node *next;

}NodeUser;

typedef struct _linkedList
{
	NodeUser *head;
	NodeUser *tail;
	NodeUser *current;

}List_User;

typedef struct  _TreeNode{
	User *data;
	struct _TreeNode *left, *right;
}TreeNode_User;

typedef struct _Tree{
	TreeNode_User *root;
}Tree_User;


/********************************链表******************************/

List_User *initList_User();
void addTail_User(List_User *list,User *data);
void Free_Userlist(NodeUser *list);
void UserToFile_list(List_User *list);
void UserFromFile_list(List_User *list);

/********************************树*******************************/

void CreateTree_User(Tree_User *tree, User *data);
void displayTree_User(TreeNode_User *tree);
void InOrder_User(TreeNode_User *tree);
void FreeTree_User(TreeNode_User *tree);
void UserFromFile_Tree(Tree_User *tree);

User *Input_User_Data();
TreeNode_User *Tree_Search_User(TreeNode_User *tree,long int number);
long int SignIn_User();
void UserToFile(User *user);

void SignIn_User_Menu();
void User_Menu(User *user);
void Recharge_User(long int number);
void xiangqing();


#endif
