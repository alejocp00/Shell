#ifndef NODE_H
#define NODE_H

/*Defining the type of node (if it's a command or a var)*/
typedef enum node_type
{
    NODE_COMMAND,
    NODE_VAR,
} Node_Type;

/*defining the type of var*/
typedef enum val_type
{
    V_SINT = 1,
    V_UINT,
    V_SLLONG,
    V_ULLONG,
    V_FLOAT,
    V_DOUBLE,
    V_CHAR,
    V_STR,
} Val_Type;

union value
{
    long sint;
    unsigned long uint;
    long long sllong;
    unsigned long long ullong;
    double sfloat;
    long double ldouble;
    char chr;
    char *str;
};

typedef struct node
{
    Node_Type type;
    Val_Type val_type;
    union value value;
    int c_children;
    struct node *first_child;
    struct node *next_sibling;
    struct node *previous_sibling;
} Node;

Node *new_node(Node_Type type);
void add_child(Node *parent, Node *child);
void free_node(Node *node);
void set_node_val(Node *node, char *val);

#endif