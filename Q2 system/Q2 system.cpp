#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;

// - - - - - - - -  COURSE CLASS - - - - - - - - - -
class Course {
	private:
		string course_code;
		string course_name;
		string room_type;
		int capacity;
		vector<string> time_slots;
		vector<int> enrolled_students;

	public:
		//Setter
		Course(string courseCode, string courseName, string roomType, int capacity, vector<string>slots) {
			this->course_code = courseCode;
			this->course_name = courseName;
			this->room_type = roomType;
			this->capacity = capacity;
			this->time_slots = slots;
		}

		//Getters
		string getCourseCode() const {
			return this->course_code;
		}
		string getName() const {
			return this->course_name;
		}
		string getRoomType() const {
			return this->room_type;
		}
		int getCapacity() const {
			return this->capacity;
		}
		const vector<string>& getTimeSlots() const {
			return this->time_slots;
		}
		const vector<int>& getEnrolledStudents() {
			return this->enrolled_students;
		}

		void addStudent(int studentId) {
			if (enrolled_students.size() < capacity) enrolled_students.push_back(studentId);
		}
};

// - - - - - - - - - STUDENT CLASS - - - - - - - - - - - -
class Student {
	protected:
		int student_identity_number;
		string major;
		vector <string> enrolled_courses;
		int academic_year;

	public:
		//Setter
		Student(int studentId, string studentMajor, int academicYear) {
			this->student_identity_number = studentId;
			this->major = studentMajor;
			this->academic_year = academicYear;
		}

		//Getter

		int getStudentId() const {
			return this->student_identity_number;
		}
		string getMajor() const {
			return this->major;
		}
		const vector<string>& getEnrolledCourses() const {
			return this->enrolled_courses;
		}
		int getAcademicYear() const {
			return this->academic_year;
		}

		void enrolledInCourse(string courseCode) {
			enrolled_courses.push_back(courseCode);
		}
};
// - - - - - - - - - ROOM CLASS - - - - - - - - - - - -
class Room {
	protected:
		int room_number;
		string type;
		int capacity;
		vector<string> available_time_slots;
		vector<string> special_equipment;

	public:
		//Setter
		Room(int roomNumber, string roomType, int roomCapacity, vector <string> timeSlot, vector<string> equipment) {
			this->room_number = roomNumber;
			this->type = roomType;
			this->capacity = roomCapacity;
			this->available_time_slots = timeSlot;
			this->special_equipment = equipment;
		}

		//Getter
		int getRoomNumber() const {
			return this->room_number;
		}
		string getRoomType() const {
			return this->type;
		}
		int getCapacity() const {
			return this->capacity;
		}
		const vector <string>& getAvailableTime() const {
			return this->available_time_slots;
		}
		const vector<string>& getSpecialEquipment() const {
			return this->special_equipment;
		}


		bool isTimeSlotAvailable(const string& slot) const {
			return find(available_time_slots.begin(), available_time_slots.end(), slot) != available_time_slots.end();
		}
};
// - - - - - - - - - - Course Registration - - - - - - - - - - - - - - - -
struct RegistrationRequest {
	Student* student;
	Course* course;
	int time_stamp;

	bool operator<(const RegistrationRequest& other) const {
	if (student->getAcademicYear() != other.student->getAcademicYear())
		return student->getAcademicYear() < other.student->getAcademicYear();
	return time_stamp > other.time_stamp;
}

};

priority_queue<RegistrationRequest> registrationQueue;

// - - - - - - - - - - - COURSE REGISTRATION - - - - - - - - - - - - 
void courseRegistration() {
	while (!registrationQueue.empty()) {
		RegistrationRequest registration = registrationQueue.top();
		registrationQueue.pop();

		cout << "- - - - - - - - - - - - - - - - Report - - - - - - - - - - - - - " << endl;
		cout << "Registration for Student " << registration.student->getStudentId()
			<< " in Course " << registration.course->getCourseCode() <<"is completed..!" << endl;
	}
}




int main()
{
	vector<string> courseTimeSlots = { "09:00-10:30", "11:00-12:30" };
	Course course1("BSC IT", "INTRODUCTION TO PYTHON", "Lecture Hall", 50, courseTimeSlots);

	vector<string> roomTimeSlots = { "09:00-10:30", "11:00-12:30", "13:00-14:30" };
	vector<string> specialEquipment = { "Projector" };
	Room room1(101, "Auditorium", 50, roomTimeSlots, specialEquipment);

	Student student1(402307058, "Computer Science", 2);

	RegistrationRequest req1{ &student1, &course1, 1 };
	registrationQueue.push(req1);

	//Registration requests
	courseRegistration();

	return 0;
}