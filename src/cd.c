#include "../incs/minishell.h"

int		ms_pwd(char *cmd)
{
	cmd = ft_strtrim(cmd, " ");
	char	cwd[1040];
	if (!ft_strncmp(cmd, "pwd\0", 4))
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			printf("%s\n", cwd);
			return (1);
		}
		else
			return (0);
	}
	else
		printf("pwd: too many arguments\n");
	return(0);
}

void freearray(char **arr)
{
	int i;
	i = -1;
	while(arr[++i])
	{
		if(arr[i])
			free(arr[i]);
	}
	free(arr);
}

void	cdwithpath(char *cmd)
{
	char **dir;

	dir = ft_split(cmd, ' ');
	if (chdir(dir[1]))
		printf("ERROR!\n");
	freearray(dir);
	return ;
}


int	ms_cd(char *cmd)
{
	if (!ft_strncmp(cmd, "cd ~\0", 5)
		|| !ft_strncmp(cmd, "cd \0", 4)
		|| !ft_strncmp(cmd, "cd\0", 3))
		{
			chdir(getenv("HOME"));
			return(1);
		}
	else if (!ft_strncmp(cmd, "cd ", 3))
	{
		cdwithpath(cmd);
		return (1);
	}
	else
		return(0);
}