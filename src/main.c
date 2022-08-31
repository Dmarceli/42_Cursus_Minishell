#include "../incs/minishell.h"

void   (*SIGINT_handler)(int);

void ignore_signal(void)
{
    SIGINT_handler = signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char **av, char **env)
{	
	char* input;
	(void)ac;
	(void)av;
	(void)*env;
	while (1)
	{
		ignore_signal();
		input = readline(CYAN"minishell$ "BLANK);
		minishellparser(input);
	}
}
