#include "../../inc/minishell.h"

int	check_rd(char c)
{
	if (c == '>' || c == '<' 
		|| c == ' ' || c == '\t')
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

int	alloc_s_red(t_bash *bash, int n_red, int i)
{
	int	x;

	x = 0;
	bash->s_cmd[i]->s_red = malloc(sizeof(t_red) * (n_red + 1));
	if (!bash->s_cmd[i]->s_red)
		return (0);
	while(x < n_red)
	{
		bash->s_cmd[i]->s_red[x] = malloc(sizeof(t_red));
		if (!bash->s_cmd[i]->s_red[x])
			return (0);
		bash->s_cmd[i]->s_red[x]->type = 0;
		bash->s_cmd[i]->s_red[x]->file = NULL;
		x++;
	}
	bash->s_cmd[i]->s_red[x] = NULL;
	return (1);
}

void	redirection_types(t_bash *bash, int i)
{
	int	j;
	int x;

	j = 0;
	x = 0;
	while(bash->s_cmd[i]->command[j])
	{
		if (bash->s_cmd[i]->command[j] == '>')
		{
			if (bash->s_cmd[i]->command[j + 1] == '>')
			{
				bash->s_cmd[i]->s_red[x]->type = APPEND;
				j += 2;
			}
			else
			{
				bash->s_cmd[i]->s_red[x]->type = OUTPUT;
				j++;
			}
			x++;
		}
		j++;
	}
}

void	redirection_types1(t_bash *bash, int i)
{
	int	j;
	int x;

	j = 0;
	x = 0;
	while(bash->s_cmd[i]->command[j])
	{
		if (bash->s_cmd[i]->command[j] == '<')
		{
			if (bash->s_cmd[i]->command[j + 1] == '<')
			{
				bash->s_cmd[i]->s_red[x]->type = HERE_DOC;
				j += 2;
			}
			else
			{
				bash->s_cmd[i]->s_red[x]->type = INPUT;
				j++;
			}
			x++;
		}
		j++;
	}
}

void	redirection_files(t_bash *bash, int i)
{
	int	j;
	int	x;
	int	start;

	j = 0;
	x = 0;
	while (bash->s_cmd[i]->command[j])
	{
		if (bash->s_cmd[i]->command[j] == '>' 
			|| bash->s_cmd[i]->command[j] == '<')
		{
			if (check_rd(bash->s_cmd[i]->command[j]))
				j += 2;
			else
				j++;
			

		}

	}
}

int	parse_redirection(t_bash *bash)
{
	int	i;
	int	n_red;

	i = 0;
	while (bash->s_cmd[i])
	{
		if (bash->s_cmd[i]->check_red == 1)
		{
			n_red = count_redirection(bash->s_cmd[i]->command);
			if (!alloc_s_red(bash, n_red, i))
				return (0);
			redirection_types(bash, i);
			redirection_types1(bash, i);
			redirection_files(bash, i);
		}
		i++;
	}
	return (1);
}
