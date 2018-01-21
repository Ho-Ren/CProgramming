#include <stdio.h>
#include <string.h>
struct Course {
   char  title[21];
   char prerequisites[21][21];
   int numPrerequisites;
   int numPrerequisitesTracker;
};

struct Course courses[21];
int coursesSize = 0;
int coursesSizeTracker = 0;
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

char prerequisites[21][21];
int sizePrerequisites = 0;


//returns index of the course
int courseExists(char title[21])
{
    for(int i = 0; i < coursesSize; i++)
    {
        if(strcmp(title, courses[i].title) == 0)
        {
            //printf("Course exists: %s\n", title);
            return i;     
        }
    }
    return -1;
}

void pushBack(char title[21])
{
    if(courseExists(title) == -1)
    {
        struct Course course;
        strcpy(course.title, title);
        strcpy(course.prerequisites[0], "0");
        course.numPrerequisites = 0;
        course.numPrerequisitesTracker = 0;
        strcpy(courses[coursesSize].title, title);
        coursesSize++;
    }
}

int hasNoPrerequisites(char title[21])
{
    for(int i = 0; i < coursesSize; i++)
    {
        if(strcmp(courses[i].title, title) == 0)
        {
            if(courses[i].numPrerequisitesTracker == 0)
            {
                return 1;
            }    
        }
    }
    return 0;
}


void pushBackPrerequisites(char title[21])
{
    for(int i = 0; i < sizePrerequisites; i++)
    {
        if(strcmp(title, prerequisites[i]) == 0){
            return;
        }
    }
    strcpy(prerequisites[sizePrerequisites], title);
    sizePrerequisites++;
}

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
            char *newline = strchr( token, '\n' );
            if (newline)
            *newline = 0;
            
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
    //printf("\nIN PREREQ FILE\n\n");
    FILE *file = NULL;
    file = fopen (filename,"r");
    char string[100];
    while(fgets(string, 100, file)) 
    {
        //printf("%s\n", string);
        char *token = strtok(string, " ");
        if (token != NULL)
        {
            int exists = courseExists(token);
            if(exists != -1 && courses[exists].numPrerequisites == 0)
            {
                //check to see if the first course exists in courses
                //if course exists in mandatory courses add prerequisites to the course
                token = strtok(NULL, " ");
                while(token != NULL)
                {
                    char *newline = strchr( token, '\n' );
                    if (newline)
                    *newline = 0;
                    
                    char str[21];
                    strcpy(str, token);
                    strcpy(courses[exists].prerequisites[courses[exists].numPrerequisites], str);
                    //printf("Course prereq: %s\n", courses[exists].prerequisites[courses[exists].numPrerequisites]);
                    courses[exists].numPrerequisites++;
                    courses[exists].numPrerequisitesTracker++;//This should add all prereqs to the course
                    //If prereq does not already exist in courses push it back
                    //add course to courses if the course does not already exist in courses
                    pushBackPrerequisites(str);
                    token = strtok(NULL, " ");
                }
            }
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
            char *newline = strchr( token, '\n' );
            if (newline)
            *newline = 0;
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
        printf("%s, ", array[i]);
    }
}

void makeMandatoryClasses()
{
    for(int i = 0; i < sizeRequiredCourses; i++)
    {
            struct Course course;
            strcpy(course.title, requiredCourses[i]);
            course.numPrerequisites = 0;
            course.numPrerequisitesTracker = 0;
            strcpy(course.prerequisites[0], "0");
            courses[coursesSize] = course;
            coursesSize++;
    }
}

void printMandatoryClasses(struct Course courses[21])
{
    for(int i = 0; i < coursesSize; i++)
    {
        printf("Mandatory: %s, %d, %d, \n", courses[i].title, courses[i].numPrerequisites, courses[i].numPrerequisitesTracker);
        printArray(courses[i].numPrerequisites, courses[i].prerequisites);
        printf("\n");
    }
}

