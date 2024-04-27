// rec13.cpp
//Natanya Anderson

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

//Task 9
void print_list(const list<int>& values_list) {
    for (list<int>::const_iterator iter = values_list.begin(); iter!=values_list.end(); ++iter) {
        cout << *iter << " ";
    }
}
//Task 10
void ranged_print_list(const list<int>& values_list) {
    for (int val : values_list) {
        cout << val << " ";
    }
}
//Task 11
void print_list_alternating(const list<int>& values_list) {
    for(auto iter = values_list.begin(); iter!=values_list.end();iter++,iter++) {
        cout << *iter << " ";
    }
}
//Task 12
list<int>::const_iterator find_item(const list<int>& values_list, int value) {
    for (list<int>::const_iterator iter = values_list.begin(); iter!=values_list.end(); iter++) {
        if (value == *iter) {
            return iter;
        }
    }
    return values_list.end();
}

//Task 13
auto find_item_auto(const list<int>& values_list, int value) {
    for (auto iter = values_list.begin(); iter!=values_list.end(); iter++) {
        if (value == *iter) {
            return iter;
        }
    }
    return values_list.end();
}
//Task 15
bool is_even(int num) {return num % 2 == 0;}
//Task 16
class is_even_functor {
public:
    bool operator() (int num) const {
        return num % 2 == 0;
    }
};
//Task 19
list<int>::iterator ourFind(list<int>::iterator begin, list<int>::iterator end, int num) {
    cout << "Running ourFind function" << endl;
    for (list<int>::iterator iter=begin; iter!=end; iter++) {
        if (*iter == num) {
            return iter;
        }
    }
    return end;
}
//Task 20
template <typename T, typename U>
T ourFind(T begin, T end, U num) {
    cout << "Running ourFind template" << endl;
    for (T iter = begin; iter != end; iter++) {
        if (*iter == num) {
            return iter;
        }
    }
    return end;
}

