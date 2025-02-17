

#ifndef FUNCTION_H
#define FUNCTION_H

#endif //FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "//Users/tranhoangthanh/Documents/project_c_bank/include/datatype.h"


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
// sap xep
void sortUsersByName();
//khoá họăc mở khoá
void lockOrUnlockUser();
//hien thi man hinh rieng
void clearScreen();
//check xem co bi trung kh
int isUserExists(const char *value, int type);