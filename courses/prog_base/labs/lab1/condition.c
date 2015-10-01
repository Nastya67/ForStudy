#import <math.h>

int satisfies(int a, int b, int c) {
   int result;
    scanf("%i, %i, %i", &a, &b, &c);
     switch(a, b, c){
        case"a<0 && b<0 && c<0" :
            if(a<b && a<c){
              int modmin = abs(a);
              int sum2 = b+c;
                if(sum2<(-256) && modmin==2, 4, 8, 16, 32, 64, 128){
                    result = 1;
                }
                if(abs(sum2)>modmin && sum2>(-256)){
                    result = 1;
                }
            }
            if(b<a && b<c){
              int modmin = abs(b);
              int sum2 = a+c;
                if(sum2<(-256) && modmin==2, 4, 8, 16, 32, 64, 128){
                   result = 1;
                }
                if(abs(sum2)>modmin && sum2>(-256)){
                    result = 1;
                }
            }
            if(c<a && c<b){
              int modmin = abs(c);
              int sum2 = a+b;
                if(sum2<(-256) && modmin==2, 4, 8, 16, 32, 64, 128){
                    result = 1;
                }
                if(abs(sum2)>modmin && sum2>(-256)){
                    result = 1;
                }
            }
         break;
        case "a>=0 && b>=0 && c>=0":
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
         break;
        default:{
          switch(a, b, c){
           if((a<0 && b>=0 && c>=0)||(b<0 && a>=0 && c>=0)||(c<0 && a>=0 && b>=0)){
            case"a<0 && b>=0 && c>=0": if(a>(-256)){
                   result =1;
               } break;
            case"b<0 && a>=0 && c>=0": if(b>(-256)){
                   result = 1;
               } break;
            case"c<0 && a>=0 && b>=0": if(c>(-256)){
                   result = 1;
               } break;
           }
           else{
            case"a<0 && b<0 && c>=0": if(((a+b)*5)>(-256)){
                       result = 1;
                   }   break;
            case"a<0 && c<0 && b>=0": if(((a+c)*5)>(-256)){
                       result = 1;
                   }   break;
            case"b<0 && c<0 && a>=0": if(((b+c)*5)>(-256)){
                       result = 1;
                   }   break;
           }
          default: result = 0;
          }
        }
     }
   return result;
}
