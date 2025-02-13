
#include <string.h>
#include <stdbool.h>
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#define MAX 100
#include"/Users/tranhoangthanh/Documents/project_bankManagement/include/datatype.h"
//khai thac ham

struct User users[MAX];
int size  = 0;



//back
void backToMenu() {
    char option;
    printf("\nGo back(b)? or Exit(0)?: ");
    scanf(" %c", &option);
    if (option == 'b') {
        return;
    } else if (option == '0') {
        exit(0);
    }
}

// chi tiet nguoi dung
void detailUser(){
    char searchId[10];
    int found = 0;
    system("clear");

    FILE *userFile = fopen("user.bin", "rb");
    if (userFile == NULL) {
        printf("No users found in the system!\n");
        return;
    }
    printf("Enter user ID to search: ");
    fflush(stdin);
    fgets(searchId, sizeof(searchId), stdin);
    searchId[strcspn(searchId, "\n")] = '\0';

    struct User user;

    // Search for the user
    while (fread(&user, sizeof(struct User), 1, userFile)) {
        if (strcmp(user.userId, searchId) == 0) {
            found = 1;
            printf("\nUser Details:\n");
            printf("------------------------------------------------------\n");
            printf("ID: %s\n", user.userId);
            printf("Name: %s\n", user.userName);
            printf("Email: %s\n", user.email);
            printf("Phone Number: %s\n", user.phoneNumber);
            printf("Birthday: %d/%d/%d\n", user.dateOfBirth.day, user.dateOfBirth.month, user.dateOfBirth.year);
            printf("------------------------------------------------------\n");
            break;
        }
    }
    fclose(userFile);

    if (!found) {
        printf("No user found with ID: %s\n", searchId);
        return;
    }
}




//tim kiem nguoi dung
void searchUserByName() {
    char searchName[50];
    int found = 0;
    system("clear");

    FILE *file = fopen("user.bin", "rb");
    if (file == NULL) {
        printf("No users found in the system!\n");
        return;
    }

    printf("Enter the name to search: ");
    fflush(stdin);
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    struct User temp;
    // First, check if there are any matches
    while (fread(&temp, sizeof(struct User), 1, file) != 0) {
        if (strstr(temp.userName, searchName) != NULL) {
            found = 1;
            break;
        }
    }

    rewind(file); // Reset file pointer to beginning

    if (!found) {
        printf(" No users found with the name \"%s\".\n", searchName);
    } else {
        printf("\n Search Results:\n");
        printf("+--------------+----------------+---------------------+-------------+--------+\n");
        printf("| ID           | Name           | Email               | Phone       | Status |\n");
        printf("+--------------+----------------+---------------------+-------------+--------+\n");

        while (fread(&temp, sizeof(struct User), 1, file) != 0) {
            if (strstr(temp.userName, searchName) != NULL) {
                printf("| %-12s | %-14s | %-19s | %-11s | %-6s |\n",
                       temp.userId,
                       temp.userName,
                       temp.email,
                       temp.phoneNumber,
                       "open");
                printf("+--------------+----------------+---------------------+-------------+--------+\n");
                found = 1;
            }
        }
    }

    fclose(file);
}

//check phone number
int checkPhoneNumber(char phone[]) {

    if (phone[0] != '0') {
        return 0;
    }


    return 1;
}

//check email
int checkEmail(const char *email) {
    return strchr(email, '@') != NULL;
}


