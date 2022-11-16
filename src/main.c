#include "../incs/minishell.h"

int main(int ac, char **av, char **envs)
{	
	t_data data;
	int 	exitvalue;
	char* input;
	(void)ac;
	(void)av;

	initenv(envs, &data);
	while (1)
	{
		ignore_signal();
		input = readline(CYAN"minishell> "BLANK);
		if(!input)
			exit(data.lastexec);
		minishellparser(input, &data);
		exitvalue = data.lastexec;
	}
	return(exitvalue);
}
