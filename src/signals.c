#include "../incs/minishell.h"

void   (*SIGINT_handler)(int);


void	ctrl_c_handler(int j)
{
	if (j == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void ignore_signal(void)
{
    SIGINT_handler = signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, &ctrl_c_handler);
}