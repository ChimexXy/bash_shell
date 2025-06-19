/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:29:59 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/19 12:30:00 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_rd(char c)
{
	if (!c)
		return (0);
	if (c == '>' || c == '<' 
		|| c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	check_rd1(char c)
{
	if (!c)
		return (0);
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_sp(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	count_redirection(char *cmd)
{
	int	i;
	int	red;

	i = 0;
	red = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
				i += 2;
			else
				i++;
			red++;
		}
		else
			i++;
	}
	return (red);
}