/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:57:02 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/19 12:25:17 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	red_parse(t_bash *bash)
{
	int	i;
	int	j;

	i = 0;
	while (i < bash->num_cmd)
	{
		j = ft_strlen(bash->s_cmd[i]->command) - 1;
		while (j >= 0 && (bash->s_cmd[i]->command[j] == ' '
				|| bash->s_cmd[i]->command[j] == '\t'))
			j--;
		if (j >= 0 && (bash->s_cmd[i]->command[j] == '>'
				|| bash->s_cmd[i]->command[j] == '<'))
			return (0);
		i++;
	}
	return (1);
}

int check_sin_dou(char *cmd)
{
	int		i;
	char	c;
	int		state;

	i = 0;
	state = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
		{
			c = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != c)
				i++;
			if (!cmd[i])
				return (0);
		}
		i++;
	}
	return (1);
}

// int	check_sin_dou(char *cmd)
// {
// 	int		i;
// 	int		num;
// 	char	c;

// 	i = 0;
// 	num = 0;
// 	if (!cmd)
// 		return (0);
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == 34 || cmd[i] == 39)
// 		{
// 			num++;
// 			c = cmd[i];
// 			i++;
// 			while (cmd[i] != c && cmd[i])
// 				i++;
// 			if (cmd[i] == c)
// 				num++;
// 			if (num % 2 != 0)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

