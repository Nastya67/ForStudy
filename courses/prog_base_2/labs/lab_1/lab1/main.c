#include <stdio.h>
#include <stdlib.h>
#include "term.h"
#include "tourniquet.h"

#define NUM_TURN 5
#define NUM_TERM 7

int main(){
    int i;
    int arr[7] = {STUDENT, TEACHER, PERSONAL, STUDENT + TEACHER, STUDENT + PERSONAL, TEACHER + PERSONAL, STUDENT + TEACHER + PERSONAL};
    turn_t * turniketu[NUM_TURN];
    term_t * terminalu[NUM_TERM];
    for(i = 0; i < NUM_TURN; i++){
          turniketu[i] = turn_new();
    }
    for(i = 0; i < NUM_TERM; i++){
          terminalu[i] = term_new(arr[i]);
    }
    int index_turn = 0, who = 0;
    term_print(NUM_TERM, terminalu);

    while(1){
        index_turn = turn_expect(NUM_TURN, turniketu);
        who = turn_who(turniketu[index_turn]);
        turn_repl_zero(turniketu[index_turn]);
        term_count(NUM_TERM, terminalu, who);
        term_print(NUM_TERM, terminalu);
    }


    for(i = 0; i < NUM_TURN; i++){
          turn_free(turniketu[i]);
    }
    for(i = 0; i < NUM_TERM; i++){
          term_free(terminalu[i]);
    }
    return 0;
}
