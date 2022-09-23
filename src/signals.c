#include "../incs/minishell.h"

static void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
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