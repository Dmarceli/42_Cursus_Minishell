#include "../incs/minishell.h"

void minishellparser(char* input, t_data *data)
{
	char **cmds;

	if (ft_strlen(input))
		add_history(input);
	else
		return(rl_replace_line("", 0));
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
	else
		cmds[0] = ft_strdup(input);
	if (!is_builtin(cmds[0], data))
	{
		free(cmds[0]);
		free(cmds);
		return ;
	}
	free(cmds);
	// if (ft_strchr(input, '$'))
	// 	cmds[0] = handle_dollar(input, data);
	// else if (ft_strchr(input, '|'))
	// {
	// 	free(cmds);
	// 	cmds = ft_split(input, '|');
	// 	handle_pipes(cmds, data);
	// 	free_split(cmds);
	// 	return ;
	// }
	// else if (ft_strchr(input, '\"') || ft_strchr(input, '\''))
	// {
	// 	printf("ola\n");
	// 	cmds[0] = removequotes(input);

	// }
	// else
	// 	cmds[0] = ft_strdup(input);
	// if (!is_builtin(cmds[0], data))
	// {
	// 	free(cmds[0]);
	// 	free(cmds);
	// 	return ;
	// }
	// free(cmds);
}