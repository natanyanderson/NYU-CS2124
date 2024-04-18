/*
 * Natanya Anderson
 * rec05.cpp
 * Section C, Feb 25, 2024
 * Students grades lab
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Section {
    friend ostream& operator<< (ostream& stream, const Section& section){
        stream << "Section: " << section.name << ", Time slot: " << section.timeSlot << ", Students: ";
        if (section.students.size() == 0) {
            stream << "None" << endl;
        } else {
            stream << endl;
            for(size_t index = 0; index < section.students.size(); ++index){
                stream << *(section.students[index]) << endl;
            }
        }
        return stream;
    }
    class StudentRecord {
        friend ostream& operator<< (ostream& stream, const StudentRecord studentRecord){
            stream << "Name: " << studentRecord.name << ", Grades:";
            for (size_t index = 0; index < studentRecord.grades.size(); ++index){
                stream << ' ' << studentRecord.grades[index];
            }
            return stream;
        }
    private:
        string name;
        vector<int> grades;
    public:
        StudentRecord(const string& studentName) : name(studentName), grades(14, -1) {}
        string getName() const {return name;}

        void setGrade(int score, int week){
            grades[week-1] = score;
        }
    };
    class TimeSlot {
        friend ostream& operator<< (ostream& stream, const TimeSlot& time){
            stream << "[Day: " << time.date << ", Start time: " ;
            if (time.hour <= 12){
                stream << time.hour << "am]";
            } else {
                stream << time.hour - 12 << "pm]";
            }
            return stream;
        }
    private:
        string date;
        int hour;
    public:
        TimeSlot(const string& day, int& hour): date(day), hour(hour) {}
    };

public:
    Section(const string& name, const string& date, int hour) : name(name), timeSlot(date, hour) {};
    void addStudent(const string& studentName){
        StudentRecord* student_report = new StudentRecord(studentName);
        students.push_back(student_report);
    }

    void setStudentGrade(const string& name, int score, int week){
        size_t hashsize = students.size();
        for (size_t index = 0; index < students.size(); ++index)
            if (students[index]->getName() == name){
                hashsize = index;
            }
        students[hashsize]->setGrade(score,week);
    }

    ~Section() {
        cout << "Section " << name << " is being deleted" << endl;
        for (size_t index = 0; index < students.size(); ++index){
            cout << "Deleting " << students[index]->getName() << endl;
            delete students[index];
        }
        students.clear();
    }

    Section(Section& section): name(section.name), timeSlot(section.timeSlot){
        for (size_t index = 0; index < section.students.size(); ++index){
            StudentRecord* new_record = new StudentRecord(*(section.students[index]));
            students.push_back(new_record);
        }
    }

private:
    string name;
    vector<StudentRecord*> students;
    TimeSlot timeSlot;
};

class Labworker {
    friend ostream& operator<< (ostream& stream, const Labworker& worker){
        if (worker.section == nullptr){
            stream << worker.name << "does not have a section";
        } else {
            stream << worker.name << "has " << *worker.section;
        }
        return stream;
    }
private:
    string name;
    Section* section;
public:
    Labworker(const string& workerName) : name(workerName), section(nullptr) {}
    void addSection(Section& sec){
        section = &sec;
    }
    void addGrade(const string& name, int score, int week){
        section -> setStudentGrade(name, score, week);
    }
};
// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    Labworker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;


    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    Labworker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
    << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
    << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
}