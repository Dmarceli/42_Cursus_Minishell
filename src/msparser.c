#include "../incs/minishell.h"

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
