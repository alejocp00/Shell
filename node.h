#ifndef NODE_H
#define NODE_H


    /*Defining the type of node (if it's a command or a var)*/
    enum node_type
    {
        N_COMAND,
        N_VAR,
    };

    /*defining the type of var*/
    enum val_type
    {
        V_SINT = 1,
        V_UINT,
        V_SLLONG,
        V_ULLONG,
        V_FLOAT,
        V_DOUBLE,
        V_CHAR,
        V_STR,
    };

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
    
    struct node
    {
        enum node_type type;
        enum val_type  val_type;
        union value value;
        int c_children;
        struct node *first_child;
        struct node *next_sibling;
        struct node *previous_sibling;
    };


    /*Defining an alias for struct node*/
    typedef struct node Node;

    Node *new_node(enum node_type type);
    void add_child(Node *parent, Node *child);
    void free_node(Node *node);
    void set_node_val(Node *node, char *val);


#endif