#include "../incs/minishell.h"

int checkechoflag(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])	
	{
		if (cmd[i] == '-' && cmd[i + 1] == 'n' )
			return(1);
		i++;
	}
	return(0);
}

int echo(char *cmd)
{
	int		is_n;
	char	**value;
	int		i;

	is_n = checkechoflag(cmd);
	value = ft_split(cmd,' ');
	free(cmd);
	if (is_n)
	{
		i = 1;
		while(value[++i])
			printf("%s ", value[i]);
		printf(" ");
		i = -1;
		while(value[++i])
			free(value[i]);
		free(value);
		return(1);
	}
	else if (!is_n)
	{
		i = 0;
		while (value[++i])
			printf("%s ", value[i]);
		printf("\n");
		i = -1;
		while(value[++i])
			free(value[i]);
		free(value);
		return(1);
	}
	else
	{
		i = -1;
		while(value[++i])
			free(value[i]);
		free(value);
		return(0);
	}
}