//
// rec08
// student.h
// Created by Natanya Anderson on 3/15/24.
//

#ifndef REC08_STUDENT_H
#define REC08_STUDENT_H

#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly {
    class Course;

    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const std::string& name);
        const std::string& getName() const;
        bool addCourse(Course*);
        // Student method needed by Course::removeStudentsFromCourse
        void removedFromCourse(Course*);

    private:
        std::string name;
        std::vector<Course*> courses;
    };

}
#endif //REC08_STUDENT_H
