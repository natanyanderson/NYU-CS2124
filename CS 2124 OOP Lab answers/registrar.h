//
// registrar.h
// rec08
// Created by Natanya Anderson on 3/15/24.
//


#ifndef REC08_REGISTRAR_H
#define REC08_REGISTRAR_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Course;
    class Student;

    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();
        // Creates a new course, if none with that name
        bool addCourse(const std::string&);
        // Creates a new student, if none with that name
        bool addStudent(const std::string&);
        // If the student and the course exist, then enroll the student.
        bool enrollStudentInCourse(const std::string& studentName,
                                   const std::string& courseName);
        // Unenroll the students from the course and remove the course
        // from the Registrar.
        bool cancelCourse(const std::string& courseName);
        // Get rid of everything!!!
        void purge();

    private:
        size_t findStudent(const std::string&) const;
        size_t findCourse(const std::string&) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}



#endif //REC08_REGISTRAR_H

