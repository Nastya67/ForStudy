#include <stdio.h>
#include <stdlib.h>

char * process(char * resultStr, /* �������� �� ������, � ��� ���������� ���������*/
               const char * textLines[], /*  ����� ����� (�����)*/
               int linesNum, /*����� ������ */
               const char * extraStr)/* ��������� ������ */{

    int i, num[100];
    int* es, vx, j, result[2];
    int numEs = sizeof(extraStr);       /*������� �������� ��������� ������*/
    for(i=0; i < linesNum; i++){      /*�������� ����� ��������� ������*/
        for(es = extraStr; es; es++){       /*�������� �������� ���������� ������*/
            vx = strchr(textLines[i], es);                /*������� �� ����� ��������� �������� ��������� ������ � ������ ��������� ������*/
            if(vx){                     /*���� � ���..*/
                num[i]++;       /*������� ���� ������ "�" ��������� ������ � ���������� �������*/
                if(num[i]==numEs) {      /*���� ������� ���� == ������� �������� ����������� �����*/
                    result[0] = textLines[i];           /*�������� ���������� �������� ������, ��� ������*/
                    result[1] = i; /*����� ������*/
                }
            }
        }
    }
    resultStr = result;
    return  resultStr;
}
/*strchr(s1, ch);
������� �������� �� ����� ��������� ������� ch � ������ s1.*/
