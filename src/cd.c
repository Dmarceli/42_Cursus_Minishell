#include "../incs/minishell.h"

int		ms_pwd(char *cmd)
{
	cmd = ft_strtrim(cmd, " ");
	char	cwd[1040];
	if (!ft_strncmp(cmd, "pwd\0", 4))
	{
		free(cmd);
		if (getcwd(cwd, sizeof(cwd)))
		{
			printf("%s\n", cwd);
			return (0);
		}
		else
			return (1);
	}
	else
		printf("pwd: too many arguments\n");
	free(cmd);
	return(1);
}

int	cdwithpath(char *cmd)
{
	char **dir;

	dir = ft_split(cmd, ' ');
	if (chdir(dir[1]))
	{
		printf("cd: no such file or directory: %s\n", dir[1]);
		return(0);
	}
	freearray(dir);
	return (1);
}

int	ms_cd(char *cmd, t_data *data)
{
	char	cwd[1040];
	int 	pos;
	if (!ft_strncmp(cmd, "cd ~\0", 5)
		|| !ft_strncmp(cmd, "cd \0", 4)
		|| !ft_strncmp(cmd, "cd\0", 3))
	{
		chdir(getenv("HOME"));
		getcwd(cwd, sizeof(cwd));
		pos = look_for_var_in_array("PWD", data);
		free(data->env[pos]);
		data->env[pos] = ft_strjoin("PWD=", cwd);
		return(0);
	}
	else if (!ft_strncmp(cmd, "cd ", 3))
	{
		if(!cdwithpath(cmd))
			return(1);
		getcwd(cwd, sizeof(cwd));
		pos = look_for_var_in_array("PWD", data);
		free(data->env[pos]);
		data->env[pos] = ft_strjoin("PWD=", cwd);
		return (0);
	}
	else
		return(1);
}