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

// void handlespecialchars(char *com)
// {	
// 	t_data *data;
// 	int i;
// 	i = 0;

// 	while (com[i])
// 	{
// 		// if (com[i] == '&')
// 		// 	function to handle &
// 		// if (com[i] == '<')
// 		// 	function to handle <
// 		// if (com[i] == '>')
// 		// 	function to handle >
// 		i++;
// 	}

// }

void minishellparser(char* input)
{
	char **cmds = NULL;
	int i = -1;

	if (!strcmp(input, "exit"))
		exit(0);
	if (input)
		add_history(input);
	if (!checkquotation(input))
		printf("%s%s\n", CYAN"minishell$ "BLANK, "Quotation incomplete");
	cmds = malloc(sizeof *cmds);
	if (ft_strchr(input, '|'))
	 	cmds = ft_split(input,'|');
	else
		cmds[0] = strdup(input);
	while (cmds[++i])
		cmds[i] = ft_strtrim(cmds[i], " ");
		//handlespecialchars(cmds[i]);
	i = -1;
	while (cmds[++i])
		printf("|%s|\n",cmds[i]);
}