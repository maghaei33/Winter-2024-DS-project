#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct node
{
    node* bigchild;
    node* brosis;
    string name;
};
node* head = new node();

vector <string> father;
vector <string>child;
vector <node>id;

void start(string member)
{
    head->name=member;
}
void isnodehere (string x , node* p , int t)
{
    if(p->name==x)
    {
        t=1;
    }
    else
    {
        if(p->bigchild!=NULL && p->brosis==NULL)
        {
            isnodehere(x, p->bigchild , t);
        }
        if(p->bigchild==NULL && p->brosis!=NULL)
        {
            isnodehere(x, p->brosis , t);
        }
        if(p->bigchild!=NULL && p->brosis!=NULL)
        {
            isnodehere(x, p->brosis , t);
            isnodehere(x, p->bigchild , t);  
        }
    }
    
}
node* foundnode(string x , node* p)
{
    if(p->name==x)
    {
        return p;
    }
    else
    {
        if(p->bigchild!=NULL && p->brosis==NULL)
        {
            foundnode(x, p->bigchild);
        }
        if(p->bigchild==NULL && p->brosis!=NULL)
        {
            foundnode(x, p->brosis);
        }
        if(p->bigchild!=NULL && p->brosis!=NULL)
        {
            foundnode(x, p->brosis);
            foundnode(x, p->bigchild);  
        }


    }
}
void addmember(string father,string member , node* p)
{
    if(p->name==father)
    {
        node* child = new node();
        child->name=member;
        if(p->bigchild==NULL)
        {
            p->bigchild=child;
        }
        else
        {
            while(p->brosis!=NULL)
            {
                p=p->brosis;
            }
            p->brosis=child;
        }
    }
    else
    {
        if(p->bigchild!=NULL && p->brosis==NULL)
        {
            addmember(father, member, p->brosis);
        }
        if(p->bigchild==NULL && p->brosis!=NULL)
        {
            addmember(father, member, p->bigchild);
        }
        if(p->bigchild!=NULL && p->brosis!=NULL)
        {
            addmember(father, member, p->brosis);
            addmember(father, member, p->bigchild);  
        }

    }

}
void removemember (string member , node* p)
{

}

//A function
bool isxgrandparent (string x , string y , int t , node* p)
{
    //if();
}
int main()
{
    while(true)
    {
        cout<<"Welcome to Family Tree!\n";
        cout << "Choose appropriate number\n";
        cout<<"1) Add a new member to tree\n";
        cout<<"2) Remove a member from tree\n";
        int t;
        cin >> t;
    }
    return 0;
}