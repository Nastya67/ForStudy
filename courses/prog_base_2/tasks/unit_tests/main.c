#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "mod.h"
#include <stdio.h>

static void size_arr(void **state){
    arr_t * arr1 = arr_new(8);
    assert_int_equal (arr_some(arr1, 8), -1);
    assert_int_equal (arr_some(arr1, -1), -1);
    arr_free(arr1);
}
static void repl_elem_and_return_some_elem(void **state){
    arr_t * arr1 = arr_new(8);
    arr_change(arr1, 1, 10.0);
    assert_int_equal (arr_some(arr1, 1), 10);
    arr_free(arr1);
}
static void not_repl_element(void **state){
    arr_t * arr1 = arr_new(1);
    arr_change(arr1, 0, 78.8);
    arr_change(arr1, 2, 10.0);
    assert_int_not_equal (arr_some(arr1, 0), 10);
    arr_free(arr1);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(size_arr),
        cmocka_unit_test(repl_elem_and_return_some_elem),
        cmocka_unit_test(not_repl_element),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
