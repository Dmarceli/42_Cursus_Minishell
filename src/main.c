#include "../incs/minishell.h"

int main(int ac, char **av, char **envs)
{	
	t_data 	data;
	int 	exitvalue;
	char* 	input;


	(void)ac;
	(void)av;
	initenv(envs, &data);
	ignore_signal();
	while (1)
	{
		input = readline(CYAN"minishell> "BLANK);
		if(!input && write(0, "\n", 1))	
			ft_exit("", &data);
		ignore_signal_i();
		minishellparser(input, &data);
		ignore_signal();
		exitvalue = data.lastexec;
	}
	return(exitvalue);
}
