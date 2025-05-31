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
