/*
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
void addStu(Student* htable[], int &curID);
void dlt(Student* htable[]);
void print(Student* htable[], int size);
void printChain(Student* current);
void reset(Student* htable[], int size);
Student** rehash(Student* htable[], Student* ntable[], int &size, int curID);

void addStu(Student* htable[], int &curID, int size){
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
	Student* new_table[size*2];
	reset(new_table, size*2);
	htable = rehash(htable, new_table, size, curID);
	cout << endl << endl << endl << endl << endl;
	htable[curID%size]->next = newPoint;
	print(htable, size);
      }
    }
  }
  curID++;
}

return;
}
Student** rehash(Student* htable[], Student* ntable[], int &size, int curID){
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
    if(i > size1){
      ntable[(i%size)]->next = NULL;
    }
  }
  print(ntable, size);
  return ntable;
}
void print(Student* htable[], int size){
  for(int i = 0; i < size; i++){
    printChain(htable[i]);
  }
  return;
}
void printChain(Student* current){
  if(current != NULL){
    cout << current->firstName << " " << current->lastName << " GPA: " << fixed << setprecision(2) << current->gpa << " " << current->id << endl;
    printChain(current->next);
  }
  return;
}
void dlt(Student* htable[]){

}
void reset(Student* htable[], int size){
  for(int i = 0; i < size; i++){
    htable[i] = NULL;
  }
}
int main(){
  bool running = true;
  Student* htable[100];
  char input[10];
  int curID = 0;
  int size = sizeof(htable)/sizeof(htable[0]);
  reset(htable, size);

  while(running == true){ // check user input                                                                                                            
  cout << "Enter a command(ADD, DELETE, PRINT, or QUIT)" << endl;
  cin.getline(input, 10);
  for (int i = 0; i < 10; i++){ // convert input to uppercase                                                                                            
    input[i] =  toupper(input[i]);
  }
  if (strcmp(input, "ADD") == 0){
    addStu(htable, curID, size);
  } else if (strcmp(input, "DELETE") == 0){
    dlt(htable);
  } else if (strcmp(input, "PRINT") == 0){
    print(htable, size);
  } else if(strcmp(input, "QUIT") == 0) {
    running = false;
  }else {
   
  }
  }
  return 0;
}
