
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

struct node
{
    node *parent = nullptr;
    node *firstChild = nullptr;
    node *broSis = nullptr;
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
    if (p == NULL)
    {
        return NULL;
    }
    if (p->name == x)
    {
        return p;
    }
    node *result = find(x, p->firstChild);
    if (result != NULL)
    {
        return result;
    }
    return find(x, p->broSis);
}

// add functions
void addstart(string member)
{
    head->name = member;
    head->level = 0;
}
void add(string parent, string member, int level)
{
    node *p = new node();
    p = find(parent, head);
    cout << p->name << endl;
    node *child = new node();
    child->name = member;
    child->parent = p;
    child->level = level;
    if (p->firstChild == NULL)
    {
        p->firstChild = child;
    }
    else
    {
        p = p->firstChild;
        while (p->broSis != NULL)
        {
            p = p->broSis;
        }
        p->broSis = child;
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
    // int t_1 = 0;
    // int t_2 = 0;
    node *r_1 = new node();
    node *r_2 = new node();
    r_1 = find(x, head);
    r_2 = find(y, head);
    if (r_1->parent == r_2->parent)
    {
        return true;
    }
    else
    {
        return false;
    }
    // while (r_1->broSis != NULL)
    // {
    //     if (r_1->name == y)
    //     {
    //         t_1 = 1;
    //         break;
    //     }
    //     else
    //     {
    //         r_1 = r_1->broSis;
    //     }
    // }
    // while (r_2->broSis != NULL)
    // {
    //     if (r_2->name == y)
    //     {
    //         t_2 = 1;
    //         break;
    //     }
    //     else
    //     {
    //         r_2 = r_2->broSis;
    //     }
    // }
    // if (t_1 == 1 || t_2 == 1)
    // {
    //     return true;
    // }
    // if (t_1 == 0 && t_2 == 0)
    // {
    //     return false;
    // }
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

// farthest relationship of tree
vector<string> farthestRelation()
{
    // not yet
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
    cout << "Welcome to Family Tree!\n";
    while (true)
    {
        cout << "Choose appropriate number\n";
        cout << "1) Add a new member to tree\n";
        cout << "2) Remove a member from tree\n";
        cout << "3) Show size of tree\n";
        cout << "4) Check if A is parent of B\n";
        cout << "5) Check if A is sibling of B\n";
        cout << "6) Check if A has far relationship with B\n";
        cout << "7) Find same grandparent\n";
        cout << "8) Find farthest born of A\n";
        cout << "9) Find farthest relationship\n";
        cout << "10) Display tree\n";
        int command;
        cin >> command;
        switch (command)
        {
        case 1:
        {
            // if 1 --------> adding new node to tree
            string parent, name;
            int level;
            cout << "Enter parent, name, level: ";
            cin >> parent >> name >> level;
            if (parent == "null")
            {
                addstart(name);
            }
            else
            {
                add(parent, name, level);
            }
            break;
        }
        case 2:
        {
            // if 2 --------> delete a node from tree
            string name;
            cout << "Enter a name to delete: ";
            cin >> name;
            deleteMember(name);
            break;
        }
        case 3:
        {
            // if 3 --------> find size of the tree
            int counter = 0;
            cout << "The tree has " << size(counter, head) << " members" << endl;
            break;
        }
        case 4:
        {
            // if 4 --------> check if A is grandparent of B
            string parent, name;
            cout << "Enter parent and child name: ";
            cin >> parent >> name;
            if (isGrandParent(parent, name))
            {
                cout << "A is grandparent of B" << endl;
            }
            else
            {
                cout << "A is not grandparent of B" << endl;
                break;
            }
        }
        case 5:
        {
            // if 5 --------> check if A is sibling of B
            string firstName, secondName;
            cout << "Enter two names: ";
            cin >> firstName >> secondName;
            if (isbroSis(firstName, secondName))
            {
                cout << "They are siblings" << endl;
            }
            else
            {
                cout << "They are not siblings" << endl;
            }
            break;
        }
        case 6:
        {
            // if 6 --------> check if A has far relationship with B (they are not siblings or parent and child)
            string firstName, secondName;
            cout << "Enter two names: ";
            cin >> firstName >> secondName;
            if (distanRelation(firstName, secondName))
            {
                cout << "They have far relationship" << endl;
            }
            else
            {
                cout << "They dont have far relationship" << endl;
            }
            break;
        }
        case 7:
        {
            // if 7 --------> find same grandparent
            string firstName, secondName;
            cout << "Enter two names: ";
            cin >> firstName >> secondName;
            cout << firstName << " and " << secondName << " same parent is: " << findSameParent(firstName, secondName) << endl;
            break;
        }
        case 8:
        {
            // if 8 --------> find farthest born of A
            string name;
            cout << "Enter name: ";
            cin >> name;
            cout << "The farthest born of " << name << " is " << farthestBorn(name) << endl;
            break;
        }
        case 9:
        {
            // if 9 --------> find farthest relationship
            vector<string> names = farthestRelation();
            cout << names[0] << " and " << names[1] << " has farthest relationship in this tree" << endl;
            break;
        }
        case 10:
        {
            // if 10 -------> visualize tree using Java
            Encoder encoder = Encode(*(new Encoder(head)));
            string Output = encoder.GetFullOutput();
            Visualize("Graph", Output, true);
            break;
        }
        default:
            break;
        }
    }
    return 0;
}