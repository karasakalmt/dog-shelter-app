/*
 *
 * Author: Mete Karasakal
 * Project Name: Dog Shelter App
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct Date{
    int day;
    int month;
    int year;
};

struct Dog{
    int id;
    char *name;
    float weight;
    float height;
    struct Date *enter;
    struct Date *leave;
};


/* Function declarations starts here*/

int hash(int, int);//takes unique key, and table size
float loadCheck(int, int);//checks load factor
void addDog(struct Dog*, int);//Adds a dog to the shelter
void printDog(struct Dog*, int);//Takes array, and index as arguments. Outputs dogs info
int searchDog(struct Dog*, int, int);//Takes array, id, and size as input and return index
void adoptDog(struct Dog*, int, int);//takes array, id of a dog, size of array to search
void rehash(struct Dog*, int*);//Table and size pointer because it will change
int primeCheck(int);//Checks if a number is prime
void printAll(struct Dog*,int);//Prints all the shelter

/* Function declarations ends here*/


int main() {

    /* Initializing dog array. */
    struct Dog *shelter;
    shelter=(struct Dog*) malloc(sizeof(struct Dog)*11);
    int size=11;
    for(int traverse=0; traverse<11;traverse++)//to know if a slot is free initialize all ids as -1, and to know if a dog is adopted made all leaves null
    {
        shelter[traverse].id = -1;
        shelter[traverse].leave = NULL;
    }
    int command=-1, n=0, id, index;//command to control the program, n is item quantity, id to use as input, index of a dog
    while(command!=4)//menu
    {
        //printAll(shelter,size); //to visualize data uncomment this line
        if(loadCheck(n,size)>0.5)// checking load factor
        {
            rehash(shelter, &size);
        }
        printf("1.Add a dog.\n2.Search for a dog.\n3.Adopt a dog.\n4.Exit\nCommand: ");
        scanf("%d", &command);
        printf("\n");
        switch (command)
        {
            case 1:
                addDog(shelter,size);
                n++;
                break;
            case 2:
                printf("Enter unique identifier: ");
                scanf("%d",&id);
                index=searchDog(shelter,id,size);
                if(index==-1)
                {
                    printf("No dog is found.\n\n");
                    break;
                }
                printDog(shelter, searchDog(shelter,id,size));
                break;
            case 3:
                printf("Enter unique identifier: ");
                scanf("%d",&id);
                adoptDog(shelter,id,size);
                break;
            default:
                if(command!=4)
                printf("\nPlease enter a command between 1-4\n");
                break;
        }
    }
    return 0;
}

int hash(int id, int size)
{
    return id%size;
}

float loadCheck(int n, int size)
{
    return n*1.0/size;
}

void addDog(struct Dog *shelter, int size)
{
    int id, index, count=0;// id for dogs id, index for find a place after hashing, count for quadratic probing sake
    printf("Enter unique identifier: ");
    scanf("%d",&id);
    while(searchDog(shelter,id,size)!=-1)
    {
        printf("Please enter another unique identifier: ");
        scanf("%d",&id);
    }
    index=hash(id, size);//finds a empty cell below
    while(shelter[index].id!=-1)
    {
        count++;
        index=(id+count*count)%size;
    }
    /* adding data to struct below */
    shelter[index].id = id;
    printf("Enter name: ");
    shelter[index].name=malloc(sizeof(char)*20);
    scanf("%s",shelter[index].name);
    printf("Enter weight: ");
    scanf("%f",&shelter[index].weight);
    printf("Enter height: ");
    scanf("%f",&shelter[index].height);
    shelter[index].enter = (struct Date*) malloc(sizeof(struct Date*));//initialize date
    printf("Enter entry date: ");
    scanf("%d.%d.%d",&shelter[index].enter->day, &shelter[index].enter->month, &shelter[index].enter->year);
    printf("%s has been added to the dog shelter.\n\n", shelter[index].name);
}

