#include <iostream>
#include <vector>

using namespace std;

//Task 1

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages) : numberOfpages(numPages) {}
    virtual void displayNumPages() const = 0;
private:
    unsigned numberOfpages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numberOfpages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages) : PrintedMaterial(numPages) {}
    void displayNumPages() const {
        PrintedMaterial::displayNumPages();
    }
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages) : PrintedMaterial(numPages) {}
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndexPages) : Book(numPages), numOfIndexPages(numIndexPages) {}
    void displayNumPages() const {
        cout << "Pages: " << endl;
        PrintedMaterial::displayNumPages();
        cout << "Index pages: " << endl;
        cout << numOfIndexPages << endl;
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages) : Book(numPages) {}
    void displayNumPages() const {
        PrintedMaterial::displayNumPages();
    }
private:
};


//void displayNumberOfPages(const PrintedMaterial& anyPm) {
    //anyPm.displayNumPages();
//}

// tester/modeler code
int main() {
    TextBook text(5430, 30);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n" << endl;

    /*
    PrintedMaterial pm(2345);
    pm.displayNumPages();

    pm = text;
    pm.displayNumPages();

    PrintedMaterial* pmPtr;
    pmPtr = &text;

    pmPtr->displayNumPages();

    //displayNumberOfPages(mag);
    //displayNumberOfPages(novel);
    //displayNumberOfPages(text);
    */

    vector<PrintedMaterial*> Prints;
    Prints.push_back(&text);
    Prints.push_back(&novel);
    Prints.push_back(&mag);
    for(size_t index = 0; index < Prints.size(); ++index) {
        Prints[index] -> displayNumPages();
        cout << endl;
    }
    cout << "===========\n";
    for (const PrintedMaterial* pmPtr : Prints) {
        pmPtr->displayNumPages();
        cout << endl;
    }
}

