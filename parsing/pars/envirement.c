/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:19 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/12 15:48:44 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_env(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
	{
		printf("minishell: export: `=': not a valid identifier\n");
		return (0);
	}
	while (str[i])
	{
		if(str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

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
	bash->s_cmd[ind]->s_env[num_env] = NULL;
	return (1);
}

void	parse_env_file_key(t_bash *bash, int i)
{
	int j;
	int m;
	int x;
	int len;

	j = 0;
	x = 0;
	while (bash->s_cmd[i]->arguments[j])
	{
		m = 0;
		if (check_env(bash->s_cmd[i]->arguments[j]))
		{
			len = ft_strlen(bash->s_cmd[i]->arguments[j]);
			while(bash->s_cmd[i]->arguments[j][m] != '=')
				m++;
			bash->s_cmd[i]->s_env[x]->key = ft_substr(bash->s_cmd[i]->arguments[j], 0, m);
			m++;
			if (m >= len)
				bash->s_cmd[i]->s_env[x]->value = ft_strdup("");
			else
				bash->s_cmd[i]->s_env[x]->value = ft_substr(bash->s_cmd[i]->arguments[j], m, len - m);
			x++;
		}
		j++;
	}
}

int parse_envirement(t_bash *bash)
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
				parse_env_file_key(bash, i);
			}
		}
		i++;
	}
	return (1);
}
