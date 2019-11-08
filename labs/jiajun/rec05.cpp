/*
  rec05.cpp
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Section
{
public:
	Section(string section_name, string day, int time) : _section(section_name), current_time(day, time) {}


	//deconstructor
	~Section() { 
		cout << "Section " << _section << " is currently being deleted" << endl;
		for (size_t i = 0; i < student_records.size(); i++) {
			cout << "Deleting " << student_records[i]->getName() << endl;
			delete student_records[i];
			student_records[i] = nullptr;
		}
	}

	//copy constructor
	Section(const Section& section_copy) : _section(section_copy._section), current_time(section_copy.current_time), student_records(section_copy.student_records) {
		for (size_t i = 0; i < student_records.size(); i++) {
			student_records[i] = new Record(*section_copy.student_records[i]);
		}
	}

	//assingment operator
	Section& operator= (const Section& rhs) {
		if (this != &rhs) {
			for (size_t i = 0; i < student_records.size(); i++) {
				delete student_records[i];
				student_records[i] = new Record(*rhs.student_records[i]);
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Section& current_section) {
		os << "Section: " << current_section._section << " " << current_section.current_time;
		if (current_section.student_records.size() == 0) {
			os << "Students: None." << endl;
		}
		else {
			os << "Students: " << endl;
			for (size_t i = 0; i < current_section.student_records.size(); i++) {
				os << "Name: " << *(current_section.student_records[i]) << endl;
			}
		}
		return os;
	}

	void setRecord(string name, int grade, int week) {
		for (size_t i = 0; i < student_records.size(); i++) {
			if (student_records[i]->getName() == name) {
				student_records[i]->setGrades(grade, week);
			}
		}
	}

	void addStudent(string name) {
		Record* current_student = new Record(name);
		student_records.push_back(current_student);
	}


private:
	string _section;

	class Time
	{
	public:
		Time(string day, int time) : _day(day), _time(time) {}

		Time() {}

		friend ostream& operator<<(ostream& os, const Time& current_time) {
			os << "[Day: " << current_time._day << ", Start Time: ";
			if (current_time._time > 12 && current_time._time != 24) {
				os << (current_time._time - 12) << "PM], ";
			}
			else if (current_time._time == 24) {
				os << "12AM], ";
			}
			else {
				os << current_time._time << "AM], ";
			}
			return os;
		}

	private:
		string _day;
		int _time;
	};

	//record class
	class Record
	{
	public:
		Record(string& name) : _name(name) {
			for (int i = 0; i < 14; i++) {
				records.push_back(-1);
			}
		}

		Record() {}

		const string getName() const { return _name; }

		const vector<int> getGrades() const { return records; }

		void setGrades(int grade, int week) {
			int index = week - 1;
			records[index] = grade;
		}

		friend ostream& operator<<(ostream& os, const Record& current_record) {
			os << current_record._name << ", Grades:" << " ";
			for (size_t i = 0; i < current_record.records.size(); i++) {
				os << current_record.records[i] << " ";
			}
			return os;
		}

		void setPointer(string* student) {
			_pointer = student;
		}

	private:
		string _name;
		string* _pointer = nullptr;
		vector <int> records;
	};
	vector <Record*> student_records; // student records, storing a value of pointers in a vector
	Time current_time; // time, dont know how to make it into a pointer
};

class LabWorker //lab worker, grading and etc, everything in here works good
{
public:
	LabWorker(string name) : _name(name) {}

	friend ostream& operator<<(ostream& os, const LabWorker& current_worker) {
		if (current_worker._section == nullptr) {
			os << current_worker._name << " does not have a section" << endl;
		}
		else {
			os << current_worker._name << " has section" << *(current_worker._section) << endl;
		}
		return os;
	}

	void addSection(Section& current_section) {
		_section = &current_section;
	}

	void addGrade(string name, int grade, int week) {
		_section->setRecord(name, grade, week);
	}

private:
	string _name;
	Section* _section = nullptr;
};

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	cout << secA2 << endl;

	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	cout << secA2 << endl;

	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe("Moe");
	cout << moe << endl;

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection(secA2);
	cout << moe << endl;

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane("Jane");
	Section secB3("B3", "Thursday", 11);
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection(secB3);
	cout << jane << endl;

	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);
	moe.addGrade("Paul", 19, 1);
	moe.addGrade("George", 16, 1);
	moe.addGrade("Ringo", 7, 1);
	cout << moe << endl;

	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);
	moe.addGrade("Paul", 20, 3);
	moe.addGrade("Ringo", 0, 3);
	moe.addGrade("George", 16, 3);
	cout << moe << endl;

	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
		<< "those students (or rather their records?)\n";

	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
		<< "then make sure the following call works:\n";
	doNothing(secA2);
	cout << "Back from doNothing\n\n";

} //main