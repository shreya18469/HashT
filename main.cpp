/*A
Shreya Suresh
2/19/23
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

struct Student {
  char firstName[10];
  char lastName[10];
  int id;
  float gpa;
  Student* next;
 };

void dlt(Student** htable, int size);
void printAll(Student** htable, int size);
void printChain(Student* current);
void reset(Student* htable[], int size);
Student** addStu(Student** htable, int &curID, int &size);
Student** mAdd(Student** htable, int &curID, int &size);
Student** rehash(Student** htable, Student** ntable, int &size, int curID);


Student** addStu(Student** htable, int &curID, int &size) {  
  int students;
  cout << "How many students are you adding?" << endl;
  cin >> students; 
  for(int i = 0; i < students; i++){
    char input[100];
    char firstName[100];
    char lastName[100];
    fstream ffile("firstName.txt");
    fstream lfile("lastName.txt");
    int count;
    int num = (rand() % 20) + 1;
    int num2 = (rand() % 20) + 1;
    Student* newPoint = new Student();
    count = 1;
    while (ffile.getline(input,100, '\n')) {
      if (count == num) {
	strcpy(firstName,input);
	count++;
      }
    count++;
  }
  ffile.close();
  count = 1;
  while (lfile.getline(input,100, '\n')) {
    if (count == num2) {
      strcpy(lastName,input);
      count++;
    }
    count++;
  }
  lfile.close();
  float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  r *= 23;
  while(r > 4){
    r -= 4;
    while(r < 2){
      r += 1;
    }
  }
  strcpy(newPoint->firstName, firstName);
  strcpy(newPoint->lastName, lastName);
  newPoint->id = curID;
  newPoint->gpa = r;
  if(htable[(curID)%size] == NULL){
    htable[(curID%size)] = newPoint;
  }
  else{
    if(htable[(curID)%size]->next == NULL){
      htable[curID%size]->next = newPoint;
    }
    else{
      if(htable[(curID)%size]->next->next == NULL){
	htable[curID%size]->next->next = newPoint;
      }
      else{
	Student** new_table = new Student*[size*2];
	reset(new_table, size*2);
	htable = rehash(htable, new_table, size, curID);
	htable[curID%size]->next = newPoint;
      }
    }
  }
  curID++;
}
return htable;
  
}
Student** mAdd(Student** htable, int &curID, int &size){
  char input[100];
  char firstName[100];
  char lastName[100];
  float gpa;
  Student* newP = new Student();
  cout << "What is their first name?" << endl;
  cin >> firstName;
  cin.clear();
  cout << "What is their last name?" << endl;
  cin >> lastName;
  cin.clear();
  cout << "What is their GPA?" << endl;
  cin >> gpa;
  cin.clear();

  strcpy(newP->firstName, firstName);
  strcpy(newP->lastName, lastName);
  newP->id = curID;
  newP->gpa = gpa;
  if (htable[(curID)%size] == NULL){
    htable[(curID%size)] = newP;
  }else {
    if (htable[(curID)%size]->next == NULL){
      htable[(curID%size)]->next = newP;
  }else {
    if (htable[(curID)%size]->next->next == NULL){
      htable[curID%size]->next->next = newP;
  }
    else { //if there are three collisions, create a new table
     Student** ntable = new Student*[size*2];
     reset(ntable, size*2);
     htable = rehash(htable, ntable, size, curID);
     htable[curID%size]->next = newP;
   }
  }
}
   curID++;
   return htable;
}
Student** rehash(Student** htable, Student** ntable, int &size, int curID){
  int size1 = size;
  size = size*2;
  for(int i = 0; i < curID; i++){ 
    if(i < size1){
      ntable[(i%size)] = htable[(i)%size1];
    }
    else if(i < size1*2){
      ntable[(i%size)] = htable[(i)%size1]->next;
    }
    else{
      ntable[i%size]->next = htable[(i)%size1]->next->next;
    }
  }
  for (int i = size/2; i < size; i++){
    ntable[(i%size)]->next = NULL;
  }
  return ntable;
}

void printAll(Student** htable, int size){
  for (int i = 0; i < size; i++){
    printChain(htable[i]);
  }
  return;
}
void printChain(Student* current){
  if(current != NULL){
    cout << current->firstName << " " << current->lastName << " GPA: " << fixed << setprecision(2) << current->gpa << " " << "ID: " << current->id << endl;
    printChain(current->next);
  }
  return;
}
void dlt(Student** htable, int size){
  int i;
  cout << "What is the student's ID?" << endl;
  cin >> i;
  cin.clear();
  if (htable[i%size]->id == i){
    htable[i%size] = htable[i%size]->next;
  } else if (htable[i%size]->next->id == i){
    htable[i%size]->next = htable[i%size]->next->next;
  } else if (htable[i%size]->next->next->id == i){
    htable[i%size]->next->next = NULL;
  }
  return;
}

void reset(Student** htable, int size){
  for(int i = 0; i < size; i++){
    htable[i] = NULL;
  }
}
int main(){
  srand(time(0));
  bool running = true;
  Student** htable = new Student*[100];
  char input[10];
  int curID = 0;
  int size = 100;
  reset(htable, size);
  while(running == true){                                                                                                           
  cout << "Enter a command(ADD (Name Randomizer), MADD (Manually), DELETE, PRINT, or QUIT)" << endl;
  cin >> input;
  for (int i = 0; i < 10; i++){ // convert input to uppercase                                                                                   
    input[i] =  toupper(input[i]);
  }
  if (strcmp(input, "ADD") == 0){
    htable = addStu(htable, curID, size);
  } else if (strcmp(input, "MADD") == 0){
    htable = mAdd(htable, curID, size);
    }else if (strcmp(input, "DELETE") == 0){
    dlt(htable, size);
    cout << "Deleted." << endl;
  } else if (strcmp(input, "PRINT") == 0){
    printAll(htable, size);
  } else if(strcmp(input, "QUIT") == 0) {
    running = false;
  }else {
   
  }
  }
  return 0;
}
