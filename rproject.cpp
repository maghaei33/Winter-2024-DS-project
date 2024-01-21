
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct node
{
    node* father;
    node* bigchild;
    node* brosis;
    string name;
};
node* head = new node();

node* find(string x, node* p);
bool isxgrandparent (string x , string y);
bool isbrosisxy(string x , string y);

vector <string> father1;
vector <string> father2;

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
    p = find(x , head);
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

//A function
bool isxgrandparent (string x , string y)
{
    node* k=new node();
    k = find(y,head);
    if(isbrosisxy(x , y)==true)
    {
        return false;
    }
    else
    {
        while(k->father!=NULL)
        {
            if(k->father->name==x)
            {
                return true;
                break;
            }
            else
            {
                k = k->father;
            }
        }
        if(k->father==NULL)
        {
            return false;
        }
    }
}
//B function
bool isbrosisxy (string x , string y )
{
    int t1=0;
    int t2=0;
    node* r1 = new node();
    node* r2 = new node();
    r1 = find(x,head);
    r2 = find(y,head);
    while(r1->brosis!=NULL)
    {
        if(r1->name==y)
        {
            t1=1;
            break;
        }
        else
        {
            r1=r1->brosis;
        }

    }
    while(r2->brosis!=NULL)
    {
        if(r2->name==y)
        {
            t2=1;
            break;
        }
        else
        {
            r2=r2->brosis;
        }

    }
    if(t1==1 || t2==1)
    {
        return true;
    }
    if (t1==0 && t2==0)
    {
        return false;
    }

}

//C function
bool longrel (string x , string y)
{
    if (isxgrandparent(x,y)==false && isbrosisxy(x,y)==false)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
//D function
string findsameparent(string x, string y)
{
    node* r1= new node();
    node* r2 = new node();
    r1 = find(x , head);
    r2 = find(y , head);
    if(isbrosisxy(x,y)==true)
    {

    }
    if(isxgrandparent(x,y)==true)
    {
        
    }

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