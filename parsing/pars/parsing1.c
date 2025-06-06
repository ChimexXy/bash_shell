#include "../../inc/minishell.h"

int	check_cmd(char *cmd)
{
	if (!check_cmd1(cmd))
		return (0);
	else if (!check_cmd2(cmd))
		return (0);
	else if (!check_cmd3(cmd))
		return (0);
	else if (!check_cmd4_1(cmd) || !check_cmd4_2(cmd))
	{
		printf("invalid token :( '>>>'\n");
		return (0);
	}
	return (1);
}

int	check_cmd1(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '|')
	{
		if (cmd[i + 1] == '|')
			printf("bash: syntax error near unexpected token `||'\n");
		else
			printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	while (cmd[i])
	{
		if (cmd[i] == '|' && cmd[i + 1] == '|')
		{
			printf("invalid token :( \n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_cmd2(char *check_cmd1)
{
	int	i;

	i = ft_strlen(check_cmd1) - 1;
	while (i >= 0 && check_cmd1[i] == ' ')
		i--;
	if (check_cmd1[i] == '|')
	{
		printf("invalid command >\n");
		return (0);
	}
	return (1);
}

int	check_cmd3(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			if (!cmd[i])
				return (0);
			while(cmd[i] == ' ')
				i++;
			if(cmd[i] == '|' || cmd[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		else
			i++;
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
