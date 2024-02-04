#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int score;
};

// Function to find the student with the highest score
struct Student highestScore(struct Student students[], int size) {
    struct Student highest = students[0];

    for (int i = 1; i < size; i++) {
        if (students[i].score > highest.score) {
            highest = students[i];
        }
    }

    return highest;
}

// Function to check if the student passed or failed
void passOrFail(struct Student students[], int size) {
    printf("\nStudents who passed...\n");
    for (int i = 0; i < size; i++) {
        if (students[i].score >= 50) {
            printf("%s\n", students[i].name);
        } else {
            printf("%s (Failed)\n", students[i].name);        }
    }
}

// Function to find students with scores above the average
void aboveAvg(struct Student students[], int size) {
    float total = 0;
    for (int i = 0; i < size; i++) {
        total += students[i].score;
    }
    float average = total / size;

    printf("\nStudents who scores above average :\n");
    for (int i = 0; i < size; ++i) {
        if (students[i].score > average) {
            printf("%s\n", students[i].name);
        }
    }
}

int main() {
    int numStudents;
    printf("Enter the number of students: ");
    scanf("%d", &numStudents);
    getchar(); // Clearing the input buffer

    struct Student students[numStudents];

    // Input data for the specified number of students
    for (int i = 0; i < numStudents; ++i) {
        printf("Enter name of student %d: ", i + 1);
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove newline from fgets

        printf("Enter score of student %d: ", i + 1);
        scanf("%d", &students[i].score);
        getchar(); // Clearing the input buffer
    }

    // Find the student with the highest score
    struct Student highestScoreStudent = highestScore(students, numStudents);

    printf("\nStudent with the highest score:\n");
    printf("Name: %s\n", highestScoreStudent.name);
    printf("Score: %d\n", highestScoreStudent.score);

    passOrFail(students, numStudents);
    aboveAvg(students, numStudents);

    return 0;
}
