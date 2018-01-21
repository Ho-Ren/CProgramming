/*Ho-Ren Kang
horenk 21397985
*/
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


int courseExists(char title[21])
{
    int i = 0;
    for(; i < coursesSize; i++)
    {
        if(strcmp(title, courses[i].title) == 0)
        {
            
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
    int i = 0;
    for(; i < coursesSize; i++)
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
    int i = 0;
    for(; i < sizePrerequisites; i++)
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
                
                sizeFall++;
            }
            else if(secondValue[0] == '2') 
            {
                strcpy(winter[sizeWinter], firstValue);
                
                sizeWinter++;
            }
            else if(secondValue[0] == '3') 
            {
                strcpy(spring[sizeSpring], firstValue);
                
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
    while(fgets(string, 100, file)) 
    {
        
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
                    
                    courses[exists].numPrerequisites++;
                    courses[exists].numPrerequisitesTracker++;

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
      
        char *token = strtok(string, " ");
        while (token != NULL)
        {
            char *newline = strchr( token, '\n' );
            if (newline)
            *newline = 0;
            
            strcpy(requiredCourses[sizeRequiredCourses], token);
            sizeRequiredCourses++;
            token = strtok(NULL, " ");
        }
    }
}



void printArray(int size, char array[21][21])
{
    int i = 0;
    for(; i < size; i++)
    {
        printf("%s, ", array[i]);
    }
}

void makeMandatoryClasses()
{
    int i = 0;
    for(; i < sizeRequiredCourses; i++)
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
    int i = 0;
    for(; i < coursesSize; i++)
    {
        printf("Mandatory: %s, %d, %d, \n", courses[i].title, courses[i].numPrerequisites, courses[i].numPrerequisitesTracker);
        printArray(courses[i].numPrerequisites, courses[i].prerequisites);
        printf("\n");
    }
}

void makeMoreMandatoryClasses()
{
    int i = 0;
    for(; i < sizePrerequisites; i++)
    {
        
        pushBack(prerequisites[i]);
    }
}


void takeCourse(char title[21])
{
    int i = 0;
    for( ;i < coursesSize; i++)
    {
        int np = courses[i].numPrerequisites;
        int j = 0;
        for(; j < np; j++)
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

void printAvailableClasses(int year, int quarter)
{
    int oneTimePrint = 1;
    if(quarter == 1)
    {
        int i = 0;
        for(; i < sizeFall; i++)
        {
            int index = courseExists(fall[i]);
            if(index != -1 && courses[index].numPrerequisitesTracker == 0)
            {
                if(oneTimePrint)
                {
                    printf("%d %d ", year, quarter);
                    oneTimePrint--;
                }
                printf("%s ", fall[i]);
                takeCourse(fall[i]);
            }
        }     
        if(oneTimePrint == 0)
        printf("\n");
    }
    else if(quarter == 2)
    {
        int i = 0;
        for(; i < sizeWinter; i++)
        {
            int index = courseExists(winter[i]);
            if(index != -1 && courses[index].numPrerequisitesTracker == 0)
            {
                if(oneTimePrint)
                {
                    printf("%d %d ", year, quarter);
                    oneTimePrint--;
                }
                printf("%s ", winter[i]);
                takeCourse(winter[i]);
            }
        }
            if(oneTimePrint == 0)
            printf("\n");
    }
    else if(quarter == 3)
    {
        int i = 0;
        for(; i < sizeSpring; i++)
        {
            int index = courseExists(spring[i]);
            if(index != -1 && courses[index].numPrerequisitesTracker == 0)
            {
                if(oneTimePrint)
                {
                    printf("%d %d ", year, quarter);
                    oneTimePrint--;
                }
                printf("%s ", spring[i]);
                takeCourse(spring[i]);
            }
        }
            if(oneTimePrint == 0)
            printf("\n");
    }

}

void printSchedule()
{
    int year = 1;
    coursesSizeTracker = coursesSize;
   
    while(coursesSizeTracker != 0 && year < 20)
    {
        int i = 1;
        for(; i < 4; i++)
        {
            
            printAvailableClasses(year, i);
            
        }
        year++;
    }
}

int main(int argc, char *argv[]) {
    char Offering[20];
    char Prerequisite[20];
    char Requirement[20];
    
    strcpy(Offering, argv[1]);
    strcpy(Prerequisite, argv[2]);
    strcpy(Requirement, argv[3]);

    readOfferingFile(Offering);
    readRequirementFile(Requirement);
    makeMandatoryClasses();
    readPrerequisiteFile(Prerequisite);
    makeMoreMandatoryClasses();
    readPrerequisiteFile(Prerequisite);
    printSchedule();
    return 0;
}
