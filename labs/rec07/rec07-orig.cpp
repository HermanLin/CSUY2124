/*
  rec07 
  Herman Lin

  Starter Code for required functionality
  Yes, you may add other methods.
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
    Course(const string&);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string&);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
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