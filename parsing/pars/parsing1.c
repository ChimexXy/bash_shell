#include "../../inc/minishell.h"

int	check_cmd(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			printf("bash: syntax error near unexpected token `||'\n");
		else
			printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
		{
			printf("invalid token :( \n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_cmd1(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
		i--;
	if (str[i] == '|')
	{
		printf("invalid command >\n");
		return (0);
	}
	return (1);
}

int	count_pipes(char *cmd)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	if (cmd[i] && cmd[i] != ' ')
		pipes++;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

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
