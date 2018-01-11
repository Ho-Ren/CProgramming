#include <stdio.h>
#include <string.h>
struct Course {
   char  title[50];
   char prerequisites[10][20];
   int  season;
};

//Array of courses
struct Course courses[20];

void readFile(char filename[50])
{
     //printf(name);
     FILE *file = NULL;
     file = fopen (filename,"r");
     char c;
     c = fgetc (file);
      while(c != EOF)
      {
        printf("%c", c);
        c = fgetc (file);
      }
}

int main() {
    struct Course course;
    strcpy(course.title, "ICS33");
    strcpy(course.prerequisites[0], "ICS31");
    strcpy(course.prerequisites[1], "ICS32");

    course.season = 2;

    printf("%s\n", course.title);
    printf("%s\n", course.prerequisites[1]);
    
    readFile("Hello.txt");
    
    return 0;
}
