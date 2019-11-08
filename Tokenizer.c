//
// Created by An on 9/23/2019.
//
#include <ctype.h>
#include "Givens.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Tokenizer.h"



char str[MY_CHAR_MAX] = ""; //line max
char token[LEXEME_MAX]=""; //max length of one lexeme


_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf)
{
    int strindex=0; //in line
    int tokenindex=0; //in temporary token
    int lexicindex=0; //in array
    //fgets(str, MY_CHAR_MAX, inf); //get first line
    //iterate thru lines
    while (fgets(str, MY_CHAR_MAX, inf)!=NULL)
    {
        while (str[strindex]!='\0') //iterate through characters
        {
            //single special characters
            if (str[strindex] == '(' || str[strindex] ==')' || str[strindex] =='{'||str[strindex] =='}'||str[strindex] ==','||str[strindex] ==';'||str[strindex] =='+'||str[strindex] =='*'||str[strindex] =='%')
            {
                //aLex[lexicindex].lexeme[0,tokenindex-1]=token[0,tokenindex-1];
                if (token[0]!='\0') //token array has something to copy
                {
                    strncpy(aLex[lexicindex].lexeme, token, tokenindex); //copy it and move to next struct
                    lexicindex++;
                    *numLex+=2; //increment number of lexemes
                }
                else *numLex+=1;

                aLex[lexicindex].lexeme[0]=str[strindex]; //copy symbol that you just read
                lexicindex++;
                strindex++;
                tokenindex=0;
                //clear out "token array"
                memset(token, '\0', sizeof(token));
            }
            else if (isspace(str[strindex])) //if it's any white space character
            {
                if (token[0]!='\0') //current token string has some values
                {
                    strncpy(aLex[lexicindex].lexeme, token, tokenindex); //copy values
                    lexicindex++;
                    *numLex+=1;
                }
                strindex++; //move on
                tokenindex=0;
                memset(token, '\0', sizeof(token));
            }
            else if (str[strindex]==('='))
            {
                if (token[0]!='\0') //something to copy
                {
                    strncpy(aLex[lexicindex].lexeme, token, tokenindex); //take preceding chars
                    lexicindex++;
                    *numLex+=2;
                    memset(token, '\0', sizeof(token)); //empty out array
                }
                else *numLex+=1;

                if (str[strindex+1]=='=') //== lexeme
                {
                    aLex[lexicindex].lexeme[0]='=';
                    aLex[lexicindex].lexeme[1]='=';
                    strindex+=2;
                    lexicindex++;
                    tokenindex=0;
                }
                else //single equals
                {
                    aLex[lexicindex].lexeme[0]='=';
                    strindex++;
                    lexicindex++;
                    tokenindex=0;
                }

            }
            else if (str[strindex]==('!')) {
                if (str[strindex + 1] == '=') { //!= lexeme
                    if (token[0]!='\0'){ //something to copy
                        strncpy(aLex[lexicindex].lexeme, token, tokenindex); //take preceding chars
                        lexicindex++;
                        *numLex+=2;
                    }
                    else *numLex+=1;
                    //aLex[lexicindex].lexeme[0, 1] = "!=";

                    aLex[lexicindex].lexeme[0]='!';
                    aLex[lexicindex].lexeme[1]='=';
                    strindex += 2;
                    lexicindex++;
                    tokenindex = 0;
                    memset(token, '\0', sizeof(token));
                }
                else //just an !, not a special symbol
                {
                    token[tokenindex]=str[strindex]; //add ! to current lexeme
                    tokenindex++;
                    strindex++;
                    //*numLex+=1;
                }
            }
            else //nonspecial character
            {
                token[tokenindex]=str[strindex]; //add to current lexeme
                tokenindex++;
                strindex++;
            }
        }
        //fgets(str, MY_CHAR_MAX, inf); //get next line
        strindex=0;
    }
    if (matchTokens(aLex, numLex)) //assign int values to each lexeme
        return true;
    return false; //any other scenario returns false
}

_Bool matchTokens(struct lexics *aLex, int *numLex) //match all lexemes to a token
{
    for (int i=0; i<*numLex; i++)
    {
        if (aLex[i].lexeme[0]==('('))
            aLex[i].token=LEFT_PARENTHESIS;
        else if (aLex[i].lexeme[0]==(')'))
            aLex[i].token=RIGHT_PARENTHESIS;
        else if (aLex[i].lexeme[0]==('{'))
            aLex[i].token=LEFT_BRACKET;
        else if (aLex[i].lexeme[0]==('}'))
            aLex[i].token=RIGHT_BRACKET;
        else if (aLex[i].lexeme[0]=='w' && aLex[i].lexeme[1]=='h' && aLex[i].lexeme[2]=='i' && aLex[i].lexeme[3]=='l' && aLex[i].lexeme[4]=='e' && aLex[i].lexeme[5]=='\0')
            aLex[i].token=WHILE_KEYWORD;
        else if (aLex[i].lexeme[0]=='r' && aLex[i].lexeme[1]=='e' && aLex[i].lexeme[2]=='t' && aLex[i].lexeme[3]=='u' && aLex[i].lexeme[4]=='r' && aLex[i].lexeme[5]=='n' && aLex[i].lexeme[6]=='\0')
            aLex[i].token=RETURN_KEYWORD;
        else if (aLex[i].lexeme[0]==('='))
            aLex[i].token=EQUAL;
        else if (aLex[i].lexeme[0]==(','))
            aLex[i].token=COMMA;
        else if (aLex[i].lexeme[0]==(';'))
            aLex[i].token=EOL;
        else if (aLex[i].lexeme[0]=='i' && aLex[i].lexeme[1]=='n' && aLex[i].lexeme[2]=='t' && aLex[i].lexeme[3]=='\0')
            aLex[i].token=VARTYPE;
        else if (aLex[i].lexeme[0]=='v' && aLex[i].lexeme[1]=='o' && aLex[i].lexeme[2]=='i' && aLex[i].lexeme[3]=='d' && aLex[i].lexeme[4]=='\0')
            aLex[i].token=VARTYPE;
        else if (aLex[i].lexeme[0]=='+'||aLex[i].lexeme[0]=='*'||aLex[i].lexeme[0]=='%')
            aLex[i].token=BINOP;
        else if (aLex[i].lexeme[0]=='!' && aLex[i].lexeme[1]=='=')
            aLex[i].token=BINOP;
        else if (aLex[i].lexeme[0]=='=' && aLex[i].lexeme[1]=='=')
            aLex[i].token=BINOP;
        else if (validNumber(aLex[i].lexeme))
            aLex[i].token=NUMBER;
        else if (validIdentifier(aLex[i].lexeme))
            aLex[i].token=IDENTIFIER;
        else return false;
    }
    return true;
}