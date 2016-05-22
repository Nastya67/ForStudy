#ifndef SENTENCE_WORD_H_INCLUDED
#define SENTENCE_WORD_H_INCLUDED

typedef struct text_s text_t;
typedef struct sen_s sen_t;
typedef struct word_s word_t;

void addSen(text_t * text, sen_t * sen);
void addWord(sen_t * sen, word_t * word);

#endif // SENTENCE_WORD_H_INCLUDED
