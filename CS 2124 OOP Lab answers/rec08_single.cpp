/*
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);
    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);
    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);
    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

//Course Functions
Course::Course(const string& courseName) : name(courseName) {}

ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if(rhs.students.size() != 0) {
        for(size_t index = 0; index < rhs.students.size(); ++index) {
            os << rhs.students[index] -> getName() << " ";
        }
    } else {
        os << "No Students";
    }
    return os;
}

const string& Course::getName() const { return name; }

bool Course::addStudent(Student* studentPtr) {
    for(size_t index = 0; index < students.size(); ++index) {
        if(students[index] == studentPtr) {
            return false;
        }
    }
    students.push_back(studentPtr);
    return true;
}

void Course::removeStudentsFromCourse() {
    students.clear();
}

//Student Functions
Student::Student(const string& name) : name(name) {}

ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if(rhs.courses.size() != 0) {
        for(size_t index = 0; index < rhs.courses.size(); ++index) {
            os << rhs.courses[index]->getName() << " ";
        }
    } else {
        os << "No Courses";
    }
    return os;
}

const string& Student::getName() const { return name; }

bool Student::addCourse(Course* coursePtr) {
    for(size_t index = 0; index < courses.size(); ++index) {
        if(courses[index] == coursePtr) {
            return false;
        }
    }
    courses.push_back(coursePtr);
    return true;
}

void Student::removedFromCourse(Course* coursePtr) {
    size_t temp = courses.size();
    for(size_t index = 0; index < courses.size(); ++index) {
        if(courses[index] == coursePtr) {
            temp = index;
        }
    }
    if(temp == courses.size()-1) {
        courses.pop_back();
    } else {
        for(size_t index = temp; index < courses.size() -1; ++index) {
            courses[index] = courses[index+1];
        }
        courses.pop_back();
    }
}

//Registrar Function
Registrar::Registrar(){}

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report" << endl;
    os << "Courses:" << endl;
    for(size_t index = 0; index < rhs.courses.size(); ++index) {
        os << *(rhs.courses[index]) << endl;
    }
    os << "Students:" << endl;
    for (size_t index = 0; index < rhs.students.size(); ++index) {
        os << *(rhs.students[index]) << endl;
    }
    return os;
}

bool Registrar::addCourse(const string& course) {
    size_t target_index = findCourse(course);
    if(target_index ==  courses.size()) {
        Course* coursePtr = new Course(course);
        courses.push_back(coursePtr);
        return true;
    }
    return false;
}

bool Registrar::addStudent(const string& student) {
    size_t target_index = findStudent(student);
    if (target_index == students.size()) {
        Student* studentPtr = new Student(student);
        students.push_back(studentPtr);
        return true;
    }
    return false;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    size_t student_index = findStudent(studentName);
    size_t course_index = findCourse(courseName);
    if(student_index != students.size() && course_index != courses.size()) {
        students[student_index] ->addCourse(courses[course_index]);
        courses[course_index] ->addStudent(students[student_index]);
        return true;
    }
    return false;
}

bool Registrar::cancelCourse(const string& courseName) {
    size_t course_index = findCourse(courseName);
    if(course_index != courses.size()) {
        if (course_index == courses.size() - 1) {
            courses.pop_back();
            return true;
        } else {
            for (size_t index = course_index; index < courses.size() - 1; ++index) {
                courses[index] = courses[index + 1];
            }
            courses.pop_back();
            return true;
        }
    }
    return false;
}

void Registrar::purge() {
    for(size_t index = 0; index < courses.size(); ++index) {
        delete courses[index];
    }
    courses.clear();
    for(size_t index = 0; index < students.size(); ++index) {
        delete students[index];
    }
    students.clear();
}

size_t Registrar::findStudent(const string& student) const {
    for(size_t index = 0; index < students.size(); ++index) {
        if(students[index] ->getName() == student) {
            return index;
        }
    }
    return students.size();
}

size_t Registrar::findCourse(const string& course) const {
    for(size_t index = 0; index < courses.size(); ++index) {
        if(courses[index] ->getName() == course) {
            return index;
        }
    }
    return courses.size();
}


