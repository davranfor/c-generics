#include <stdio.h>
#include <stdlib.h>
#include "ast_node.h"
#include "ast_data.h"
#include "ast_heap.h"

///////////////////////////////////////////////////////////////////////////////

static void die(void)
{
    fprintf(stderr, "Max number of nested elements = %d\n", MAX_HEAP);
    exit(EXIT_FAILURE);
}

///////////////////////////////////////////////////////////////////////////////

ast_data *push(ast_node **root, ast_data *data)
{
    ast_node *node;

    node = malloc(sizeof *node);
    if (node == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->right = *root;
    node->left = NULL;
    node->data = data;
    *root = node;
    return data;
}

ast_data *pop(ast_node **root)
{
    ast_data *data = NULL;
    ast_node *node;

    if ((node = *root) != NULL)
    {
        *root = node->right;
        data = node->data;
        free(node);
    }
    return data;
}

ast_data *move(ast_node **target, ast_node **source)
{
    ast_node *node;

    if ((node = *source) == NULL)
    {
        return NULL;
    }
    *source = node->right;
    node->right = *target;
    *target = node;
    return node->data;
}

ast_data *peek(const ast_node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    return root->data;
}

void clear(ast_node *root)
{
    if (root != NULL)
    {
        clear(root->left);
        clear(root->right);
        free(root);
    }
}

///////////////////////////////////////////////////////////////////////////////

struct branches
{
    const ast_node *node[MAX_HEAP];
    int iterators;
    int count;
};

static struct branches branches;

void push_branch(const ast_node *node)
{
    if (branches.count == MAX_HEAP)
    {
        die();
    }
    branches.node[branches.count++] = node;
    if (is_iterator(node->data))
    {
        branches.iterators++;
    }
}

const ast_node *pop_branch(void)
{
    if (branches.count == 0)
    {
        return NULL;
    }

    const ast_node *node = branches.node[--branches.count];

    if (is_iterator(node->data))
    {
        branches.iterators--;
    }
    return node;
}

const ast_node *peek_branch(void)
{
    if (branches.count == 0)
    {
        return NULL;
    }
    return branches.node[branches.count - 1];
}

int current_branch(void)
{
    if (branches.count == 0)
    {
        return 0;
    }
    return branches.node[branches.count - 1]->data->statement->key;
}

int iterating(void)
{
    return branches.iterators != 0;
}

///////////////////////////////////////////////////////////////////////////////

struct calls
{
    ast_node *node[MAX_HEAP];
    int count;
};

static struct calls calls;

void push_call(ast_node *node)
{
    if (calls.count == MAX_HEAP)
    {
        die();
    }
    calls.node[calls.count++] = node;
}

ast_node *pop_call(void)
{
    if (calls.count == 0)
    {
        return NULL;
    }
    return calls.node[--calls.count];
}

ast_node *peek_call(void)
{
    if (calls.count == 0)
    {
        return NULL;
    }
    return calls.node[calls.count - 1];
}

///////////////////////////////////////////////////////////////////////////////

struct jumps
{
    const ast_node *node[MAX_HEAP];
    int count;
};

static struct jumps jumps;

void push_jump(const ast_node *node)
{
    if (jumps.count == MAX_HEAP)
    {
        die();
    }
    jumps.node[jumps.count++] = node;
}

const ast_node *pop_jump(void)
{
    if (jumps.count == 0)
    {
        return NULL;
    }
    return jumps.node[--jumps.count];
}

const ast_node *peek_jump(void)
{
    if (jumps.count == 0)
    {
        return NULL;
    }
    return jumps.node[jumps.count - 1];
}

