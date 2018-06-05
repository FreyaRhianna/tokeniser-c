#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

regex_t regex;
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


struct token{
    enum tokenType type;
    char *data;
};


void tokeniser(char *str){
    result = regexec(&regex,str,0,NULL,0);
    if(!result) {
        puts("It matches!");
    }else{
        puts("It doesn't match");
    };
}


int main(){
    result = regcomp(&regex, "^[[:digit:]+]",0);
    if(result){
        exit(1);
    }
    tokeniser("84 street");
}