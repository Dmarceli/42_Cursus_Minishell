#include "../incs/minishell.h"

int clear_screen(void)
{
	printf(CLEAR_SCREEN);
	return (1);
}

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