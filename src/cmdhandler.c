#include "../incs/minishell.h"

int		ms_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, 256))
	{
		ft_putendl_fd(cwd, 1);
		return (1);
	}
	else
		return (0);
}

int	ms_cd(char *cmd)
{
	if (!ft_strncmp(cmd, "cd ~\0", 5)
		|| !ft_strncmp(cmd, "cd\0", 3)
		|| !ft_strncmp(cmd, "cd \0", 4))
		{
			chdir(getenv("HOME"));
			return(1);
		}
	else
		return(0);
}

int	is_builtin(char *value)
{
	if (!value)
		return (0);
	else if (!(ft_strncmp(value, "echo", 4)))
		return (1);
	else if (!(ft_strncmp(value, "cd", 2)))
		return (ms_cd(value));
	else if (!(ft_strncmp(value, "pwd", 3)))
		return(ms_pwd());
	else if (!(ft_strncmp(value, "export", 6)))
		return (1);
	else if (!(ft_strncmp(value, "unset",5)))
		return (1);
	else if (!(ft_strncmp(value, "env", 3)))
		return (1);
	else if (!(ft_strncmp(value, "exit", 4)))
		exit(1);
	else	
		return (0);
}