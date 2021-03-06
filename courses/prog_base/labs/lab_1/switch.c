#import <math.h>

int exec(int op, int a, int b) {
   int result;
    const double PI = 3.1415;
   if(op<0){
       int c =0;
       c=a;
       a=b;
       b=c;
   }
     switch(op){
      case 0: result = -a;
         break;
      case 1: result = a+b;
         break;
      case 2: result = a-b;
         break;
      case 3: result = a*b;
         break;
      case 4: result = a/b;
         break;
      case 5: result = abs(a);
         break;
      case 6: result = pow(a,b);
         break;
      case 7:

      case 13:

      case 77: result = a%b;
         break;
      case 8: if(a>b){
          result = a;
         }
         if(b>a){
          result = b;
         }
         break;
      case 9: if(a<b){
          result = a;
         }
         if(b<a){
          result = b;
         }
         break;
      case 10:

         switch(abs(b)%8){
             case 0 :result = sizeof(char);
             break;
             case 1: result = sizeof(signed char);
             break;
             case 2: result = sizeof(short);
             break;
             case 3: result = sizeof(unsigned int);
             break;
             case 4: result = sizeof(long);
             break;
             case 5: result = sizeof(unsigned long long);
             break;
             case 6: result = sizeof(float);
             break;
             case 7: result = sizeof(double);
             break;
         }
         result = result*abs(a);
             break;
      case 11:
         if(a==0)
             return NAN;
         else
             result = 6*cos(b*PI)/a;
         break;
      default: if(op<100){
             result = (op%abs(a+1)+(op%abs(b+1)));
         }
         else
             result = -1;
     }

   return result;
}
