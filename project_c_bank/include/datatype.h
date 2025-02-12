//
// Created by tran hoang thanh on 12/2/25.
//

#ifndef DATATYPE_H
#define DATATYPE_H

#endif //DATATYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
//tao struct


//1 date
struct Date{
    int day, month, year;
};


//2 account infor

struct AccountInfo {
    char userId[10];
    float balance;
    bool status;
    char userName[10];
    char password[10];
};



// 3 user

struct User {
    char userId[10];
    char userName[20];
    struct Date dateOfBirth;
    int gender;
    char phoneNumber[15];
    char email[25];
};


