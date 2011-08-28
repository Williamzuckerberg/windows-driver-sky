//文件名:Linktype.h 
typedef struct _DATA_LINK
{
/*链域，*llink是左链域指针，*rlink是右链域指针*/
//struct _DATA_LINK *L;
//struct _DATA_LINK *R;
LIST_ENTRY Entry;
// struct _DATA_LINK *Head;
int data; /*数据域*/
int data2;
}DATA_LINK,*PDATA_LINK; 

//LIST_ENTRY My_List; //自定义链接头 
 

PDATA_LINK head;//=new(PagedPool) DATA_LINK;
PDATA_LINK	pData;
VOID Link_Init() 
{ 
	KdPrint(("\n-----------SYS模式 双向循环链表测试 初始化--------     \n"));
	head=new(PagedPool) DATA_LINK;
	//初始化链表
	//head->L=head->R=head;
	//head->Entry.Blink=head->Entry.Flink=&head->Entry;
	InitializeListHead(&head->Entry);
	 head->data=0;
	 head->data2=0;
    DbgPrint("head=%x\n",head);
	//PDATA_LINK Tlink;
	 
	//在链表中插入5个元素
	DbgPrint(("开始构建链表 \n"));
	for (int i=1 ; i<=5 ; i++)
	{
	  pData =new(PagedPool) DATA_LINK;  
	   pData->data = i;
	   pData->data2= i+1;
	   InsertHeadList(&head->Entry,&pData->Entry);
	   /*
	   //
	   Tlink=head->R;//保存后续结点
	   Tlink->L=pData;
	   head->R=pData;
	   //
	   pData->R=Tlink;
	   pData->L=head;
	  */
	   //  DbgPrint("Node%d=%x,R=%x,L=%x,%d,%d\n",
	   //	pData->data-7,pData,pData->R,pData->L,pData->data,pData->data2);	 
	}
	
	//从链表中取出，并显示
	DbgPrint("head=%x\n",head);
	
    PDATA_LINK pnode=head;
   	do   //判断 R遍历完成否
	{
		
		//显示链表内存结构
		DbgPrint("结点%d=%x,R=%x,L=%x,%d,%d\n",
			pnode->data,pnode,pnode->Entry.Flink,pnode->Entry.Blink,pnode->data,pnode->data2);
		pnode=(PDATA_LINK)pnode->Entry.Blink; 
	} while (!(pnode==head));
	
}

VOID Link_Delete()
{
	KdPrint(("\n-----------SYS模式 双向循环链表测试 删除节点--------     \n"));
	RemoveHeadList(&head->Entry);
	PDATA_LINK pnode=head;
	do   //判断 R遍历完成否
	{

		//显示链表内存结构
		DbgPrint("结点%d=%x,R=%x,L=%x,%d,%d\n",
			pnode->data,pnode,pnode->Entry.Flink,pnode->Entry.Blink,pnode->data,pnode->data2);
		pnode=(PDATA_LINK)pnode->Entry.Blink; 
	} while (!(pnode==head));
}