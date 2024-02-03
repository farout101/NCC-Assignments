#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define INITIAL_CREDITS 100
#define INITIAL_ADMIN_CREDITS 500

struct User
{
    char name[50];
    char password[50];
    int credits;
    int isAdmin;
    int isBan;
};

char testfile[20] = "data.txt";

struct User users[50];

int userCount = 0;

// Function declaration
int isNumeric(const char *str);
void createFile(const char *file_name);
int isStrongPassword(const char *password);
int emailChecker(const char *username);
void shareCredits(struct User *sender, struct User *receiver);
void registration();
int login();
void readFile(const char *file_name);
void appendFile(const char *file_name, struct User *user);
void loadUserData(const char *file_name);
void deleteUser();
void banUser();
void unbanUser();
// End of declaration

int loggedInUserIndex = -1; // to track the logged-in user's credit

int main()
{
    char choice[50];

    // Load user data from the file
    loadUserData(testfile);

    if (access(testfile, F_OK) != -1)
    {
        printf("The data file is ready...\n");
    }
    else
    {
        createFile(testfile);
    }

    do
    {
        printf("\n---Welcome to Credit Management System---\n");

        printf("\n1. to Login\n2. to Register\n3. to Exit");
        printf("\nEnter your choice : ");
        scanf(" %[^\n]", choice);

        if (strcmp(choice, "1") == 0)
        {
            if (login())
            {
                system("cls");
                if (users[loggedInUserIndex].isAdmin == 0)
                {
                    printf("---Successfully logged in as user [%s]---\n", users[loggedInUserIndex].name);
                }
                else
                {
                    printf("---Successfully logged in as admin [%s]---\n", users[loggedInUserIndex].name);
                }
                char option[50];

                // Display additional options for admins
                if (users[loggedInUserIndex].isAdmin)
                {
                    do
                    {
                        printf("--Admin Menu--\n\n");

                        printf("Current credit : %d\n", users[loggedInUserIndex].credits);
                        printf("\n1. to share\n2. to delete user\n3. to ban user\n4. to unban user\n5. to logout\nEnter your choice : ");
                        scanf(" %[^\n]", option);

                        if (strcmp(option, "1") == 0)
                        {
                            char recipient[50];
                            printf("Enter the username to share credits with: ");
                            scanf(" %[^\n]", recipient);

                            // Find the recipient user
                            struct User *recipientUser = NULL;
                            for (int j = 0; j < userCount; j++)
                            {
                                if (strcmp(users[j].name, recipient) == 0 && users[j].isBan == 0)
                                {
                                    recipientUser = &users[j];
                                    break;
                                }
                            }

                            if (recipientUser != NULL)
                            {
                                shareCredits(&users[loggedInUserIndex], recipientUser);
                                continue;
                            }
                            else
                            {
                                system("cls");
                                printf("Recipient not found.\n");
                                continue;
                            }
                        }
                        if (strcmp(option, "2") == 0)
                        {
                            deleteUser();
                            continue;
                        }

                        if (strcmp(option, "3") == 0)
                        {
                            banUser();
                            continue;
                        }

                        if (strcmp(option, "4") == 0)
                        {
                            unbanUser();
                            continue;
                        }
                        if (strcmp(option, "5") == 0)
                        {
                            system("cls");
                            printf("You have logged out!\n");
                            loggedInUserIndex = -1; // Set loggedInUserIndex to -1 to stay in the main loop
                            break;
                        }

                        else
                        {
                            system("cls");
                            printf("Invalid choice. Please try again. \n");
                            continue;
                        }

                    } while (strcmp(option, "5") != 0);
                }
                else
                {
                    do
                    {
                        printf("--User Menu--\n\n");

                        char option[50];
                        printf("Current credit : %d\n", users[loggedInUserIndex].credits);
                        printf("\n1. to share\n2. to logout\nEnter your choice : ");
                        scanf(" %[^\n]", option);

                        if (strcmp(option, "1") == 0)
                        {
                            char recipient[50];
                            printf("Enter the username to share credits with: ");
                            scanf(" %[^\n]", recipient);

                            // Find the recipient user
                            struct User *recipientUser = NULL;
                            for (int j = 0; j < userCount; j++)
                            {
                                if (strcmp(users[j].name, recipient) == 0)
                                {
                                    recipientUser = &users[j];
                                    break;
                                }
                            }

                            if (recipientUser != NULL)
                            {
                                shareCredits(&users[loggedInUserIndex], recipientUser);
                                continue;
                            }
                            else
                            {
                                system("cls");
                                printf("Recipient not found.\n");
                                continue;
                            }
                        }
                        else if (strcmp(option, "2") == 0)
                        {
                            system("cls");
                            printf("You have logged out!\n");
                            loggedInUserIndex = -1; // Set loggedInUserIndex to -1 to stay in the main loop
                            break;
                        }
                        else
                        {
                            system("cls");
                            printf("Invalid choice. Please try again. \n");
                            continue;
                        }
                    } while (strcmp(option, "2") != 0);
                }
            }
            continue;
        }
        if (strcmp(choice, "2") == 0)
        {
            system("cls");
            registration();
            continue;
        }
        if (strcmp(choice, "3") == 0)
        {
            system("cls");
            printf("The program terminated\n");
            continue;
        }

        else
        {
            system("cls");
            printf("Invalid choice. Please try again. \n");
        }
    } while (strcmp(choice, "3") != 0);

    return 0;
}

