#include <stdio.h>
#include <string.h>

// Define the Student structure
struct Student {
    int roll;
    char name[50];
    float marks1, marks2, marks3;
    float average;
    char grade;
    int position;
};

struct Student students[100]; // Array of 100 students
int count = 0; // Tracks how many students are stored

// Function to calculate grade from average marks
char calculateGrade(float average) {
    if (average >= 90) return 'A';
    else if (average >= 80) return 'B';
    else if (average >= 70) return 'C';
    else if (average >= 60) return 'D';
    else return 'F';
}

// Function to calculate positions (based on average)
void calculatePositions() {
    int index[100];
    for (int i = 0; i < count; i++)
        index[i] = i;

    // Sort indices by average marks (Bubble Sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[index[j]].average < students[index[j + 1]].average) {
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }

    // Assign position based on sorted order
    for (int i = 0; i < count; i++) {
        students[index[i]].position = i + 1;
    }
}

// Add a new student
void addStudent() {
    printf("Enter roll number: ");
    scanf("%d", &students[count].roll);
    printf("Enter name: ");
    scanf(" %[^\n]", students[count].name);
    printf("Enter marks for subject 1: ");
    scanf("%f", &students[count].marks1);
    printf("Enter marks for subject 2: ");
    scanf("%f", &students[count].marks2);
    printf("Enter marks for subject 3: ");
    scanf("%f", &students[count].marks3);

    float avg = (students[count].marks1 + students[count].marks2 + students[count].marks3) / 3;
    students[count].average = avg;
    students[count].grade = calculateGrade(avg);

    count++;
    calculatePositions();
}

// Delete student by roll number
void deleteStudent() {
    int roll, found = 0;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            // Shift data left
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            found = 1;
            printf("Student deleted.\n");
            calculatePositions();
            break;
        }
    }
    if (!found) printf("Student not found.\n");
}

// Update student marks and name
void updateStudent() {
    int roll, found = 0;
    printf("Enter roll number to update: ");
    scanf("%d", &roll);
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new marks for subject 1: ");
            scanf("%f", &students[i].marks1);
            printf("Enter new marks for subject 2: ");
            scanf("%f", &students[i].marks2);
            printf("Enter new marks for subject 3: ");
            scanf("%f", &students[i].marks3);

            students[i].average = (students[i].marks1 + students[i].marks2 + students[i].marks3) / 3;
            students[i].grade = calculateGrade(students[i].average);
            found = 1;
            printf("Student updated.\n");
            calculatePositions();
            break;
        }
    }
    if (!found) printf("Student not found.\n");
}

// Display all student records
void displayAll() {
    if (count == 0) {
        printf("No student records.\n");
        return;
    }

    printf("\nAll Student Records:\n");
    for (int i = 0; i < count; i++) {
        printf("Roll: %d, Name: %s, Marks: %.2f %.2f %.2f, Avg: %.2f, Grade: %c, Position: %d\n",
               students[i].roll, students[i].name,
               students[i].marks1, students[i].marks2, students[i].marks3,
               students[i].average, students[i].grade, students[i].position);
    }
}

// Display one student by roll number
void displayOne() {
    int roll, found = 0;
    printf("Enter roll number to display: ");
    scanf("%d", &roll);
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Roll: %d, Name: %s, Marks: %.2f %.2f %.2f, Avg: %.2f, Grade: %c, Position: %d\n",
                   students[i].roll, students[i].name,
                   students[i].marks1, students[i].marks2, students[i].marks3,
                   students[i].average, students[i].grade, students[i].position);
            found = 1;
            break;
        }
    }
    if (!found) printf("Student not found.\n");
}

// Main menu loop
int main() {
    int choice;
    while (1) {
        printf("\n==== Student Record Manager ====\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Display All\n");
        printf("5. Display One\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) addStudent();
        else if (choice == 2) deleteStudent();
        else if (choice == 3) updateStudent();
        else if (choice == 4) displayAll();
        else if (choice == 5) displayOne();
        else if (choice == 6) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
