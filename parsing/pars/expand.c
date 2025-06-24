/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:35 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/24 23:28:37 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_quotes(char *cmd)
{
	int	e;

	e = ft_strlen(cmd);
	if (cmd[0] == 39  && cmd[e] == 39)
		return (0);
	return (1);
}

int	check_expand(t_bash *bash, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j] != '$' && cmd[j])
		j++;
	if (cmd[j] == '$')
		j++;
	// j == ?
		// return exit_status
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
	int		c;
	char	**sp;

	c = check_expand(bash, bash->s_cmd[i]->arguments[j]);
	sp = NULL;
	if (bash->s_cmd[i]->arguments[j][0] != '$')
		sp = ft_split(bash->s_cmd[i]->arguments[j], '$');
	if (c != -1)
	{
		free(bash->s_cmd[i]->arguments[j]);
		if (sp && sp[0])
			bash->s_cmd[i]->arguments[j] = ft_strjoin(sp[0], bash->path_env[c]->value);
		else
			bash->s_cmd[i]->arguments[j] = ft_strdup(bash->path_env[c]->value);
	}
	else
	{
		free(bash->s_cmd[i]->arguments[j]);
		bash->s_cmd[i]->arguments[j] = ft_strdup("");
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
			if (check_dollar(bash->s_cmd[i]->arguments[j])
				&& check_quotes(bash->s_cmd[i]->arguments[j]))
				select_new(bash, i, j);
			j++;
		}
		i++;
	}
}
