#include "../incs/minishell.h"


int main(int ac, char **av, char **envs)
{	
	char* input;
	t_data data;
	(void)ac;
	(void)av;

	initenv(envs, &data);
	while (1)
	{
		ignore_signal();
		input = readline(CYAN"minishell$ "BLANK);
		if(!input)
			exit(0);
		minishellparser(input, &data);
	}
	free(data.env);
}
