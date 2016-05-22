#include <stdio.h>
#include <stdlib.h>
#include "sentence_word.h"
#include <ctype.h>

int main(){
    const char name[] = "text.txt";
    FILE * file;
    file = fopen(name, "r");
    if(NULL == file)
        return 1;
    char c;
    int len = 0;
    char word[25] = "";
    text_t * text = text_new();
    sen_t * sen = sen_new();
    while((c = fgetc(file)) != EOF){
        //printf("%c", c);
        if(ispunct(c)){
            if(c == '.' || c == '!' || c == '?'){
                if(len == 0)
                    continue;
                addWord(sen, word_new(word));
                addSen(text, sen);
                sen = sen_new();
                memset(word, 0, 25);
                len = 0;
            }
            continue;
        }
        else if(isspace(c)){
            if(len == 0)
                continue;
            addWord(sen, word_new(word));
            memset(word, 0, 25);
            len = 0;
        }
        else{
            word[len] = c;
            len++;
        }
    }

    fclose(file);
    fprint(text);
    text_free(text);
    return 0;
}
