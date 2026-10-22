//Created header file included
#include "dining.h"


float calculateBMI(float weight, float height) {
    return weight / (height * height);
}

enum BMICategory getBMICategory(float bmi) {
    if (bmi < 18.5) {
        return UNDERWEIGHT;
    }
    else if (bmi < 25.0) {
        return NORMAL;
    }
    else if (bmi < 30.0) {
        return OVERWEIGHT;
    }
    else {
        return OBESE;
    }
}

float calculateTDEE(float weight, float height, enum ActivityLevel activity) {
    float bmr;
    float height_cm;
    float multiplier;

    height_cm = height * 100.0;
    bmr = 10.0 * weight + 6.25 * height_cm - 5.0 * 22.0 + 5.0;

    if (activity == NOT_ACTIVE) {
        multiplier = 1.2;
    }
    else if (activity == MODERATELY_ACTIVE) {
        multiplier = 1.55;
    }
    else {
        multiplier = 1.9;
    }

    return bmr * multiplier;
}

void printBMICategory(enum BMICategory cat) {
    if (cat == UNDERWEIGHT) {
        printf("Underweight");
    }
    else if (cat == NORMAL) {
        printf("Normal");
    }
    else if (cat == OVERWEIGHT) {
        printf("Overweight");
    }
    else {
        printf("Obese");
    }
}

void printActivityLevel(enum ActivityLevel act) {
    if (act == NOT_ACTIVE) {
        printf("Not Active");
    }
    else if (act == MODERATELY_ACTIVE) {
        printf("Moderately Active");
    }
    else {
        printf("Intense Workout");
    }
}

int loadStudents(struct Student **students) {
    FILE *file;
    int count;

    file = fopen(STUDENT_FILE, "rb");
    if (file == NULL) {
        *students = malloc(sizeof(struct Student));
        return 0;
    }

    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        *students = malloc(sizeof(struct Student));
        return 0;
    }

    if (count <= 0) {
        fclose(file);
        *students = malloc(sizeof(struct Student));
        return 0;
    }

    *students = malloc(count * sizeof(struct Student));
    if (*students == NULL) {
        fclose(file);
        return 0;
    }

    if (fread(*students, sizeof(struct Student), count, file) != (size_t)count) {
        fclose(file);
        free(*students);
        *students = malloc(sizeof(struct Student));
        return 0;
    }

    fclose(file);
    return count;
}

