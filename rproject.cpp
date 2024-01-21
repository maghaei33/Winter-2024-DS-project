
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node
{
    node *parent;
    node *firstChild;
    node *broSis;
    string name;
};
node *head = new node();

node *find(string x, node *p);
bool isGrandParent(string x, string y);
bool isBroSis(string x, string y);

vector<string> parent_1;
vector<string> parent_2;

// size function
int size(int t, node *p)
{
    if (p->firstChild != NULL && p->broSis == NULL)
    {
        t++;
        size(t, p->firstChild);
    }
    if (p->firstChild == NULL && p->broSis != NULL)
    {
        t++;
        size(t, p->broSis);
    }
    if (p->firstChild == NULL && p->broSis == NULL)
    {
        t++;
        t++;
        size(t, p->firstChild);
        size(t, p->broSis);
    }
    return t;
}

// delete function
void deleteMember(string x)
{
    node *p = new node();
    p = find(x, head);
    if (p->parent->firstChild == p)
    {
        if (p->broSis != NULL)
        {
            p->parent->firstChild = p->broSis;
        }
        else
        {
            p->parent->firstChild = NULL;
        }
    }
    if (p->parent->broSis == p)
    {
        if (p->broSis != NULL)
        {
            p->parent->broSis = p->broSis;
        }
        else
        {
            p->parent->broSis = NULL;
        }
    }
}

// find finction
node *find(string x, node *p)
{
    if (p->name == x)
    {
        return p;
    }
    else
    {
        if (p->firstChild != NULL && p->broSis == NULL)
        {
            find(x, p->firstChild);
        }
        if (p->firstChild == NULL && p->broSis != NULL)
        {
            find(x, p->broSis);
        }
        if (p->firstChild != NULL && p->broSis != NULL)
        {
            find(x, p->broSis);
            find(x, p->firstChild);
        }
    }
}

// add function
void addstart(string member)
{
    head->name = member;
}
void add(string parent, string member, node *p)
{
    if (p->name == parent)
    {
        node *child = new node();
        child->name = member;
        child->parent = p;
        if (p->firstChild == NULL)
        {
            p->firstChild = child;
        }
        else
        {
            while (p->broSis != NULL)
            {
                p = p->broSis;
            }
            p->broSis = child;
        }
    }
    else
    {
        if (p->firstChild != NULL && p->broSis == NULL)
        {
            add(parent, member, p->firstChild);
        }
        if (p->firstChild == NULL && p->broSis != NULL)
        {
            add(parent, member, p->broSis);
        }
        if (p->firstChild != NULL && p->broSis != NULL)
        {
            add(parent, member, p->broSis);
            add(parent, member, p->firstChild);
        }
    }
}

// isGrandParent function
bool isGrandParent(string x, string y)
{
    node *k = new node();
    k = find(y, head);
    if (isBroSis(x, y) == true)
    {
        return false;
    }
    else
    {
        while (k->parent != NULL)
        {
            if (k->parent->name == x)
            {
                return true;
                break;
            }
            else
            {
                k = k->parent;
            }
        }
        if (k->parent == NULL)
        {
            return false;
        }
    }
}

// isBroSis function
bool isBroSis(string x, string y)
{
    int t_1 = 0;
    int t_2 = 0;
    node *r_1 = new node();
    node *r_2 = new node();
    r_1 = find(x, head);
    r_2 = find(y, head);
    while (r_1->broSis != NULL)
    {
        if (r_1->name == y)
        {
            t_1 = 1;
            break;
        }
        else
        {
            r_1 = r_1->broSis;
        }
    }
    while (r_2->broSis != NULL)
    {
        if (r_2->name == y)
        {
            t_2 = 1;
            break;
        }
        else
        {
            r_2 = r_2->broSis;
        }
    }
    if (t_1 == 1 || t_2 == 1)
    {
        return true;
    }
    if (t_1 == 0 && t_2 == 0)
    {
        return false;
    }
}

// distanRelation function
bool distanRelation(string x, string y)
{
    if (isGrandParent(x, y) == false && isBroSis(x, y) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// findSameParent function
string findSameParent(string x, string y)
{
    node *r_1 = new node();
    node *r_2 = new node();
    r_1 = find(x, head);
    r_2 = find(y, head);
    if (isBroSis(x, y) == true)
    {
    }
    if (isGrandParent(x, y) == true)
    {
    }
}

// farthestBorn function
int farthestBorn(string name)
{
    int count = 0;
    node *parent = new node();
    parent = find(name, head);
    node *child = parent->firstChild;
    while (child != NULL)
    {
        count++;
        child = child->firstChild;
    }
    return count;
}

int main()
{
    while (true)
    {
        cout << "Welcome to Family Tree!\n";
        cout << "Choose appropriate number\n";
        cout << "1) Add a new member to tree\n";
        cout << "2) Remove a member from tree\n";
        int command;
        cin >> command;
    }
    return 0;
}