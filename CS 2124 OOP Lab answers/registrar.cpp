//
// registrar.cpp
// rec08
// Created by Natanya Anderson on 3/15/24.
//

#include "course.h"
#include "student.h"
#include "registrar.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
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

}