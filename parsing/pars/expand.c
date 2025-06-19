/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:11 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/19 15:53:04 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int count_ex(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

void	free_double_pointer_ex(char **arr)
{
	int	p;

	p = 0;
	while (arr[p])
	{
		free(arr[p]);
		p++;
	}
	free(arr);
}

void print_dou(char **env)
{
	int j = 0;
	while(env[j])
	{
		printf("%s\n", env[j]);
		j++;
	}

}

void	expand_func(t_bash *bash, char **env)
{
	int		i;
	char	**splited;

	i = 0;
	bash->path_env = malloc(sizeof(t_env *) * (count_ex(env) + 1));
	while(env[i])
	{
		bash->path_env[i] = malloc(sizeof(t_env));
    	if (!bash->path_env[i])
        	return ;
		splited = ft_split(env[i], '=');
		if (!splited)
		{
			free_double_pointer_ex(splited);
			return ;
		}
		bash->path_env[i]->key = ft_strdup(splited[0]); 
		if(!splited[1])
			bash->path_env[i]->value = ft_strdup("");
		else
			bash->path_env[i]->value = ft_strdup(splited[1]);
		free_double_pointer_ex(splited);
		i++;
	}
}

