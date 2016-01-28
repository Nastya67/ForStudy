#import <math.h>

int satisfies(int a, int b, int c) {
   int result;
       scanf("%i, %i, %i", &a, &b, &c);
         if(a<0 && b<0 && c<0) {
               if(a<b && a<c){
                 int modmin = abs(a);
                 int sum2 = b+c;
                   if(sum2<(-256) && (modmin==2||modmin==4||modmin==8||modmin==16
                                      ||modmin==32||modmin==64||modmin==128)){
                       result = 1;
                   }
                   if(abs(sum2)>modmin && sum2>(-256)){
                       result = 1;
                   }
               }
               if(b<a && b<c){
                 int modmin = abs(b);
                 int sum2 = a+c;
                   if(sum2<(-256) && (modmin==2||modmin==4||modmin==8||modmin==16
                                      ||modmin==32||modmin==64||modmin==128)){
                      result = 1;
                   }
                   if(abs(sum2)>modmin && sum2>(-256)){
                       result = 1;
                   }
               }
               if(c<a && c<b){
                 int modmin = abs(c);
                 int sum2 = a+b;
                   if(sum2<(-256) && (modmin==2||modmin==4||modmin==8||modmin==16
                                      ||modmin==32||modmin==64||modmin==128)){
                       result = 1;
                   }
                   if(abs(sum2)>modmin && sum2>(-256)){
                       result = 1;
                   }
               }
         }
         else if(a>=0 && b>=0 && c>=0){
               if(a>b, a>c){
                   int max = a;
                   if(b>c){
                       int min = c;
                       if((max-min)>32){
                           result = 1;
                       }
                   }
                   else{
                       int min = b;
                       if((max-min)>32){
                           result = 1;
                       }
                   }
               }
               if(b>a, b>c){
                   int max = b;
                   if(a>c){
                       int min = c;
                       if((max-min)>32){
                           result = 1;
                       }
                   }
                   else{
                       int min = a;
                       if((max-min)>32){
                           result = 1;
                       }
                   }
               }
               if(c>a, c>b){
                   int max = c;
                   if(a>b){
                       int min = b;
                       if((max-min)>32){
                           result = 1;
                       }
                   }
                   else{
                       int min = a;
                       if((max-min)>32){
                           result = 1;
                       }
                   }
               }
         }
         else if(a<0 && b>=0 && c>=0){
               if(a>(-256)){
                      result =1;
               }
         }
         else if(b<0 && a>=0 && c>=0){
               if(b>(-256)){
                      result = 1;
               }
         }
         else if(c<0 && a>=0 && b>=0){
               if(c>(-256)){
                      result = 1;
               }
         }
         else if(a<0 && b<0 && c>=0){
               if(((a+b)*5)>(-256)){
                      result = 1;
               }
         }
         else if(a<0 && c<0 && b>=0){
               if(((a+c)*5)>(-256)){
                      result = 1;
               }
         }
         else if(b<0 && c<0 && a>=0){
               if(((b+c)*5)>(-256)){
                      result = 1;
               }
         }
        else {
            return 0;
        }

   return result;
}

