#include "minishell.h"

static char	*get_env_val(t_dlist *node);

char	**ms_lst_to_env(t_main *main)
{
	int	size;
	int	i;
	char	**rtn;
	t_dlist	*current;

	size = ms_dlist_size(main->env_list);
	rtn = malloc (sizeof (char *) * (size + 1));
	i = 0;
	current = main->env_list;
	while (i < size)
	{
		rtn[i] = get_env_val(current);
		current = current->next;
		i ++;
	}
	rtn[i] = NULL;
	return (rtn);
}

static char	*get_env_val(t_dlist *node)
{
	t_env	*env;
	char	*rtn;
	char	*set;

	env = (t_env *)node->content;
	set = malloc(2);
	set[0] = '=';
	set[1] = '\0';
	rtn = ms_strjoin_free(env->key, set);
	rtn = ms_strjoin_free(rtn, env->value);
	return (rtn);
}