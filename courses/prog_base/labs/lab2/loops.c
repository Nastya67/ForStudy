#include<stdio.h>
#include<math.h>

double calc(int n, int m){
    double x = 0;
    int i, j;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= m; j++){
            x = x + cos(M_PI/i)*(i/j);
        }
    }
    return x;
}



