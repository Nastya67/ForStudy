#include <stdio.h>
#include <stdlib.h>

void fillRand(int mat[4][4]){
    int i, j;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            mat[i][j]=(rand()%2000)-1000;
        }
    }
}
void rotateCCW270(int mat[4][4]){
    int mat2[4][4], i, j;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            mat2[i][j]=mat[3-j][i];
        }
    }
    return mat2;
}

void flipH(int mat[4][4]){
    int mat3[4][4], i, j;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            mat3[i][j]=mat[i][3-j];
        }
    }
    return mat3;
}

void transposSide(int mat[4][4]){
    int i, j, mat4[4][4];
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            mat4[i][j]=mat[3-j][3-i];
        }
    }
    return mat4;
}
