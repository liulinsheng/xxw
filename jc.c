#include"jc.h"


/***********************************************************/

List_Book *initList_Book (){
	
	List_Book *list = (List_Book *)malloc(sizeof(List_Book));
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;

	return list;
}//链表初始化

NodeBook *Find_Book_name_node(List_Book *list,char name[]){
	NodeBook *tmp = list->head;
	while(tmp != NULL && strcmp(tmp->data->name,name)){
		tmp = tmp->next;
	}
	return tmp;
}

List_Book *Find_Book_name(List_Book *list,char name[]){
	NodeBook *tmp = list->head;
	while(tmp != NULL){
		if( !strcmp(tmp->data->name,name)){
			tmp->data->sign = 1;
		}
		tmp = tmp->next;
	}
	return list;
}//通过name查找节点并返回

List_Book *Find_Book_Isbn(List_Book *list,long int isbn){
	NodeBook *tmp = list->head;
	while(tmp != NULL){
		if( tmp->data->isbn == isbn){
			tmp->data->sign = 1;			
		}
		tmp = tmp->next;
	}
	return list;
}//通过author查找节点并返回

List_Book *Find_Book_Type(List_Book *list,char type[]){
	NodeBook *tmp = list->head;
	while(tmp != NULL){
		if( !strcmp(tmp->data->type,type)){
			tmp->data->sign = 1;	
		}
		tmp = tmp->next;
	}
	return list;
}//通过type查找节点并返回

NodeBook *PromptFind_Book_name(List_Book *list){
	char name[20];
	NodeBook *goods;
	printf("\n请输入您要删除的书名\n");
	scanf("%s",name);
	goods = Find_Book_name_node(list,name);
	
	return goods;
}

int Order_Number(){
	int order = 1,id = 0;
	int integral,sign;
	long int isbn;
	char name[32],reward[32],type[32],Discount[32];
	float price,disprice;
	time_t atime;


	FILE *fp;
	fp = fopen("goods.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			fscanf(fp,"%d",&id);
			fscanf(fp,"%s",name);
			fscanf(fp,"%ld",&isbn);
			fscanf(fp,"%f",&price);
			fscanf(fp,"%s",type);
			fscanf(fp,"%ld",&atime);
			fscanf(fp,"%d",&sign);
			fscanf(fp,"%d",&integral);

			fscanf(fp,"%s",Discount);
			fscanf(fp,"%f",&disprice);

			order = id + 1;
		}
		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return order;

}

void PromptInput_Type(Book *book){
	int flat;
	printf("请问您的书是几成新？\n");
	xiangqing();
	printf("1.九九新\t2.九五新\t\t3.良品\t\t4.中品\t\t5.拒绝\n");
	scanf("%d",&flat);
	switch(flat){
			case 1: strcpy(book->Discount,"九九新");
					book->disprice = book->price*0.3;
					break;
			case 2:	strcpy(book->Discount,"九五新");
					book->disprice = book->price*0.2;			
					break;
			case 3:	strcpy(book->Discount,"良品");
					book->disprice = book->price*0.1;
					break;
			case 4:	strcpy(book->Discount,"中品");
					book->disprice = book->price*0.05;
					break;
			case 5:	strcpy(book->Discount,"拒绝");
					book->disprice = book->price*0;
					break;
			
			default:printf("未找到命令 ！\n");
	}
	return;
}//作为PromptFoodInput_Data的内部函数提醒用户选择菜类型

Book *PromptInput_Data(List_Book *list){
	Book *book = (Book *)malloc(sizeof(Book));
	int id;
	int integral;
	float price;
	long int isbn;
	char name[32];
	char type[32];
	id = Order_Number();
	book->id = id;
	book->sign = 0;
	book->atime = time(0);
	printf("请输入书名\n");
	scanf("%s",name);
	strcpy(book->name,name);

	printf("请输入KBN\n");
	scanf("%ld",&isbn);
	book->isbn = isbn;

	printf("请输入类型\n");
	scanf("%s",type);
	strcpy(book->type,type);

	printf("请输入原定价\n");
	scanf("%f",&price);
	book->price = price;
/*
	printf("请输入积分\n");
	scanf("%d",&integral);
	book->integral = integral;
*/
	PromptInput_Type(book);

	printf("折后价格 %.2f\n", book->disprice);



	return book;

}

