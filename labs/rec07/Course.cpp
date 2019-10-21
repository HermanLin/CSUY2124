/* 
    COURSE SOURCE FILE 
    Herman Lin
*/

#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
    
    // ========================== //
    // Course Class Functionality //
    // ========================== //
    ostream& operator<<(ostream& os, const Course& rhs) {
        os << rhs.name << ": ";
        if (rhs.students.size() != 0) {
            for (Student* student : rhs.students) {
                os << student->getName() << " ";
            }
        }
        else { os << "No Students"; }
        os << endl;
        return os;
    }

    Course::Course(const string& courseName) : name(courseName) {}

    const string& Course::getName() const { return name; }

    bool Course::addStudent(Student* newStudent) {
        for (size_t index = 0; index < students.size(); ++index) {
            if (students[index]->getName() == newStudent->getName()) {
                return false;
            }
        }
        students.push_back(newStudent);
        return true;
    }

    void Course::removeStudentsFromCourse() {
        for (Student* student : students) {
            student->removedFromCourse(this);
        }
        students.clear();
    }
    
}
