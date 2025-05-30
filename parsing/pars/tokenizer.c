#include "../../inc/minishell.h"

void	free_double_pointer_tk(char **arr, int p)
{
	if (!arr)
		return ;
	while (p >= 0)
	{
		free(arr[p]);
		p--;
	}
	free(arr);
}


int	check_tokinzer(char c)
{
	if (c == '>' || c == '<' 
		|| c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	count_word_tk(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (check_tokinzer(cmd[i]) && cmd[i])
			i++;
		if (!check_tokinzer(cmd[i]) && cmd[i])
			j++;
		while (!check_tokinzer(cmd[i]) && cmd[i])
			i++;
	}
	return (j);
}

char	**alloc_words_tk(char **ret, char *cmd, int word)
{
	int		i;
	int		x;
	int		start;

	i = 0;
	x = 0;
	start = 0;
	while(x < word)
	{
		while(check_tokinzer(cmd[i]) == 1 && cmd[i])
			i++;
		start = i;
		while(check_tokinzer(cmd[i]) == 0 && cmd[i])
			i++;
		ret[x] = ft_substr(cmd, start, i - start);
		if (!ret[x])
		{
			free_double_pointer_tk(ret, x);
			return (NULL);
		}
		x++;
	}
	ret[x] = NULL;
	return (ret);
}

char **tokenizer(char *cmd)
{
	int		word;
	char	**ret;

	if(!cmd)
		return (NULL);
	word = count_word_tk(cmd);
	ret = malloc(sizeof(char *) * (word + 1));
	if (!ret)
		return (NULL);
	ret = alloc_words_tk(ret, cmd, word);
	if (!ret)
		return (NULL);
	return (ret);
}