void addTail_Book(List_Book *list){
	
	NodeBook *node = (NodeBook *)malloc(sizeof(NodeBook));
	node->data = PromptInput_Data(list);
	node->next = NULL;

	if(list->head == NULL){
		list->head = node;
	}else{
		list->tail->next = node;
	}
	list->tail = node;

	return;
}


void delNode_Book(List_Book *list){
	NodeBook *node = PromptFind_Book_name(list);
	if(node == list->head){
		if(list->head->next == NULL){
			list->head = list->tail = NULL;
		}else{
			list->head = list->head->next;
		}
	}else{
		NodeBook *tmp = list->head;
		while(tmp != NULL && tmp->next != node){
			tmp = tmp->next;
		}
		if(tmp != NULL){
			tmp->next = node->next;
		}
	}
	free(node);

	return;
}

void BookToFile(List_Book *list){
	
	NodeBook *tmp = list->head;
	FILE *fp;
	fp = fopen("goods.txt","a");
	if (fp != NULL)
	{
		while(tmp != NULL){
			fprintf(fp, "%d\t", tmp->data->id);
			fprintf(fp, "%s\t\t", tmp->data->name);
			fprintf(fp, "%ld\t\t", tmp->data->isbn);
			fprintf(fp, "%.2f\t\t", tmp->data->price);
			fprintf(fp, "%s\t\t", tmp->data->type);
			fprintf(fp, "%ld\t\t", tmp->data->atime);
			fprintf(fp, "%d\t\t", tmp->data->sign);
			fprintf(fp, "%d\t\t",tmp->data->integral);

			fprintf(fp, "%s\t\t", tmp->data->Discount);
			fprintf(fp, "%.2f\n", tmp->data->disprice);

			tmp = tmp->next;
		}
		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
}

void BookToFile_Del(List_Book *list){
	
	NodeBook *tmp = list->head;
	FILE *fp;
	int id = 0;
	fp = fopen("goods.txt","w");
	if (fp != NULL)
	{
		while(tmp != NULL){
				if (tmp->data->price == 0) break;
				id++;
				fprintf(fp, "%d\t\t", id);
				fprintf(fp, "%s\t\t", tmp->data->name);
				fprintf(fp, "%ld\t\t", tmp->data->isbn);
				fprintf(fp, "%.2f\t\t", tmp->data->price);
				fprintf(fp, "%s\t\t", tmp->data->type);
				fprintf(fp, "%ld\t\t", tmp->data->atime);
				fprintf(fp, "%d\t\t", tmp->data->sign);
				fprintf(fp, "%d\t\t",tmp->data->integral);

				fprintf(fp, "%s\t\t", tmp->data->Discount);
				fprintf(fp, "%.2f\n", tmp->data->disprice);				



				tmp = tmp->next;
			
		}
		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
}

void addTail_Book_File(List_Book *list,Book *data){
	NodeBook *node = (NodeBook *)malloc(sizeof(NodeBook));
	node->data = data;
	node->next = NULL;

	if(list->head == NULL){
		list->head = node;
	}else{
		list->tail->next = node;
	}
	list->tail = node;

	return;
}

void BookFromFile(List_Book *list){
	FILE *fp;
	fp = fopen("goods.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			Book *book = (Book *)malloc(sizeof(Book));
			fscanf(fp,"%d",&(book->id));
			fscanf(fp,"%s",book->name);
			fscanf(fp,"%ld",&(book->isbn));
			fscanf(fp,"%f",&(book->price));
			fscanf(fp,"%s",book->type);
			fscanf(fp,"%ld",&(book->atime));
			fscanf(fp,"%d",&(book->sign));
			fscanf(fp,"%d",&(book->integral));

			fscanf(fp,"%s",book->Discount);
			fscanf(fp,"%f",&(book->disprice));

			addTail_Book_File(list,book);
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return;
}

void Free_Booklist(NodeBook *list){

	NodeBook *tmp;
	while(list != NULL){
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	return;
}

/************************************************************/


void CreateTree(Tree *tree, Book *data){
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	if (tree->root == NULL){
		tree->root = node;
	}else{
		TreeNode *tmp = tree->root;
		while(tmp != NULL){
			if (data->id < tmp->data->id){
				if (tmp->left == NULL){
					tmp->left = node;
					return;
				}else{
					tmp = tmp->left;
				}
			}else{
				if (tmp->right ==NULL){
					tmp->right = node;
					return;
				}else{
					tmp = tmp->right;
				}
			}
		}
	}
	return;
}
void display_Book(NodeBook *node){
	timeform *form;	
	form = localtime(&(node->data->atime));
	if( node->data->id > 0){
		printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("书名: %s\t", node->data->name);
		printf("KBN码: %ld\t", node->data->isbn);

		printf("类型: %s\t", node->data->type);
		printf("价格: %.2f\t", node->data->price);
		printf("积分: %d\t",node->data->integral);

		//printf("打折: %s\t", node->data->Discount);
		printf("折后价: %.2f\t", node->data->disprice/2);

		printf("入库时间:%04u-%02u-%02u  %02u:%02u:%02u\n",
		form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );
		printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	return;
}


void displayTree_Book(TreeNode *tree){
	timeform *form;	
	form = localtime(&(tree->data->atime));
	if( tree->data->id > 0){
		printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%d", tree->data->id);
		printf("书名: %s\t", tree->data->name);
		printf("KBN码: %ld\t", tree->data->isbn);

		printf("类型: %s\t", tree->data->type);
		printf("价格: %.2f\t", tree->data->price);
		printf("积分: %d\t",tree->data->integral);

		//printf("打折: %s\t", tree->data->Discount);
		printf("折后价: %.2f\t", tree->data->disprice);

		printf("入库时间:%04u-%02u-%02u  %02u:%02u:%02u\n",
		form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );
		
	}
	return;
}

void InOrder(TreeNode *tree){
	if (tree){
		InOrder(tree->left);
		displayTree_Book(tree);
		InOrder(tree->right);
	}
	return;
}

void BookFromFile_Tree(Tree *tree){
	FILE *fp;
	fp = fopen("goods.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			Book *book = (Book *)malloc(sizeof(Book));
			fscanf(fp,"%d",&(book->id));
			fscanf(fp,"%s",book->name);
			fscanf(fp,"%ld",&(book->isbn));
			fscanf(fp,"%f",&(book->price));
			fscanf(fp,"%s",book->type);
			fscanf(fp,"%ld",&(book->atime));
			fscanf(fp,"%d",&(book->sign));
			fscanf(fp,"%d",&(book->integral));

			fscanf(fp,"%s",book->Discount);
			fscanf(fp,"%f",&(book->disprice));

			CreateTree(tree, book);
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return;	
}

void FreeTree_Book(TreeNode *tree){
	if (tree){
		FreeTree_Book(tree->left);
		free(tree->data);
		free(tree);
		FreeTree_Book(tree->right);
	}
}


/***************************************************/

void Seek_name(){
	system("clear");
	char name[20];
	NodeBook *tmp;
	List_Book *list1;
	List_Book *list = initList_Book();
	BookFromFile(list);
	
	printf("请输入您要查找的书名\n");
	scanf("%s",name);
	list1 = Find_Book_name(list,name);
	tmp = list1->head;
	while(tmp != NULL){
		if(tmp->data->sign == 1){
			display_Book(tmp);
		}
		tmp = tmp->next;
	}
	
	Free_Booklist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}

void Seek_Isbn(){
	system("clear");
	long int isbn;
	NodeBook *tmp;
	List_Book *list1;
	List_Book *list = initList_Book();
	BookFromFile(list);

	printf("请输入你要查找的KBN码\n");
	scanf("%ld",&isbn);
	list1 = Find_Book_Isbn(list,isbn);
	tmp = list1->head;
	while(tmp != NULL){
		if(tmp->data->sign == 1){
			display_Book(tmp);
		}
		tmp = tmp->next;
	}

	Free_Booklist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}

void Seek_Type(){
	system("clear");
	char type[32];
	NodeBook *tmp;
	List_Book *list1;
	List_Book *list = initList_Book();
	BookFromFile(list);

	printf("请输入你要查找的类型\n");
	scanf("%s",type);
	list1 = Find_Book_Type(list,type);
	tmp = list1->head;
	while(tmp != NULL){
		if(tmp->data->sign == 1){
			display_Book(tmp);
		}
		tmp = tmp->next;
	}

	Free_Booklist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");
}

void Seek_Menu(){
	system("clear");
	char flat;
	while(1){
		printf("请选择你要进行的操作\n");
		printf("1.书名查找\n");
		printf("2.KBN码查找\n");
		printf("3.类型查找\n");
		printf("4.退出\n");
		flat = getchar();
		switch(flat){
			case '1':	Seek_name();
						break;
			case '2':	Seek_Isbn();
						break;
			case '3':	Seek_Type();
						break;
			case '4':	system("clear");
						return;
		}

	}


	return;
}



/****************************************************/

void Book_MenuCheck(){
	system("clear");
	Tree *tree = (Tree *)malloc(sizeof(Tree));
	tree->root = NULL;
	BookFromFile_Tree(tree);
	InOrder(tree->root);
	FreeTree_Book(tree->root);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}

void Book_MenuAdd(){
	system("clear");
	char flat = 'n';
	List_Book *list = initList_Book();
	while(flat != 'y'){

		addTail_Book(list);
		printf("是否退出y or n\n");
		getchar();
		scanf("%c",&flat);
	}
	BookToFile(list);
	Free_Booklist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}

void Book_MenuDel(){
	system("clear");
	char flat = 'n';
	List_Book *list = initList_Book();
	BookFromFile(list);
	while(flat != 'y'){
		delNode_Book(list);
		printf("是否退出y or n\n");
		getchar();
		scanf("%c",&flat);
	}
	BookToFile_Del(list);
	Free_Booklist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	system("clear");

	return;
}

void Book_Menu(){
	system("clear");
	char flat;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
    tree->root = NULL;
    UserFromFile_Tree(tree);
	while(1){
		printf("请选择你要进行的操作\n");
		printf("1.查看书籍\n");
		printf("2.添加书籍\n");
		printf("3.删除书籍\n");
		printf("4.书籍查询\n");
		printf("5.用户信息\n");
		printf("6.返回上层\n");
		flat = getchar();
		switch(flat){
			case '1':	Book_MenuCheck();
						break;
			case '2':	Book_MenuAdd();
						break;
			case '3':	Book_MenuDel();
						break;
			case '4':	getchar();
						Seek_Menu();
						getchar();
						break;
			case '5':	getchar();
                        system("clear");
                        InOrder_User(tree->root);
                        printf("\n");
                        printf("请按任意键返回\n");
                        getchar();
                        system("clear");
                        break;
			case '6':	system("clear");
						FreeTree_User(tree->root);
						return;
		}

	}
	return;
}

void Main_Menu(){
	system("clear");
	char flat;
	long int password;
	while(1){
		printf("请选择你要进行的操作\n");
		printf("1.用户\n");
		printf("2.管理\n");
		printf("3.退出\n");
		flat = getchar();
		switch(flat){
			case '1':	getchar();
						SignIn_User_Menu();
						getchar();
						break;
			case '2':	getchar();
						printf("请输入管理员密码\n");
						scanf("%ld",&password);
						if (password == 666666)
						{
							getchar();
							Book_Menu();
							getchar();
							break;
						}else
						{
							printf("密码错误！！！\n");
							getchar();
							getchar();
							system("clear");
							break;
						}
						
						//getchar();
						//break;
			case '3':	system("clear");
						return;
		}

	}
	return;
}

/*************************************************/

List_User *initList_User(){
    
    List_User *list = (List_User *)malloc(sizeof(List_User));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;

    return list;
}//链表初始化

void addTail_User(List_User *list,User *data){
    
    NodeUser *node = (NodeUser *)malloc(sizeof(NodeUser));
    node->data = data;
    node->next = NULL;

    if(list->head == NULL){
        list->head = node;
    }else{
        list->tail->next = node;
    }
    list->tail = node;

    return;
}//头插法构建链表  

void Free_Userlist(NodeUser *list){

    NodeUser *tmp;
    while(list != NULL){
        tmp = list;
        list = list->next;
        free(tmp);
        tmp = NULL;
    }
    return;
}//释放链表 


void UserToFile_list(List_User *list){
    
    NodeUser *tmp = list->head;
    FILE *fp;
    fp = fopen("user.txt","a");
    if (fp != NULL)
    {
        while(tmp != NULL){
            fprintf(fp, "%ld\t", tmp->data->number);
            fprintf(fp, "%s\t", tmp->data->password);
            fprintf(fp, "%s\t", tmp->data->name);
            fprintf(fp, "%d\n", tmp->data->integral);

            tmp = tmp->next;
        }
        fclose(fp);
    }else{
        printf("文件保存失败 ！\n");
    }
}

void UserFromFile_list(List_User *list){
    FILE *fp;
    fp = fopen("user.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp)){
            User *user = (User *)malloc(sizeof(User));
            fscanf(fp, "%ld", &(user->number));
            fscanf(fp, "%s", user->password);
            fscanf(fp, "%s", user->name);
            fscanf(fp, "%d",&(user->integral));

            addTail_User(list,user);
        }

        fclose(fp);

    }else{
        printf("文件打开失败 ！\n");
    }
    return;
}
/************************************************************************/

void CreateTree_User(Tree_User *tree, User *data){
    TreeNode_User *node = (TreeNode_User *)malloc(sizeof(TreeNode_User));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    if (tree->root == NULL){
        tree->root = node;
    }else{
        TreeNode_User *tmp = tree->root;
        while(tmp != NULL){
            if (tmp->data->number > data->number ){
                if (tmp->left == NULL){
                    tmp->left = node;
                    return;
                }else{
                    tmp = tmp->left;
                }
            }else{
                if (tmp->right ==NULL){
                    tmp->right = node;
                    return;
                }else{
                    tmp = tmp->right;
                }
            }
        }
    }
    return;
}

void displayTree_User(TreeNode_User *tree){ 
    
    if(tree->data->number == 0 || tree->data->number > 1000000000000)       return;
    printf("账号: %ld\t",tree->data->number);
    printf("用户名: %s\t",tree->data->name);
    printf("积分: %d\t", tree->data->integral);

 
    printf("\n");
    printf("_____________________________________________________________________________________\n");

    return;
}

void InOrder_User(TreeNode_User *tree){
    if (tree){
        InOrder_User(tree->left);
        displayTree_User(tree);
        InOrder_User(tree->right);
    }
    return;
}

void FreeTree_User(TreeNode_User *tree){
    if (tree){
        FreeTree_User(tree->left);
        free(tree->data);
        free(tree);
        FreeTree_User(tree->right);
    }
    return;
}

void UserFromFile_Tree(Tree_User *tree){
    FILE *fp;
    fp = fopen("user.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp)){
            User *user = (User *)malloc(sizeof(User));
            fscanf(fp, "%ld", &(user->number));
            fscanf(fp, "%s", user->password);
            fscanf(fp, "%s", user->name);
            fscanf(fp, "%d",&(user->integral));

            //fscanf(fp, "%s", user->Discount);
            //fscanf(fp, "%f", user->disprice);

            CreateTree_User(tree, user);
        }

        fclose(fp);

    }else{
        printf("文件打开失败 ！\n");
    }
    return; 
}
/****************************************************************/
void Recharge_User(long int number){
	system("clear");
	FILE *fp;
	char name[32];
	List_Book *listg;
	NodeBook *goodsnode;
	listg = initList_Book();
	BookFromFile(listg);

	Tree *treeg = (Tree *)malloc(sizeof(Tree));
	treeg->root = NULL;
	BookFromFile_Tree(treeg);

	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *Treenode;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	Treenode = Tree_Search_User(tree->root,number);
	List_User *list;
	list = initList_User();
	UserFromFile_list(list);
	NodeUser *tmp1 = list->head;
	while(tmp1 != NULL && tmp1->data->number != Treenode->data->number){
		tmp1 = tmp1->next;
	}
	
	NodeUser *node = tmp1;
	if(node == list->head){
		if(list->head->next == NULL){
			list->head = list->tail = NULL;
		}else{
			list->head = list->head->next;
		}
	}else{
		NodeUser *tmp = list->head;
		while(tmp != NULL && tmp->next != node){
			tmp = tmp->next;
		}
		if(tmp != NULL){
			tmp->next = node->next;
		}
	}
	free(node);

	fp = fopen("user.txt","w");
	memset(fp,0,sizeof(fp));

	InOrder(treeg->root);
	printf("\n");
	printf("请选择您要购买的书籍(书名)\n");
	scanf("%s",name);
	goodsnode = Find_Book_name_node(listg,name);
	if(goodsnode != NULL){
		printf("选购成功 !\n");
		Treenode->data->integral += goodsnode->data->integral;
	}
	UserToFile(Treenode->data);
	NodeUser *tmp2 = list->head;
	while(tmp2 != NULL){
		UserToFile(tmp2->data);
		tmp2 = tmp2->next;
	}
	fclose(fp);
	Free_Userlist(list->head);
	FreeTree_User(tree->root);
	FreeTree_Book(treeg->root);
	Free_Booklist(listg->head);

	return;
}



User *Input_User_Data(){
    system("clear");
    long int number;
    char password[50];
    char name[30];
    User *user = (User *)malloc(sizeof(User));
    user->integral = 0;
    printf("请输入你要注册的账户\n");
    scanf("%ld",&number);
    user->number = number;

    printf("请输入用户名\n");
    scanf("%s",name);
    strcpy(user->name,name);

    printf("请输入密码\n");
    scanf("%s",password);
    strcpy(user->password,password);
    
    printf("\n");
    printf("请按任意键返回\n");
    getchar();
    getchar();
    system("clear");


    return user;
}

TreeNode_User *Tree_Search_User(TreeNode_User *tree,long int number){
    TreeNode_User *ptr = tree;
    while(ptr){
        if ( ptr->data->number == number )  return(ptr);
        if (ptr->data->number > number )        ptr = ptr->left;
        else    ptr = ptr->right;
    }
    return NULL;
}

long int SignIn_User(){
    system("clear");
    long int number;
    char password[50];
    int sign1 = 1, sign2 = 1;
    Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
    TreeNode_User *node;
    tree->root = NULL;
    UserFromFile_Tree(tree);
    printf("请输入账号\n");
    scanf("%ld",&number);

    while(1){
        if(sign1 >= 3){
                printf("账号错误三次 !\n");
                printf("正在退出....\n");
                sleep(2);
                system("clear");
                return 0;
                
        }else if((node = Tree_Search_User(tree->root,number)) == NULL){
                printf("账号不存在 !\n");
                printf("请重新输入\n");
                scanf("%ld",&number);
                
                sign1++;
            
        }else{
            break;
        }
    }
    printf("请输入密码\n");
    scanf("%s",password);
    while(1){
        if(sign2 >= 3){
                printf("密码错误三次 !\n");
                printf("正在退出....\n");
                sleep(2);
                system("clear");
                return 0;
                
        }else if(strcmp(node->data->password,password)){
                printf("密码错误 !\n");
                printf("请重新输入\n");
                scanf("%s",password);

                sign2++;
        }else{
            break;
        }
    }
    FreeTree_User(tree->root);
    printf("\n");
    printf("正在登入.....\n");
    sleep(2);
    getchar();
    system("clear");

    return number;
}

void UserToFile(User *user){
    
    FILE *fp;
    fp = fopen("user.txt","a");
    if (fp != NULL){
            if(user->number == 0)       return;
            fprintf(fp, "%ld\t", user->number);
            fprintf(fp, "%s\t", user->password);
            fprintf(fp, "%s\t", user->name);
            fprintf(fp, "%d\t", user->integral);


        fclose(fp);
    }else{
        printf("文件保存失败 ！\n");
    }
    return;
}

void xiangqing(){

	printf("______________________________________________________________________________________________\n");
    printf("1.九九新：无笔记、书角无窝折、上下封皮及书脊有及其细微的使用痕迹\n");
    printf("______________________________________________________________________________________________\n");
    printf("2.九五新：无笔记、书角有摩擦痕迹、有少量折页无窝角、有使用痕迹\n");
    printf("______________________________________________________________________________________________\n");
    printf("3.良品：有少量划线或标注、少量文字笔记、附件缺失、轻度折痕、轻度老化/霉斑、书脊轻度磨损\n");
    printf("       上下封皮轻度磨损、有亮膜、\n");
    printf("——————————————————————————————————————————————————————————————————————————————————————————————\n");
    printf("4.中品：有大量划线或标注、少量文字笔记、有折页、少量窝角、有霉斑、老化、印刷质量有问题但\n");
    printf("       不影响阅读、封皮有破损不影响阅读、有变形有磨损、有胶带有标签、轻度污渍不影响阅读\n");
    printf("——————————————————————————————————————————————————————————————————————————————————————————————\n");
    printf("5.拒绝：盗版、缺页、严重老化、笔记过多影响阅读、含有印章-贴纸-标签等、有大量窝角、大面积破损、\n");
    printf("       严重变形、缺外封皮、胶带粘黏、书页无法翻开、严重污渍\n");
    
    printf("——————————————————————————————————————————————————————————————————————————————————————————————\n");

}

void User_Menu(User *user){
    char flag;
    int sign = 0;
    TreeNode_User *node;
    Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
    tree->root = NULL;

    while(1){
        printf("欢迎您: %s\n",user->name );
        printf("1.选购书籍\n");
        printf("2.查看书籍\n");
        printf("3.我要卖书\n");
        printf("4.书籍查询\n");
        printf("5.积分查询\n");
        printf("6.返回上层\n");
        flag = getchar();
        switch(flag){

 			case '1':	Recharge_User(user->number);
 						printf("\n");
 						getchar();
						printf("请按任意键返回\n");
						getchar();
						system("clear");
						break;
			case '2':	Book_MenuCheck();
						break;

			case '3':	Book_MenuAdd();
						user->integral += 1;
						break;
			case '4':	getchar();
						Seek_Menu();
						getchar();
						break;

			case '5':	system("clear");
						UserFromFile_Tree(tree);
						node = Tree_Search_User(tree->root,user->number);
						printf("您的账号有: %d 积分\n",node->data->integral );
						printf("\n");
						getchar();
						printf("请按任意键返回\n");
						getchar();
						FreeTree_User(tree->root);
						tree->root = NULL;
						system("clear");
						break;

            case '6':   FreeTree_User(tree->root);
                        system("clear");

                        return;
        }
        
    }
    return;
}


void SignIn_User_Menu(){
    system("clear");
    char flag;
    long int number;
    User *user = (User *)malloc(sizeof(User));
    User *user1;
    Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
    TreeNode_User *node;
    tree->root = NULL;
    UserFromFile_Tree(tree);
    while(1){
        printf("1.登入\n");
        printf("2.注册\n");
        printf("3.退出\n");
        flag = getchar();
        switch(flag){
            case '1':   UserFromFile_Tree(tree);
                        if((number = SignIn_User(user)) != 0){
                            node = Tree_Search_User(tree->root,number);
                            User_Menu(node->data);
                            
                        }
                        FreeTree_User(tree->root);
                        tree->root = NULL;
                        getchar();
                        break;
            case '2':   user1 = Input_User_Data();
                        UserToFile(user1);
                        FreeTree_User(tree->root);
                        tree->root = NULL;
                        break;
            case '3':   free(user);
                        FreeTree_User(tree->root);
                        system("clear");
                        
                        return;
        }
    }


    return;
}


