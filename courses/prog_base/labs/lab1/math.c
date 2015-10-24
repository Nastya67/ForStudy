#include <math.h>

double calc(double x, double y, double z) {
  double a;
  if(x==y||x== -y||sin(y)==0||z==0)
      return NAN;


  a=pow(x,y+1)/pow((x-y),1/z)+y/(6*fabs(x+y))+pow(x,1/fabs(sin(y)));

  return a;
 }
