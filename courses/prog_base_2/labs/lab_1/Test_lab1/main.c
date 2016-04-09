#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "term.h"
#include "tourniquet.h"
#include <stdio.h>

static void term_status_trueStatus(void **state){
    term_t * stud = term_new(STUDENT);
    assert_int_equal(term_status(stud), STUDENT);
    term_free(stud);
}
static void term_count_neither(void **state){
    term_t * stud = term_new(STUDENT);
    assert_int_equal(term_num(stud, STUDENT), 0);
    term_free(stud);
}
static void term_count_onePerson(void **state){
    term_t * stud[2];
    stud[0] = term_new(STUDENT);
    stud[1] = term_new(STUDENT);
    term_count(2, stud, STUDENT);
    assert_int_equal(term_num(stud[0], STUDENT), 1);
    term_free(stud);
}
static void term_count_twoTerm(void **state){
    term_t * stud[2];
    stud[0] = term_new(STUDENT);
    stud[1] = term_new(STUDENT);
    term_count(2, stud, STUDENT);
    assert_int_equal(term_num(stud[0], STUDENT), term_num(stud[1], STUDENT));
    term_free(stud);
}
static void term_count_notPerson(void **state){
    term_t * stud[2];
    stud[0] = term_new(STUDENT);
    stud[1] = term_new(STUDENT);
    term_count(2, stud, 34567);
    assert_int_equal(term_num(stud[0], STUDENT), 0);
    term_free(stud);
}
static void term_count_onePerson_false(void **state){
    term_t * stud[2];
    stud[0] = term_new(STUDENT);
    stud[1] = term_new(TEACHER);
    term_count(2, stud, STUDENT);
    assert_int_not_equal(term_num(stud[0], STUDENT), term_num(stud[1], STUDENT));
    term_free(stud);
}
static void term_count_onePerson_true(void **state){
    term_t * stud[2];
    stud[0] = term_new(STUDENT);
    stud[1] = term_new(STUDENT);
    term_count(2, stud, STUDENT);
    assert_int_equal(term_num(stud[0], STUDENT), term_num(stud[1], STUDENT));
    term_free(stud);
}
static void term_counstructor_onePerson_false(void **state){
    term_t * stud[2];
    stud[0] = term_new(STUDENT);
    stud[1] = term_new(STUDENT);
    term_count(2, stud, TEACHER);
    term_count(2, stud, TEACHER);
    assert_int_equal(term_num(stud[0], TEACHER), -1);
    term_free(stud);
}
static void term_count_onePersonTwoTerm_false(void **state){
    term_t * stud[2];
    stud[0] = term_new(STUDENT);
    stud[1] = term_new(TEACHER);
    term_count(2, stud, TEACHER);
    term_count(2, stud, TEACHER);
    assert_int_not_equal(term_num(stud[0], TEACHER), term_num(stud[1], TEACHER));
    term_free(stud);
}
static void turn_constructor_zero(void **state){
    turn_t * turn[2];
    turn[0] = turn_new();
    turn[1] = turn_new();
    assert_int_equal(turn_who(turn[0]), 0);
    turn_free(turn);
}
static void turn_returnIndex(void **state){
    turn_t * turn[2];
    turn[0] = turn_new();
    turn[1] = turn_new();
    //printf("enter num ");
    assert_int_equal(turn_expect(2, turn, 3), 0 || 1);
    turn_free(turn);
}
static void turn_delNum_zeroValue(void **state){
    turn_t * turn[2];
    turn[0] = turn_new();
    turn[1] = turn_new();
    //printf("enter num ");
    int index = turn_expect(2, turn, 3);
    turn_repl_zero(turn[index]);
    assert_int_equal(turn_who(turn[index]), 0);
    turn_free(turn);
}
static void turn_scanfWho_truePerson(void **state){
    turn_t * turn[2];
    turn[0] = turn_new();
    turn[1] = turn_new();
    //printf("enter num ");
    int index = turn_expect(2, turn, TEACHER);
    int index2;
    //printf("\nenter the same num ");
    //scanf("%i", &index2);
    assert_int_equal(turn_who(turn[index]), TEACHER);
    turn_free(turn);
}






int main(){
   const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(term_status_trueStatus),
        cmocka_unit_test(term_count_neither),
        cmocka_unit_test(term_count_onePerson),
        cmocka_unit_test(term_count_twoTerm),
        cmocka_unit_test(term_count_notPerson),
        cmocka_unit_test(term_count_onePerson_false),
        cmocka_unit_test(term_count_onePerson_true),
        cmocka_unit_test(term_counstructor_onePerson_false),
        cmocka_unit_test(term_count_onePersonTwoTerm_false),
        cmocka_unit_test(turn_constructor_zero),
        cmocka_unit_test(turn_returnIndex),
        cmocka_unit_test(turn_delNum_zeroValue),
        cmocka_unit_test(turn_scanfWho_truePerson),



    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
