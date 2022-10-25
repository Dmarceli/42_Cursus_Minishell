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
	int i;


	if (input)
		add_history(input);
	if (!checkquotation(input))
	{
		printf("%s\n", "Quotation incomplete");
		return ;
	}
	cmds = malloc(sizeof(cmds));
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);	//function to handle operators
	//if (ft_strchr(input, '|'))
	 	//cmds = ft_split(input,'|');
	else
		cmds[0] = ft_strdup(input);
	i = -1;
	while (++i < (int)sizeof(**cmds))
	{
		cmds[i] = ft_strtrim(cmds[i], " ");
		if (!is_builtin(cmds[i], data))
			return ;
	}
	free (cmds);
}