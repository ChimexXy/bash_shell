#include "../../inc/minishell.h"

int check_redirection(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		if((str[i] == '<') || (str[i] == '>') 
			|| (str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>'))
			return (1);
		i++;
	}
	return (0);
}

int check_envirment(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void check_red_env(t_bash *bash)
{
	int	i;

	i = 0;
	while(bash->s_cmd[i])
	{
		if(check_envirment(bash->s_cmd[i]->command) == 1)
			bash->s_cmd[i]->check_env = 1;
		if(check_redirection(bash->s_cmd[i]->command) == 1)
			bash->s_cmd[i]->check_red = 1;
		i++;
	}
}

int	check_cmd4_1(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while(str[i])
	{
		x = 0;
		if (str[i] == '>')
		{
			while(str[i] && str[i] == '>')
			{
				i++;
				x++;
			}
			if (x > 2)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	check_cmd4_2(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while(str[i])
	{
		x = 0;
		if (str[i] == '<')
		{
			while (str[i] && str[i] == '<')
			{
				i++;
				x++;
			}
			if (x > 2)
				return (0);
		}
		else
			i++;
	}
	return (1);
}
