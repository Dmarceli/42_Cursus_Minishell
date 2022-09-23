#include "../incs/minishell.h"


char** initenv(char **envs)
{
	char **envcopy;
	size_t i;
	i = 0;

	while (envs[i])
		i++;
	envcopy = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envs[++i])
		envcopy[i] = ft_strdup(envs[i]);
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
	while (1)
	{
		ignore_signal();
		input = readline(CYAN"minishell$ "BLANK);
		if(!input)
			exit(0);
		minishellparser(input);
	}
}
