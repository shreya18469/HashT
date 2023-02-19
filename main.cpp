/*
Shreya Suresh
10/24/22
Student List- Create a list of students. You can add, delete, or print students. You can also quit.
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

struct Student {
  char firstName[10];
  char lastName[10];
  int id;
  float gpa;
};
void addStu(vector<Student*> &Vector);
void deleteStu(vector<Student*> &Vector);
void printStu(vector<Student*> &Vector);

int main(){
  bool running = true;
  vector<Student*> Vector;
  char input[10];
  
  while(running == true){ // check user input
  cout << "Enter a command(ADD, DELETE, PRINT, or QUIT)" << endl;
  cin.getline(input, 10);
  for (int i = 0; i < 10; i++){ // convert input to uppercase
    input[i] =  toupper(input[i]);
  }
  if (strcmp(input, "ADD") == 0){ // run add function- add student to list
    addStu(Vector);
  } else if (strcmp(input, "DELETE") == 0){ // run delete function- remove student from list
    deleteStu(Vector);
  } else if (strcmp(input, "PRINT") == 0){ // run print function- display student list
    printStu(Vector);
  } else if(strcmp(input, "QUIT") == 0) { //quit program
    running = false;
  }else {
    cout << "You can only ADD, DELETE, PRINT, or QUIT" << endl;
  }
  }
  return 0;
}
void addStu(vector<Student*> &Vector){ // Add a new student to the list
    Student* student = new Student;
    cout << "Enter First name: " << endl;
    cin >> student->firstName;
    cin.ignore(10, '\n');
    cout << "Enter Last name: " << endl;
    cin >> student->lastName;
    cin.ignore(10, '\n');
    cout << "Enter ID: " << endl;
    cin >> student->id;
    cin.ignore(10, '\n');
    cout << "Enter GPA: " << endl;
    cin >> student->gpa;
    cin.ignore(10, '\n');

    Vector.push_back(student);
}
void deleteStu(vector<Student*> &Vector){ // delete a student from the list
    cout << "Enter a student ID to remove a student from the list." << endl;
    int num = 0;
    cin >> num;
    cin.ignore(10, '\n');
    for (vector<Student*>::iterator it = Vector.begin(); it != Vector.end(); it++){ //iterate through list
      if((*it)-> id == num){ // check if input is an existing id 
	delete Vector[it-Vector.begin()];
	Vector.erase(it); // erase student from list
	break;
      } else { 
	cout << "Invalid Student ID." << endl;
      }
    }
}
void printStu(vector<Student*> &Vector){ // display student list
    for(vector<Student*>::iterator it = Vector.begin(); it != Vector.end(); it++){
      cout << (*it) -> firstName << " ";
      cout << (*it) -> lastName << ", ";
      cout << (*it) ->  id << ",";
      cout << fixed << setprecision(2) << (*it) -> gpa << endl; // round gpa to 2 places
    }
}