void printDog(struct Dog* shelter, int index)
{
    //printf("ID of the dog: %d\n",shelter[index].id);//to show id uncomment this line
    printf("Name: %s\nWeight: %.2f\nHeight: %.2f\nEntry Date: %d.%d.%d\n", shelter[index].name, shelter[index].weight, shelter[index].height, shelter[index].enter->day, shelter[index].enter->month, shelter[index].enter->year);
}//I would add "leave date" also but in the instructions of the assignment it wasn't included, that is why i didn't add.

int searchDog(struct Dog* shelter, int id, int size)
{//id's of free slots are -1
    int index,count=0;
    index=hash(id,size);
    if(id==shelter[index].id && shelter[index].id!=-1)
        return index;
    else if(shelter[index].id == -1)
        return -1;
    else
    {
        while (id != shelter[index].id) {
            count++;
            index = (id+count*count)%size;
            if(shelter[index].id == -1)
                return -1;
        }
        return index;
    }
}

void adoptDog(struct Dog* shelter, int id, int size)
{
    int index;
    index=searchDog(shelter,id,size);
    if(index==-1)
    {
        printf("No dog is found.\n\n");
    }
    else
    {
        printDog(shelter,index);
        if(shelter[index].leave==NULL)
        {
            printf("Enter leave date: ");
            shelter[index].leave = (struct Date*) malloc(sizeof(struct Date));//initialize leave date struct
            scanf("%d.%d.%d",&shelter[index].leave->day,&shelter[index].leave->month,&shelter[index].leave->year);
            printf("%s has been adopted. \n\n",shelter[index].name);
        }
        else
        {
            printf("Dog is already adopted!\n\n");
        }
    }
}

void rehash(struct Dog* shelter, int *size)
{
    int current_s=*size, new_s=*size;
    struct Dog* tmp;
    tmp = (struct Dog*) malloc(sizeof(struct Dog)*current_s);
    new_s*=2;
    do
    {
        new_s++;
    }while(!primeCheck(new_s));//finds closest prime
    *size=new_s;//new size declared here
    for(int i=0; i<current_s; i++)//copying shelter array to temporary array
    {
        tmp[i].name=shelter[i].name;
        tmp[i].height=shelter[i].height;
        tmp[i].weight=shelter[i].weight;
        tmp[i].id=shelter[i].id;
        tmp[i].leave=shelter[i].leave;
        tmp[i].enter=shelter[i].enter;
        shelter[i].id=-1;
        shelter[i].leave=NULL;
    }
    shelter=(struct Dog*) realloc(shelter ,sizeof(struct Dog)*new_s);//adding new cells onto current structure array
    for(int i=current_s-1; i<new_s; i++)//initializing new cells
    {
        shelter[i].id=-1;
        shelter[i].leave=NULL;
    }
    int index,count=0;//index of our main array, counter for inside loop
    for(int i=0; i<current_s; i++)//hashing old data to new places inside rehashed array
    {
        if(tmp[i].id==-1)
            continue;
        else
        {//allocate new cells and swap operations
            index=hash(tmp[i].id,*size);
            while(shelter[index].id!=-1)
            {
                count++;
                index=(tmp[i].id+count*count)% new_s;
            }
            shelter[index].id=tmp[i].id;
            shelter[index].name=tmp[i].name;
            shelter[index].weight=tmp[i].weight;
            shelter[index].height=tmp[i].height;
            shelter[index].enter=tmp[i].enter;
            shelter[index].leave=tmp[i].leave;
        }
    }
}

int primeCheck(int num)
{
    int half=num/2;
    for(int i=2;i<=half;i++)
    {
        if(num%i==0)
        {
            return 0;
        }
    }
    return 1;
}

void printAll(struct Dog *shelter, int size)
{
    printf("-----------------------------\n");
    for(int i=0; i<size; i++)
    {
        printf("%d\n",i);
        if(shelter[i].id!=-1)
        printDog(shelter,i);
        printf("-----------------------------\n");
    }
}
