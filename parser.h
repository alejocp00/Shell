#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "source.h"
#include "node.h"

Node *parse_simple_command(Token *token);

#endif