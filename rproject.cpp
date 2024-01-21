
#include<iostream>
#include<string>

using namespace std;

struct node
{
    node* father;
    node* bigchild;
    node* brosis;
    string name;
};
node* head = new node();

//size function
int size(int t , node* p)
{
    if(p->bigchild!=NULL && p->brosis==NULL)
    {
        t++;
        size(t,p->bigchild);
    }
    if(p->bigchild==NULL && p->brosis!=NULL)
    {
        t++;
        size(t,p->brosis); 
    }
    if(p->bigchild==NULL && p->brosis==NULL)
    {
        t++;
        t++;
        size(t,p->bigchild);
        size(t,p->brosis); 
    }
    return t;
}

//delete function
void deleten (string x)
{
    node* p=new node();
    p = find(x,head);
    if(p->father->bigchild==p)
    {
        if(p->brosis!=NULL)
        {
            p->father->bigchild = p->brosis;
        }
        else
        {
            p->father->bigchild=NULL;
        }

    }
    if(p->father->brosis==p)
    {
        if(p->brosis!=NULL)
        {
            p->father->brosis = p->brosis;
        }
        else
        {
            p->father->brosis=NULL;
        }

    }

}
//find finction
node* find(string x , node* p)
{
    if(p->name==x)
    {
        return p;
    }
    else
    {
        if(p->bigchild!=NULL && p->brosis==NULL)
        {
            find(x, p->bigchild);
        }
        if(p->bigchild==NULL && p->brosis!=NULL)
        {
            find(x, p->brosis);
        }
        if(p->bigchild!=NULL && p->brosis!=NULL)
        {
            find(x, p->brosis);
            find(x, p->bigchild);  
        }
    }
}
//add function
void addstart(string member)
{
    head->name=member;
}
void add(string father,string member , node* p)
{
    if(p->name==father)
    {
        node* child = new node();
        child->name=member;
        child->father=p;
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
            add(father, member, p->bigchild);
        }
        if(p->bigchild==NULL && p->brosis!=NULL)
        {
            add(father, member, p->brosis);
        }
        if(p->bigchild!=NULL && p->brosis!=NULL)
        {
            add(father, member, p->brosis);
            add(father, member, p->bigchild);  
        }

    }

}

//continue

void inhertitence (string x , node* p , int t)
{
    if(p->name==x)
    {
        t=1;
    }
    else
    {
        if(p->bigchild!=NULL && p->brosis==NULL)
        {
            inhertitence(x, p->bigchild , t);
        }
        if(p->bigchild==NULL && p->brosis!=NULL)
        {
            inhertitence(x, p->brosis , t);
        }
        if(p->bigchild!=NULL && p->brosis!=NULL)
        {
            inhertitence(x, p->brosis , t);
            inhertitence(x, p->bigchild , t);  
        }
    }
    
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