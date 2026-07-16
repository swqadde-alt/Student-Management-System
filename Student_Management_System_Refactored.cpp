/*
 * ============================================================
 * Title   : Student Management System
 * Author  : Student Project
 * Language: C
 * Description:
 *   Console-based application to register students, list records,
 *   calculate weighted averages, and generate class statistics.
 * ============================================================
 */
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define NAME_LENGTH 20

// --- SYSTEM MENU AREA ---
void showMenu() {
    printf("=========================================\n");
    printf("        STUDENT MANAGEMENT SYSTEM        \n");
    printf("=========================================\n");
    printf("  [1] Register New Student\n");
    printf("  [2] View Directory List\n");
    printf("  [3] Calculate Student Average\n");
    printf("  [4] Analytics & Class Statistics\n");
    printf("  [5] Terminate System\n");
    printf("=========================================\n");
    printf(">> Select an operation (1-5): ");
}

// --- REGISTER STUDENT ---
int addStudent(int currentCount, char studentNames[][NAME_LENGTH], int midtermGrades[], int finalGrades[]) {
    if (currentCount >= MAX_STUDENTS) {
        printf("\n[OVERFLOW] System storage full! Limit: %d\n", MAX_STUDENTS);
        return 0;
    }

    printf("\n- Enter Student Name: ");
    scanf("%s", studentNames[currentCount]);

    printf("- Enter Midterm Grade [0-100]: ");
    scanf("%d", &midtermGrades[currentCount]);

    printf("- Enter Final Grade [0-100]: ");
    scanf("%d", &finalGrades[currentCount]);

    // Validation
    if (midtermGrades[currentCount] < 0 || midtermGrades[currentCount] > 100 || 
        finalGrades[currentCount] < 0 || finalGrades[currentCount] > 100) {
        printf("\n[VALIDATION ERROR] Grades out of range! Fields reset.\n");
        midtermGrades[currentCount] = 0;
        finalGrades[currentCount] = 0;
        return 0;
    }

    printf("\n[SUCCESS] Student record saved to local buffer.\n");
    return 1;
}

// --- LIST DIRECTORY ---
void listStudents(int currentCount, char studentNames[][NAME_LENGTH], int midtermGrades[], int finalGrades[]) {
    if (currentCount == 0) {
        printf("\n[EMPTY] No records found in the current session.\n");
        return;
    }

    printf("\n=========================================\n");
    printf("             ACTIVE DATABASE             \n");
    printf("=========================================\n");
    for (int i = 0; i < currentCount; i++) {
        printf(" Index: #0%d  |  Name: %s\n", i + 1, studentNames[i]);
        printf("   Midterm: [%d] | Final: [%d]\n", midtermGrades[i], finalGrades[i]);
        printf("-----------------------------------------\n");
    }
}

// --- ANALYZE SINGLE DATA ---
void calculateSingleAverage(int currentCount, char studentNames[][NAME_LENGTH], int midtermGrades[], int finalGrades[]) {
    if (currentCount == 0) {
        printf("\n[EMPTY] No data available for metrics.\n");
        return;
    }

    int studentIndex = 0;
    printf("\n-> Enter Target Index ID (1-%d): ",currentCount);
    scanf("%d",&studentIndex);

    int selectedIndex=studentIndex - 1;

    if (selectedIndex >= 0 && selectedIndex<currentCount) {
        float weightedAverage=(midtermGrades[selectedIndex]*0.40) + (finalGrades[selectedIndex]*0.60);
        printf("\nResult >> %s's Weighted Average: [ %.2f ]\n", studentNames[selectedIndex], weightedAverage);
    } else {
        printf("\n[POINTER ERROR] Index out of bounds!\n");
    }
}

// --- CORE ANALYTICS ---
void displayClassStatistics(int currentCount, char studentNames[][NAME_LENGTH], int midtermGrades[], int finalGrades[]) {
    if (currentCount == 0) {
        printf("\n[EMPTY] Analytics engine requires active records.\n");
        return;
    }

    float classTotal=0;
    float highestAverage=-1.0;
    float lowestAverage=101.0;
    int topStudentIndex=0;
    int bottomStudentIndex=0;

    printf("\n--- ANALYTICS REPORT ENGINE ---\n");
    printf(" Total Population: [ %d ]\n",currentCount);
    
    printf(" Network Registry: ");
    for (int i=0; i<currentCount; i++) {
        printf("%s%s",studentNames[i],(i == currentCount - 1) ? "" : ", ");
    }
    printf("\n-----------------------------------------\n");

    for (int i = 0; i < currentCount; i++) {
        float currentAverage = (midtermGrades[i] * 0.40) + (finalGrades[i] * 0.60);
        classTotal += currentAverage;

        if (currentAverage > highestAverage) {
            highestAverage = currentAverage;
            topStudentIndex = i;
        }
        if (currentAverage < lowestAverage) {
            lowestAverage = currentAverage;
            bottomStudentIndex = i;
        }
    }

    float class_weightedAverage = classTotal / currentCount;
    printf(" Mean Class Score:    %.2f\n", class_weightedAverage);
    printf(" Apex Performer:      %s [ Grade: %.2f ]\n", studentNames[topStudentIndex], highestAverage);
    printf(" Lowest Metric:       %s [ Grade: %.2f ]\n", studentNames[bottomStudentIndex], lowestAverage);
    printf("-----------------------------------------\n");
}

int main() {
    int menuChoice = 0;
    int studentCount = 0;
    int midtermGrades[MAX_STUDENTS];
    int finalGrades[MAX_STUDENTS];
    char studentNames[MAX_STUDENTS][NAME_LENGTH];

    do {
        showMenu();
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1:
                if (addStudent(studentCount, studentNames, midtermGrades, finalGrades) == 1) {
                    studentCount++;
                }
                break;
            case 2:
                listStudents(studentCount, studentNames, midtermGrades, finalGrades);
                break;
            case 3:
                listStudents(studentCount, studentNames, midtermGrades, finalGrades);
                calculateSingleAverage(studentCount, studentNames, midtermGrades, finalGrades);
                break;
            case 4:
                displayClassStatistics(studentCount, studentNames, midtermGrades, finalGrades);
                break;
            case 5:
                printf("\n[SHUTDOWN] Terminating session. System offline.\n");
                break;
            default:
                printf("\n[INVALID SELECTION] Command unrecognized.\n");
        }
    } while (menuChoice != 5);

    return 0;
}
