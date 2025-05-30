#include "../../inc/minishell.h"

int count_env(char *str)
{
	int i;
	int env;

	i = 0;
	env = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] != '=')
			env++;
		i++;
	}
	return (env);
}

int alloc_env(t_bash *bash, int num_env, int ind)
{
	int i;

	i = 0;
	bash->s_cmd[ind]->s_env = malloc(sizeof(t_env *) * (num_env + 1));
	if (!bash->s_cmd[ind]->s_env)
		return (0);
	while (i < num_env)
	{
		bash->s_cmd[ind]->s_env[i] = malloc(sizeof(t_env));
		if (!bash->s_cmd[ind]->s_env[i])
			return (0);
		bash->s_cmd[ind]->s_env[i]->key = NULL;
		bash->s_cmd[ind]->s_env[i]->value = NULL;
		i++;
	}
	return (1);
}

int parse_env(t_bash *bash)
{
	int i;
	int num_env;

	i = 0;
	while (bash->s_cmd[i])
	{
		if (bash->s_cmd[i]->check_env == 1)
		{
			num_env = count_env(bash->s_cmd[i]->command);
			if (num_env > 0)
			{
				if (alloc_env(bash, num_env, i) == 0)
					return (0);
				parse_env_entries(bash, i);
			}
		}
		i++;
	}
	return (1);
}