void createFile(const char *file_name)
{
    FILE *file = fopen(file_name, "w");

    if (file == NULL)
    {
        perror("Error creating file!");
    }
    else
    {
        printf("The file %s is successfully created...\n", file_name);
    }
}

void appendFile(const char *file_name, struct User *user)
{
    FILE *file = fopen(file_name, "a");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    // Format the data and append it to the file
    fprintf(file, "%s %s %d %d %d\n", user->name, user->password, user->credits, user->isAdmin, user->isBan);

    fclose(file);
}

void loadUserData(const char *file_name)
{
    userCount = 0;

    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        perror("Error opening file for reading");
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Handle user registration record
        if (sscanf(buffer, "%s %s %d %d %d", users[userCount].name, users[userCount].password, &users[userCount].credits, &users[userCount].isAdmin, &users[userCount].isBan) != 5)
        {
            printf("Error reading user registration record.\n");
            break;
        }

        userCount++;

        if (userCount >= sizeof(users) / sizeof(users[0]))
        {
            printf("Warning: Maximum user limit reached.\n");
            break;
        }
    }
    fclose(file);
}

// Unused function
void readFile(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file);
}

int isStrongPassword(const char *password)
{
    int len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < len; i++)
    {
        if (isupper(password[i]))
        {
            hasUpper++;
        }
        else if (islower(password[i]))
        {
            hasLower++;
        }
        else if (isdigit(password[i]))
        {
            hasDigit++;
        }
        else if (ispunct(password[i]))
        {
            hasSpecial++;
        }
        else if (isspace(password[i]))
        {
            return 0;
        }
    }

    if (len >= 6 && hasUpper && hasLower && hasDigit && hasSpecial)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int emailChecker(const char *username)
{
    int len = strlen(username);
    int atCount = 0;
    int dotCount = 0;

    for (int i = 0; i < len; i++)
    {
        if (username[i] == '@')
        {
            atCount++;
        }
        else if (username[i] == '.')
        {
            dotCount++;
        }
    }

    if (atCount == 1 && dotCount >= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void shareCredits(struct User *sender, struct User *receiver)
{
    int creditToShare;

    printf("Your current credit : %d\n", sender->credits);
    printf("Enter the amount of credits to share : ");
    scanf("%d", &creditToShare);

    if (creditToShare <= sender->credits)
    {
        receiver->credits += creditToShare;
        sender->credits -= creditToShare;

        FILE *file = fopen(testfile, "r");
        FILE *tempFile = fopen("tempfile.txt", "w");

        if (file == NULL || tempFile == NULL)
        {
            printf("Error opening files.\n");
            return;
        }

        // Copy records to the temporary file, updating the records for sender and receiver
        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(users[i].name, sender->name) == 0)
            {
                fprintf(tempFile, "%s %s %d %d %d\n", sender->name, sender->password, sender->credits, sender->isAdmin, sender->isBan);
            }
            else if (strcmp(users[i].name, receiver->name) == 0)
            {
                fprintf(tempFile, "%s %s %d %d %d\n", receiver->name, receiver->password, receiver->credits, receiver->isAdmin, receiver->isBan);
            }
            else
            {
                fprintf(tempFile, "%s %s %d %d %d\n", users[i].name, users[i].password, users[i].credits, users[i].isAdmin, users[i].isBan);
            }
        }

        fclose(file);
        fclose(tempFile);

        system("cls");
        // Replace the original file with the temporary file
        if (remove(testfile) == 0 && rename("tempfile.txt", testfile) == 0)
        {
            printf("User data updated successfully.\n");
        }
        else
        {
            printf("Error updating user data.\n");
        }

        printf("Credits shared successfully!\n");
        printf("The current credits %s (%d credits) and %s (%d credits)\n\n", sender->name, sender->credits, receiver->name, receiver->credits);
    }
    else
    {
        system("cls");
        printf("Insufficient credits to share.\n");
    }
}

