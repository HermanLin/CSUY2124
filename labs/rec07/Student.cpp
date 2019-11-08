/* 
    STUDENT SOURCE FILE 
    Herman Lin
*/

#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {

    // =========================== //
    // Student Class Functionality //
    // =========================== //
    ostream& operator<<(ostream& os, const Student& rhs) {
        os << rhs.name << ": ";
        if (rhs.courses.size() != 0) {
            for (Course* course : rhs.courses) {
                os << course->getName() << " ";
            }
        }
        else { os << "No Courses"; }
        os << endl;
        return os;
    }

    Student::Student(const string& name) : name(name) {}

    const string& Student::getName() const { return name; }

    bool Student::addCourse(Course* newCourse) {
        for (size_t index = 0; index < courses.size(); ++index) {
            if (courses[index]->getName() == newCourse->getName()) {
                return false;
            }
        }
        courses.push_back(newCourse);
        return true;
    }

    void Student::removedFromCourse(Course* courseName) {
        size_t indexOfCourse;
        for (size_t index = 0; index < courses.size(); ++index) {
            if (courses[index]->getName() == courseName->getName()) {
                indexOfCourse = index;
                break;
            }
        }
        for (size_t index = indexOfCourse; index < courses.size(); ++index) {
            courses[index] = courses[index + 1];
        }
        courses.pop_back();
    }

}