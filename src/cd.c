#include "../incs/minishell.h"

int		ms_pwd(void)
{
	char	cwd[1040];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (1);
	}
	else
		return (0);
}

void	cdwithpath(char *cmd)
{
	char **dir;

	dir = ft_split(cmd, ' ');
	if (chdir(dir[1]))
		printf("ERROR!\n");
	free (dir);	
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