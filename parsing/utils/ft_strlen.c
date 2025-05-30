#include "../../inc/minishell.h"

int	ft_strlen(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while(cmd[i])
		i++;
	return (i);
}