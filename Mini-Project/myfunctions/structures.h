#ifndef STRUCTURES
#define STRUCTURES

struct Student{
    char login_id[50];
    char name[50];
    char password[50];
    int age;
    char email_id[50];
    bool active;
    int courses_ID[30];
    int stud_id;
    int pass_modify;


};

struct Faculty{
    char login_id[50];
    char name[50];
    char password[50];
    char department[50];
    char email_id[50];
    bool active;
    int age;
    int courses_ID[30];
    int faculty_id;
    int pass_modify;
};

struct Course {
    char courseName[50];
    char department[50];
    int totalseats;
    int availableseats;
    int course_ID;
    bool active;
    
};


#endif