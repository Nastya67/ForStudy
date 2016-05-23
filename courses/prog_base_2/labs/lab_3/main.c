#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <windows.h>

static void queue_size_one(void **state){
    queue_osnova * q1 = new_queue_osnova();
    queue_add(q1, 40);
    assert_int_equal(queue_size(q1), 1);
}
static void queue_size_zero(void **state){
    queue_osnova * q1 = new_queue_osnova();
    assert_int_equal(queue_size(q1), 0);
}
static void queue_2add_1Del_sizeOne(void **state){
    queue_osnova * q1 = new_queue_osnova();
    queue_add(q1, 40);
    queue_add(q1, 50);
    queue_delete(q1);
    assert_int_equal(queue_size(q1), 1);
}
static void queue_getValue(void **state){
    queue_osnova * q1 = new_queue_osnova();
    queue_add(q1, 400);
    assert_int_equal(queue_value(q1, 1), 400);
}
static void queue_delFirst(void **state){
    queue_osnova * q1 = new_queue_osnova();
    queue_add(q1, 10);
    queue_add(q1, 20);
    assert_int_equal(queue_delete(q1), 10);
}
static void queue_getLastVal_lastVal(void **state){
    queue_osnova * q1 = new_queue_osnova();
    queue_add(q1, 10);
    queue_add(q1, 20);
    assert_int_equal(queue_value(q1, queue_size(q1)), 20);
}
static void queue2_addInFirs_secondEmpty(void **state){
    queue_osnova * q1 = new_queue_osnova();
    queue_osnova * q2 = new_queue_osnova();
    queue_add(q1, 10);
    queue_add(q1, 20);
    assert_int_equal(queue_size(q2), 0);
}
static void queue_del_firstNext(void **state){
    queue_osnova * q1 = new_queue_osnova();
    queue_add(q1, 10);
    queue_add(q1, 20);
    queue_delete(q1);
    assert_int_equal(queue_value(q1, 1), 20);
}


int test(){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(queue_size_one),
        cmocka_unit_test(queue_size_zero),
        cmocka_unit_test(queue_2add_1Del_sizeOne),
        cmocka_unit_test(queue_getValue),
        cmocka_unit_test(queue_delFirst),
        cmocka_unit_test(queue_getLastVal_lastVal),
        cmocka_unit_test(queue2_addInFirs_secondEmpty),
        cmocka_unit_test(queue_del_firstNext)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

int main(){
    test();
    Sleep(4000);
    queue_osnova * q1 = new_queue_osnova();
    queue_osnova * q2 = new_queue_osnova();

    queue_subscribe_full(q1, q2, queue_full);
    queue_subscribe_full(q2, q1, queue_full);
    queue_subscribe_empty(q1, q2, queue_empty);
    queue_subscribe_empty(q2, q1, queue_empty);

    user_t * us1 = user_new("Hanna");
    user_t * us2 = user_new("Nina");
    queue_subscribe_multi(q1, us1, queue_overflow);
    queue_subscribe_multi(q1, us2, queue_overflow);
    queue_subscribe_multi(q2, us1, queue_overflow);
    queue_subscribe_multi(q2, us2, queue_overflow);

    int i;
    for(i = 0; i < 3; i++){
        queue_add(q1, rand()%40);
        queue_add(q2, rand()%40);
    }

    int num;
    while(1){
        system("cls");
        num = rand()%100-50;
        queue_osnova * cur = random(q1, q2);
        if(num >= 0){
            queue_add(cur, num);
        }
        else if(num < 0){
            queue_delete(cur);
        }
        queue_print(q1);
        printf("------\n");
        queue_print(q2);
        Sleep(1000);
    }
    user_free(us1);
    user_free(us2);

    return 0;
}
