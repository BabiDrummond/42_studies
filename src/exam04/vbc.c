#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	}   type;
	int val;
	struct node *l;
	struct node *r;
}   node;

node	*parse_expr(char **s);

node	*new_node(node n)
{
	node *ret = calloc(1, sizeof(n));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void	destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of file\n");
}

int	accept(char **s, char c)
{
	if (**s && **s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

node	*parse_factor(char **s)
{
	node	*n;

	if (isdigit(**s))
	{
		n = new_node((node){VAL, **s - 48, NULL, NULL});
		accept(s, **s);
		return (n);
	}
	else if (expect(s, '('))
	{
		n = parse_expr(s);
		if (n == NULL)
			return (NULL);
		if (expect(s, ')'))
			return (n);
		else
			return (destroy_tree(n), NULL);
	}
	else
		return (NULL);
}

node	*parse_term(char **s)
{
	node	*left;
	node    *right;

	left = parse_factor(s);
	if (left == NULL)
		return (NULL);
	while (**s)
	{
		if (**s == '*')
		{
			accept(s, '*');
			right = parse_factor(s);
			if (right == NULL)
				return (destroy_tree(left), NULL);
			left = new_node((node){MULTI, '*', left, right});
		}
		else
			return (left);
	}
	return (left);
}

node	*parse_expr(char **s)
{
	node	*left;
	node	*right;

	if (**s)
	{
		left = parse_term(s);
		if (left == NULL)
			return (NULL);
		while (**s)
		{
			if (**s == '+')
			{
				accept(s, '+');
				right = parse_term(s);
				if (right == NULL)
					return (destroy_tree(left), NULL);
				left = new_node((node){ADD, '+', left, right});
			}
			else
				return (left);
		}
	}
	else
		return (NULL);
	return (left);
}

int	eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return (tree->val);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	char *args = argv[1];
	node *tree = parse_expr(&args);
	if (!tree)
		return (0);
	if (*args != '\0')
		return (unexpected(*args), destroy_tree(tree), 1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}
