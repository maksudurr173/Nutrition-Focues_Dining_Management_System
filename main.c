//Including created header file
#include "dining.h"

int main(void) {
    int choice;

    do { //Exit-controlled loop; condition is checked after working
        printf("\n\n");
        printf("    UNIVERSITY DINING MANAGEMENT SYSTEM\n");
        printf("\n");
        printf("1. Student Section\n");
        printf("2. Meal Manager Section\n");
        printf("3. Meal Manager - View All Records\n");
        printf("4. Dining Manager Section\n");
        printf("5. Dining Manager - View All Records\n");
        printf("6. Exit\n");
        printf("\nEnter choice: ");

        //Input the choice
        scanf("%d", &choice);

        //It's time for choosing the thing I want
        if (choice == 1) {
            //This is for student
            studentSection();
        }
        else if (choice == 2) {
            //This section is for section officer
            mealManagerSection();
        }
        else if (choice == 3) {
            //This section is for tracking the previous meal menu the student have taken
            showAllMealRecords();
        }
        else if (choice == 4) {
            //This section is for dining manager
            diningManagerSection();
        }
        else if (choice == 5) {
            //This is to confirm the previous budget and menu
            showAllBudgetRecords();
        }
        else if (choice == 6) {
            
            printf("\nProgram ended.\n");
        }
        else {
            //For better error handling
            printf("\nInvalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}