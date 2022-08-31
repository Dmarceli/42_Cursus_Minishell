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


void minishellparser(char* input)
{
	if (input)
		add_history(input);
	if (!checkquotation(input))
		printf("%s%s\n", CYAN"minishell$ "BLANK, "Quotation incomplete");	
	if (!strcmp(input, "exit"))
		exit(0);
}