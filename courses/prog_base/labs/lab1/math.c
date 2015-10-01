#include <math.h>
double calc(double x,
            double y,
            double z) {
   double a;
   if(x==y)
       retern0;
   if(x==-y)
       retern0;
   if(sin(y)==0)
       retern NAN;

a=pow(x,y+1)/pow((x-y),0.5)+y/(6*fabs(x+y))+pow(x,1/fabs(sin(y)));

   return a;
}

