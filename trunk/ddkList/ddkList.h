//�ļ���:Linktype.h 
typedef struct _DATA_LINK
{
/*����*llink��������ָ�룬*rlink��������ָ��*/
//struct _DATA_LINK *L;
//struct _DATA_LINK *R;
LIST_ENTRY Entry;
// struct _DATA_LINK *Head;
int data; /*������*/
int data2;
}DATA_LINK,*PDATA_LINK; 

//LIST_ENTRY My_List; //�Զ�������ͷ 
 

PDATA_LINK head;//=new(PagedPool) DATA_LINK;
PDATA_LINK	pData;
VOID Link_Init() 
{ 
	KdPrint(("\n-----------SYSģʽ ˫��ѭ��������� ��ʼ��--------     \n"));
	head=new(PagedPool) DATA_LINK;
	//��ʼ������
	//head->L=head->R=head;
	//head->Entry.Blink=head->Entry.Flink=&head->Entry;
	InitializeListHead(&head->Entry);
	 head->data=0;
	 head->data2=0;
    DbgPrint("head=%x\n",head);
	//PDATA_LINK Tlink;
	 
	//�������в���5��Ԫ��
	DbgPrint(("��ʼ�������� \n"));
	for (int i=1 ; i<=5 ; i++)
	{
	  pData =new(PagedPool) DATA_LINK;  
	   pData->data = i;
	   pData->data2= i+1;
	   InsertHeadList(&head->Entry,&pData->Entry);
	   /*
	   //
	   Tlink=head->R;//����������
	   Tlink->L=pData;
	   head->R=pData;
	   //
	   pData->R=Tlink;
	   pData->L=head;
	  */
	   //  DbgPrint("Node%d=%x,R=%x,L=%x,%d,%d\n",
	   //	pData->data-7,pData,pData->R,pData->L,pData->data,pData->data2);	 
	}
	
	//��������ȡ��������ʾ
	DbgPrint("head=%x\n",head);
	
    PDATA_LINK pnode=head;
   	do   //�ж� R������ɷ�
	{
		
		//��ʾ�����ڴ�ṹ
		DbgPrint("���%d=%x,R=%x,L=%x,%d,%d\n",
			pnode->data,pnode,pnode->Entry.Flink,pnode->Entry.Blink,pnode->data,pnode->data2);
		pnode=(PDATA_LINK)pnode->Entry.Blink; 
	} while (!(pnode==head));
	
}

VOID Link_Delete()
{
	KdPrint(("\n-----------SYSģʽ ˫��ѭ��������� ɾ���ڵ�--------     \n"));
	RemoveHeadList(&head->Entry);
	PDATA_LINK pnode=head;
	do   //�ж� R������ɷ�
	{

		//��ʾ�����ڴ�ṹ
		DbgPrint("���%d=%x,R=%x,L=%x,%d,%d\n",
			pnode->data,pnode,pnode->Entry.Flink,pnode->Entry.Blink,pnode->data,pnode->data2);
		pnode=(PDATA_LINK)pnode->Entry.Blink; 
	} while (!(pnode==head));
}