void saveStudents(struct Student *students, int count) {
    FILE *file;
    file = fopen(STUDENT_FILE, "wb");
    if (file == NULL) {
        printf("Cannot save student data.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), count, file);
    fclose(file);
}

int loadMealPlans(struct MealPlan **plans) {
    FILE *file;
    int count;

    file = fopen(MEAL_FILE, "rb");
    if (file == NULL) {
        *plans = malloc(sizeof(struct MealPlan));
        return 0;
    }

    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        *plans = malloc(sizeof(struct MealPlan));
        return 0;
    }

    if (count <= 0) {
        fclose(file);
        *plans = malloc(sizeof(struct MealPlan));
        return 0;
    }

    *plans = malloc(count * sizeof(struct MealPlan));
    if (*plans == NULL) {
        fclose(file);
        return 0;
    }

    if (fread(*plans, sizeof(struct MealPlan), count, file) != (size_t)count) {
        fclose(file);
        free(*plans);
        *plans = malloc(sizeof(struct MealPlan));
        return 0;
    }

    fclose(file);
    return count;
}

void saveMealPlans(struct MealPlan *plans, int count) {
    FILE *file;
    file = fopen(MEAL_FILE, "wb");
    if (file == NULL) {
        printf("Cannot save meal data.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(plans, sizeof(struct MealPlan), count, file);
    fclose(file);
}

int loadBudgetRecords(struct BudgetRecord **records) {
    FILE *file;
    int count;

    file = fopen(BUDGET_FILE, "rb");
    if (file == NULL) {
        *records = malloc(sizeof(struct BudgetRecord));
        return 0;
    }

    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        *records = malloc(sizeof(struct BudgetRecord));
        return 0;
    }

    if (count <= 0) {
        fclose(file);
        *records = malloc(sizeof(struct BudgetRecord));
        return 0;
    }

    *records = malloc(count * sizeof(struct BudgetRecord));
    if (*records == NULL) {
        fclose(file);
        return 0;
    }

    if (fread(*records, sizeof(struct BudgetRecord), count, file) != (size_t)count) {
        fclose(file);
        free(*records);
        *records = malloc(sizeof(struct BudgetRecord));
        return 0;
    }

    fclose(file);
    return count;
}

void saveBudgetRecords(struct BudgetRecord *records, int count) {
    FILE *file;
    file = fopen(BUDGET_FILE, "wb");
    if (file == NULL) {
        printf("Cannot save budget data.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(records, sizeof(struct BudgetRecord), count, file);
    fclose(file);
}

int findStudentByRoll(struct Student *students, int count, int roll, int month, int year) {
    int i;
    for (i = 0; i < count; i++) {
        if (students[i].roll == roll && students[i].month == month && students[i].year == year) {
            return i;
        }
    }
    return -1;
}

void studentSection(void) {
    struct Student *students;
    int studentCount;
    int roll, month, year, choice;
    int actChoice;
    int existing;
    struct Student *temp;
    float tdee;

    studentCount = loadStudents(&students);

    printf("\n      STUDENT SECTION \n");
    printf("Enter your Roll Number: ");
    scanf("%d", &roll);
    printf("Enter Month (1-12): ");
    scanf("%d", &month);
    printf("Enter Year: ");
    scanf("%d", &year);

    if (month < 1 || month > 12) {
        printf("Invalid month.\n");
        saveStudents(students, studentCount);
        free(students);
        return;
    }

    existing = findStudentByRoll(students, studentCount, roll, month, year);

    if (existing >= 0) {
        printf("\nYou already submitted data for this month.\n");
        printf("Do you want to update? (1 = Yes, 0 = No): ");
        scanf("%d", &choice);
        if (choice != 1) {
            printf("No changes made.\n");
            saveStudents(students, studentCount);
            free(students);
            return;
        }

        printf("Enter your Height in meters: ");
        scanf("%f", &students[existing].height);
        printf("Enter your Weight in kg: ");
        scanf("%f", &students[existing].weight);

        if (students[existing].height <= 0 || students[existing].weight <= 0) {
            printf("Height and weight must be positive.\n");
            free(students);
            return;
        }

        printf("\nSelect Activity Level:\n");
        printf("1. Not Active\n");
        printf("2. Moderately Active\n");
        printf("3. Intense Workout\n");
        printf("Choice: ");
        scanf("%d", &actChoice);

        if (actChoice == 1) {
            students[existing].activity = NOT_ACTIVE;
        }
        else if (actChoice == 2) {
            students[existing].activity = MODERATELY_ACTIVE;
        }
        else if (actChoice == 3) {
            students[existing].activity = INTENSE_WORKOUT;
        }
        else {
            printf("Invalid activity choice.\n");
            free(students);
            return;
        }

        students[existing].bmi = calculateBMI(students[existing].weight, students[existing].height);
        students[existing].category = getBMICategory(students[existing].bmi);

        tdee = calculateTDEE(students[existing].weight, students[existing].height, students[existing].activity);
        students[existing].tdee = tdee;

        students[existing].ideal_protein = (tdee * 0.30) / 4.0;
        students[existing].ideal_carbs = (tdee * 0.50) / 4.0;
        students[existing].ideal_fat = (tdee * 0.20) / 9.0;

        printf("\nData updated successfully!\n");
    }
    else {
        temp = realloc(students, (studentCount + 1) * sizeof(struct Student));
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            free(students);
            return;
        }
        students = temp;

        students[studentCount].roll = roll;
        students[studentCount].month = month;
        students[studentCount].year = year;

        printf("Enter your Height in meters: ");
        scanf("%f", &students[studentCount].height);
        printf("Enter your Weight in kg: ");
        scanf("%f", &students[studentCount].weight);

        if (students[studentCount].height <= 0 || students[studentCount].weight <= 0) {
            printf("Height and weight must be positive.\n");
            free(students);
            return;
        }

        printf("\nSelect Activity Level:\n");
        printf("1. Not Active\n");
        printf("2. Moderately Active\n");
        printf("3. Intense Workout\n");
        printf("Choice: ");
        scanf("%d", &actChoice);

        if (actChoice == 1) {
            students[studentCount].activity = NOT_ACTIVE;
        }
        else if (actChoice == 2) {
            students[studentCount].activity = MODERATELY_ACTIVE;
        }
        else if (actChoice == 3) {
            students[studentCount].activity = INTENSE_WORKOUT;
        }
        else {
            printf("Invalid activity choice.\n");
            free(students);
            return;
        }

        students[studentCount].bmi = calculateBMI(students[studentCount].weight, students[studentCount].height);
        students[studentCount].category = getBMICategory(students[studentCount].bmi);

        tdee = calculateTDEE(students[studentCount].weight, students[studentCount].height, students[studentCount].activity);
        students[studentCount].tdee = tdee;

        students[studentCount].ideal_protein = (tdee * 0.30) / 4.0;
        students[studentCount].ideal_carbs = (tdee * 0.50) / 4.0;
        students[studentCount].ideal_fat = (tdee * 0.20) / 9.0;

        studentCount++;
        printf("\nData submitted successfully!\n");
    }

    printf("\n     Your Health Info \n");
    if (existing >= 0) {
        printf("Roll: %d\n", students[existing].roll);
        printf("Height: %.2f m\n", students[existing].height);
        printf("Weight: %.2f kg\n", students[existing].weight);
        printf("BMI: %.2f (", students[existing].bmi);
        printBMICategory(students[existing].category);
        printf(")\n");
        printf("Activity: ");
        printActivityLevel(students[existing].activity);
        printf("\n");
        printf("TDEE: %.0f kcal/day\n", students[existing].tdee);
        printf("Ideal Protein: %.1f g/day\n", students[existing].ideal_protein);
        printf("Ideal Carbs: %.1f g/day\n", students[existing].ideal_carbs);
        printf("Ideal Fat: %.1f g/day\n", students[existing].ideal_fat);
    }
    else {
        printf("Roll: %d\n", students[studentCount - 1].roll);
        printf("Height: %.2f m\n", students[studentCount - 1].height);
        printf("Weight: %.2f kg\n", students[studentCount - 1].weight);
        printf("BMI: %.2f (", students[studentCount - 1].bmi);
        printBMICategory(students[studentCount - 1].category);
        printf(")\n");
        printf("Activity: ");
        printActivityLevel(students[studentCount - 1].activity);
        printf("\n");
        printf("TDEE: %.0f kcal/day\n", students[studentCount - 1].tdee);
        printf("Ideal Protein: %.1f g/day\n", students[studentCount - 1].ideal_protein);
        printf("Ideal Carbs: %.1f g/day\n", students[studentCount - 1].ideal_carbs);
        printf("Ideal Fat: %.1f g/day\n", students[studentCount - 1].ideal_fat);
    }

    saveStudents(students, studentCount);
    free(students);
    printf("Data saved.\n");
}

void mealManagerSection(void) {
    char password[50];
    struct Student *students;
    struct MealPlan *plans;
    struct MealPlan *temp;
    int studentCount, planCount;
    int month, year;
    int i, found, totalStudents;
    float totalProtein, totalCarbs, totalFat, totalTDEE;
    float avgProtein, avgCarbs, avgFat;
    int existingPlan;

    printf("\n===== MEAL MANAGER SECTION =====\n");
    printf("Enter Password: ");
    scanf(" %[^\n]", password);

    if (strcmp(password, MEAL_PASS) != 0) {
        printf("Wrong password. Access denied.\n");
        return;
    }

    printf("Access granted.\n");

    studentCount = loadStudents(&students);
    planCount = loadMealPlans(&plans);

    if (studentCount == 0) {
        printf("No student data available.\n");
        free(students);
        free(plans);
        return;
    }

    printf("\nEnter Month (1-12): ");
    scanf("%d", &month);
    printf("Enter Year: ");
    scanf("%d", &year);

    if (month < 1 || month > 12) {
        printf("Invalid month.\n");
        free(students);
        free(plans);
        return;
    }

    totalStudents = 0;
    totalProtein = 0;
    totalCarbs = 0;
    totalFat = 0;
    totalTDEE = 0;

    for (i = 0; i < studentCount; i++) {
        if (students[i].month == month && students[i].year == year) {
            totalStudents++;
            totalProtein += students[i].ideal_protein;
            totalCarbs += students[i].ideal_carbs;
            totalFat += students[i].ideal_fat;
            totalTDEE += students[i].tdee;
        }
    }

    if (totalStudents == 0) {
        printf("No student data found for %d/%d.\n", month, year);
        free(students);
        free(plans);
        return;
    }

    printf("\nFound %d students for %d/%d\n", totalStudents, month, year);

    avgProtein = totalProtein / totalStudents;
    avgCarbs = totalCarbs / totalStudents;
    avgFat = totalFat / totalStudents;

    existingPlan = -1;
    for (i = 0; i < planCount; i++) {
        if (plans[i].month == month && plans[i].year == year) {
            existingPlan = i;
        }
    }

    if (existingPlan >= 0) {
        plans[existingPlan].student_count = totalStudents;
        plans[existingPlan].avg_protein = avgProtein;
        plans[existingPlan].avg_carbs = avgCarbs;
        plans[existingPlan].avg_fat = avgFat;
        plans[existingPlan].avg_calories = totalTDEE / totalStudents;
        plans[existingPlan].lunch_protein = (avgProtein * 0.45) * totalStudents;
        plans[existingPlan].lunch_carbs = (avgCarbs * 0.45) * totalStudents;
        plans[existingPlan].lunch_fat = (avgFat * 0.45) * totalStudents;
        plans[existingPlan].dinner_protein = (avgProtein * 0.55) * totalStudents;
        plans[existingPlan].dinner_carbs = (avgCarbs * 0.55) * totalStudents;
        plans[existingPlan].dinner_fat = (avgFat * 0.55) * totalStudents;

        printf("\nMeal plan updated for %d/%d.\n", month, year);
    }
    else {
        temp = realloc(plans, (planCount + 1) * sizeof(struct MealPlan));
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            free(students);
            free(plans);
            return;
        }
        plans = temp;

        plans[planCount].month = month;
        plans[planCount].year = year;
        plans[planCount].student_count = totalStudents;
        plans[planCount].avg_protein = avgProtein;
        plans[planCount].avg_carbs = avgCarbs;
        plans[planCount].avg_fat = avgFat;
        plans[planCount].avg_calories = totalTDEE / totalStudents;
        plans[planCount].lunch_protein = (avgProtein * 0.45) * totalStudents;
        plans[planCount].lunch_carbs = (avgCarbs * 0.45) * totalStudents;
        plans[planCount].lunch_fat = (avgFat * 0.45) * totalStudents;
        plans[planCount].dinner_protein = (avgProtein * 0.55) * totalStudents;
        plans[planCount].dinner_carbs = (avgCarbs * 0.55) * totalStudents;
        plans[planCount].dinner_fat = (avgFat * 0.55) * totalStudents;

        planCount++;
        printf("\nMeal plan created for %d/%d.\n", month, year);
    }

    printf("\n     Meal Plan Summary \n");
    printf("Month: %d/%d\n", month, year);
    printf("Total Students: %d\n", totalStudents);
    printf("\nAvg per student per day:\n");
    printf("  Protein: %.1f g\n", avgProtein);
    printf("  Carbs: %.1f g\n", avgCarbs);
    printf("  Fat: %.1f g\n", avgFat);
    printf("  Calories: %.0f kcal\n", totalTDEE / totalStudents);
    printf("\nTotal Lunch Nutrition Needed:\n");

    found = (existingPlan >= 0) ? existingPlan : planCount - 1;
    printf("  Protein: %.1f g\n", plans[found].lunch_protein);
    printf("  Carbs: %.1f g\n", plans[found].lunch_carbs);
    printf("  Fat: %.1f g\n", plans[found].lunch_fat);
    printf("\nTotal Dinner Nutrition Needed:\n");
    printf("  Protein: %.1f g\n", plans[found].dinner_protein);
    printf("  Carbs: %.1f g\n", plans[found].dinner_carbs);
    printf("  Fat: %.1f g\n", plans[found].dinner_fat);

    printf("\nTotal Combined Daily Nutrition:\n");
    printf("  Protein: %.1f g\n", plans[found].lunch_protein + plans[found].dinner_protein);
    printf("  Carbs: %.1f g\n", plans[found].lunch_carbs + plans[found].dinner_carbs);
    printf("  Fat: %.1f g\n", plans[found].lunch_fat + plans[found].dinner_fat);

    saveMealPlans(plans, planCount);
    free(students);
    free(plans);
    printf("Meal data saved.\n");
}

void showAllMealRecords(void) {
    struct MealPlan *plans;
    int planCount, i;
    char password[50];

    printf("\nEnter Meal Manager Password: ");
    scanf(" %[^\n]", password);

    if (strcmp(password, MEAL_PASS) != 0) {
        printf("Wrong password.\n");
        return;
    }

    planCount = loadMealPlans(&plans);
    if (planCount == 0) {
        printf("No meal records found.\n");
        free(plans);
        return;
    }

    printf("\n      ALL MEAL RECORDS \n");
    for (i = 0; i < planCount; i++) {
        printf("\n    Record %d: %d/%d \n", i + 1, plans[i].month, plans[i].year);
        printf("Total Students: %d\n", plans[i].student_count);
        printf("Avg Protein: %.1f g | Avg Carbs: %.1f g | Avg Fat: %.1f g\n",
               plans[i].avg_protein, plans[i].avg_carbs, plans[i].avg_fat);
        printf("Avg Calories: %.0f kcal\n", plans[i].avg_calories);
    }

    free(plans);
}

void diningManagerSection(void) {
    char password[50];
    struct MealPlan *plans;
    struct BudgetRecord *records;
    struct BudgetRecord *temp;
    struct Student *students;
    int planCount, recordCount, studentCount;
    int month, year, i;
    int foodCount;
    float budgetPerStudent;
    float dailyBudget;
    float totalDailyNutritionProtein, totalDailyNutritionCarbs, totalDailyNutritionFat;
    float totalFoodCost;
    float remainingBudget;
    int mealPlanIndex;
    int existingRecord;
    float avgBmiCurrent, avgBmiPrev;
    int countCurrent, countPrev;
    float bmiChange;
    int checkQuarter;
    float quarterAvgCurrent, quarterAvgPrev;
    int qCount1, qCount2;

    printf("\n     DINING MANAGER SECTION   \n");
    printf("Enter Password: ");
    scanf(" %[^\n]", password);

    if (strcmp(password, DINING_PASS) != 0) {
        printf("Wrong password. Access denied.\n");
        return;
    }

    printf("Access granted.\n");

    planCount = loadMealPlans(&plans);
    recordCount = loadBudgetRecords(&records);
    studentCount = loadStudents(&students);

    if (planCount == 0) {
        printf("No meal plan data available. Meal Manager must enter data first.\n");
        free(plans);
        free(records);
        free(students);
        return;
    }

    printf("\nAvailable meal plans:\n");
    for (i = 0; i < planCount; i++) {
        printf("  %d/%d\n", plans[i].month, plans[i].year);
    }

    printf("\nEnter Month (1-12): ");
    scanf("%d", &month);
    printf("Enter Year: ");
    scanf("%d", &year);

    mealPlanIndex = -1;
    for (i = 0; i < planCount; i++) {
        if (plans[i].month == month && plans[i].year == year) {
            mealPlanIndex = i;
        }
    }

    if (mealPlanIndex < 0) {
        printf("No meal plan found for %d/%d.\n", month, year);
        free(plans);
        free(records);
        free(students);
        return;
    }

    totalDailyNutritionProtein = plans[mealPlanIndex].lunch_protein + plans[mealPlanIndex].dinner_protein;
    totalDailyNutritionCarbs = plans[mealPlanIndex].lunch_carbs + plans[mealPlanIndex].dinner_carbs;
    totalDailyNutritionFat = plans[mealPlanIndex].lunch_fat + plans[mealPlanIndex].dinner_fat;

    printf("\nDaily nutrition target from meal plan:\n");
    printf("  Total Protein: %.1f g\n", totalDailyNutritionProtein);
    printf("  Total Carbs: %.1f g\n", totalDailyNutritionCarbs);
    printf("  Total Fat: %.1f g\n", totalDailyNutritionFat);

    printf("\nEnter budget per student per month (BDT): ");
    scanf("%f", &budgetPerStudent);

    if (budgetPerStudent <= 0) {
        printf("Budget must be positive.\n");
        free(plans);
        free(records);
        free(students);
        return;
    }

    dailyBudget = (budgetPerStudent * plans[mealPlanIndex].student_count) / 30.0;

    printf("Total daily budget for all students: %.2f BDT\n", dailyBudget);

    printf("\nEnter number of food items: ");
    scanf("%d", &foodCount);

    if (foodCount <= 0 || foodCount > MAX_FOODS) {
        printf("Invalid food count.\n");
        free(plans);
        free(records);
        free(students);
        return;
    }

    existingRecord = -1;
    for (i = 0; i < recordCount; i++) {
        if (records[i].month == month && records[i].year == year) {
            existingRecord = i;
        }
    }

    if (existingRecord < 0) {
        temp = realloc(records, (recordCount + 1) * sizeof(struct BudgetRecord));
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            free(plans);
            free(records);
            free(students);
            return;
        }
        records = temp;
        existingRecord = recordCount;
        recordCount++;
    }

    records[existingRecord].month = month;
    records[existingRecord].year = year;
    records[existingRecord].budget_per_student = budgetPerStudent;
    records[existingRecord].food_count = foodCount;

    for (i = 0; i < foodCount; i++) {
        printf("\n    Food Item %d   \n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", records[existingRecord].foods[i].name);
        printf("Price per kg (BDT): ");
        scanf("%f", &records[existingRecord].foods[i].price_per_kg);
        printf("Protein per 100g: ");
        scanf("%f", &records[existingRecord].foods[i].protein_per_100g);
        printf("Carbs per 100g: ");
        scanf("%f", &records[existingRecord].foods[i].carbs_per_100g);
        printf("Fat per 100g: ");
        scanf("%f", &records[existingRecord].foods[i].fat_per_100g);
    }

    printf("\n    Daily Food Distribution (fitting budget) \n");

    totalFoodCost = 0;
    remainingBudget = dailyBudget;

    for (i = 0; i < foodCount; i++) {
        float shareBudget;
        float kgCanBuy;
        float proteinFromFood, carbsFromFood, fatFromFood;

        shareBudget = remainingBudget / (foodCount - i);
        kgCanBuy = shareBudget / records[existingRecord].foods[i].price_per_kg;

        proteinFromFood = kgCanBuy * 10.0 * records[existingRecord].foods[i].protein_per_100g;
        carbsFromFood = kgCanBuy * 10.0 * records[existingRecord].foods[i].carbs_per_100g;
        fatFromFood = kgCanBuy * 10.0 * records[existingRecord].foods[i].fat_per_100g;

        records[existingRecord].food_kg_per_day[i] = kgCanBuy;
        totalFoodCost += kgCanBuy * records[existingRecord].foods[i].price_per_kg;
        remainingBudget -= kgCanBuy * records[existingRecord].foods[i].price_per_kg;

        printf("\n%s:\n", records[existingRecord].foods[i].name);
        printf("  Quantity: %.2f kg/day\n", kgCanBuy);
        printf("  Cost: %.2f BDT/day\n", kgCanBuy * records[existingRecord].foods[i].price_per_kg);
        printf("  Provides - Protein: %.1f g | Carbs: %.1f g | Fat: %.1f g\n",
               proteinFromFood, carbsFromFood, fatFromFood);
    }

    printf("\nTotal Daily Food Cost: %.2f BDT\n", totalFoodCost);
    printf("Monthly Food Cost: %.2f BDT\n", totalFoodCost * 30);
    printf("Daily Budget: %.2f BDT\n", dailyBudget);

    if (totalFoodCost <= dailyBudget) {
        printf("Status: Within budget\n");
    }
    else {
        printf("Status: Over budget by %.2f BDT/day\n", totalFoodCost - dailyBudget);
    }

    avgBmiCurrent = 0;
    countCurrent = 0;
    for (i = 0; i < studentCount; i++) {
        if (students[i].month == month && students[i].year == year) {
            avgBmiCurrent += students[i].bmi;
            countCurrent++;
        }
    }
    if (countCurrent > 0) {
        avgBmiCurrent = avgBmiCurrent / countCurrent;
    }

    records[existingRecord].avg_bmi = avgBmiCurrent;

    avgBmiPrev = 0;
    countPrev = 0;

    if (month > 1) {
        for (i = 0; i < studentCount; i++) {
            if (students[i].month == month - 1 && students[i].year == year) {
                avgBmiPrev += students[i].bmi;
                countPrev++;
            }
        }
    }
    else {
        for (i = 0; i < studentCount; i++) {
            if (students[i].month == 12 && students[i].year == year - 1) {
                avgBmiPrev += students[i].bmi;
                countPrev++;
            }
        }
    }

    if (countPrev > 0) {
        avgBmiPrev = avgBmiPrev / countPrev;
        bmiChange = ((avgBmiCurrent - avgBmiPrev) / avgBmiPrev) * 100.0;
        records[existingRecord].bmi_change_percent = bmiChange;

        printf("\n--- Monthly BMI Analysis ---\n");
        printf("Current month avg BMI: %.2f\n", avgBmiCurrent);
        printf("Previous month avg BMI: %.2f\n", avgBmiPrev);

        if (bmiChange >= 0) {
            printf("BMI Change: +%.2f%%\n", bmiChange);
        }
        else {
            printf("BMI Change: %.2f%%\n", bmiChange);
        }
    }
    else {
        records[existingRecord].bmi_change_percent = 0;
        printf("\n--- Monthly BMI Analysis ---\n");
        printf("Current month avg BMI: %.2f\n", avgBmiCurrent);
        printf("No previous month data for comparison.\n");
    }

    checkQuarter = 0;
    if (month >= 4) {
        quarterAvgCurrent = 0;
        quarterAvgPrev = 0;
        qCount1 = 0;
        qCount2 = 0;

        for (i = 0; i < recordCount; i++) {
            if (records[i].year == year) {
                if (records[i].month >= month - 2 && records[i].month <= month) {
                    quarterAvgCurrent += records[i].avg_bmi;
                    qCount1++;
                }
                if (records[i].month >= month - 5 && records[i].month <= month - 3) {
                    quarterAvgPrev += records[i].avg_bmi;
                    qCount2++;
                }
            }
        }

        if (qCount1 == 3 && qCount2 == 3) {
            checkQuarter = 1;
            quarterAvgCurrent = quarterAvgCurrent / 3.0;
            quarterAvgPrev = quarterAvgPrev / 3.0;
        }
    }

    if (checkQuarter == 1) {
        float qChange;
        float normalBmi = 22.0;
        float currentGap, prevGap;

        qChange = ((quarterAvgCurrent - quarterAvgPrev) / quarterAvgPrev) * 100.0;

        printf("\n    3-Month Quarter Analysis\n");
        printf("Current 3-month avg BMI: %.2f\n", quarterAvgCurrent);
        printf("Previous 3-month avg BMI: %.2f\n", quarterAvgPrev);

        if (qChange >= 0) {
            printf("Quarter BMI Change: +%.2f%%\n", qChange);
        }
        else {
            printf("Quarter BMI Change: %.2f%%\n", qChange);
        }

        currentGap = quarterAvgCurrent - normalBmi;
        if (currentGap < 0) {
            currentGap = -currentGap;
        }
        prevGap = quarterAvgPrev - normalBmi;
        if (prevGap < 0) {
            prevGap = -prevGap;
        }

        if (currentGap > prevGap) {
            float suggestedIncrease;
            suggestedIncrease = budgetPerStudent * (currentGap - prevGap) / normalBmi;

            printf("\nWARNING: Avg BMI is moving away from normal range!\n");
            printf("Suggested budget increase: %.2f BDT per student per month\n", suggestedIncrease);
            printf("New suggested budget: %.2f BDT per student per month\n",
                   budgetPerStudent + suggestedIncrease);
        }
        else {
            printf("\nBMI trend is improving or stable. Budget is adequate.\n");
        }
    }

    saveBudgetRecords(records, recordCount);
    free(plans);
    free(records);
    free(students);
    printf("Budget data saved.\n");
}


//Choice No.5
void showAllBudgetRecords(void) {
    struct BudgetRecord *records;
    int recordCount, i, j;
    char password[50];

    printf("\nEnter Dining Manager Password: ");
    scanf(" %[^\n]", password);

    if (strcmp(password, DINING_PASS) != 0) {
        printf("Wrong password.\n");
        return;
    }

    recordCount = loadBudgetRecords(&records);

    if (recordCount == 0) {
        printf("No budget records found.\n");
        free(records);
        return;
    }

    printf("\n===== ALL BUDGET RECORDS =====\n");
    for (i = 0; i < recordCount; i++) {
        printf("\n--- Record %d: %d/%d ---\n", i + 1, records[i].month, records[i].year);
        printf("Budget per student: %.2f BDT\n", records[i].budget_per_student);
        printf("Avg BMI: %.2f\n", records[i].avg_bmi);
        printf("BMI Change: %.2f%%\n", records[i].bmi_change_percent);
        printf("Food items: %d\n", records[i].food_count);
        for (j = 0; j < records[i].food_count; j++) {
            printf("  %s: %.2f kg/day @ %.2f BDT/kg\n",
                   records[i].foods[j].name,
                   records[i].food_kg_per_day[j],
                   records[i].foods[j].price_per_kg);
        }
    }

    free(records); //If there any memory location is abandoned/unused
}
