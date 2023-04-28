#ifndef NODE_H
#define NODE_H

/*Defining the type of node (if it's a command or a var)*/
typedef enum node_type
{
    NODE_COMMAND,
    NODE_OPERATOR,
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

typedef enum precedence
{
    // &
    BG,
    // ;
    UNION,
    // && ||
    LOGIC,
    // |
    PIPE,
    // > >>
    REDIR,
    // <
    REDIR_IN
} Precedence;

/**
 * @brief The value of the node
 *
 */
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

union val_info
{
    Val_Type val_type;
    Precedence precedence;
};

/**
 * @brief The node of the AST
 *
 */
typedef struct node
{
    /**
     * @brief The type of the node
     *
     */
    Node_Type type;

    /**
     * @brief The value type of the node
     *
     */
    union val_info val_info;

    /**
     * @brief The value of the node
     *
     */
    union value value;

    /**
     * @brief The number of children
     *
     */
    int c_children;

    /**
     * @brief The first child
     *
     */
    struct node *first_child;

    /**
     * @brief The next sibling
     *
     */
    struct node *next_sibling;

    /**
     * @brief The previous sibling
     *
     */
    struct node *previous_sibling;
} Node;

/**
 * @brief Create a new node object
 *
 * @param type The type of the node
 * @return Node* The node created
 */
Node *new_node(Node_Type type);

/**
 * @brief Add a child to a node
 *
 * @param parent The parent node
 * @param child The child node
 */
void add_child(Node *parent, Node *child);

/**
 * @brief Free a node
 *
 * @param node The node to free
 */
void free_node(Node *node);

/**
 * @brief Set the node val object
 *
 * @param node The node to set the value
 * @param val The value to set
 */
void set_node_val(Node *node, char *val);

/**
 * @brief Set the node operator precedence.
 *
 * @param node A Node struct that represent the operator.
 */
void set_operator_precedence(Node *node);

#endif