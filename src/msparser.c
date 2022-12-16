/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msparser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:02:27 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/16 16:25:41 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	minishellparser(char *input, t_data *data)
{
	char	**cmds;
	int		pid;

	if (msparser_checks(input))
		return ;
	if (check_special(input, '|'))
	{
		cmds = ms_init_pipes(input, data);
		handle_pipes(cmds, data);
		freearray(cmds);
		return ;
	}
	cmds = msparser_inits(input, data);
	if (check_special(cmds[0], '>') || check_special(cmds[0], '<'))
	{
		pid = fork();
		if (pid == 0)
			redirect(cmds[0], data);
		waitpid(pid, &g_exitvalue, 0);
		g_exitvalue = exit_status(g_exitvalue);
	}
	else
		is_builtin(cmds[0], data);
	freearray(cmds);
}

int	msparser_checks(char *input)
{
	if (!check_emptyprompt(input))
	{
		free(input);
		return (1);
	}
	if (ft_strlen(input))
		add_history(input);
	if (checkquotation(input))
	{
		printf("Quotation incomplete\n");
		free(input);
		return (1);
	}
	return (0);
}

char	**msparser_inits(char *input_u, t_data *data)
{
	char	**cmds;
	char	*input;

	input = ft_strtrim(input_u, " ");
	cmds = ft_calloc(sizeof(char **) * ft_strlen(input), sizeof(cmds));
	cmds[0] = NULL;
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);
	else
		cmds[0] = ft_strdup(input);
	free(input);
	free(input_u);
	return (cmds);
}

char	**ms_init_pipes(char *input_u, t_data *data)
{
	char	**cmds;
	char	*new_input;
	char	*input;

	input = ft_strtrim(input_u, " ");
	if (ft_strchr(input, '$'))
	{
		new_input = handle_dollar(input, data);
		cmds = ft_split(new_input, '|');
		free(new_input);
	}
	else
		cmds = ft_split(input, '|');
	free(input);
	free(input_u);
	return (cmds);
}
