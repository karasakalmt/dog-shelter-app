# Dog Shelter App

This is built to keep track of dogs inside a shelter. This program uses Dog structure array which is a hash table with quadratic probing open addressed. Dog structure is as follows:

```C
int id;
char *name;
float weight;
float height;
struct Date *enter;
struct Date *leave;
```  
Date Structure:
```C
int day;
int month;
int year;
```  
There are 3 main functions respectively:
```
1.Add a dog.
2.Search for a dog.
3.Adopt a dog.
```
All functions declerations and functionalities are listed below
```C
int hash(int, int);//takes unique key, and table size returns key%size
float loadCheck(int, int);//checks load factor n/size
void addDog(struct Dog*, int);//Adds a dog to the shelter
void printDog(struct Dog*, int);//Takes array, and index as arguments. Outputs dogs info
int searchDog(struct Dog*, int, int);//Takes array, id, and size as input and return index if there is no such dog exist returns -1
void adoptDog(struct Dog*, int, int);//takes array, id of a dog, size of array to search, and adds leave date
void rehash(struct Dog*, int*);//Takes array and size pointer because it will be the next prime number
int primeCheck(int);//Checks if a number is prime
void printAll(struct Dog*,int);//Prints all the shelter
```
It rehashes in main function and change the size to next prime number when **load factor**>0.5 
