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

	i = -1;
	while (cmd[++i])
	{
		if (is_space(cmd[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void minishellparser(char* input, t_data *data)
{
	char **cmds;
	int	pid;

	if (ft_strlen(input))
		add_history(input);
	if (!check_emptyprompt(input))
		return;
	if (checkquotation(input))
		return((void)printf("Quotation incomplete\n"));
	if (check_special(input, '|'))
	{
		cmds = ft_split(input, '|');
		handle_pipes(cmds, data);
		freearray(cmds);
		return ;
	}
	cmds = malloc(sizeof(cmds));
	cmds[0] = NULL;
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);
	else
		cmds[0] = ft_strdup(input);
	free(input);
	if (check_special(cmds[0], '>') || check_special(cmds[0], '<'))
	{
		pid = fork();
		if (pid == 0)
			redirect(cmds[0], data);
		waitpid(pid, NULL, 0);
		free(cmds[0]);
	}
	else if (!is_builtin(cmds[0], data))
	{
		free(cmds);
		return ;
	}
	free(cmds);
}
