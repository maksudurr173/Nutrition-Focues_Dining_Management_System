
# University Dining Management System

A menu-driven C application that turns student health data into monthly meal plans and budget-aware food distribution.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [How the Numbers Are Calculated](#how-the-numbers-are-calculated)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Data Storage](#data-storage)
- [Tech Notes](#tech-notes)

## Overview

Running a university dining hall means answering three questions every month: what do students actually need to eat, how much must be served at lunch and dinner, and can the hall afford it?

This program answers all three from one terminal interface. Students submit their body measurements, the Meal Manager converts that into a nutrition plan for the whole hall, and the Dining Manager spreads a monthly budget across food items while tracking the BMI trend to decide whether the budget is still enough.

It is written in plain C with no external dependencies and stores its data in simple binary files, so it builds and runs anywhere GCC is available.

## Features

### Student Section

- Submit monthly data by roll number, month and year
- Enter height (m), weight (kg) and activity level (Not Active, Moderately Active, Intense Workout)
- Automatic BMI and BMI category (Underweight, Normal, Overweight, Obese)
- Automatic TDEE (daily calorie need) and ideal daily protein, carbs and fat
- Re-submitting for the same month offers to update the existing record

### Meal Manager Section (password protected)

- Aggregates all student data for a chosen month
- Computes average protein, carbs, fat and calories per student per day
- Calculates the total nutrition the hall must provide, split into Lunch (45%) and Dinner (55%)
- Creates or updates the meal plan for that month
- View All Records lists every saved meal plan

### Dining Manager Section (password protected)

- Loads the Meal Manager's plan for a chosen month
- Takes a monthly budget per student (BDT) and converts it into a daily budget for the hall
- Accepts up to 50 food items, each with price per kg and protein, carbs and fat per 100 g
- Distributes the budget across the foods and reports quantity (kg/day), cost and nutrition per item, with a within/over budget status
- Monthly BMI analysis: compares this month's average BMI with the previous month's
- Quarter analysis: compares the latest 3-month average BMI with the 3 months before it
- Warns when average BMI is moving away from the healthy reference of 22.0 and suggests a budget increase
- View All Records lists every saved budget record

## How the Numbers Are Calculated

| Metric | Formula |
|---|---|
| BMI | `weight / height²` |
| BMR | `10 × weight + 6.25 × height(cm) − 5 × age + 5` (Mifflin-St Jeor, age fixed at 22) |
| TDEE | `BMR × activity multiplier` |
| Ideal protein | 30% of TDEE ÷ 4 kcal/g |
| Ideal carbs | 50% of TDEE ÷ 4 kcal/g |
| Ideal fat | 20% of TDEE ÷ 9 kcal/g |

| Activity level | Multiplier |
|---|---|
| Not Active | 1.2 |
| Moderately Active | 1.55 |
| Intense Workout | 1.9 |

| BMI category | Range |
|---|---|
| Underweight | below 18.5 |
| Normal | 18.5 to 24.9 |
| Overweight | 25 to 29.9 |
| Obese | 30 and above |

**Budget suggestion.** When the BMI gap from 22.0 grows between quarters, the suggested increase is:

```
budget × (current gap − previous gap) / 22.0
```

## Project Structure

```
DININGMANAGEMENT 2.0/
├── main.c         Entry point and main menu loop
├── functions.c    Calculations, file I/O and role sections
├── dining.h       Structs, enums, constants and prototypes
└── Makefile       Build and clean targets
```

## Getting Started

### Prerequisites

- A C compiler (GCC recommended)
- `make` (optional)

### Build

```bash
make
```

Or compile directly:

```bash
gcc main.c functions.c -o dining
```

### Run

```bash
./dining        # Linux / macOS
dining.exe      # Windows
```

### Clean

```bash
make clean
```

## Usage

On launch, the main menu appears:

```
========================================
  UNIVERSITY DINING MANAGEMENT SYSTEM
========================================
1. Student Section
2. Meal Manager Section
3. Meal Manager - View All Records
4. Dining Manager Section
5. Dining Manager - View All Records
6. Exit
```

### Typical workflow

1. Students choose option 1 and submit their roll number, month, year, height, weight and activity level.
2. The Meal Manager chooses option 2, signs in, selects a month and year, and generates the meal plan.
3. The Dining Manager chooses option 4, signs in, selects the month, enters the budget and food items, and reviews the distribution and BMI analysis.
4. Options 3 and 5 show all past meal and budget records.

Notes:

- The Dining Manager can only work on months for which the Meal Manager has already created a plan.
- Quarter analysis needs BMI records for six consecutive months in the same year (the current three and the previous three).

### Default credentials

| Role | Password |
|---|---|
| Meal Manager | `meal123` |
| Dining Manager | `dining123` |

Both are defined in `dining.h` as `MEAL_PASS` and `DINING_PASS`.

## Data Storage

The program creates these files in the directory it is run from:

| File | Contents |
|---|---|
| `student_data.dat` | Student submissions (per roll, month and year) |
| `meal_data.dat` | Monthly meal plans |
| `budget_data.dat` | Monthly budget records and food distributions |
| `food_items.dat` | Food item storage |

Delete these files to reset the system, and run the program from the same directory each time so it finds its data.

## Tech Notes

- Plain C using only the standard library
- Records are held in dynamically allocated arrays (`malloc` / `realloc`) and persisted with `fread` / `fwrite`
- Declarations in `dining.h`, logic in `functions.c`, menu loop in `main.c`
- `enum` types for activity levels and BMI categories

