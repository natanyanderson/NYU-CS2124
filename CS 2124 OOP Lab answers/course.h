//
// course.h
// rec08
// Created by Natanya Anderson on 3/15/24.
//

#ifndef REC08_COURSE_H
#define REC08_COURSE_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Student;

    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        // Course methods needed by Registrar
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student*);
        // Tell the students that they are no longer in the course
        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student*> students;
    };

}
#endif //REC08_COURSE_H
