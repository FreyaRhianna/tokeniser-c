#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

regex_t regexInteger;
regex_t regexIdentifier;
regex_t regexStringlit;
regex_t regexToken;

int result;
struct allTokens{
    struct token *token;
    struct allTokens *nextToken;
};


enum tokenType{
    LITERAL_STRING,
    INTEGER,
    TOKEN,
    IDENTIFIER,
    EMPTY
};


typedef struct token{
    enum tokenType type;
    char *data;
}token_t;

void assignToken(token_t *tail, enum tokenType type, char *str){
    tail->type = type;
    tail->data = malloc(sizeof(char) * 50);
    tail->data = str;
    puts(tail->data);
}

void tokeniser(char *str){
    char delimiter[] = " ";
    char *word = strtok(str,delimiter);
    token_t *tail = malloc(sizeof(token_t));
    if(!regexec(&regexInteger,word,0,NULL,0)){
        assignToken(tail, INTEGER, word);
    }else if(!regexec(&regexStringlit,word,0,NULL,0)){
        word = &word[1];
        word[strlen(word) - 1] = '\0';
        assignToken(tail,LITERAL_STRING,word);
    }else if(!regexec(&regexIdentifier,word,0,NULL,0)){
        assignToken(tail,IDENTIFIER,word);
    }else if(!regexec(&regexToken,word,0,NULL,0)){
        assignToken(tail,TOKEN,word);
    }
}


int main(){
    char str[] = "{ alNUm street";
    if(regcomp(&regexInteger, "^[[:digit:]+]",0)){
        exit(1);
    };
    if(regcomp(&regexStringlit,"^\".*\"",0)){
        exit(1);
    };
    if(regcomp(&regexIdentifier,"^[a-z][:alnum:]",0)){
        exit(1);
    };
    if(regcomp(&regexToken,"[^[:alnum:]]",0)){
        exit(1);
    };

    tokeniser(str);
}