/*A
Shreya Suresh
2/19/23
Hash Table- Create a hash table and a random student generator
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
//function prototypes
void dlt(Student** htable, int size);
void printAll(Student** htable, int size);
void printChain(Student* current);
void reset(Student* htable[], int size);
Student** addStu(Student** htable, int &curID, int &size);
Student** mAdd(Student** htable, int &curID, int &size);
Student** rehash(Student** htable, Student** ntable, int &size, int curID);


Student** addStu(Student** htable, int &curID, int &size) { //add students using random student generator  
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
    //retrieve first name from file
    while (ffile.getline(input,100, '\n')) {
      if (count == num) {
	strcpy(firstName,input);
	count++;
      }
    count++;
  }
  ffile.close();
  count = 1;
  //retrieve last name from file
  while (lfile.getline(input,100, '\n')) {
    if (count == num2) {
      strcpy(lastName,input);
      count++;
    }
    count++;
  }
  lfile.close();
  //random GPA generator
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
  if(htable[(curID)%size] == NULL){ //case of no collisions
    htable[(curID%size)] = newPoint;
  }
  else{
    if(htable[(curID)%size]->next == NULL){ //case of one collision
      htable[curID%size]->next = newPoint;
    }
    else{
      if(htable[(curID)%size]->next->next == NULL){ //case of two collisions
	htable[curID%size]->next->next = newPoint;
      }
      else{ //case of three collisions, prompt to create a new table
	Student** new_table = new Student*[size*2]; //making a new table
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
Student** mAdd(Student** htable, int &curID, int &size){ //add students manually
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
Student** rehash(Student** htable, Student** ntable, int &size, int curID){ //rehash students into new table
  int size1 = size;
  size = size*2;
  for(int i = 0; i < curID; i++){ 
    if(i < size1){ //if first node
      ntable[(i%size)] = htable[(i)%size1];
    }
    else if(i < size1*2){ //if second node
      ntable[(i%size)] = htable[(i)%size1]->next;
    }
    else{ //if last node
      ntable[i%size]->next = htable[(i)%size1]->next->next;
    }
  }
  for (int i = size/2; i < size; i++){
    ntable[(i%size)]->next = NULL;
  }
  return ntable;
}

void printAll(Student** htable, int size){ //print out all the students{
  for (int i = 0; i < size; i++){
    printChain(htable[i]);
  }
  return;
}
void printChain(Student* current){ //recursively print a chain, makes printing all easier
  if(current != NULL){
    cout << current->firstName << " " << current->lastName << " GPA: " << fixed << setprecision(2) << current->gpa << " " << "ID: " << current->id << endl;
    printChain(current->next);
  }
  return;
}
void dlt(Student** htable, int size){ //delete a specific student
  int i;
  cout << "What is the student's ID?" << endl;
  cin >> i;
  cin.clear();
  //find that student and override it
  if (htable[i%size]->id == i){
    htable[i%size] = htable[i%size]->next;
  } else if (htable[i%size]->next->id == i){
    htable[i%size]->next = htable[i%size]->next->next;
  } else if (htable[i%size]->next->next->id == i){
    htable[i%size]->next->next = NULL;
  }
  return;
}

void reset(Student** htable, int size){ //resets the values in the table
  for(int i = 0; i < size; i++){
    htable[i] = NULL;
  }
}
int main(){ //main function
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
  if (strcmp(input, "ADD") == 0){ //call add function
    htable = addStu(htable, curID, size);
  } else if (strcmp(input, "MADD") == 0){ //call manual add function
    htable = mAdd(htable, curID, size);
  }else if (strcmp(input, "DELETE") == 0){ //call delete function
    dlt(htable, size);
    cout << "Deleted." << endl;
  } else if (strcmp(input, "PRINT") == 0){ //call print function
    printAll(htable, size);
  } else if(strcmp(input, "QUIT") == 0) { //quit progran
    running = false;
  }else {
   
  }
  }
  return 0;
}
