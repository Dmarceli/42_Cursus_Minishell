#include "../incs/minishell.h"


void	initenv(char **envs, t_data *data)
{
	size_t i;
	i = 0;

	while (envs[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envs[++i])
		data->env[i] = ft_strdup(envs[i]);
	data->env[i] = 0;
}

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
}
