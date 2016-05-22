#include "sentence_word.h"
#include "list/list.h"
#include <stdio.h>

struct text_s{
    list_t * text;
};
struct sen_s{
    list_t * sen;
};
struct word_s{
    char * word;
};

text_t * text_new(){
    text_t * self = malloc(sizeof(text_t));
    self->text = list_new();
    return self;
}
sen_t * sen_new(){
    sen_t * self = malloc(sizeof(sen_t));
    self->sen = list_new();
    return self;
}
word_t * word_new(char * word){
    word_t * self = malloc(sizeof(word_t));
    self->word = malloc(sizeof(char)*strlen(word));
    strcpy(self->word, word);
    return self;
}
void addWord(sen_t * sen, word_t * word){
    int i;
    for(i = 0; i < list_getSize(sen->sen); i++){
        word_t * tmp = (word_t * )list_get(sen->sen, i);
        if(!strcmp(word->word, tmp->word))
            return 0;
    }
    list_push_back(sen->sen, word);
}
void addSen(text_t * text, sen_t * sen){
    list_push_back(text->text, sen);
}
void text_free(text_t * text){
    list_free(text->text);
}
void fprint(text_t * text){
    const char name[] = "text_final.txt";
    FILE * file;
    file = fopen(name, "w");
    if(NULL == file)
        return 1;
    int i, j;
    for(i = 0; i < list_getSize(text->text); i++){
        sen_t * sen = (sen_t *)list_get(text->text, i);
        for(j = 0; j < list_getSize(sen->sen); j++){
            if(j > 0)
                fprintf(file, ", ");
            word_t * word = (word_t * )list_get(sen->sen, j);
            printf("%s", word->word);
            fprintf(file, "%s",  word->word);
        }
        fprintf(file, ".\n");
        printf(".\n");
    }
    fclose(file);
}

