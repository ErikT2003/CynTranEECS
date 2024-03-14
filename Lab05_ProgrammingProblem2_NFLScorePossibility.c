#include <stdio.h>

int main() {
    // Problem 2: DETERMINING FOOTBALL SCORE POSSIBILITY
    int score;
    printf("PLEASE ENTER FOOTBALL SCORE: ");
    scanf("%d", &score);
    
    if (score < 2){
        printf("INVALID SCORE: SCORE MUST BE AT LEAST 2 OR HIGHER");
        return 1;
    }
    
    // Different play
    int TD = 6; // Touchdown value
    int FG = 3; // Field goal value
    int safety = 2; // Safety point
    int TD_Con = 8; // Touchdown and conversion point
    int TD_FG = 7; // Touchdown and field goal
    
    // Loop to try to find all possible play with the sum of product equal the score
    printf("possible combinations of scoring plays:\n");
    int count = 0; // Count the possibilities
    for (int a = 0; a <= score/TD; a++){
        for (int b = 0; b <= score/FG; b++){
            for (int c = 0; c <= score/safety; c++){
                for (int d = 0; d <= score/TD_Con; d++){
                    for (int e = 0; e <= score/TD_FG; e++){
                        if ((TD*a + FG*b + safety*c + TD_Con*d + TD_FG*e) == score){
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", d, e, a, b, c);
                            count++;
                        }
                    }
                }
            }
        }
    }
    
    printf("Total combinations: %d\n", count);
    return 0;
}



