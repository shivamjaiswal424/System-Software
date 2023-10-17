#ifndef DEFINE
#define DEFINE


//LOGIN
#define LOGIN_ID "Enter your login ID"
#define PASSWORD "Enter your password #\n "
#define INVALID_LOGIN "The login ID specified doesn't exist!$"
#define INVALID_PASSWORD "The password specified doesn't match!$"


//LOGIN WELCOME
#define ADMIN_LOGIN_WELCOME "Welcome dear admin! With great power comes great responsibility!\nEnter your credentials to unlock this power!"
#define STUDENT_LOGIN_WELCOME "Welcome dear Student! Enter your credentials to get access!"
#define FACULTY_LOGIN_WELCOME " Welcome dear Faculty! Enter your credentials to get access!" 
#define ADMIN_LOGIN_SUCCESS "Welcome ADMIN!"
#define INVALID_MENU_CHOICE "It seems you've made an invalid menu choice\nYou'll now be redirected to the main menu!^"


//MENU
#define ADMIN_MENU "1. Add Faculty\n2. Add Student\n3. Remove Student\n4. Update Student/Faculty details\n5. Get Student Details\n6. Get Faculty Details\n7. Press any other number to exit\n"
#define ADD_DETAILS "Let's start with giving details.\n\n"
#define USER_NAME "\nEnter the name of the user.\n"
#define ENTER_PASSWORD "\nEnter user password. #\n"
#define ENTER_AGE "\nEnter User Age.\n"
#define ENTER_EMAIL "\nEnter User Email ID\n"
#define ADMIN_MOD_CUSTOMER_MENU "Which information would you like to modify?\n1. Name 2. Age 3. Gender 4.Active Status \nPress any other key to cancel"
#define ERRON_INPUT_FOR_NUMBER "It seems you have passed a sequence of alphabets when a number was expected or you have entered an invalid number!\nYou'll now be redirected to the main menu!^"
#define ADMIN_MOD_STUDENT_NEW_NAME "What's the updated value for name?"
#define ADMIN_MOD_STUDENT_NEW_AGE "What's the updated value for age?"
#define ADMIN_MOD_STUDENT_NEW_LOGIN_ID "What's the updated value for login ID?"
#define ADMIN_MOD_STUDENT_NEW_STATUS "What is updated status for student"
#define ADMIN_MOD_STUDENT_SUCCESS "The required modification was successfully made!\nYou'll now be redirected to the main menu!^"

// STUDENT
#define GET_STUDENT_ID "Enter the Student ID of the student you're searching for.\n"
#define NO_STUDENT_ID "No student could be found for the given ID."
#define STUDENT_ADD_ID "The newly created Student ID is :"
#define STUDENT_ACKDEC_ID "What is the Student ID of the Student you want to Activate/Deactivate?\n"
//#define STUDENT_ACKDEC_FAILURE "This Student cannot be Activated since the student has already enrolled in some courses.\nRedirecting you to the main page...^"
#define STUDENT_ACKDEC_SUCCESS "This student has been successfully Activated/Deactivated.\nRedirecting you to the main menu ...^"
#define STUDENT_MOD_ID "Enter the ID of the student who's information you want to edit"

//DELETE 


//Faculty
#define FACULTY_ADD_ID "The newly created Faculty ID is:"
#define GET_FACULTY_ID "Enter the Faculty ID of the student you're searching for.\n"
#define NO_FACULTY_ID "No faculty could be found for the given ID."
#define FACULTY_ID_DOESNT_EXIST "No Faculty could be found for the given Faculty ID$"
#define FACULTY_LOGIN_SUCCESS "Welcome Faculty you have successully logged in to System!"
#define FACULTY_MENU "1.Add new Course\n2. Remove offered Course\n3. View enrollments in Courses\n4. Password Change\n5. Press any other key to logout"
#define FACULTY_LOGOUT "Logging you out now dear faculty! Good bye!$"

//UPDATE 

#define ADMIN_LOGOUT "Logging out now! Thankyou.$"

#define STUDENT_FILE "./records/student.txt"
#define FACULTY_FILE "./records/faculty.txt"
#define COURSE_FILE "./records/course.txt"

#endif