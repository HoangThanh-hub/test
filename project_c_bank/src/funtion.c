
#include <string.h>
#include <stdbool.h>
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#define MAX 100
#include"/Users/tranhoangthanh/Documents/project_c_bank/include/datatype.h"
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

//khoa hoac mở khoá
void lockOrUnlockUser() {
    char searchId[10];
    int found = 0;

    FILE *file = fopen("user.bin", "rb+");  // Mở file để đọc và ghi
    if (!file) {
        printf("No users found in the system!\n");
        return;
    }

    printf("Enter user ID to lock/unlock: ");
    scanf("%s", searchId);

    struct User user;

    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.userId, searchId) == 0) {
            found = 1;
            printf("User ID: %s\n", user.userId);
            printf("Current Status: %s\n", user.status ? "Open" : "Close");

            int confirm;
            if (user.status == 1) {
                printf("Confirm lock? (1: Yes, 0: No): ");
            } else {
                printf("Confirm unlock? (1: Yes, 0: No): ");
            }
            scanf("%d", &confirm);

            if (confirm == 1) {
                user.status = !user.status;  // Đảo trạng thái
                fseek(file, -sizeof(struct User), SEEK_CUR);  // Quay lại vị trí user trong file
                fwrite(&user, sizeof(struct User), 1, file);  // Ghi đè dữ liệu mới

                printf("User status updated successfully! New status: %s\n", user.status ? "Open" : "Close");
            } else {
                printf("Operation cancelled.\n");
            }
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("User ID not found!\n");
    }
}



