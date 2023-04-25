#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "source.h"
#include "node.h"

/**
 * @brief Parse a simple command
 *
 * @param token The token to parse
 * @return Node* The node of the AST
 */
Node *parse_simple_command(Token *token);

#endif