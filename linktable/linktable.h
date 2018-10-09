#include<typeinfo>
typedef  int linktype;
using namespace std;

struct linknode
{
    linktype data;
    linknode *next;
};

class linktable
{
    private:
        linknode **head;
        int _size;

    public:
        linktable();
        linktable(linknode **_head);
        ~linktable();
        void display()const;
        void reverselink();
        void insertnode(int local, linktype number);
        void deletenode(int local);
        linktable* simplemerge(const linktable &t)const;
		linktype query_number(int local)const;
		int get()const;
};
