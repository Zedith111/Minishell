#include "minishell.h"


void	print_token_node(t_dlist *node)
{
	t_token *token;

	token = (t_token *)node->content;
	if (token->type == TOKEN_QUOTE)
		printf("Quote\n");
	else if (token->type == TOKEN_WORD)
		printf("Word\n");
	else if (token->type == TOKEN_AIN)
		printf("Append Infile\n");
	else if (token->type == TOKEN_AOUT)
		printf("Append Outfile\n");
	else if (token->type == TOKEN_IN)
		printf("Infile\n");
	else if (token->type == TOKEN_OUT)
		printf("Outfile\n");
	else if (token->type == TOKEN_PIPE)
		printf("Pipe\n");
	printf ("%s\n", token->value);
}


void	print_token_list(t_dlist **list)
{
	t_dlist *current;

	current = *list;
	while (current != NULL)
	{
		print_token_node(current);
		current = current->next;
	}
}

void	print_env_node(void *content)
{
	t_env *env;

	env = (t_env *)content;
	printf("key : %s\n", env->key);
	printf("value : %s\n", env->value);
}

void	print_env_list(t_dlist **lst)
{
	t_dlist *current;

	current = *lst;
	while (current != NULL)
	{
		print_env_node(current->content);
		current = current->next;
	}
}

