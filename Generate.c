#include <stdio.h>
#include <string.h>
struct Course {
   char  title[21];
   char prerequisites[21][21];
   int numPrerequisites;
};

struct Course courses[21];
int coursesSize = 0;
/*
    1. Get all Requirements in an array
    2. Check Prerequisites of Requirements and store all prereqs in an array  .
    3. 
*/
//Array of course
char fall[21][21];
int sizeFall = 0;
char winter[21][21];
int sizeWinter = 0;
char spring[21][21];
int sizeSpring = 0;

char requiredCourses[21][21];
int sizeRequiredCourses = 0;

char prerequisites[101][101];
int sizePrerequisites = 0;

void readOfferingFile(char filename[20])
{
    FILE *file = NULL;
    file = fopen (filename,"r");
    char string[100];
    char firstValue[21];
    char secondValue[21];
    
    while(fgets(string, 100, file)) {
        printf("%s\n", string);
        char *token = strtok(string, " ");
        while (token != NULL)
        {    
            strcpy(secondValue, token);
            if(secondValue[0] == '1') 
            {
                strcpy(fall[sizeFall], firstValue);
                printf(" Fall quarter: %s\n", fall[sizeFall]);
                sizeFall++;
            }
            else if(secondValue[0] == '2') 
            {
                strcpy(winter[sizeWinter], firstValue);
                printf(" Winter quarter: %s\n", winter[sizeWinter]);
                sizeWinter++;
            }
            else if(secondValue[0] == '3') 
            {
                strcpy(spring[sizeSpring], firstValue);
                printf(" Spring quarter: %s\n", spring[sizeSpring]);
                sizeSpring++;
            }
            token = strtok(NULL, " ");
            strcpy(firstValue, secondValue);
        }
         
    }

}


void readPrerequisiteFile(char filename[20])
{
    FILE *file = NULL;
    file = fopen (filename,"r");
    char string[100];
    char firstValue[21];
    while(fgets(string, 100, file)) 
    {
        strcpy(firstValue, token);
        printf("%s\n", string);
        char *token = strtok(string, " ");
        while (token != NULL)
        {
            printf("%s\n", token);
            
            strcpy(prerequisites[sizePrerequisites], token);
            sizePrerequisites++;
            token = strtok(NULL, " ");
        }
    }
    
}

void readRequirementFile(char filename[20])
{
    FILE *file = NULL;
    file = fopen (filename,"r");
    char string[100];
    while(fgets(string, 100, file)) 
    {
        //printf("%s\n", string);
        char *token = strtok(string, " ");
        while (token != NULL)
        {
            //printf("%s\n", token);
            strcpy(requiredCourses[sizeRequiredCourses], token);
            sizeRequiredCourses++;
            token = strtok(NULL, " ");
        }
    }
}



void printArray(int size, char array[21][21])
{
    for(int i = 0; i < size; i++)
    {
        printf("%s\n", array[i]);
    }
}

void makeMandatoryClasses()
{
    for(int i = 0; i < sizeRequiredCourses; i++)
    {
            struct Course course;
            strcpy(course.title, requiredCourses[i]);
            course.numPrerequisites = 0;
            strcpy(course.prerequisites[0], "0");
            courses[coursesSize] = course;
            coursesSize++;
    }
}

void printMandatoryClasses(struct Course courses[21])
{
    for(int i = 0; i < coursesSize; i++)
    {
        printf("%s\n", courses[i].title);
        printArray(courses[i].numPrerequisites, courses[i].prerequisites);
    }
}
int main() {
    struct Course course;
    // strcpy(course.title, "ICS33");
    // strcpy(course.prerequisites[0], "ICS31");
    // strcpy(course.prerequisites[1], "ICS32");

    // //course.season = 2;
    
    // printf("%s\n", course.title);
    // printf("%s\n", course.prerequisites[1]);
    
    char Offering[20];
    char Prerequisite[20];
    char Requirement[20];

    // printf("Enter Offering filename\n");
    // scanf("%s", Offering);
    // printf("Enter Prerequisite filename\n");
    // scanf("%s", Prerequisite);
    // printf("Enter Requirement filename\n");
    // scanf("%s", Requirement);
    
    printf("%s\n", Offering);

    readOfferingFile("Offering.txt");
    printf("\nFall courses: \n");
    printArray(sizeFall, fall);
    
    printf("\nWinter courses: \n");
    printArray(sizeWinter, winter);
    
    printf("\nSpring courses: \n");
    printArray(sizeSpring, spring);
    printf("\nRequirements: \n");

    readRequirementFile("Requirement.txt");
    printf("\nRequirement contents: \n");
    printArray(sizeRequiredCourses, requiredCourses);

    makeMandatoryClasses();
    
    //readPrerequisiteFile("Prerequisite.txt");
    printf("\nPrerequisite contents: \n");
    printMandatoryClasses(courses);
    printArray(courses[0].numPrerequisites,courses[0].prerequisites);
    return 0;
}
