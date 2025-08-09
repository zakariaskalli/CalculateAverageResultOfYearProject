# Academic Year Average Calculator in C++

---

## Project Overview

This C++ console application calculates the **annual average grade for multiple academic subjects** based on exam scores, attentions (such as participation or bonus points), and coefficients (weights) for each subject.

The program supports dynamic input of subjects with varying numbers of exams (up to 4), optional attentions with adjustable weights, and subject-specific coefficients that affect the final weighted average calculation.

Data is persisted in a structured text file to allow saving, loading, and displaying a detailed report of all subjects and their calculated averages.

---

## Key Features

- **Flexible Subject Input:** Enter between 2 to 30 subjects with individual exam counts.
- **Multiple Exams per Subject:** Supports up to 4 exams per subject, with individual scores.
- **Attention Handling:** Optionally include an "Attention" score that contributes a percentage to the final subject average.
- **Coefficient Weighting:** Each subject's average is multiplied by a coefficient to reflect its importance.
- **Persistent Storage:** Saves subject data to a text file (`AverageResultOfYearData.txt`) with a custom delimiter for easy loading and processing.
- **Detailed Reporting:** Outputs a formatted summary table showing each subject’s details, partial averages, coefficients, and the overall yearly average.

---

## Data Structures

- **`stMatierData`** — Represents all relevant data for a subject:
  - Subject name
  - Number of exams and individual exam scores
  - Whether the subject has an attention score, the attention value, and its percentage weight
  - Coefficient (weight) of the subject
  - Calculated average and weighted average

- **`stBultaneTotals`** — Tracks cumulative totals across all subjects for:
  - Total sum of coefficients
  - Total weighted averages for final yearly average computation

---

## How It Works

1. The program prompts the user to input the number of subjects.
2. For each subject, the user enters:
   - Subject name
   - Number of exams and the corresponding scores (validated between 0 and 20)
   - Whether an attention score exists; if yes, its value and percentage weight
   - The coefficient for the subject
3. The average for each subject is calculated using the formula:

   \[
   \text{Average} = \frac{\sum \text{Exam Scores}}{\text{Number of Exams}}
   \]

   If attention applies:

   \[
   \text{Weighted Average} = \left(\frac{\text{Average} \times (100 - \text{Attention \%})}{100}\right) + \left(\frac{\text{Attention Score} \times \text{Attention \%}}{100}\right)
   \]

4. The weighted average is multiplied by the coefficient for each subject.
5. After all subjects are entered, the program loads all data from the file, computes the total coefficients and weighted averages, and prints a comprehensive table with:
   - Subject details
   - Exam scores
   - Attention details
   - Calculated averages
   - Final weighted averages
6. The program also computes and displays the **overall average for the academic year** by dividing the total weighted averages by the total coefficients.

---

## Usage Instructions

### Compilation

Make sure you have a C++ compiler installed (e.g., `g++`).

Compile the program with:

```bash
g++ -std=c++17 -o AcademicAverageCalculator main.cpp
