#include<string.h>
#include<math.h>

void fillRand3(int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        arr[i] = rand()%2;
    }
    return arr;
}

int checkRand3(int arr[], int size){        //�������� �������� ������
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

float meanValue(int arr[], int size) {      // ��������� ������ �������� ����� �������� ������
    int i, x = 0;
    for(i = 0; i < size; i++){
        x = x + arr[i];
    }
    return x/size;
}

int minValue(int arr[], int size){      //��������� ��������� ����� �������� ������
    int i, x = arr[0];
    for(i = 0; i < size; i++){
        if(x > arr[i]){
            x = arr[i]
        }
    }
    return x;
}

int meanIndex(int arr[], int size){     //��������� ������ ������� ��������, �������� ����� ��������� �� ���������� �������� ����� �������� ������
    int i, ix;
    float s, x;
    s = meanValue(arr[],size);
    x = fabs(arr[size - 1]-s);
    for(i = size - 1; i >= 0; i--){
        if(x > fabs(arr[i] - s)){
            x = fabs(arr[i] - s;
            ix = i;
        }
    }
    return ix;
}

int minIndex(int arr[], int size){      //��������� ������ ������� ���������� �������� ������
    int i, ix, x = arr[size - 1];
    for(i = size - 1; i >= 0; i--){
        if(x >= arr[i]){
            x = arr[i];
            ix = i;
        }
    }
    return ix;
}

int maxOccurance(int arr[], int size){      //��������� ��������, ��� ��������� ����������� � �����. ���� ����� �������, ������� ����� � ���
    int i, j, arr2[size], x, x2 = 0;
    for(i = 0; i < size; i++){
        idArr[i] = 0;
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

int diff(int arr1[], int arr2[], int res[], int size){    //������������ ������ �� ���������� ���������� ������ arr1 � arr2.
    int i, x = 0;                                         //�� ������ ���������� � ��������� ������� ������ res.
    for(i = 0; i < size; i++){                            //���� �� ������ ��� 0 (����� ������ arr1 � arr2 ��������, �� ������� ������� 1, ������ - 0)
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

void sub(int arr1[], int arr2[], int res[], int size){      //������
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
        res[i] = arr1[i] & arr2[i];
    }
}
