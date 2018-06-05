#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

regex_t regexInteger;
regex_t regexIdentifier;
regex_t regexStringlit;
regex_t regexToken;

int result;
typedef struct allTokens{
    struct token *token;
    struct allTokens *nextToken;
}all_token;

all_token *list_head;

enum tokenType{
    LITERAL_STRING,
    INTEGER,
    TOKEN,
    IDENTIFIER,
    EMPTY
};

const char* getType(enum tokenType type){
    switch(type){
        case LITERAL_STRING : return "LITERAL STRING";
        case INTEGER : return "INTEGER";
        case TOKEN : return "TOKEN";
        case IDENTIFIER : return "IDENTIFIER";
        case EMPTY : return "Empty";
    }
}

typedef struct token{
    enum tokenType type;
    char *data;
}token_t;

void assignToken(token_t *tail, enum tokenType type, char *str){
    tail->type = type;
    tail->data = malloc(sizeof(char) * 50);
    tail->data = str;
}

void tokeniser(char *str){
    char delimiter[] = " ";
    token_t *tail = malloc(sizeof(token_t));
    list_head = malloc(sizeof(token_t));
    list_head= NULL;
    all_token *list_tail = malloc(sizeof(all_token));
    all_token *temp = malloc(sizeof(all_token));

    char *word = strtok(str,delimiter);

    while(word != NULL) {
        if (!regexec(&regexInteger, word, 0, NULL, 0)) {
            assignToken(tail, INTEGER, word);
        } else if (!regexec(&regexStringlit, word, 0, NULL, 0)) {
            word = &word[1];
            word[strlen(word) - 1] = '\0';
            assignToken(tail, LITERAL_STRING, word);
        } else if (!regexec(&regexIdentifier, word, 0, NULL, 0)) {
            assignToken(tail, IDENTIFIER, word);
        } else if (!regexec(&regexToken, word, 0, NULL, 0)) {
            assignToken(tail, TOKEN, word);
        }

        if(!list_head){
            list_head = malloc(sizeof(all_token));
            list_head ->token = tail;
            list_head ->nextToken = NULL;
            list_tail = list_head;
        }else{
            temp = malloc(sizeof(all_token));
            temp->token = tail;
            temp->nextToken = NULL;
            list_tail->nextToken = temp;
            list_tail = temp;
        }
        word = strtok(NULL,delimiter);
        tail = malloc(sizeof(token_t));
    }
}


int main(){
    char str[] = "{ alNUm * street 0 90 \"hey\"";
    if(regcomp(&regexInteger, "^[[:digit:]+]",0)){
        exit(1);
    };
    if(regcomp(&regexStringlit,"^\".*\"",0)){
        exit(1);
    };
    if(regcomp(&regexIdentifier,"^[a-z][a-zA-Z0-9]*",0)){
        exit(1);
    };
    if(regcomp(&regexToken,"[^[:alnum:]]",0)){
        exit(1);
    };

    tokeniser(str);
    while(list_head){
        printf("%s is a/an %s\n", list_head->token->data, getType(list_head->token->type));
        list_head = list_head->nextToken;
    };
    //Still need to do push back
}