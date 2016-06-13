#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void func_oneAlpha_1(void **state){
    assert_int_equal (func("a"), 1);

}
static void func_alphaAndNumb_1(void **state){
    assert_int_equal (func("a2"), 1);
}
static void func_alphaSignAlpha_2(void **state){
    assert_int_equal (func("a/q"), 2);
}
static void func_alphaSpaceAlpha_2(void **state){
    assert_int_equal (func("a q"), 2);
}
static void func_alphAndStr_3(void **state){
    assert_int_equal (func("a q/aSss"), 3);
}
static void func_text_4(void **state){
    assert_int_equal (func("Hello! My name is..."), 4);
}
static void func_doubleSpaseAndPoint_2(void **state){
    assert_int_equal (func("A  s."), 2);
}

int isAlpha(char c){
    if((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a'))
       return 1;
    return 0;
}
int func(char str[]){
    int i = 0;
    int count = 0;
    for(i = 0; i < strlen(str); i++){
        //printf("%c, %c\n", str[i], str[i+1]);
        if(isAlpha(str[i]) && !isAlpha(str[i+1])){
            count++;
            //printf("ok\n");
        }
    }
    //printf("%i\n", count);
    return count;
}

int main(){

    func("mgfkgv lugl/uj ,jg,i");
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(func_oneAlpha_1),
        cmocka_unit_test(func_alphaAndNumb_1),
        cmocka_unit_test(func_alphaSignAlpha_2),
        cmocka_unit_test(func_alphaSpaceAlpha_2),
        cmocka_unit_test(func_alphAndStr_3),
        cmocka_unit_test(func_text_4),
        cmocka_unit_test(func_doubleSpaseAndPoint_2),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