void makeMoreMandatoryClasses()
{
    for(int i = 0; i < sizePrerequisites; i++)
    {
        printf("prerequisites: %s\n", prerequisites[i]);
        pushBack(prerequisites[i]);
    }
}


void takeCourse(char title[21])
{
    for(int i = 0; i < coursesSize; i++)
    {
        int np = courses[i].numPrerequisites;
        for(int j = 0; j < np; j++)
        {
            if(strcmp(courses[i].prerequisites[j], title) == 0)
            {
                //add in another numPrereqs. 
                strcpy(courses[i].prerequisites[j], "00");
                courses[i].numPrerequisitesTracker--;
            }
        }
        if(strcmp(courses[i].title, title) == 0)
        {
            strcpy(courses[i].title, "00");
            coursesSizeTracker--;
        }
    }
}

void printAvailableClasses(int quarter)
{
    if(quarter == 1)
    {
        for(int i = 0; i < sizeFall; i++)
        {
            int index = courseExists(fall[i]);
            if(index != -1 && courses[index].numPrerequisitesTracker == 0)
            {
                printf("%s ", fall[i]);
                takeCourse(fall[i]);
            }
        }     
    }
    else if(quarter == 2)
    {
        for(int i = 0; i < sizeWinter; i++)
        {
            int index = courseExists(winter[i]);
            if(index != -1 && courses[index].numPrerequisitesTracker == 0)
            {
                printf("%s ", winter[i]);
                takeCourse(winter[i]);
            }
        }
    }
    else if(quarter == 3)
    {
        for(int i = 0; i < sizeSpring; i++)
        {
            int index = courseExists(spring[i]);
            if(index != -1 && courses[index].numPrerequisitesTracker == 0)
            {
                printf("%s ", spring[i]);
                takeCourse(spring[i]);
            }
        }
    }

}

void printSchedule()
{
    int year = 1;
    coursesSizeTracker = coursesSize;
    printf("%d \n\n", coursesSizeTracker);
    while(coursesSizeTracker != 0 && year < 11)
    {
        for(int i = 1; i < 4; i++)
        {
            printf("%d %d ", year, i);
            printAvailableClasses(i);
            printf("\n");
        }
        year++;
    }
}

int main() {
    char Offering[20];
    char Prerequisite[20];
    char Requirement[20];
    // printf("Enter Offering filename\n");
    // scanf("%s", Offering);
    // printf("Enter Prerequisite filename\n");
    // scanf("%s", Prerequisite);
    // printf("Enter Requirement filename\n");
    // scanf("%s", Requirement);
    
    // printf("%s\n", Offering);

    readOfferingFile("Offering.txt");
    printf("\nFall courses: \n");
    printArray(sizeFall, fall);
    
    printf("\nWinter courses: \n");
    printArray(sizeWinter, winter);
    
    printf("\nSpring courses: \n");
    printArray(sizeSpring, spring);
    

    readRequirementFile("Requirement.txt");
    printf("\nRequirement contents: \n");
    printArray(sizeRequiredCourses, requiredCourses);
    
    makeMandatoryClasses();
    
    //readPrerequisiteFile("Prerequisite.txt");
    printf("\nPrerequisite contents: \n");
    printMandatoryClasses(courses);
    printArray(courses[0].numPrerequisites,courses[0].prerequisites);
    
    readPrerequisiteFile("Prerequisite.txt");
    
    //printf("\n\n");
    //printMandatoryClasses(courses);
    
    //printArray(sizePrerequisites, prerequisites);
    
    makeMoreMandatoryClasses();
    printf("\n");
    //printMandatoryClasses(courses);
    
    readPrerequisiteFile("Prerequisite.txt");
    
    printf("\n\n");
    printMandatoryClasses(courses);

    printSchedule();
    
    //printMandatoryClasses(courses);
    return 0;
}
