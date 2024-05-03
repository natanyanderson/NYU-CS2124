/*
  rec14.cpp
  Natanya Anderson
*/

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;


// Node type for the linked list
struct Node {
    int data = 0;
    Node* next = nullptr;
};

// Node type for the binary tree
struct TNode {
    int data = 0;
    TNode* left = nullptr;
    TNode* mid = nullptr;
    TNode* right = nullptr;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);
//
// Your functions go here
//
//   Task 1 function:
Node* listSum (const Node* lst1, const Node* lst2) {
    if (!lst1 && !lst2) {
        return nullptr; //Base case
    }
    Node* curr = new Node(); // Create a new node with default initialization
    if (lst1) {
        curr->data += lst1->data; // Add data from lst1 if it is not null
        lst1 = lst1->next; // Move to the next element in lst1
    }
    if (lst2) {
        curr->data += lst2->data; // Add data from lst2 if it is not null
        lst2 = lst2->next; // Move to the next element in lst2
    }
    curr->next = listSum(lst1, lst2); // Recursive call for the next elements in the lists
    return curr;
}
//   Task 2 function:
//treeMax
int treeMax(TNode* root){
    if (root == nullptr){
        throw invalid_argument("Root is nullptr");
    }
    int max_val = root->data;
    if (root->left != nullptr) {
        max_val = max(max_val, treeMax(root->left));
    }
    if (root->mid != nullptr) {
        max_val = max(max_val, treeMax(root->mid));
    }
    if (root->right != nullptr) {
        max_val = max(max_val, treeMax(root->right));
    }
    return max_val; // Return the maximum value found
}

//   Task 3 function:
//palindrome
bool palindrome(char s[], int length) {
    if (length <= 1) {
        return true;
    } else {
        if (s[0] == s[length-1]) {
            return palindrome(++s, length-2);
        } else {
            return false;
        }
    }
}
//   Task 4 function:
//parity
bool parity(int num) {
    if (num == 0) {
        return true;
    } else if (num == 1) {
        return false;
    } else {
        int digit = num % 2;
        if (digit == 0) {
            return parity((num )/2);
        } else {
            return !parity((num)/2);
        }
    }
}
//   Task 5 function:
int towers(int n, char start, char goal, char spare){
    if (n == 0){
        return 0;
    } else {
        return 1 + towers(n-1, start, spare, goal) + towers(n-1, spare, goal, start);
    }
}
//Task 6
void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}

int main() {
    // We have provided some test code to save you time. Certainly fee
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);

    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);


    cout << "\n==============\n"
    << "#2) Testing treeMax\n";
    // Task 2:
    TNode a{1}, b{2}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
    cout << "treeMax(&f): " << treeMax(&f) << endl;

    //How do you keep this from crashing? try/catch! Here in main!
    try {
        cout << treeMax(nullptr) << endl;
    } catch (const invalid_argument& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    // Task 3:
    cout << "\n==============\n"
    << "#3) Testing palindrome\n";
    cout << boolalpha
        << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
        << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
        << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
        << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;

    // Task 4:
    cout << "\n==============\n"
    << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }
//
//
//
    // Task 5:
    cout << "\n==============\n"
    << "#5) How many moves are required for various sized towers?\n";
    for (int i = 1; i < 30; ++i) {
        cout << "towers(" << i << ", 'a', 'b', 'c'): " << towers(i, 'a', 'b', 'c') << endl;
    }
    cout << "\n==============\n"
    << "#6) Testing mystery\n";
    //Task 6
    mystery(1);
    mystery(2);
    mystery(3);
    mystery(4);
}

//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}
// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}
// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
    result = new Node{vals[index-1], result};
    }
    return result;
}

