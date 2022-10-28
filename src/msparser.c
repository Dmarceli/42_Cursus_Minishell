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
	if (onequote + doublequote == 0)
		return (1);
	else
		return (0);
}

void minishellparser(char* input, t_data *data)
{
	char **cmds;
	//int 	i;

	if (input)
		add_history(input);
	if (!ft_strlen(input))
		return(rl_replace_line("", 0));
	if (!checkquotation(input))
		return((void)printf("%s\n", "Quotation incomplete"));
	cmds = malloc(sizeof(cmds));
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);	//function to handle operators
	else
		cmds[0] = ft_strdup(input);
	if (!is_builtin(cmds[0], data))
	{
		free (cmds[0]);
		free(cmds);
		return ;
	}
	free (cmds[0]);
	free(cmds);
}