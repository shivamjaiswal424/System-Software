#ifndef ADMIN_FUNCTIONS
#define ADMIN_FUNCTIONS
#include "./common.h"


bool admin_operation_handler(int connectionFD);
bool add_student();
bool add_faculty();
bool activeDeactiveStudent();
bool update();

bool admin_operation_handler(int connectionFD){
    if(login_handler(0,connectionFD,NULL)){

    }
    else{
        return false;
    }
    return true;
}