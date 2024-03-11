//
//  main.c
//  Lab05_ProgrammingProblem1_SaleReport
//
//  Created by Cyn Tran on 3/6/24.
//

#include <stdio.h>

int main() {
    
    // Monthly sales numbers
    double sales[12]; // Array to store the sales for 12 months
    double total_sales = 0.0; // Variable to store the total sales

    // Input monthly sales from the user
    printf("Enter 12 monthly sales numbers:\n");
    // Loop to input sales from January to December
    for (int i = 0; i < 12; i++) {
        scanf("%lf", &sales[i]); // Read the sales for each month
        total_sales += sales[i]; // Update the total sales
    }

    // Print monthly sales report
    printf("\nMonthly sales report for 2022:\n");
    const char* months[12] = {"January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        printf("%s $%.2lf\n", months[i], sales[i]);
    }
    
    // Calculate average sales
    double average_sales = total_sales / 12;

    // Find minimum sales
    double min_sales = sales[0];
    int min_month = 0;
    for (int i = 1; i < 12; i++) {
        if (sales[i] < min_sales) {
            min_sales = sales[i];
            min_month = i;
        }
    }

    // Find maximum sales
    double max_sales = sales[0];
    int max_month = 0;
    for (int i = 1; i < 12; i++) {
        if (sales[i] > max_sales) {
            max_sales = sales[i];
            max_month = i;
        }
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
    // Sort sales in descending order
    for (int i = 0; i < 11; i++) {
        for (int j = i + 1; j < 12; j++) {
            if (sales[i] < sales[j]) {
                double temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
                // Swap months as well
                const char* temp_month = months[i];
                months[i] = months[j];
                months[j] = temp_month;
            }
        }
    }


    // Print Sales Report (Highest to Lowest)
    printf("\nSales Report (Highest to Lowest):\n");
    for (int i = 0; i < 12; i++) {
        printf("%s $%.2lf\n", months[i], sales[i]);
    }

    return 0;
}

