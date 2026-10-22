//Safely declared -> ifndef, duplicate declaration problem prevented
//Uppercase for better determination betn variable and header file
//lowercase can be used, _H indicates association to header file
#ifndef DINING_H
#define DINING_H


//Necessary built-in header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Declaring global var. (File) as bin file 
#define STUDENT_FILE "student_data.dat"
#define MEAL_FILE "meal_data.dat"
#define FOOD_FILE "food_items.dat"
#define BUDGET_FILE "budget_data.dat"

//Password Section
#define MEAL_PASS "meal123"
#define DINING_PASS "dining123"

//bounded foot item numbers
#define MAX_FOODS 50

//To avoid error, declaring max months
#define MAX_MONTHS 12


//This the second parameter to calculate the food consumption needed
enum ActivityLevel {
    //3 categories
    NOT_ACTIVE,
    MODERATELY_ACTIVE,
    INTENSE_WORKOUT
};
//typedef enum{.....} ActivityLevel;

//1st parameter to calculate food consumption needed
enum BMICategory {
    UNDERWEIGHT,
    NORMAL,
    OVERWEIGHT,
    OBESE
};

//Student info; 12 variables
struct Student {
    int roll;
    float height;
    float weight;
    enum ActivityLevel activity;
    float bmi;
    enum BMICategory category;
    float tdee;
    float ideal_protein;
    float ideal_carbs;
    float ideal_fat;
    int month;
    int year;
};


//Meal info; 13 points
struct MealPlan {
    int month;
    int year;
    int student_count;
    float avg_protein;
    float avg_carbs;  //carbs mean carbohydrate
    float avg_fat;
    float avg_calories;

    //for lunch part
    float lunch_protein;
    float lunch_carbs;
    float lunch_fat;

    //for dinner part
    float dinner_protein;
    float dinner_carbs;
    float dinner_fat;
};


//these are for each hall's food availability
struct FoodItem {
    char name[50];
    float price_per_kg;
    float protein_per_100g;
    float carbs_per_100g;
    float fat_per_100g;
};

//Calculating 
struct BudgetRecord {
    int month;
    int year;
    float budget_per_student;
    float avg_bmi;
    float bmi_change_percent;
    int food_count;
    struct FoodItem foods[MAX_FOODS];
    float food_kg_per_day[MAX_FOODS];
};

//Maksud's Part
float calculateBMI(float weight, float height);
enum BMICategory getBMICategory(float bmi);
float calculateTDEE(float weight, float height, enum ActivityLevel activity);
void diningManagerSection(void);
void showAllBudgetRecords(void);
int loadBudgetRecords(struct BudgetRecord **records);
void saveBudgetRecords(struct BudgetRecord *records, int count);

//Rahat's Part
void studentSection(void);

void printBMICategory(enum BMICategory cat);
void printActivityLevel(enum ActivityLevel act);

int loadStudents(struct Student **students);
void saveStudents(struct Student *students, int count);
int findStudentByRoll(struct Student *students, int count, int roll, int month, int year);


//Maruf's Part
void mealManagerSection(void);
void showAllMealRecords(void);
int loadMealPlans(struct MealPlan **plans);
void saveMealPlans(struct MealPlan *plans, int count);


#endif