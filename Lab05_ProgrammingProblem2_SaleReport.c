//
//  main.c
//  Lab05_ProgrammingProblem1_SaleReport
//
//  Created by Cyn Tran on 3/6/24.
//

#include <stdio.h>

int main() {
    
    // Monthly sales numbers
    double sales[12]; //create array to put values of sale for 12 month sale
    double total_sales = 0.0; //initialize sale of the 12 months

    // Input monthly sales from the user
    printf("Enter 12 monthly sales numbers:\n");
    for (int i = 0; i < 12; i++) { //iterate through the array and get the value inside the array
        scanf("%lf", &sales[i]); //
        total_sales += sales[i];
    }

    // Calculate average sales
    double average_sales = total_sales / 12;

    // Find minimum sales
    double min_sales = sales[0];
    int min_month = 0;
    for (int i = 1; i < 12; i++) { //go through the array of the sale of each month
        if (sales[i] < min_sales) { //compare value of minimum sale to sale of each month, if smaller then minimum sale
            min_sales = sales[i]; //then we set minimum sale to new value
            min_month = i;
        }
    }

    // Find maximum sales
    double max_sales = sales[0];
    int max_month = 0;
    for (int i = 1; i < 12; i++) { //similar to minimum sale but compare which value is bigger than max sale
        if (sales[i] > max_sales) {
            max_sales = sales[i];
            max_month = i;
        }
    }

    // Sort sales in descending order
    for (int i = 0; i < 11; i++) {
        for (int j = i + 1; j < 12; j++) {
            if (sales[i] < sales[j]) {
                double temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
            }
        }
    }

    // Print monthly sales report
    printf("\nMonthly sales report for 2022:\n");
    const char* months[12] = {"January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        printf("%s $%.2lf\n", months[i], sales[i]);
    }

    // Print sales summary
    printf("\nSales summary:\n");
    printf("Minimum sales: $%.2lf (%s)\n", min_sales, months[min_month]);
    printf("Maximum sales: $%.2lf (%s)\n", max_sales, months[max_month]);
    printf("Average sales: $%.2lf\n", average_sales);

    // Calculate and print six-month moving averages
    printf("\nSix-Month Moving Average Report:\n");
    for (int i = 0; i < 7; i++) {
        double sum = 0.0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        double average = sum / 6;
        printf("%s - %s $%.2lf\n", months[i], months[i + 5], average);
    }

    // Print Sales Report (Highest to Lowest)
    printf("\nSales Report (Highest to Lowest):\n");
    for (int i = 0; i < 12; i++) {
        printf("%s $%.2lf\n", months[i], sales[i]);
    }

    return 0;
}

