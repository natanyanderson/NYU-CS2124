//
// rec08
// student.cpp
// Created by Natanya Anderson on 3/15/24.
//


#include "student.h"
#include "registrar.h"
#include "course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
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
}
