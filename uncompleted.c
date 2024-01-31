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
};

struct User users[50];

int userCount = 0;

// Function declaration
void createFile(const char *file_name);
int isStrongPassword(const char *password);
int emailChecker(const char *username);
void shareCredits(struct User *sender, struct User *receiver);
void registration();
int login();
void readFile(const char *file_name);
void appendFile(const char *file_name, const char *username, const char *hashed_password, int user_point);
void loadUserData(const char *file_name); // Added function to load user data
// End of declaration

int loggedInUserIndex = -1; // to track the logged-in user's credit

int main()
{
    int choice;

    // Load user data from the file
    loadUserData("Data.txt");

    if (access("Data.txt", F_OK) != -1)
    {
        printf("The data file is ready...\n");
    }
    else
    {
        createFile("Data.txt");
    }

    do
    {
        printf("\n1. to Login\n2. to Register\n3. to Exit");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (login())
            {
                if (userCount >= 5)
                {
                    printf("---Successfully loggend in---\n");
                    while (loggedInUserIndex != -1)
                    { // Check if the user has logged in
                        int option;
                        printf("Current credit : %d\n", users[loggedInUserIndex].credits);
                        printf("\n1. to share\n2. to logout\nEnter your choice : ");
                        scanf(" %d", &option);

                        if (option == 1)
                        {
                            char recipient[50];
                            printf("Enter the username to share credits with: ");
                            scanf("%s", recipient);

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
                                shareCredits(&users[loggedInUserIndex], recipientUser); // returning the address of it
                            }
                            else
                            {
                                printf("Recipient not found.\n");
                                continue;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    printf("We need at least 5 users to operate this program!\n");
                }
            }
            else
            {
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

    } while (choice != 3);

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

void appendFile(const char *file_name, const char *username, const char *hashed_password, int user_point)
{
    FILE *file = fopen(file_name, "a");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    // Format the data and append it to the file
    if (userCount < 3)
    {
        fprintf(file, "Admin %s %s %d\n", username, hashed_password, user_point);
    }
    else
    {
        fprintf(file, "%d. %s %s %d\n", userCount-2, username, hashed_password, user_point);
    }

    fclose(file);
}

void loadUserData(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        perror("Error opening file for reading");
        return;
    }

    char action[10]; // To store the action (register or transfer)

    while (fscanf(file, "%s", action) != EOF)
    {
        if (strcmp(action, "transfer") == 0)
        {
            // Handle transfer record
            char source[50], destination[50];
            int amount;

            fscanf(file, "%s %s %d", source, destination, &amount);

            // Find the source and destination users
            struct User *sourceUser = NULL, *destinationUser = NULL;
            for (int i = 0; i < userCount; i++)
            {
                if (strcmp(users[i].name, source) == 0)
                {
                    sourceUser = &users[i];
                }
                else if (strcmp(users[i].name, destination) == 0)
                {
                    destinationUser = &users[i];
                }

                if (sourceUser != NULL && destinationUser != NULL)
                {
                    // Transfer logic for loadfunc
                    if (sourceUser->credits >= amount)
                    {
                        sourceUser->credits -= amount;
                        destinationUser->credits += amount;
                    }
                    break; // Both users found
                }
            }

            if (sourceUser == NULL || destinationUser == NULL)
            {
                printf("Source or destination user not found.\n");
            }
        }
        else
        {
            // Handle user registration record
            fscanf(file, "%s %s %d", users[userCount].name, users[userCount].password, &users[userCount].credits);

            // Check if userCount exceeds the array size
            if (userCount >= sizeof(users) / sizeof(users[0]))
            {
                printf("Warning: Maximum user limit reached.\n");
                break;
            }
        }
    }

    // Increment the userCount for the next user
    userCount++;

    fclose(file);
}

void readFile(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    char buffer[256]; // Adjust the buffer size as needed

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Process each line as needed
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
        else if (ispunct(password[i]) || isspace(password[i]))
        {
            hasSpecial++;
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
        receiver->credits += creditToShare; // arrow usage for pointers only
        sender->credits -= creditToShare;

        // Record the transfer log in the file
        FILE *file = fopen("Data.txt", "a");

        if (file == NULL)
        {
            printf("Error opening file: Data.txt\n");
            return;
        }

        fprintf(file, "transfer %s %s %d\n", sender->name, receiver->name, creditToShare);

        fclose(file);

        printf("Credits shared successfully!\n");
        printf("The current credits %s (%d credits) and %s (%d credits)\n\n", sender->name, sender->credits, receiver->name, receiver->credits);
    }
    else
    {
        printf("Insufficient credits to share.\n");
    }
}

void registration()
{
    if (userCount < 50)
    {
        char username[50];
        char password[50];
        char confirmPass[50];
        int uExists = 0;

        printf("Enter your email : ");
        scanf("%s", username);

        if (!emailChecker(username))
        {
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
            printf("E-mail already exists. Try another name...\n");
        }
        else
        {
            strcpy(users[userCount].name, username);
            printf("Enter password : ");
            scanf("%s", password);

            if (!isStrongPassword(password))
            {
                printf("Password is not strong enough.\n(The password must be at least 8 characters, at least 1 upper case, digit and punctuation).\nPlease use a stronger password.\n");
                return;
            }

            printf("Confirm password : ");
            scanf("%s", confirmPass);

            if (strcmp(password, confirmPass) == 0)
            {
                strcpy(users[userCount].password, password);
                if (userCount < 4)
                {
                    printf("Successfully Registered as an Admin!!!\n");
                    users[userCount].credits = INITIAL_ADMIN_CREDITS;
                }
                else
                {
                    printf("Successfully Registered!!!\n");
                    users[userCount].credits = INITIAL_CREDITS;
                }
                printf("Current credit : %d\n", users[userCount].credits);

                appendFile("Data.txt", users[userCount].name, users[userCount].password, users[userCount].credits);
                userCount++;
            }
            else
            {
                printf("Password doesn't match\n");
            }
        }
    }
    else
    {
        printf("User limit reached (50 users) :( ");
    }
}

int login()
{
    char username[50];
    char password[50];

    printf("Enter your e-mail : ");
    scanf("%s", username);
    printf("Enter password : ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            loggedInUserIndex = i;
            return 1;
        }
    }
    return 0;
}
