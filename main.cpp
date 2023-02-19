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

void addStu(Student* htable[], int &curID){
  Student* newPoint = new Student();
  strcpy(newPoint->firstName, "S");
  strcpy(newPoint->lastName, "R");
  newPoint->id = curID;
  newPoint->gpa = 4.12;
  htable[(curID%100)] = newPoint;
  curID++;
  return;
}
void print(Student* htable[], int size){
  for(int i = 0; i < size; i++){
    printChain(htable[i]);
  }
  return;
}
void printChain(Student* current){
  if(current != NULL){
    cout << current->firstName << " " << current->lastName << endl;
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
    addStu(htable, curID);
  } else if (strcmp(input, "DELETE") == 0){

  } else if (strcmp(input, "PRINT") == 0){
    cout << sizeof(htable) << endl;
    print(htable, size);
  } else if(strcmp(input, "QUIT") == 0) {
    running = false;
  }else {
    cout << "You can only ADD, DELETE, PRINT, or QUIT" << endl;
  }
  }
  return 0;
}
