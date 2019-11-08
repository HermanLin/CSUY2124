/* 
    REGISTRAR SOURCE FILE
    Herman Lin
*/

#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {

    // ============================= //
    // Registrar Class Functionality //
    // ============================= //
    ostream& operator<<(ostream& os, const Registrar& rhs) {
        os << "Registrar's Report\n";
        os << "Courses:\n";
        for (Course* course : rhs.courses) {
            os << *course;
        }
        os << "Students:\n";
        for (Student* student : rhs.students) {
            os << *student;
        }
        return os;
    }

    Registrar::Registrar() {}

    bool Registrar::addCourse(const string& courseName) {
        if (findCourse(courseName) == courses.size()) {
            Course* newCourse = new Course(courseName);
            courses.push_back(newCourse);
            return true;
        }
        return false;
    }

    bool Registrar::addStudent(const string& studentName) {
        if (findStudent(studentName) == students.size()) {
            Student* newStudent = new Student(studentName);
            students.push_back(newStudent);
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);

        if (studentIndex == students.size()) {
            return false;
        }
        else if (courseIndex == courses.size()) {
            return false;
        }
        else {
            Student* student = students[studentIndex];
            Course* course = courses[courseIndex];
            student->addCourse(course);
            course->addStudent(student);
            return true;
        }
    }

    bool Registrar::cancelCourse(const string& courseName) {
        size_t courseIndex = findCourse(courseName);

        if (courseIndex != courses.size()) { 
            courses[courseIndex]->removeStudentsFromCourse();
            delete(courses[courseIndex]);
            for (size_t index = courseIndex; index < courses.size(); ++index) {
                courses[index] = courses[index + 1];
            }
            courses.pop_back();
            return true;
        }
        return false;
    }

    void Registrar::purge() {
        for (Course* course : courses) {
            delete(course);
        }
        courses.clear();
        for (Student* student : students) {
            delete(student);
        }
        students.clear();
    }

    size_t Registrar::findCourse(const string& courseName) const {
        for (size_t index = 0; index < courses.size(); ++index) {
            if (courses[index]->getName() == courseName) { return index; }
        }
        return courses.size();
    }

    size_t Registrar::findStudent(const string& studentName) const {
        for (size_t index = 0; index < students.size(); ++index) {
            if (students[index]->getName() == studentName) { return index; }
        }
        return students.size();
    }

}