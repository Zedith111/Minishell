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

void	print_command_node(void *content)
{
	t_command *cmd;
	int size;
	int i;

	cmd = (t_command *)content;
	size = 0;
	while (cmd->full_command[size] != NULL)
		size ++;
	printf("Length of double array is %d\n", size);
	i = 0;
	while (i < size)
	{
		printf("%s\n", cmd->full_command[i]);
		i ++;
	}
	printf("infile is %d\n", cmd->infile);
	printf("outfile id %d\n", cmd->outfile);
}

void print_command_list(t_dlist **list)
{
	t_dlist *current;

	current = *list;
	while (current->next != NULL)
	{
		print_command_node(current->content);
		current =current->next;
	}
	
}

