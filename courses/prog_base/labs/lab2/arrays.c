#include<string.h>
#include<math.h>
void fillRand3(int arr[], int size);
int checkRand3(int arr[], int size);
float meanValue(int arr[], int size);
int minValue(int arr[], int size);
int meanIndex(int arr[], int size);
int minIndex(int arr[], int size);
int maxOccurance(int arr[], int size);
int diff(int arr1[], int arr2[], int res[], int size);
void sub(int arr1[], int arr2[], int res[], int size);
int eq(int arr1[], int arr2[], int size);
void land(int arr1[], int arr2[], int res[], int size);

int main(){
    int size = 6;
    int arr[size];
    int arr1[6]={1,2,3,4,5,6};
    int arr2[6]={-11,-12,-13,-14,-15,-16};
    int res[6];
    int i;
    fillRand3(arr, size);
    for (i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\nrez = %d\n",checkRand3(arr, size));
    printf("sred = %.3f\n",meanValue(arr, size));
    printf("min = %d\n", minValue(arr, size));
    printf("index= %i\n", meanIndex(arr, size));
    printf("index = %d\n", minIndex(arr, size));
    printf("elem = %d\n", maxOccurance(arr, size));
    printf("res = %d\n", diff(arr1, arr2, res, size));
    sub(arr1, arr2, res, size);
    for (i=0;i<size;i++)
        printf("%d\t", res[i]);
    printf("\neq= %d\n", eq(arr1, arr2, size));
    land(arr1, arr2, res, size);
    for (i=0;i<size;i++)
        printf("%d\t", res[i]);
    return 0;
}



void fillRand3(int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        arr[i] = rand()%2;
    }
}

int checkRand3(int arr[], int size){        //ѕерев≥рка елемент≥в масиву
    int i, x = 2;
    for(i = 0; i < size; i++){
        if(arr[i] != 0 && arr[i] != 1){
            x = 0;
            i = size;
        }
    }
    if(x == 0){
        return 0;
    }
    else{
        return 1;
    }
}

float meanValue(int arr[], int size) {      // знаходить середнЇ значенн€ серед елемент≥в масиву
    int i, x = 0;
    float ix;
    for(i = 0; i < size; i++){
        x = x + arr[i];
    }
    ix = x/size;
    return ix;
}

int minValue(int arr[], int size){      //«находить м≥н≥мальний серед елемент≥в масиву
    int i, x = arr[0];
    for(i = 0; i < size; i++){
        if(x > arr[i]){
            x = arr[i];
        }
    }
    return x;
}

int meanIndex(int arr[], int size){     //«находить ≥ндекс першого елементу, значенн€ €кого найближче до середнього значенн€ серед елемент≥в масиву
    int i, a, sum = 0;
    float ix;
    for(i = 0; i < size; i++){
        sum = sum + arr[i];
    }
    ix = sum/size;
    float x;
    x = fabs(arr[size - 1]-ix);
    a = arr[size - 1];
    for(i = size - 1; i >= 0; i--){
        if(x > fabs(arr[i] - ix)){
            x = fabs(arr[i] - ix);
            a = i;
        }
    }
    return a;
}

int minIndex(int arr[], int size){      //«находить ≥ндекс першого м≥н≥мального елемента масиву
    int i, ix, x = arr[size - 1];
    for(i = size - 1; i >= 0; i--){
        if(x >= arr[i]){
            x = arr[i];
            ix = i;
        }
    }
    return ix;
}

int maxOccurance(int arr[], int size){      //«находить значенн€, €ке найчаст≥ше зустр≥чаЇтьс€ у масив≥. якщо таких дек≥лька, повертаЇ б≥льше з них
    int i, j, arr2[size], x, x2 = 0;
    for(i = 0; i < size; i++){
        arr2[i] = 0;
    }
    for(i = 0; i < size; i++){
        x = arr[i];
        for(j = 0; j < size; j++){
            if(x == arr[j]){
                x2++;
                arr2[i] = x2;
            }
        }
    }
    x2 =0;
    x = NULL;
    for(i = 0; i < size; i++){
        if(x2 < arr2[i]){
            x2 = arr2[i];
            if(x < arr[i]){
                x = arr[i];
            }
        }
    }
    return x;
}

int diff(int arr1[], int arr2[], int res[], int size){    //ѕерев≥р€Їтьс€ р≥зниц€ м≥ж в≥дпов≥дними елементами масив≥в arr1 ≥ arr2.
    int i, x = 0;                                         //÷€ р≥зниц€ записуЇтьс€ у в≥дпов≥дний елемент масиву res.
    for(i = 0; i < size; i++){                            //якщо вс≥ р≥зниц≥ р≥вн≥ 0 (тобто масиви arr1 ≥ arr2 одинаков≥, то функц≥€ повертаЇ 1, ≥накше - 0)
        res[i] = arr1[i] - arr2[i];
        x = x + res[i];
    }
    if(x == 0){
        return 0;
    }
    else{
        return 1;
    }
}

void sub(int arr1[], int arr2[], int res[], int size){      //р≥зниц€
    int i;
    for(i = 0; i < size; i++){
        res[i] = arr1[i] - arr2[i];
    }
}

int eq(int arr1[], int arr2[], int size){
    int i, x;
    for(i = 0; i < size; i++){
        if(arr1[i] == arr2[i]){
            x++;
        }
    }
    if(x == size){
        return 1;
    }
    else{
        return 0;
    }
}

void land(int arr1[], int arr2[], int res[], int size){
    int i;
    for(i = 0; i < size; i++){
        res[i] = arr1[i] && arr2[i];
    }
}
