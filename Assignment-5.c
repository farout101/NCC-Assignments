#include <stdio.h>
#include <string.h>
#include <ctype.h> 

#define INITIAL_CREDITS 100

struct User {
    char name[50];
    char password[50];
    int credits;
};

struct User users[50]; 

int userCount = 0;

int isStrongPassword(const char *password) {
    int len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) {
            hasUpper++;
        } else if (islower(password[i])) {
            hasLower++;
        } else if (isdigit(password[i])) {
            hasDigit++;
        } else if (ispunct(password[i]) || isspace(password[i])) {
            hasSpecial++;
        }
    }

    if (len >= 6 && hasUpper && hasLower && hasDigit && hasSpecial) {
        return 1;
    } else {
        return 0; 
    }
}

int emailChecker(const char *username) {
    int len = strlen(username);
    int atCount = 0;
    int dotCount = 0;

    for (int i=0; i<len; i++) {
        if(username[i] == '@') {
            atCount++;
        } else if (username[i] == '.') {
            dotCount++;
        }
    }

    if(atCount == 1 && dotCount >= 1) {
        return 1;
    } else {
        return 0;
    }
}

void shareCredits(struct User *sender, struct User *reciver) {
    int creditToShare;

    printf("Your current credit : %d\n", sender->credits);
    printf ("Enter the amount of credits to share : ");
    scanf ("%d", &creditToShare);

    if (creditToShare <= sender->credits) {
        reciver->credits += creditToShare;  // arrow usage for pointers only 
        sender->credits -= creditToShare;
        printf("Credits shared successfully!\n");
    } else {
        printf("Insufficient credits to share.\n");
    }

}

void registration() {
    if(userCount < 50) {
        char username[50];
        char password[50];  
        char confirmPass[50];
        int uExists = 0;

        printf("Enter your email : ");
        scanf("%s", username);

        if(!emailChecker(username)) {
            printf("Not a valid email. Please enter a valid email address. \n");
            return;
        }

        for (int i = 0; i < userCount; i++) {
            if (strcmp(username, users[i].name) == 0) {
                uExists = 1;
                break;
            }
        }

        if(uExists) {
            printf("Username already exists. Try another name...\n");
        } else {
            strcpy(users[userCount].name, username);
            printf("Enter password : ");
            scanf("%s", password);

            if (!isStrongPassword(password)) {
                printf("Password is not strong enough.\n(The password must be at least 8 characters, at least 1 upper case, digit and punctuatoin).\nPlease use a stronger password.\n");
                return;
            } 

            printf("Confirm password : ");
            scanf("%s", confirmPass);

            if(strcmp(password,confirmPass) == 0) {
                strcpy(users[userCount].password, password); 
                printf("Successfully Registered!!!\n");
                users[userCount].credits = INITIAL_CREDITS;
                printf("Current credit : %d\n", users[userCount].credits);
                userCount++;
            } else {
                printf("Password doesn't match\n");
            }
        }
    } else {
        printf("User limit reached (50 users) :( ");
    }
}

int loggedInUserIndex = -1; // to track the logged in user's credit 

int login() {
    char username[50];
    char password[50];

    printf("Enter username : ");
    scanf("%s", username);
    printf("Enter password : ");
    scanf("%s", password);

    for (int i=0; i<userCount; i++) {
        if (strcmp(users[i].name, username) == 0 && strcmp(users[i].password, password) == 0) {
            loggedInUserIndex = i;
            return 1;
        }
    }
    return 0;
}

int main() {
    
    int choice;

    do {                                                
        printf("\n1. to Login\n2. to Register\n3. to Exit");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if(login()) {
                    printf("\n\nSuccessfully Logged in\n");
                    if (userCount >= 5) {
                        if (loggedInUserIndex != -1) { // Check if the user has logged in
                            int option;
                            printf("Current credit : %d\n", users[loggedInUserIndex].credits);
                            printf("\n1. to share\n2. to logout\n");
                            scanf("%d", &option);

                            if (option == 1) {
                                char recipient[50];
                                printf("Enter the username to share credits with: ");
                                scanf("%s", recipient);

                                // Find the recipient user
                                struct User *recipientUser = NULL;
                                for (int j = 0; j < userCount; j++) {
                                    if (strcmp(users[j].name, recipient) == 0) {
                                        recipientUser = &users[j];
                                        break;
                                    }
                                }

                                if (recipientUser != NULL) {
                                    shareCredits(&users[loggedInUserIndex], recipientUser); // returning the address of it 
                                } else {
                                    printf("Recipient not found.\n");
                                    continue;
                                }
                            }
                        } else {
                            printf("Error: You must log in first.\n");
                        }
                    } else {
                        printf("We need at least 5 users to operate this program!\n");
                    }
                } else {
                    printf("Invalid username or password. Please try again.\n");
                }
            break;

            case 2:
                registration();
                break;
            
            case 3:
                printf("The program terminated\n");
                break;

            default: 
                printf("Invalid choice. Please try again. \n");
        }

    } while(choice != 3);

    return 0;
}