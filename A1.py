# 🔘PROBLEM STATEMENT:-
# Telephone book database of N clients using a hash table.
# Use linear and quadratic probing for collision handling and compare them using number of comparisons.

# Take input from the user for size of hash table
size = int(input("Enter size of Hash Table: "))

# Initialize two hash tables for both probing techniques
array1 = [None] * size  # For Linear Probing
array2 = [None] * size  # For Quadratic Probing

# Function to insert using Linear Probing
def insert_LinearProbing(data):
    i = 0
    count = 1  # To count comparisons
    value = (data + i) % size
    while array1[value] is not None:
        i += 1
        value = (data + i) % size
        count += 1
    array1[value] = data
    display_LinearProbing()
    print("Number of comparisons (Linear Probing):", count)

# Function to insert using Quadratic Probing
def insert_QuadraticProbing(data):
    i = 0
    count = 1
    value = (data + i * i) % size
    while array2[value] is not None:
        if count > 2 * size:
            print("Oops, Index Not Found...")
            return
        i += 1
        value = (data + i * i) % size
        count += 1
    array2[value] = data
    display_QuadraticProbing()
    print("Number of comparisons (Quadratic Probing):", count)

# Function to display hash table with Linear Probing
def display_LinearProbing():
    print("Hash Table using Linear Probing:")
    print(array1)

# Function to display hash table with Quadratic Probing
def display_QuadraticProbing():
    print("Hash Table using Quadratic Probing:")
    print(array2)

# Function to search data using Linear Probing
def search_Linear(data):
    i = 0
    count = 1
    value = (data + i) % size
    while array1[value] is not None:
        if array1[value] == data:
            print("Telephone number found (Linear Probing).")
            print("Number of comparisons:", count)
            return
        i += 1
        value = (data + i) % size
        count += 1
        if count > 2 * size:
            break
    print("Telephone number not found (Linear Probing).")
    print("Number of comparisons:", count)

# Function to search data using Quadratic Probing
def search_Quadratic(data):
    i = 0
    count = 1
    value = (data + i * i) % size
    while array2[value] is not None:
        if array2[value] == data:
            print("Telephone number found (Quadratic Probing).")
            print("Number of comparisons:", count)
            return
        i += 1
        value = (data + i * i) % size
        count += 1
        if count > 2 * size:
            break
    print("Telephone number not found (Quadratic Probing).")
    print("Number of comparisons:", count)

# Main program loop
while True:
    print("\n1. Insert    2. Search    3. Exit")
    choice = int(input("Enter Choice: "))

    if choice == 1:
        data1 = int(input("Enter Telephone Number: "))
        print()
        insert_LinearProbing(data1)
        insert_QuadraticProbing(data1)

    elif choice == 2:
        data1 = int(input("Enter Telephone Number to Search: "))
        print()
        search_Linear(data1)
        search_Quadratic(data1)

    elif choice == 3:
        print("Exiting Program.")
        break

    else:
        print("Invalid Choice. Please select from the menu.")
