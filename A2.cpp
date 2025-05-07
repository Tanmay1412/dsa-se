/*
🔘PROBLEM STATEMENT:-
Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining 
with/without replacement.
Data: Set of (key, value) pairs. Keys must be unique and comparable.
Operations: Insert(key, value), Find(key), Delete(key)
*/

#include <iostream>
#include <string.h>
using namespace std;

// Class for Hash Table implementation
class HashFunction
{
    typedef struct hash
    {
        long key;        // Telephone number
        char name[10];   // Client name
    } hash;

    hash h[10];  // Hash table of fixed size 10

public:
    HashFunction();         // Constructor
    void insert();          // Insert (key, value)
    void display();         // Display table
    int find(long);         // Find by key
    void Delete(long);      // Delete by key
};

// Constructor to initialize hash table with -1 keys and "NULL" names
HashFunction::HashFunction()
{
    for (int i = 0; i < 10; i++)
    {
        h[i].key = -1;
        strcpy(h[i].name, "NULL");
    }
}

// Delete key from the table
void HashFunction::Delete(long k)
{
    int index = find(k); // First find the key
    if (index == -1)
    {
        cout << "\n\tKey Not Found";
    }
    else
    {
        h[index].key = -1;                 // Mark key slot as empty
        strcpy(h[index].name, "NULL");
        cout << "\n\tKey is Deleted";
    }
}

// Find key in the table, return index or -1 if not found
int HashFunction::find(long k)
{
    for (int i = 0; i < 10; i++)
    {
        if (h[i].key == k)
        {
            cout << "\n\t" << h[i].key << " is Found at " << i << " Location With Name " << h[i].name;
            return i;
        }
    }
    return -1;  // Key not found
}

// Display the entire hash table
void HashFunction::display()
{
    cout << "\n\t\tKey\t\tName";
    for (int i = 0; i < 10; i++)
    {
        cout << "\n\th[" << i << "]\t" << h[i].key << "\t\t" << h[i].name;
    }
}

// Insert key-value pair using replacement technique
void HashFunction::insert()
{
    char ans, n[10], ntemp[10];
    long k, temp;
    int hi, cnt = 0, flag = 0, i;

    do
    {
        if (cnt >= 10)
        {
            cout << "\n\tHash Table is FULL";
            break;
        }

        cout << "\n\tEnter a Telephone No: ";
        cin >> k;
        cout << "\n\tEnter a Client Name: ";
        cin >> n;
        hi = k % 10; // Hash function to get index

        // If slot is empty, insert directly
        if (h[hi].key == -1)
        {
            h[hi].key = k;
            strcpy(h[hi].name, n);
        }
        else
        {
            // If collision and current key is not in its home position
            if (h[hi].key % 10 != hi)
            {
                // Replacement: swap old key with new key
                temp = h[hi].key;
                strcpy(ntemp, h[hi].name);
                h[hi].key = k;
                strcpy(h[hi].name, n);

                // Place displaced key into next available slot
                for (i = hi + 1; i < 10; i++)
                {
                    if (h[i].key == -1)
                    {
                        h[i].key = temp;
                        strcpy(h[i].name, ntemp);
                        flag = 1;
                        break;
                    }
                }
                for (i = 0; i < hi && flag == 0; i++) // Wrap around if needed
                {
                    if (h[i].key == -1)
                    {
                        h[i].key = temp;
                        strcpy(h[i].name, ntemp);
                        break;
                    }
                }
            }
            else
            {
                // Without replacement: just insert new key in next available slot
                for (i = hi + 1; i < 10; i++)
                {
                    if (h[i].key == -1)
                    {
                        h[i].key = k;
                        strcpy(h[i].name, n);
                        flag = 1;
                        break;
                    }
                }
                for (i = 0; i < hi && flag == 0; i++) // Wrap around
                {
                    if (h[i].key == -1)
                    {
                        h[i].key = k;
                        strcpy(h[i].name, n);
                        break;
                    }
                }
            }
        }

        flag = 0;  // Reset flag for next iteration
        cnt++;     // Increase count of inserted elements

        cout << "\n\t..... Do You Want to Insert More Key: y/n ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');
}

// Main menu
int main()
{
    long k;
    int ch, index;
    char ans;
    HashFunction obj;

    do
    {
        cout << "\n\t***** Telephone Book (Dictionary ADT) *****";
        cout << "\n\t1. Insert\n\t2. Display\n\t3. Find\n\t4. Delete\n\t5. Exit";
        cout << "\n\t..... Enter Your Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            obj.insert();
            break;
        case 2:
            obj.display();
            break;
        case 3:
            cout << "\n\tEnter a Key Which You Want to Search: ";
            cin >> k;
            index = obj.find(k);
            if (index == -1)
            {
                cout << "\n\tKey Not Found";
            }
            break;
        case 4:
            cout << "\n\tEnter a Key Which You Want to Delete: ";
            cin >> k;
            obj.Delete(k);
            break;
        case 5:
            cout << "\n\tExiting Program...";
            break;
        default:
            cout << "\n\tInvalid Choice!";
        }

        cout << "\n\t..... Do You Want to Continue in Main Menu: y/n ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    return 0;
}