void registration()
{

    system("cls");

    printf("---Registration---\n\n");

    if (userCount < 50)
    {
        char username[50];
        char password[50];
        char confirmPass[50];
        int uExists = 0;

        printf("Enter your email : ");
        scanf(" %[^\n]", username);

        if (!emailChecker(username))
        {
            system("cls");
            printf("Not a valid email. Please enter a valid email address. \n");
            return;
        }

        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(username, users[i].name) == 0)
            {
                uExists = 1;
                break;
            }
        }

        if (uExists)
        {
            system("cls");
            printf("E-mail already exists. Try another name...\n");
        }
        else
        {
            strcpy(users[userCount].name, username);
            printf("Enter password (no space is allowed): ");
            scanf(" %[^\n]", password);

            if (!isStrongPassword(password))
            {
                system("cls");
                printf("Password is not strong enough.\n(The password must be at least 8 characters, at least 1 upper case, digit and punctuation).\nPlease use a stronger password.\n");
                return;
            }

            printf("Confirm password : ");
            scanf(" %[^\n]", confirmPass);

            if (strcmp(password, confirmPass) == 0)
            {
                strcpy(users[userCount].password, password);

                // Set the isAdmin flag based on userCount
                users[userCount].isAdmin = (userCount < 3) ? 1 : 0;

                // Set the initial credits based on admin status
                users[userCount].credits = (users[userCount].isAdmin) ? INITIAL_ADMIN_CREDITS : INITIAL_CREDITS;

                if (users[userCount].isAdmin)
                {
                    system("cls");
                    printf("Successfully Registered as an Admin!!!\n");
                }
                else
                {
                    system("cls");
                    printf("Successfully Registered!!!\n");
                }

                printf("Current credit of [%s] : %d\n", users[userCount].name, users[userCount].credits);

                appendFile(testfile, &users[userCount]);
                userCount++;
            }
            else
            {
                system("cls");
                printf("Password doesn't match\n");
            }
        }
    }
    else
    {
        system("cls");
        printf("User limit reached (50 users) :( ");
    }
}

int login()
{
    system("cls");

    printf("---Login---\n\n");

    char username[50];
    char password[50];

    printf("Enter your e-mail : ");
    scanf(" %[^\n]", username);

    // Check if the user is banned
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0 && users[i].isBan == 1)
        {
            system("cls");
            printf("Your account has been banned. Please contact support.\n");
            return 0;
        }
    }

    printf("Enter password : ");
    scanf(" %[^\n]", password);

    // Authenticate the user
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            loggedInUserIndex = i;
            printf("---Successfully logged in---\n");
            return 1;
        }
    }

    // If the loop completes, the username or password is incorrect
    system("cls");
    printf("Invalid username or password. Please try again.\n");
    return 0;
}

