#include "../../inc/minishell.h"

void free_cmd_array(t_bash *bash)
{
	int i;

	i = 0;
	if (!bash->s_cmd)
		return;
	while (i < bash->num_cmd)
	{
		if (bash->s_cmd[i])
		{
			free(bash->s_cmd[i]->command);
			free(bash->s_cmd[i]->s_red);
			free(bash->s_cmd[i]->s_env);
			free(bash->s_cmd[i]->arguments);
			free(bash->s_cmd[i]);
		}
		i++;
	}
	free(bash->s_cmd);
	bash->s_cmd = NULL;
}