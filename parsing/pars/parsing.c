/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:24 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/20 10:47:49 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	select_struct1(t_bash *bash, char *cmd)
{
	bash->num_cmd = count_pipes(cmd);
	if (!check_cmd(cmd))
	{
		free(cmd);
		return (0);
	}
	bash->s_cmd = malloc(sizeof(t_cmd *) * (bash->num_cmd + 1));
	if (!bash->s_cmd)
	{
		free(cmd);
		return (0);
	}
	bash->commands = ft_strdup(cmd);
	bash->args_pip = ft_split(cmd, '|');
	free(cmd);
	return (1);
}

int	select_struct2(t_bash *bash)
{
	int	i;

	i = 0;
	while(i < bash->num_cmd)
	{
		bash->s_cmd[i] = malloc(sizeof(t_cmd));
		if (!bash->s_cmd[i])
			return (0);
		bash->s_cmd[i]->command = ft_strdup(bash->args_pip[i]);
		bash->s_cmd[i]->s_red = NULL;
		bash->s_cmd[i]->s_env = NULL;
		bash->s_cmd[i]->check_env = 0;
		bash->s_cmd[i]->check_red = 0;
		i++;
	}
	bash->s_cmd[i] = NULL;
	if (!red_parse(bash))
	{
        printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	select_struct3(t_bash *bash)
{
	int	i;
	int	j;

	i = 0;
	while (bash->s_cmd[i])
	{
		if (!bash->s_cmd[i]->command)
			return (0);
		bash->s_cmd[i]->arguments = tokenizer(bash->s_cmd[i]->command);
		i++;
	}
	return (1);
}

void	select_struct(t_bash *bash, char *cmd, char **env)
{
	bash->commands = NULL;
	bash->args_pip = NULL;
	bash->s_cmd = NULL;
	bash->num_cmd = 0;
	if (!select_struct1(bash, cmd))
		return ;
	if (!select_struct2(bash))
		return ;
	if (!select_struct3(bash))
		return ;
	check_red_env(bash);
	parse_redirection(bash);
	parse_envirement(bash);
	expand_func(bash, env);
}



int	main(int ac, char **av, char **env)
{
	t_bash	*bash;
	char	*cmd;

	bash = malloc(sizeof(t_bash));
	if (!bash)
		return 0;
	(void)ac;
	(void)av;
	while(1)
	{
		cmd = readline("minishell$ ");
		add_history(cmd);
		if(!cmd)
		{
			printf("exit\n");
			free(cmd);
			break;
		}
		select_struct(bash, cmd, env);

		if(bash->s_cmd)
		{
			int i = 0;
			while(bash->s_cmd[i])
			{
				int j = 0;
				if (bash->s_cmd[i]->s_env)
				{
					while(bash->s_cmd[i]->s_env[j])
					{
						printf("env num %d file: %s\n", j, bash->s_cmd[i]->s_env[j]->key);
						printf("env num %d type: %s\n", j, bash->s_cmd[i]->s_env[j]->value);
						j++;
					}
				}
				i++;
			}
		}
		// free_bash(bash);
	}
}
