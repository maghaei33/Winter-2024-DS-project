
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

struct node
{
    node *parent;
    node *firstChild;
    node *broSis;
    string name;
    int level;
};

node *head = new node();

node *find(string x, node *p);
bool isGrandParent(string x, string y);
bool isbroSis(string x, string y);

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

// add functions
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
    if (isbroSis(x, y) == true)
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

// isbroSis function
bool isbroSis(string x, string y)
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
    if (isGrandParent(x, y) == false && isbroSis(x, y) == false)
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
    node *a = find(x, head);
    node *b = find(y, head);
    if (a->level > b->level)
    {
        while (a->level != b->level)
        {
            a = a->parent;
        }
    }
    else if (a->level < b->level)
    {
        while (b->level != a->level)
        {
            b = b->parent;
        }
    }
    else
    {
        while (a != b)
        {
            a = a->parent;
            b = b->parent;
        }
        return a->name;
    }
}

// farthestBorn function
int farthestBorn(string name)
{
    // later
}

int getChildCount(node *n)
{
    if (n == nullptr || n->firstChild == nullptr)
        return 0;
    int count = 1;
    node *temp = n->firstChild;
    while (temp->broSis != nullptr)
    {
        count++;
        temp = temp->broSis;
    }
    return count;
}

int getRowLength(node *n, int layerNum)
{
    // layerNum++;
    int Result = 0;
    if (layerNum > 0)
    {
        if (n->firstChild != nullptr)
            return getRowLength(n->firstChild, layerNum - 1);

        while (n->broSis != nullptr)
        {
            n = n->broSis;
            if (n->firstChild != nullptr)
                return getRowLength(n->firstChild, layerNum - 1);
        }
        return 0;
    }
    else
    {
        Result = 1;
        while (n->broSis != nullptr)
        {
            n = n->broSis;
            Result++;
        }
        return Result;
    }
}

int getNextRowChildCount(node *n)
{
    int layerCount = 1;

    if (n == nullptr)
    {
        cout << "getNextRowChildCount(): n is null!" << endl; // error
        return 0;
    }

    while (n->parent != nullptr)
    {
        n = n->parent;
        layerCount++;
    }

    int result = getRowLength(n, layerCount);
    return result;
}

int getNextRowWidth(node *n)
{
    if (n->parent == nullptr)
        return getChildCount(n);
    n = n->parent;
    return getNextRowChildCount(n);
}

bool LastChildInRow(node *n)
{
    bool result = true;
    if (n->parent == nullptr)
        return true;
    node *current = n->parent;

    while (current->broSis != nullptr)
    {
        current = current->broSis;
        if (current->firstChild != nullptr)
        {
            result = false;
            break;
        }
    }

    return result;
}

struct Encoder
{
public:
    // Properties
    node *currnetNode = head;
    string Output;
    int length = 0; // Generation Count

    // Seprate from Recrusion
    vector<int> rowWidth;

    // Const Variables
    const string layerSign = "$";
    const string childSign = "#";

    Encoder(node *current, string output = "", int len = 0)
    {
        this->currnetNode = current;
        this->Output = output;
        this->length = len;
    }

    Encoder operator=(const Encoder &e)
    {
        return *new Encoder(e.currnetNode, e.Output, e.length);
    }

    Encoder MoveToFirstChild()
    {
        this->currnetNode = this->currnetNode->firstChild;
        return *this;
    }

    Encoder MoveToBroSis()
    {
        this->currnetNode = this->currnetNode->broSis;
        return *this;
    }

    Encoder MoveToParent()
    {
        this->currnetNode = this->currnetNode->parent;
        return *this;
    }

    string GetFullOutput()
    {
        string sizeData = to_string(this->length) + ' ';

        for (int i = 0; i < this->length; i++)
            sizeData += to_string(this->rowWidth[i]) + ' ';

        return sizeData + this->Output;
    }
};

