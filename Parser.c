//
// Created by An on 9/23/2019.
//
#include <stdbool.h>
#include "Givens.h"
#include "Parser.h"

//char *l; //stores lookahead lexeme
int i =0;
struct lexics *Lexics; //store global variable for lexics array

_Bool parser(struct lexics *someLexics, int numberOfLexics)
{
    Lexics = someLexics;
    return function();
}

_Bool function()
{
    if (header()==false)
    {return false;}
    if (body()==false)
    {return false;}
    return true;
}

_Bool header()
{
    if (Lexics[i].token == VARTYPE)
    { i++; }
    else return false;

    if (Lexics[i].token == IDENTIFIER)
    {i++; }
    else return false;

    if (Lexics[i].token == LEFT_PARENTHESIS)
    {i++;}
    else return false;

    if (arg_decl()==true) //optional arg_decl
    {
        i++;
    }

    if (Lexics[i].token ==  RIGHT_PARENTHESIS)
    {i++;}
    else return false;

    return true;
}

_Bool arg_decl()
{
    if (Lexics[i].token == VARTYPE)
    { i++; }
    else return false;

    if (Lexics[i].token == IDENTIFIER)
    {i++; }
    else return false;

    // {COMMA VARTYPE IDENTIFIER}
    bool x=true; //default
    while (x=true)
    {
        if (Lexics[i].token == COMMA)
        { i++; }
        else
        {
            x=false;
            i--; //reset
            break;
        }

        if (Lexics[i].token == VARTYPE)
        { i++; }
        else
        {
            x=false;
            i-=2; //reset
            break;
        }

        if (Lexics[i].token == IDENTIFIER)
        {i++; }
        else
        {
            x=false;
            i-=3; //reset
            break;
        }
    }
    return true;
}

_Bool body()
{
    if (Lexics[i].token == LEFT_BRACKET)
    { i++;}
    else return false;
    if (statement_list()==true)
    {
        i++;
    }
    if (Lexics[i].token == RIGHT_BRACKET)
    {i++;}
    else return false;
    return true;
}

_Bool statement_list()
{
    bool x = statement();
    if (x==true)
    {i++;}
    else return false;
    x = statement();
    while (x)
    {
        i++;
        x=statement();
    }
    return false;
}

_Bool statement()
{
    if (while_loop())
        return true;
    if (return0())
        return true;
    if (assignment())
        return true;
    if (body())
        return true;
    return false;
}

//WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
_Bool while_loop()
{
    if (Lexics[i].token == WHILE_KEYWORD)
    { i++;}
    else return false;

    if (Lexics[i].token == LEFT_PARENTHESIS)
    { i++;}
    else return false;

    if (expression())
        i++;
    else return false;

    if (Lexics[i].token == RIGHT_PARENTHESIS)
    { i++;}
    else return false;

    if (statement())
    { i++;}
    else return false;

    return true;
}

_Bool return0()
{
    if (Lexics[i].token == RETURN_KEYWORD)
    { i++;}
    else return false;

    if (expression())
        i++;
    else return false;

    if (Lexics[i].token == EOL)
    { i++;}
    else return false;

    return true;
}

_Bool assignment()
{
    if (Lexics[i].token == IDENTIFIER)
    { i++;}
    else return false;

    if (Lexics[i].token == EQUAL)
    { i++;}
    else return false;

    if(expression())
        i++;
    else return false;

    if (Lexics[i].token == EOL)
    { i++;}
    else return false;

    return true;
}

_Bool expression()
{
    //first half - term {binop term}
    bool overall=false;
    if (term()) {
        i++;
        overall = true;
    }
    //else overall=false;

    bool x = true;
    while (x) //{binop term}
    {
        if (Lexics[i].token == BINOP)
        {
            i++;
            if (term())
            {
                i++;
            }
            else
            {
                i--;
                x=false;
            }
        }
        else x=false;
    }

    if (overall) return true;

    //first half didn't pass
    if (Lexics[i].token == LEFT_PARENTHESIS)
    { i++;}
    else overall= false;

    if (expression())
    {
        i++;
    }
    else overall=false;

    if (Lexics[i].token == RIGHT_PARENTHESIS)
    {
        i++;
        overall = true;
    }
    else overall= false;

    return overall;
} //messy

_Bool term()
{
    if (Lexics[i].token == IDENTIFIER)
    { i++;}
    else if (Lexics[i].token == NUMBER)
    { i++;}
    else return false;

    return true;
}


