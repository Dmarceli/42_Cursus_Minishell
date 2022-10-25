#include "../incs/minishell.h"


int main(int ac, char **av, char **envs)
{	
	t_data data;
	char* input;
	(void)ac;
	(void)av;

	initenv(envs, &data);
	while (1)
	{
		ignore_signal();
		input = readline(CYAN"minishell> "BLANK);
		if(!input)
			exit(0);
		minishellparser(input, &data);
	}
	free(data.env);
}
