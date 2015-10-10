#include <math.h>
double calc(double x, double y, double z) {
   double a;
   if(x==y)
       return NAN;
   if(x==-y)
       return NAN;
   if(sin(y)==0)
       return NAN;
   if(z==0)
       return NAN;
       
a=pow(x,(y+1))/pow((x-y),(1/z))+y/(6*fabs(x+y))+pow(x,(1/fabs(sin(y))));

   return a;
}

