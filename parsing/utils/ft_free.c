/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:41 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/13 14:51:37 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redirections(t_bash *bash, int ind)
{
	int i;

	i = 0;
	if (!bash->s_cmd[ind]->s_red)
		return ;
	while (bash->s_cmd[ind]->s_red[i])
	{
		free(bash->s_cmd[ind]->s_red[i]->file);
		free(bash->s_cmd[ind]->s_red[i]);
		i++;
	}
	free(bash->s_cmd[ind]->s_red);
}

void	free_envs(t_bash *bash, int ind)
{
	int i;

	i = 0;
	if (!bash->s_cmd[ind]->s_env)
		return ;
	while (bash->s_cmd[ind]->s_env[i])
	{
		free(bash->s_cmd[ind]->s_env[i]->key);
		free(bash->s_cmd[ind]->s_env[i]->value);
		free(bash->s_cmd[ind]->s_env[i]);
		i++;
	}
	free(bash->s_cmd[ind]->s_env);
}

void	free_cmds(t_bash *bash)
{
	int i;

	i = 0;
	if (!bash->s_cmd)
		return ;
	while (bash->s_cmd[i])
	{
		free(bash->s_cmd[i]->command);
		if (bash->s_cmd[i]->arguments)
		{
			int j = 0;
			while (bash->s_cmd[i]->arguments[j])
			{
				free(bash->s_cmd[i]->arguments[j]);
				j++;
			}
			free(bash->s_cmd[i]->arguments);
		}
		free_redirections(bash, i);
		free_envs(bash, i);
		free(bash->s_cmd[i]);
		i++;
	}
	free(bash->s_cmd);
}

void	free_bash(t_bash *bash)
{
	if (!bash)
		return ;
	if (bash->commands)
		free(bash->commands);
	if (bash->args_pip)
	{
		// pause();
		int i = 0;
		while (bash->args_pip[i])
		{
			free(bash->args_pip[i]);
			i++;
		}
		free(bash->args_pip);
	}
	free_cmds(bash);
}


