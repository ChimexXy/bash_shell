/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:46 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/12 08:28:46 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strdup(char *cmd)
{
	int	i;
	char *ret;

	i = 0;
	if (!cmd)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(cmd) + 1);
	if (!ret)
		return (NULL);
	while(cmd[i])
	{
		ret[i] = cmd[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
