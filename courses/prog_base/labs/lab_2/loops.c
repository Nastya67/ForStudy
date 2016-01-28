#include<stdio.h>
#include<math.h>

double calc(int n, int m);

int main(){
    int n, m;
    printf("n = ");
    scanf("%i", &n);
    printf("m = ");
    scanf("%i", &m);
    printf("%f", calc(n, m));
    return 0;
}

double calc(int n, int m){
    double x = 0;
    int i, j;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= m; j++){
            x = x + cos(M_PI/i)*((double)i/j);
        }
    }
    return x;
}



