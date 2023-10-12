#ifndef STRUCTURES
#define STRUCTURES

typedef struct{
    char login_id[50];
    char name[50];
    char password[50];
    int age;
    char email_id[50];
    bool active;
    int courses;
    int stud_id;


} Student;

typedef struct{
    char login_id[50];
    char name[50];
    char password[50];
    char department[50];
    char email_id[50];
    bool active;
    int courses;
    int faculty_id;
} Faculty;

typedef struct 
{
    char courseName[50];
    char department[50];
    int totalseats;
    int availableseats;
    
} Course;


#endif