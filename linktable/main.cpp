//不带头链表
#include<iostream>
#include"linktable.h"

int main()
{
    linknode **head1 = new linknode*;//必须手动初始化以后才能代入函数，实际上是分配了一个由head指向的空间，保存结构指针*head
    linktable link(head1);/*
    linknode **head2 = new linknode*;//必须手动初始化以后才能代入函数，实际上是分配了一个由head指向的空间，保存结构指针*head
    linktable link1(head2);
    link.display();
    link1.display();
    linktable *link2 = link.simplemerge(link1);
    link2->display();*/

    cout<<" ********1.display\n ********2.reverse\n ********3.insertnode\n ********4.deletenode\n ********5.query\n";
    int opcode;
    while(cin>>opcode)
    {
       if (opcode ==1)
            link.display();
       else if (opcode ==2)
            link.reverselink();
       else if (opcode ==3)
	   {
			linktype number;
			int local;
			cout << "localization:   :  ";
			cin >> local;
			cout<<"please input your insert number: ";
			cin>>number;
			while(local>link.get())
			{
				cout << "please reset localization as guide:  ";
				cin >> local;
			}
            link.insertnode(local,number);
	   }
	   else if (opcode == 4)
	   {
		   int local;
		   cout << "input a delete localization:  (not bigger than " <<link.get() - 1 << ")  ";
		   cin >> local;
		   while (local >= link.get() || local <0)
		   {
			   cout << "please reset localization as guide:   ";
			   cin >> local;;
		   }
		   link.deletenode(local);
	   }   
	   else if (opcode == 5)
	   {
		   int local;
		   cout << "input auery localization:  (not bigger than " << link.get() - 1 << ")  ";
		   cin >> local;
		   while (local >= link.get() || local <0)
		   {
			   cout << "please reset localization as guide:   ";
			   cin >> local;
		   }
		   cout<<link.query_number(local);
	   }
    };
	system("pause");
    return 0;
}
