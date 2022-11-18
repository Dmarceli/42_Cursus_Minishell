#include "../incs/minishell.h"

int check_emptyprompt(char *cmd)
{
	int i;
	i = -1;
	while (cmd[++i])
	{
		if(cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		if (!cmd[i])
			return(0);
	}
	return(1);
	
}

void minishellparser(char* input, t_data *data)
{
	char **cmds;
	int	pid;

	if (ft_strlen(input))
		add_history(input);
	else
		return(rl_replace_line("", 0));
	if (!check_emptyprompt(input))
		return;
	if (checkquotation(input))
		return((void)printf("Quotation incomplete\n"));
	if (check_special(input, '|'))
	{
		cmds = ft_split(input, '|');
		handle_pipes(cmds, data);
		free_split(cmds);
		return ;
	}
	cmds = malloc(sizeof(cmds));
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);
	else if (ft_strchr(input, '\'') || ft_strchr(input, '\"'))
		cmds[0] = removequotes(input);
	else
		cmds[0] = ft_strdup(input);
	if (check_special(cmds[0], '>') || check_special(cmds[0], '<'))
	{
		pid = fork();
		if (pid == 0)
			redirect(cmds[0], data);
		waitpid(pid, NULL, 0);
	}
	else if (!is_builtin(cmds[0], data))
	{
		if (!cmds[0])
			free(cmds[0]);
		free(cmds);
		return ;
	}
	free(cmds);
}