void deleteUser()
{
    system("cls");

    printf("---Delete User---\n\n");

    char username[50];
    int userIndex = -1;

    printf("Enter the username to delete : ");
    scanf(" %[^\n]", username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0)
        {
            userIndex = i;
            break;
        }
    }

    if (userIndex != -1)
    {
        // Check if the user to be deleted is an admin or not
        if (!users[userIndex].isAdmin)
        {
            // Remove the user from the array
            for (int i = userIndex; i < userCount - 1; i++)
            {
                strcpy(users[i].name, users[i + 1].name);
                strcpy(users[i].password, users[i + 1].password);
                users[i].credits = users[i + 1].credits;
                users[i].isAdmin = users[i + 1].isAdmin;
                users[i].isBan = users[i + 1].isBan;
            }

            userCount--;

            // Update the file with the modified user data
            FILE *file = fopen(testfile, "w");

            if (file == NULL)
            {
                printf("Error opening file for writing.\n");
                return;
            }

            for (int i = 0; i < userCount; i++)
            {
                fprintf(file, "%s %s %d %d %d\n", users[i].name, users[i].password, users[i].credits, users[i].isAdmin, users[i].isBan);
            }

            fclose(file);

            system("cls");
            printf("User %s is deleted successfully.\n", username);
        }
        else
        {
            system("cls");
            printf("Admin accounts cannot be deleted.\n");
        }
    }
    else
    {
        system("cls");
        printf("User %s doesn't exist\n", username);
    }
}

void banUser()
{
    system("cls");
    char username[50];

    printf("---Ban User---\n\n");

    printf("Enter the username to ban : ");
    scanf(" %[^\n]", username);

    FILE *tempFile = fopen("tempfile.txt", "w");

    if (tempFile == NULL)
    {
        system("cls");
        printf("Error creating temporary file.\n");
        return;
    }

    int userBanned = 0;
    int track_user = 0;

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0)
        {
            track_user = 1;
            // Check if the user is an admin
            if (users[i].isAdmin == 1)
            {
                system("cls");
                printf("Admin accounts cannot be banned.\n");
                return;
            }
            else
            {
                // Update the ban status
                users[i].isBan = 1;

                system("cls");
                printf("The user %s has been banned.\n", username);
                userBanned = 1;
            }
        }

        // Copy other records to the temporary file
        fprintf(tempFile, "%s %s %d %d %d\n", users[i].name, users[i].password, users[i].credits, users[i].isAdmin, users[i].isBan);
    }

    if (track_user == 0)
    {
        system("cls");
        printf("User not found\n");
        remove("tempfile.txt");
        return;
    }

    fclose(tempFile);

    if (userBanned)
    {
        // Replace the original file with the temporary file only if a user was banned
        if (remove(testfile) == 0 && rename("tempfile.txt", testfile) == 0)
        {
            printf("User data updated successfully.\n");
        }
        else
        {
            printf("Error updating user data.\n");
        }
    }
    else
    {
        // No user was banned, remove the temporary file
        remove("tempfile.txt");
    }
}

void unbanUser()
{
    char username[50];
    system("cls");
    printf("<---Unban User--->\n\n");
    printf("Enter email to unban : ");
    scanf(" %[^\n]", username);
    FILE *tempFile = fopen("tempfile.txt", "w");
    if (tempFile == NULL)
    {
        system("cls");
        printf("Error creating temporary file.\n");
        return;
    }

    int userUnbanned = 0;
    int search_tracker = 0;
    for (int i = 0; i < userCount; i++)
    {

        if (strcmp(users[i].name, username) == 0)
        {
            search_tracker = 1;
            if (users[i].isBan == 1)
            {
                system("cls");
                users[i].isBan = 0;
                printf("The user is successfully unbanned.\n");
                userUnbanned = 1;
            }
            else
            {
                system("cls");
                printf("The user is not banned yet!\n");
            }
        }
        fprintf(tempFile, "%s %s %d %d %d\n", users[i].name, users[i].password, users[i].credits, users[i].isAdmin, users[i].isBan);
    }
    fclose(tempFile);
    if (search_tracker == 0)
    {
        system("cls");
        printf("User not found!\n");
        remove("tempfile.txt");
    }
    if (userUnbanned)
    {
        // Replace the original file with the temporary file only if a user was banned
        if (remove(testfile) == 0 && rename("tempfile.txt", testfile) == 0)
        {
            printf("User data updated successfully.\n");
        }
        else
        {
            printf("Error updating user data.\n");
        }
    }
    else
    {
        // No user was banned, remove the temporary file
        remove("tempfile.txt");
    }
}

int isNumeric(const char *str)
{

    for (int i = 0; str[i] != '\0'; i++)
    {
        // Check if the character is not a digit
        if (!isdigit(str[i]))
        {
            return 0; // Not a Number
        }
    }

    return 1; // Number
}
