#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
// Include limits for numeric_limits
// #include <iostream> is used to collect inputs from the user.
// #include <vector> is from the C++ Standard Template Library and is used for Array-like structures.
// #include <iomanip> on the other hand is used for formatting output in C++.
using namespace std; 
// 'namespace' contains all the standard library Classes, Functions and Objects.

// Step 1: printing the tableau

void printTableau(const vector<vector<double>> &tableau) { // Added & to avoid copying
    for (const auto &row : tableau) { // Corrected line 13
        for (double value : row) {
            cout << setw(8)  << fixed << setprecision(2) << value << " ";
        }
        cout << "\n";
    }
}
// this printTableau is used to aid visualisation of the tableau as it progresses.
// Step 2: this code is aimed to find the pivot column.

int findPivotColumn(const vector<vector<double>> &tableau) {
    int pivotCol = -1;
    double minValue = 0.0;

    for (int j = 0; j < tableau[0].size() - 1; ++j) {
        if (tableau.back()[j] < minValue) {
            minValue = tableau.back()[j];
            pivotCol = j;
        }
    }
    return pivotCol;
}

// Step 3: this next step is aimed at finding the pivot row
// Where the general formula is given as "Ratio/(RightHandSide/PivotColumnValue)"

int findPivotRow(const vector<vector<double>> &tableau, int pivotCol) {
    int pivotRow = -1;
    double minRatio = numeric_limits<double>::infinity();

    for (int i = 0; i < tableau.size() - 1; ++i) {
        double value = tableau[i][pivotCol];
        if (value > 0) {
            double ratio = tableau[i].back() / value;
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = i;
            }
        }
    }
    return pivotRow;
}

// Step 4: Pivot operation.
// The pivot operation ensures that the element == 1; all other elements become == 0.

void pivot(vector<vector<double>> &tableau, int pivotRow, int pivotCol) {
    double pivotValue = tableau[pivotRow][pivotCol];
    int cols = tableau[0].size();

    // Make the pivot element 1
    for (int j = 0; j < cols; ++j) {
        tableau[pivotRow][j] /= pivotValue;
    }

    // Make all other elements in the pivot column 0
    for (int i = 0; i < tableau.size(); ++i) {
        if (i != pivotRow) {
            double factor = tableau[i][pivotCol];
            for (int j = 0; j < cols; ++j) {
                tableau[i][j] -= factor * tableau[pivotRow][j];
            }
        }
    }
}

// Step 5
// Random string of constraints...
vector<vector<double>> tableau = {
    {2, 3, 1, 0, 0, 100}, // Constraint 1...
    {4, 1, 0, 1, 0, 80},  // Constraint 2...
    {3, 2, 0, 0, 1, 60},  // Constraint 3...
    {-3, -5, 0, 0, 0, 0}  // Objective function...
};

// Main function to execute the program
int main() {
    // Print the initial tableau
    cout << "Initial Tableau:\n";
    printTableau(tableau);

    // Find the pivot column
    int pivotCol = findPivotColumn(tableau);
    cout << "Pivot Column: " << pivotCol << "\n";

    // Find the pivot row
    int pivotRow = findPivotRow(tableau, pivotCol);
    cout << "Pivot Row: " << pivotRow << "\n";

    // Perform the pivot operation
    pivot(tableau, pivotRow, pivotCol);
    
    // Print the updated tableau
    cout << "Updated Tableau after pivoting:\n";
    printTableau(tableau);
            }