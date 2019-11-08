//
// Created by An on 9/25/2019.
//

#ifndef CMSC403A4_PARSER_H
#define CMSC403A4_PARSER_H

_Bool parser(struct lexics *someLexics, int numberOfLexics);

_Bool function();
_Bool header();
_Bool arg_decl();
_Bool body();
_Bool statement_list();
_Bool statement();
_Bool while_loop();
_Bool return0();
_Bool assignment();
_Bool expression();
_Bool term();



#endif //CMSC403A4_PARSER_H
