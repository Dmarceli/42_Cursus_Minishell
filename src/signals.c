#include "../incs/minishell.h"

void	sighandler_i(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
void ignore_signal_i(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler_i);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		write(1,"olasoueu\n",10);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void ignore_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
}