// chi tiet nguoi dung
void detailUser(){
    char searchId[10];
    int found = 0;
    system("clear");

    FILE *userFile = fopen("/Users/tranhoangthanh/Documents/project_c_bank/cmake-build-debug/user.bin", "rb");
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
            printf("Phone Number: %s\n", user.phone);
            printf("Birthday: %d/%d/%d\n", user.dateOfBirth.day, user.dateOfBirth.month, user.dateOfBirth.year);
            printf("Gender: %s\n", user.gender ? "Male" : "Female");
            printf("Status: %s\n", user.status ? "Open" : "Close");
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

    FILE *file = fopen("/Users/tranhoangthanh/Documents/project_c_bank/cmake-build-debug/user.bin", "rb");
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
        printf("+--------------+----------------+-------------+---------------------+--------+\n");
        printf("| ID           | Name           | Phone       | Email               | Status |\n");
        printf("+--------------+----------------+-------------+---------------------+--------+\n");

        while (fread(&temp, sizeof(struct User), 1, file) != 0) {
            if (strstr(temp.userName, searchName) != NULL) {
                printf("| %-12s | %-14s | %-19s | %-11s | %-6s |\n",
                       temp.userId,
                       temp.userName,
                       temp.phone,
                       temp.email,
                       temp.status ? "Open" : "Close");
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

//check xem co bi trung kh
int isUserExists(const char *value, int type) {
    FILE *file = fopen("/Users/tranhoangthanh/Documents/project_c_bank/cmake-build-debug/user.bin", "rb");
    if (!file) return 0; // Nếu file không tồn tại, không có dữ liệu trùng

    struct User temp;
    while (fread(&temp, sizeof(temp), 1, file)) {
        if ((type == 1 && strcmp(temp.userId, value) == 0) ||
            (type == 2 && strcmp(temp.email, value) == 0) ||
            (type == 3 && strcmp(temp.phone, value) == 0)) {
            fclose(file);
            return 1;  // Dữ liệu đã tồn tại
            }
    }
    fclose(file);
    return 0;  // Không có dữ liệu trùng
}


//doc du lieu file danh sach ng dung
void readUserData() {
    FILE *file;
    file = fopen("/Users/tranhoangthanh/Documents/project_c_bank/cmake-build-debug/user.bin", "rb");
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

    }

    fclose(file);
}

    //them user
    void addUser() {
        FILE *file = fopen("user.bin", "ab");
        if (file == NULL) {
            printf("can't open\n");
            return;
        }

            struct User user;

        do{
            printf("Enter the id: ");
            fgets(user.userId, sizeof(user.userId), stdin);
            user.userId[strcspn(user.userId ,"\n")] = '\0';
        } while (isUserExists(user.userId, 1) && printf(" ID already exists! Try again.\n"));

            printf("Enter the name: ");
            fgets(user.userName, sizeof(user.userName), stdin);
            user.userName[strcspn(user.userName ,"\n")] = '\0';

        do{
            do {
                printf("Enter the Email: ");
                fgets(user.email, sizeof(user.email), stdin);
                user.email[strcspn(user.email,"\n")] = '\0';
                if (!checkEmail(user.email)) {
                    printf("Invalid email! Email must contain '@'. Please try again.\n");
                }
            } while (!checkEmail(user.email));
        } while (isUserExists(user.email, 2) && printf(" Email already exists! Try again.\n"));
    do{
        do {
            printf("Enter the Email: ");
            fgets(user.email1, sizeof(user.email1), stdin);
            user.email1[strcspn(user.email1,"\n")] = '\0';
            if (!checkEmail(user.email1)) {
                printf("Invalid email! Email must contain '@'. Please try again.\n");
            }
        } while (!checkEmail(user.email1));
    } while (isUserExists(user.email1, 2) && printf(" Email already exists! Try again.\n"));


        // do{
        //     do {
        //         printf("Enter the Phone Number: ");
        //         fgets(user.phone, sizeof(user.phone), stdin);
        //         user.phone[strcspn(user.phone,"\n")] = '\0';
        //         if (!checkPhoneNumber(user.phone)) {
        //             printf("Invalid phone number! Must start with 0 and have 10 digits. Please try again.\n");
        //         }
        //     } while (!checkPhoneNumber(user.phone));
        // } while (isUserExists(user.phone, 3) && printf(" Phone Number already exists! Try again.\n"));

            printf("Enter the gender (1: Male, 0: Female): ");
            scanf("%d", &user.gender);

            printf("Enter the status (1: open ,0: close): ");
            scanf("%d", &user.status);


            printf("Enter the Date of Birth:\n");
            printf("   Enter the Day: ");
            scanf("%d", &user.dateOfBirth.day);
            printf("   Enter the Month: ");
            scanf("%d", &user.dateOfBirth.month);
            printf("   Enter the Year: ");
            scanf("%d", &user.dateOfBirth.year);



            getchar();



            fwrite(&user, sizeof(struct User), 1, file);
            fclose(file);

            printf("User added successfully!\n");
        };


//bang danh sach
void listUser() {
    system("clear");
    FILE *file = fopen("/Users/tranhoangthanh/Documents/project_c_bank/cmake-build-debug/user.bin", "rb");
    if (file == NULL) {
        printf("can't open\n");
        return;
    }



    printf("+--------------+----------------+-------------+---------------------+--------+\n");
    printf("| ID           | Name           | Email1       | Email               | Status |\n");
    printf("+--------------+----------------+-------------+---------------------+--------+\n");


    struct User temp;
    while (fread(&temp, sizeof(temp), 1, file) != 0){
        printf("| %-12s | %-14s | %-19s | %-19s | %-6s |\n",
               temp.userId,
               temp.userName,
               temp.email1,
               temp.email,
               temp.status ? "Open" : "Close");
        printf("+--------------+----------------+-------------+---------------------+--------+\n");
    }
    fclose(file);

}

// sap xep
void sortUsersByName() {
    int userCount = 0;

    FILE *file = fopen("/Users/tranhoangthanh/Documents/project_c_bank/cmake-build-debug/user.bin", "rb");
    if (!file) {
        printf("Error: No users found!\n");
        return;
    }

    // Load users into an array
    while (fread(&users[userCount], sizeof(struct User), 1, file)) {
        userCount++;
    }
    fclose(file);

    if (userCount == 0) {
        printf("No users available to sort.\n");
        return;
    }

    int choice;
    printf("\nChoose sorting order:\n");
    printf("1. Sort in Ascending order (A → Z)\n");
    printf("2. Sort in Descending order (Z → A)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  // Fix input buffer issue

    // Bubble Sort
    struct User temp;
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            int compareResult = strcmp(users[j].userName, users[j + 1].userName);
            if ((choice == 1 && compareResult > 0) || (choice == 2 && compareResult < 0)) {
                temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
    file = fopen("/Users/tranhoangthanh/Documents/project_c_bank/cmake-build-debug/user.bin", "wb");
    fwrite(users, sizeof(struct User), userCount, file);
    fclose(file);

    printf("\nUser list after sorting:\n");
    listUser();  // Display the sorted user list
}

//hien thi man hinh rieng
void clearScreen() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}


//3 menu admin
void menuAdmin() {
    while (1) {
        clearScreen();

    printf("\n\n***Bank Management System Using C***\n");
    printf("=====================================\n");
    printf("              MENU\n");
    printf("====================================\n");
    printf("[1] Show all user\n");
    printf("[2] Add a new user\n");
    printf("[3] Find users\n");
    printf("[4] Show detail an user\n");
    printf("[5] Sort users\n");
    printf("[6] Lock (unlock) an user\n");
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
            sortUsersByName();
        break;
        case 6:
            lockOrUnlockUser();
        break;
        case 0:
            break;
        default:
            printf("Invalid Choice\n");
    }
        printf("\nPress Enter to return");
        getchar();  // Đợi người dùng nhấn Enter
    }
};

//1 menu chinh
void mainMenu() {
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
}