int main() {
// 1. Create a vector with some values and display using ranged for
cout << "Task 1:\n";
vector<int> values = {1,2,4,6,3,5};
for (int val : values) {
    cout << val << " ";
}
cout << "\n=======\n";

// 2. Initalize a list as a copy of values from the vector
cout << "Task 2:\n";
list<int> values_list(values.begin(), values.end());
for (int val : values_list) {
    cout << val << " ";
}
cout << "\n=======\n";

// 3. Sort the original vector.  Display both the vector and the list
cout << "Task 3:\n";
sort(values.begin(), values.end());
for (int sorted_val : values) {
    cout << sorted_val << " ";
}
cout << "\n";
for (int sorted_val : values_list) {
    cout << sorted_val << " ";
}
cout << "\n=======\n";

// 4. print every other element of the vector.
cout << "Task 4:\n";

for (size_t index = 0; index < values.size(); index+=2) {
    cout << values[index] << " ";
}
cout << "\n=======\n";

// 5. Attempt to print every other element of the list using the
//    same technique.
cout << "Task 5:\n";

//for (size_t index = 0; index < values_list.size(); index+=2) {
//    cout << values_list[index] << " "; //list<int> doesn't support bracket operator
//}

cout << "\n=======\n";

//
// Iterators
//

// 6. Repeat task 4 using iterators.  Do not use auto;
cout << "Task 6:\n";
for (vector<int>::iterator iter = values.begin(); iter<values.end(); iter+=2) {
    cout << *iter << " ";
}

cout << "\n=======\n";

// 7. Repeat the previous task using the list.  Again, do not use auto.
//    Note that you cannot use the same simple mechanism to bump
//    the iterator as in task 6.
cout << "Task 7:\n";
for (list<int>::iterator iter = values_list.begin(); iter!=values_list.end(); iter++,iter++) {
    cout << *iter << " ";
}

cout << "\n=======\n";

// 8. Sorting a list
cout << "Task 8:\n";
values_list.sort();
for (int sorted_val : values_list) {
    cout << sorted_val << " ";
}


cout << "\n=======\n";

// 9. Calling the function to print the list
cout << "Task 9:\n";

print_list(values_list);

cout << "\n=======\n";

// 10. Calling the function that prints the list, using ranged-for
cout << "Task 10:\n";

ranged_print_list(values_list);

cout << "\n=======\n";

//
// Auto
//

// 11. Calling the function that, using auto, prints alterate
// items in the list
cout << "Task 11:\n";

print_list_alternating(values_list);

cout << "\n=======\n";


// 12.  Write a function find that takes a list and value to search for.
//      What should we return if not found
cout << "Task 12:\n";

if (find_item(values_list, 3) == values_list.end()) {
    cout << "Num not found" << endl;
} else {
    cout << *find_item(values_list, 3) << endl;
}

if (find_item(values_list, 20) == values_list.end()) {
cout << "Num not found" << endl;
} else {
    cout << *find_item(values_list, 20) << endl;
}

cout << "=======\n";

// 13.  Write a function find that takes a list and value to search for.
//      What should we return if not found
cout << "Task 13:\n";

if (find_item_auto(values_list, 3) == values_list.end()) {
cout << "Num not found" << endl;
} else {
cout << *find_item_auto(values_list, 3) << endl;
}

if (find_item_auto(values_list, 20) == values_list.end()) {
cout << "Num not found" << endl;
} else {
cout << *find_item_auto(values_list, 20) << endl;
}



cout << "=======\n";

//
// Generic Algorithms
//

// 14. Generic algorithms: find
cout << "Task 14:\n";
list<int>::iterator iter = find(values_list.begin(), values_list.end(), 3);
if (iter == values_list.end()) {
    cout << "Num not Found" << endl;
} else {
    cout << *iter << endl;
}
list<int>::iterator iter2 = find(values_list.begin(), values_list.end(), 20);
if (iter2 == values_list.end()) {
cout << "Num not Found" << endl;
} else {
cout << *iter2 << endl;
}

cout << "=======\n";

// 15. Generic algorithms: find_if
cout << "Task 15:\n";

list<int>::iterator iter15 = find_if(values_list.begin(), values_list.end(), is_even);
if (iter15 != values_list.end()) {
    cout << "The first even number is: " << *iter15 << endl;
} else {
    cout << "No even number in the list" << endl;
}


cout << "=======\n";

// 16. Functor
cout << "Task 16:\n";

list<int>::iterator iter16 = find_if(values_list.begin(), values_list.end(), is_even_functor());
if (iter16 != values_list.end()) {
    cout << "The first even number is: " << *iter16 << endl;
} else {
    cout << "No even number in the list" << endl;
}

cout << "=======\n";

// 17. Lambda
cout << "Task 17:\n";
list<int>::iterator iter17 = find_if(values_list.begin(), values_list.end(), [](int num)->bool {return num % 2 == 0;});
if (iter17 != values_list.end()) {
    cout << "The first even number is: " << *iter16 << endl;
} else {
    cout << "No even number in the list" << endl;
}

cout << "=======\n";

// 18. Generic algorithms: copy to an array
cout << "Task 18:\n";
int* arr = new int[6];
copy(values_list.begin(), values_list.end(), arr);
for (size_t index = 0; index < 6; ++index) {
    cout << arr[index] << " ";
}
delete[] arr;
cout << "\n=======\n";

//
// Templated Functions
//

// 19. Implement find as a function for lists
cout << "Task 19:\n";
list<int>::iterator iter19 = ourFind(values_list.begin(), values_list.end(), 3);
if (iter19 == values_list.end()) {
    cout << "Num not found" << endl;
} else {
    cout << *iter19 << endl;
}

list<int>::iterator iter19_2 = ourFind(values_list.begin(), values_list.end(), 20);
if (iter19_2 == values_list.end()) {
cout << "Num not found" << endl;
} else {
cout << *iter19_2 << endl;
}

cout << "=======\n";

// 20. Implement find as a templated function
cout << "Task 20:\n";
vector<int>::iterator iter20 = ourFind(values.begin(), values.end(), 3);
if (iter20 == values.end()) {
    cout << "Num not found" << endl;
} else {
    cout << *iter20 << endl;
}

vector<int>::iterator iter20_2 = ourFind(values.begin(), values.end(), 20);
if (iter20_2 == values.end()) {
cout << "Num not found" << endl;
} else {
cout << *iter20_2 << endl;
}
cout << "=======\n";

//
// Associative collections
//

// 21. Using a vector of strings, print a line showing the number
//     of distinct words and the words themselves.
cout << "Task 21:\n";
ifstream ifs("pooh-nopunc.txt");
if (!ifs) {
    cerr << "Could not open file" << endl;
    exit(1);
}
vector<string>words;
string word;
while (ifs >> word) {
    vector<string>::iterator iter = find(words.begin(), words.end(), word);
    if (iter == words.end()) {
        words.push_back(word);
    }
}
cout << "The number of distinct words are: " << words.size() << endl;

cout << "\n=======\n";

// 22. Repeating previous step, but using the set
cout << "Task 22:\n";
ifs.clear();
ifs.seekg(0, ios::beg);

set<string> words_set;
while (ifs >> word) {
    words_set.insert(word);
}
cout << "The number of distinct words: " << words_set.size() << endl;

cout << "=======\n";

// 23. Word co-occurence using map
cout << "Task 23:\n";
ifs.clear();
ifs.seekg(0, ios::beg);

map<string, vector<int>> wordMap;
int index = 1;
while (ifs >> word) {
    wordMap[word].push_back(index);
    index++;
}

for (auto pair : wordMap) {
    cout << pair.first << " position: ";
    for (int num : pair.second) {
        cout << num << " ";
    }
}
cout << "=======\n";
ifs.close();
}