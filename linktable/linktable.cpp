#include<iostream>
#include"linktable.h"

linktable::linktable()
{
    _size = 0;
    head = new linknode*;//实例化
    *head = NULL; 
}

linktable::linktable(linknode **_head)
{
	head = _head;
	_size = 0;

	linktype newdata;
	cout<<"please input numbers \n";
	linknode **p = head;//要想修改第一个节点，必须令p==head；
	while(1)//保证每次有新的数以后才分配节点。
	{
	    if(cin>>newdata)
        {
           *p = new linknode;
           (*p)->data = newdata;
           p= &((*p)->next);   //通过临时指针，将令P转移到指向下一个节点
           cout<<"please input next number\n";
           _size ++;
        }
        else
        {
            cin.clear();
            char temp = cin.get();
            if (temp == 'q')
                break;
            else
                cout<<"please input a 'number' ";
        };
	}
	*p = NULL;
};

linktable:: ~linktable()
{
    linknode *temp;
    linknode *p = *head;
    for(int i=0;i<_size;i++)
    {
        temp = p->next;
        delete p;
        p = temp;
    }
};

/*void init(linknode **head) 需要对头节点进行检测
{
	linktype newdata;
	cout<<"please input numbers \n";
	if(cin>>newdata)              //因为*head永远被head指着，所以不能带入迭代
	{
		linknode *p = new linknode;
		*head = p;
		 p -> data = newdata;
		 cout<<"please input next number\n";
		while(cin>>newdata)//这样需要保证保证每次有新的数以后才分配节点。即循环开始前应该是一条完整地链
		{
		   linknode *temp = new linknode;

		   p->next = temp;
		   p = temp;
		   p->data = newdata;
		   cout<<"please input next number\n";
		}
		p->next = NULL;
	}
}*/

void linktable::display()const
{
	linknode *p;
	p=*head;
	cout<<"----------show linknode"<<endl;
	while(p)
	{
		cout<<p->data<<" ";
		p = p->next;
	}
	cout<<endl<<"----------length of linknode :  " <<_size<<endl;
};


linktype linktable::query_number(int local)const
{
	linknode *temp =*head; //temp指向第0个节点
	if (local >= _size || local < 0)
	{
		cout << "query localization shoule not bigger than " << _size - 1 << ")  ";
		return NULL;
	}
	else
	{
		for (int i = 0; i < local; i++)//0到local一共local+1个节点，每次循环指向下一个节点，所以需要local次
		{
			temp = (*temp).next;
		}
		return temp->data;
	}
}

void linktable::reverselink()
{
	linknode *bac;
	linknode *midd;
	linknode *fron;

	fron = *head;  //标记前两个节点
	midd = fron->next;
	fron->next = NULL;

	while(midd)
	{
	 bac = midd->next;
	 midd->next = fron;
	 fron = midd;
	 midd = bac;
	}
	*head = fron;
}

void linktable::insertnode(int local, linktype number)
{
	if (local>_size)
	{
		cout << "insert localization shoule not bigger than " << _size  << ")  ";
		return;
	}

	linknode *p = new linknode;
	p-> data= number;
	
	linknode **fron = head;  //利用二重指针避开边界特殊化处理
	for(int i=0;i<local;i++)  //fron表示第i个节点（因为fron是第i个节点next的地址。）
	{
		fron=&((*fron)->next); //fron存放下一个节点指针的地址。
	}
	p-> next = *fron;    //*fron是下一个节点的指针
	*fron = p;

	_size++;
}
/*
int linktable::deletenode()//左闭右闭,这样无法释放删除节点的空间，会导致内存溢出。
{
	int lo,hi;
	cout<<"input delete localation RANGE:  (not bigger than "<<_size<<")  ";
	cin>>lo>>hi;
	if(hi>=_size || lo<0 || lo>hi)
	{
		return -1;
	}
	else
	{
		linknode **fron = head;
		for(int i=0;i<lo;i++)
		{
			fron=&((*fron)->next);//fron ==lo的上一节点
		}
		linknode *tail = *fron; //tail 从lo节点开始
		for(int i=lo;i<hi;i++)
		{
			tail = tail->next;
		}
		*fron = tail->next;
	}
	_size =_size-(hi-lo+1);
}
*/

int linktable::get()const
{
	return _size;
}

void linktable::deletenode(int local)
{
	if (local >= _size || local < 0)
	{
		cout << "delete localization shoule not bigger than " << _size - 1 << ")  ";
		return;
	}
    linknode **fron = head;
    linknode *temp;
    for(int i=1;i<local;i++)
    {
        fron=&((*fron)->next);//fron是产出节点的上一节点
    }
    temp = *fron;
    (*fron) = (*fron)->next;
    delete temp;
    _size--;
}
/*
linktable linktable::simplemerge(const linktable &t)const //将下一个链表插入到当前链表后方
{
    linktable newlink; //声明新链表,不会被旧链表的delete析构掉 //局部变量，函数结束后自行析构。
    linknode **newlk = newlink.head;  //指向新链表的二重指针
	newlink._size = _size + t._size;  //重新赋值_size；

    linknode *lk1 = *head;
    for(int i=0;i<_size;i++)//每一次循环都将lk1指向下一个节点。循环前指向第一个节点，所以循环n次后指向第n+1个节点。
    {
        linknode *temp =new linknode;//给下一个节点分配空间
        *newlk = temp;              //*newlk表示下一节点的指针。!!!!!!错位，非成员函数不能修改newlink。应该调用newlink的插入函数！！！！！

        (*newlk)->data = lk1->data;
        newlk = &((*newlk)-> next); //newlk表示当前节点。

        lk1 = lk1->next;
    }

    linknode *lk2 = *t.head;
    for(int i=0;i<t._size;i++)//每一次循环都指向下一个节点，要得到最后第n个节点，所以要循环n-1次。
    {
        linknode *temp =new linknode;//给下一个节点分配空间
        *newlk = temp;

        (*newlk)->data = lk2->data;
        newlk = &((*newlk)-> next); //newlk表示当前节点。

        lk2 = lk2->next;
    }
    *newlk = NULL;
    return newlink;//调用复制构造函数。
}
*/

linktable* linktable::simplemerge(const linktable &t)const //将下一个链表插入到当前链表后方
{
	linktable *newlink =new linktable(); //声明新链表,为了不被旧链表的delete析构掉 ,动态分配内存。
	linknode **newlk = newlink->head;  //声明指向新链表头的二重指针

	linknode *lk1 = *head;
	for (int i = 0; i<_size; i++)//每一次循环都将一个元素插入，所以循环n次。
	{
		newlink->insertnode(i,lk1->data);
		lk1 = lk1->next;
	}

	linknode *lk2 = *t.head;
	for (int i = 0; i<t._size; i++)//
	{
		newlink->insertnode(_size+i, lk2->data);
		lk2 = lk2->next;
	}
	//return newlink;//返回的实际是一个指针，当函数结束的那一刻，这个指针所指向的内容就全部被修改了。
	return newlink; //必须用new来动态分配内存才能保留.
}