Encoder EncodeNextRowChilds(Encoder &encoder);

Encoder Encode(Encoder &encoder)
{
    // null Case
    if (encoder.currnetNode == nullptr)
        return encoder;

    // Adding First Line for parent
    if (encoder.currnetNode == head)
    {
        encoder.length++;
        encoder.rowWidth.push_back(1); // Width of First Row
        encoder.Output += encoder.layerSign + to_string(encoder.length) + ' ';
    }

    // Adding Current Value
    encoder.Output += encoder.currnetNode->name + ' ' + encoder.childSign + to_string(getChildCount(encoder.currnetNode)) + ' ';

    // Passing Encoder to Next
    if (encoder.currnetNode->parent == nullptr) // parent Case
    {
        // Setting Up Next Line
        encoder.Output += encoder.layerSign + to_string(encoder.length) + ' ';
        // encoder.rowWidth.push_back(getNextRowWidth(encoder.currnetNode));
        encoder.MoveToFirstChild();
        Encode(encoder);
    }
    // If there are more Siblings Continue Encoding
    else if (encoder.currnetNode->broSis != nullptr)
    {
        encoder.MoveToBroSis();
        Encode(encoder);
    }
    // Only Go to Next Row if Current Node is the Last Child
    else if (getNextRowWidth(encoder.currnetNode) > 0 &&
             LastChildInRow(encoder.currnetNode) &&
             encoder.currnetNode->parent != nullptr)
    {
        encoder.MoveToParent();
        EncodeNextRowChilds(encoder);
    }

    return encoder;
}

Encoder EncodeNextRowChilds(Encoder &encoder) // Takes the Current Row's parent Encoder
{
    // Adding New Line Sign
    encoder.length++;
    encoder.Output += encoder.layerSign + to_string(encoder.length) + ' ';

    // Adding Current Row Length to RowWidth List
    encoder.rowWidth.push_back(getNextRowChildCount(encoder.currnetNode));

    // Checking Big Child
    encoder = encoder.MoveToFirstChild();
    if (encoder.currnetNode->firstChild != nullptr)
    {
        encoder.MoveToFirstChild();
        Encode(encoder);
    }

    // Checking Other Childs
    while (encoder.currnetNode->broSis != nullptr)
    {
        encoder = encoder.MoveToBroSis();
        if (encoder.currnetNode->firstChild != nullptr)
        {
            encoder.MoveToFirstChild();
            Encode(encoder);
        }
        if (encoder.currnetNode == nullptr)
            return encoder;
    }

    return encoder;
}

void Visualize(string className, string params, bool Compile = true)
{
    if (Compile)
    {
        string compileCommand = "javac " + className + ".java";
        char cCommand[500];
        strcpy_s(cCommand, compileCommand.c_str());
        system(cCommand);
    }

    string command = "java " + className + ' ' + params;
    char cmd[500];
    strcpy_s(cmd, command.c_str());
    system(cmd);
}

int main()
{
    node *ali = new node();
    node *mehdi = new node();
    head->parent = nullptr;
    head->name = "Alireza";
    head->level = 1;
    head->broSis = nullptr;
    ali->parent = head;
    ali->broSis = nullptr;
    ali->name = "ali";
    ali->level = 2;
    head->firstChild = ali;
    mehdi->parent = ali;
    mehdi->broSis = nullptr;
    mehdi->name = "mehdi";
    mehdi->level = 3;
    ali->firstChild = mehdi;
    Encoder encoder = Encode(*(new Encoder(head)));
    string Output = encoder.GetFullOutput();
    Visualize("Graph", Output, true);
    // while (true)
    // {
    //     cout << "Welcome to Family Tree!\n";
    //     cout << "Choose appropriate number\n";
    //     cout << "1) Add a new member to tree\n";
    //     cout << "2) Remove a member from tree\n";
    //     int command;
    //     cin >> command;
    // }
    return 0;
}