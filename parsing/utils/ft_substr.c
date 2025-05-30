#include "../../inc/minishell.h"

char	*ft_substr(char *str, int start, int len)
{
	int	i;
	char *ret;

	i = 0;
	ret = malloc(len + 1);
	if(!ret || !str)
		return (NULL);
	while(i < len)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}