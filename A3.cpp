#include <iostream>
#include <string>
using namespace std;

// Structure for each node in the general tree
struct node
{
    string label;           // Label (title of book/chapter/section)
    int ch_count;           // Number of children (chapters/sections/subsections)
    struct node *child[10]; // Array of child pointers (max 10 children)
} * root; // Global root pointer

// General Tree class
class GT
{
public:
    GT()
    {
        root = NULL;
    }

    void create_tree();          // Function to create the tree
    void display(node *r1);      // Function to display the tree
};

// Create tree structure: Book → Chapters → Sections
void GT::create_tree()
{
    int tchapters;
    root = new node; // Allocate memory for book root

    // Input book title
    cout << "Enter name of book : ";
    cin.ignore(); // Flush newline character from input buffer
    getline(cin, root->label);

    // Input number of chapters
    cout << "Enter number of chapters in book : ";
    cin >> tchapters;
    root->ch_count = tchapters;

    // Loop to enter each chapter
    for (int i = 0; i < tchapters; i++)
    {
        root->child[i] = new node;
        cout << "Enter the name of Chapter " << i + 1 << " : ";
        cin.ignore(); // Flush newline
        getline(cin, root->child[i]->label);

        // Input number of sections in this chapter
        cout << "Enter number of sections in Chapter " << root->child[i]->label << " : ";
        cin >> root->child[i]->ch_count;

        // Loop to enter each section
        for (int j = 0; j < root->child[i]->ch_count; j++)
        {
            root->child[i]->child[j] = new node;
            cout << "Enter Name of Section " << j + 1 << " : ";
            cin.ignore(); // Flush newline
            getline(cin, root->child[i]->child[j]->label);
        }
    }
}

// Display the tree in hierarchical format
void GT::display(node *r1)
{
    if (r1 != NULL)
    {
        cout << "\n----- Book Hierarchy -----";
        cout << "\nBook Title: " << r1->label;

        // Display chapters and their sections
        for (int i = 0; i < r1->ch_count; i++)
        {
            cout << "\n  Chapter " << i + 1 << ": " << r1->child[i]->label;
            cout << "\n    Sections:";

            for (int j = 0; j < r1->child[i]->ch_count; j++)
            {
                cout << "\n      - " << r1->child[i]->child[j]->label;
            }
        }
    }
    cout << endl;
}

// Main function with menu
int main()
{
    int choice;
    GT gt;

    while (1)
    {
        cout << "\n-----------------------------" << endl;
        cout << "       Book Tree Menu        " << endl;
        cout << "-----------------------------" << endl;
        cout << "1. Create Book Structure" << endl;
        cout << "2. Display Book Structure" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            gt.create_tree();
            break; // 🛠️ FIXED: Prevent fall-through
        case 2:
            gt.display(root);
            break;
        case 3:
            cout << "Thanks for using this program!" << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
