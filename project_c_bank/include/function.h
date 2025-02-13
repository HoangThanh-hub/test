

#ifndef FUNCTION_H
#define FUNCTION_H

#endif //FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "/Users/tranhoangthanh/Documents/project_bankManagement/include/datatype.h"


// dinh nghia ham


void mainMenu();



void menuAdmin();

void listUser();



int checkEmail(const char *email) ;

int checkPhoneNumber(char phone[]);
//doc du lieu file danh sach ng dung
void readUserData();

//them user
void addUser();
// tim kiem nguoi dung
void searchUserByName();
// chi tiet nguoi dung
void detailUser();
//back
void backToMenu();