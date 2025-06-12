/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:24 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/12 08:28:24 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_cmd_array(t_bash *bash)
{
	int i;

	i = 0;
	if (!bash->s_cmd)
		return;
	while (i < bash->num_cmd)
	{
		if (bash->s_cmd[i])
		{
			free(bash->s_cmd[i]->command);
			free(bash->s_cmd[i]->s_red);
			free(bash->s_cmd[i]->s_env);
			free(bash->s_cmd[i]->arguments);
			free(bash->s_cmd[i]);
			bash->s_cmd[i] = NULL;
		}
		i++;
	}
	free(bash->s_cmd);
	bash->s_cmd = NULL;
}

int	select_struct1(t_bash *bash)
{
	char *cmd;

	cmd = readline("minishell$ ");
	if(!cmd || !check_cmd(cmd))
	{
		// bash->num_cmd = 0;
		free(cmd);
		return (0);
	}
	bash->num_cmd = count_pipes(cmd);
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
        // free_cmd_array(bash);
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

void	select_struct(t_bash *bash)
{
	if (!select_struct1(bash))
		return ;
	if (!select_struct2(bash))
		return ;
	if (!select_struct3(bash))
		return ;
	check_red_env(bash);
	parse_redirection(bash);
	parse_envirement(bash);
}

int	main(int ac, char **av, char **env)
{
	t_bash	*bash;

	bash = malloc(sizeof(t_bash));
	if (!bash)
		return 0;
	(void)ac;
	(void)av;
	while(1)
	{
		select_struct(bash);
		// int i = 0;
		// while(bash->s_cmd[i])
		// {
		// 	int j = 0;
		// 	if (bash->s_cmd[i]->s_red)
		// 	{
		// 		while(bash->s_cmd[i]->s_red[j])
		// 		{
		// 			printf("env num %d file: %s\n", j, bash->s_cmd[i]->s_red[j]->file);
		// 			printf("env num %d type: %u\n", j, bash->s_cmd[i]->s_red[j]->type);
		// 			j++;
		// 		}
		// 	}
		// 	i++;
		// }
	}
}
