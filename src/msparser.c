#include "../incs/minishell.h"

int	checkquotation(char *input)
{
	int	i;
	int	onequote;
	int	doublequote;

	i = 0;
	onequote = 0;
	doublequote = 0;
	while (input[i])
	{
		if (input[i] == '\"' && doublequote == 0 && onequote == 0)
			doublequote = 1;
		else if (input[i] == '\"' && doublequote == 1 && onequote == 0)
			doublequote = 0;
		else if (input[i] == '\'' && onequote == 0 && doublequote == 0)
			onequote = 1;
		else if (input[i] == '\'' && onequote == 1 && doublequote == 0)
			onequote = 0;
		i++;
	}
	if (onequote && !doublequote)
		return (1);
	if (!onequote && doublequote)
		return (2);
	else
		return (0);
}

void minishellparser(char* input, t_data *data)
{
	char **cmds;

	if (ft_strlen(input))
		add_history(input);
	else
		return(rl_replace_line("", 0));
	if (checkquotation(input))
		return((void)printf("Quotation incomplete\n"));
	cmds = malloc(sizeof(cmds));
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);
	else if (ft_strchr(input, '|'))
	{
		free(cmds);
		cmds = ft_split(input, '|');
		handle_pipes(cmds, data);
		free_split(cmds);
		return ;
	}
	else
		cmds[0] = ft_strdup(input);
	if (!is_builtin(cmds[0], data))
	{
		free(cmds[0]);
		free(cmds);
		return ;
	}
	free(cmds);
}