//doc du lieu file danh sach ng dung
void readUserData() {
    FILE *file;
    file = fopen("user.bin", "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    int i = 0;
    struct User temp;
    while (fread(&temp, sizeof(temp), 1, file) != 0) {
        users[i] = temp;
        i++;
        size++;
        printf("%s-%s\n", temp.phoneNumber, temp.userName);

    }

    fclose(file);
}

    //them user
    void addUser() {
    system("clear");
        FILE *file = fopen("user.bin", "ab");
        if (file == NULL) {
            printf("can't open\n");
            return;
        }

            struct User user;

            printf("Enter the id: ");
            fgets(user.userId, sizeof(user.userId), stdin);
            user.userId[strcspn(user.userId ,"\n")] = '\0';
            printf("Enter the name: ");
            fgets(user.userName, sizeof(user.userName), stdin);
            user.userName[strcspn(user.userName ,"\n")] = '\0';
            do {
                printf("Enter the Email: ");
                fgets(user.email, sizeof(user.email), stdin);
                user.email[strcspn(user.email,"\n")] = '\0';
                if (!checkEmail(user.email)) {
                    printf("Invalid email! Email must contain '@'. Please try again.\n");
                }
            } while (!checkEmail(user.email));
            do {
                printf("Enter the Phone Number: ");
                fgets(user.phoneNumber, sizeof(user.phoneNumber), stdin);
                user.phoneNumber[strcspn(user.phoneNumber,"\n")] = '\0';
                if (!checkPhoneNumber(user.phoneNumber)) {
                    printf("Invalid phone number! Must start with 0 and have 10 digits. Please try again.\n");
                }else {
                    break;
                }
            } while (1);

            printf("Enter the gender (1: Male, 2: Female): ");
            scanf("%d", &user.gender);


            printf("Enter the Date of Birth:\n");
            printf("   Enter the Day: ");
            scanf("%d", &user.dateOfBirth.day);
            printf("   Enter the Month: ");
            scanf("%d", &user.dateOfBirth.month);
            printf("   Enter the Year: ");
            scanf("%d", &user.dateOfBirth.year);



            fwrite(&user, sizeof(struct User), 1, file);
            fclose(file);

            printf("User added successfully!\n");
        };


//bang danh sach
void listUser() {
    system("clear");
    FILE *file = fopen("user.bin", "rb");
    if (file == NULL) {
        printf("can't open\n");
        return;
    }



    printf("+--------------+----------------+---------------------+-------------+--------+\n");
    printf("| ID           | Name           | Email               | Phone       | Status |\n");
    printf("+--------------+----------------+---------------------+-------------+--------+\n");


    struct User temp;
    while (fread(&temp, sizeof(temp), 1, file) != 0){
        printf("| %-12s | %-14s | %-19s | %-11s | %-6s |\n",
               temp.userId,
               temp.userName,
               temp.email,
               temp.phoneNumber,
               "open");
        printf("+--------------+----------------+---------------------+-------------+--------+\n");
    }
    fclose(file);

    printf("Go back (b)? or Exit (0)?: ");
}




//3 menu admin
void menuAdmin() {
    system("clear");
    printf("\n\n***Bank Management System Using C***\n");
    printf("=====================================\n");
    printf("              MENU\n");
    printf("====================================\n");
    printf("[1] Show all user\n");
    printf("[2] Add a new user\n");
    printf("[3] Find users\n");
    printf("[4] Show detail an user\n");
    printf("[5] Lock (unlock) an user\n");
    printf("[6] About us\n");
    printf("[0] Exit\n");
    printf("======================================\n");
    int choice1;
    printf("Please enter your choice: ");
    scanf("%d", &choice1);
    fflush(stdin);
    switch(choice1) {
        case 1:
            listUser();
            break;
        case 2:
            addUser();
            break;
        case 3:
            searchUserByName();
            break;
        case 4:
            detailUser();
            break;
        case 5:
            break;
        case 6:
            break;
        case 0:
            break;
        default:
            printf("Invalid Choice\n");
    }
};

//1 menu chinh
void mainMenu() {
    system("clear");
    printf("\n***Bank Management System Using C***\n\n");
    printf("====================================\n");
    printf("|        CHOOSE YOUR ROLE          |\n");
    printf("====================================\n");
    printf("[1] Admin\n");
    printf("[2] User\n");
    printf("[0] Exit the Program\n");
    printf("====================================\n");

    int choice;
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            menuAdmin();
        break;
        case 2:
            printf("User\n");
        break;
        case 0:
            exit(0);
        default:
            printf("Invalid Choice\n");
    }
    printf("\e[1;1H\e[2J");
};





