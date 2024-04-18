//
// rec08
// course.cpp
// Created by Natanya Anderson on 3/15/24.
//
#include "course.h"
#include "student.h"
using namespace std;

namespace BrooklynPoly {
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
}