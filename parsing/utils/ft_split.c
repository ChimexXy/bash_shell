#include "../../inc/minishell.h"

void	free_double_pointer(char **arr, int p)
{
	while (p >= 0)
	{
		free(arr[p]);
		p--;
	}
	free(arr);
}

int	ft_count_word(char *cmd, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == sep)
			i++;
		if (cmd[i] != sep && cmd[i])
			j++;
		while (cmd[i] && cmd[i] != sep)
			i++;
	}
	return (j);
}

char	**alloc_words(char **ret, char *cmd, char sep, int word)
{
	int		i;
	int		x;
	int		start;

	i = 0;
	x = 0;
	start = 0;
	while(x < word)
	{
		while(cmd[i] == sep && cmd[i])
			i++;
		start = i;
		while(cmd[i] != sep && cmd[i])
			i++;
		ret[x] = ft_substr(cmd, start, i - start);
		if (!ret[x])
		{
			free_double_pointer(ret, x);
			return (NULL);
		}
		x++;
	}
	ret[x] = NULL;
	return (ret);
}

char **ft_split(char *cmd, char sep)
{
	int		word;
	char	**ret;

	if(!cmd)
		return (NULL);
	word = ft_count_word(cmd, sep) + 1;
	ret = malloc(sizeof(char *) * word);
	if (!ret)
		return (NULL);
	ret = alloc_words(ret, cmd, sep, word);
	if (!ret)
		return (NULL);
	return (ret);
}
