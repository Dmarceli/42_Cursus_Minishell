#include "../incs/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int check_emptyprompt(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_space(cmd[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_inquotes(char *cmd)
{
	int	counter;
	int	len;
	char	*tmp;

	counter = 1;
	len = ft_strlen(cmd) - 1;
	tmp = ft_strtrim(cmd, " ");
	if (tmp[0] == '\"')
	{
		while (tmp[counter])
		{
			if (tmp[counter] == '\"' && counter == len)
				break;
			else if (tmp[counter] == '\"' && tmp[counter - 1] != '\\')
			{
				free(tmp);
				return (0);
			}
			counter++;
		}
	}
	else
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

void minishellparser(char* input, t_data *data)
{
	char **cmds;
	int	pid;

	if (ft_strlen(input))
		add_history(input);
	if (!check_emptyprompt(input))
	{
		free(input);
		return ;
	}
	if (check_inquotes(input))
	{
		printf("%s: command not found\n", input);
		data->lastexec = 127;
		return	;
	}
	if (checkquotation(input))
		return((void)printf("Quotation incomplete\n"));
	if (check_special(input, '|'))
	{
		cmds = ft_split(input, '|');
		handle_pipes(cmds, data);
		freearray(cmds);
		return ;
	}
	cmds = ft_calloc(sizeof(char **) * ft_strlen(input), sizeof(cmds));
	cmds[0] = NULL;
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);
	else
		cmds[0] = ft_strdup(input); //leak, idk why
	free(input);
	if (check_special(cmds[0], '>') || check_special(cmds[0], '<'))
	{
		pid = fork();
		if (pid == 0)
			redirect(cmds[0], data);
		waitpid(pid, NULL, 0);
	}
	else if (!is_builtin(cmds[0], data))
	{
		freearray(cmds);
		return ;
	}
	freearray(cmds);
}
