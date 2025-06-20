/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:35 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/20 12:13:23 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_expand(t_bash *bash, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd[i] == '$')
		j++;
	while (bash->path_env[i])
	{
		if (ft_strcmp(bash->path_env[i]->key, cmd + j) == 1)
			return (i);
		i++;
	}
	return (-1);
}

void	select_new(t_bash *bash, int i, int j)
{
	int	c;

	c = check_expand(bash, bash->s_cmd[i]->arguments[j]);
	if (c != -1)
	{
		free(bash->s_cmd[i]->arguments[j]);
		bash->s_cmd[i]->arguments[j] = ft_strdup(bash->path_env[c]->value);
	}
}

void	expand_func(t_bash *bash)
{
	int	i;
	int	j;

	i = 0;
	while (bash->s_cmd[i])
	{
		j = 0;
		while (bash->s_cmd[i]->arguments[j])
		{
			if (check_dollar(bash->s_cmd[i]->arguments[j]))
				select_new(bash, i, j);
			j++;
		}
		i++;
	}
}
