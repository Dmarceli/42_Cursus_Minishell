#include "../incs/minishell.h"

void   (*SIGINT_handler)(int);

void ignore_signal(void)
{
    SIGINT_handler = signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

char** initenv(char **envs)
{
	char **envcopy;
	size_t i;
	i = 0;

	while (envs[i])
		i++;
	envcopy = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envs[i])
	{
		envcopy[i] = ft_strdup(envs[i]);
		i++;
	}
	envcopy[i] = 0;
	return (envcopy);
}

int main(int ac, char **av, char **envs)
{	
	char* input;
	t_data data;

	(void)ac;
	(void)av;

	data.env = initenv(envs);
	printf("%s\n" , data.env[4]);

	while (1)
	{
		ignore_signal();
		input = readline(CYAN"minishell$ "BLANK);
		minishellparser(input);
	}
}
