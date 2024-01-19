#include <iostream>
using namespace std;

struct node
{
    node* children;
    node* brosis;
    int name;
};
node* head = new node();

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