/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msparser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:02:27 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/11 18:16:20 by dhomem-d         ###   ########.fr       */
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
		cmds = ft_split(input, '|');
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
		waitpid(pid, NULL, 0);
	}
	else if (!is_builtin(cmds[0], data))
		return ;
	freearray(cmds);
}

int	msparser_checks(char *input)
{
	if (ft_strlen(input))
		add_history(input);
	if (!check_emptyprompt(input))
	{
		free(input);
		return (1);
	}
	if (checkquotation(input))
	{
		printf("Quotation incomplete\n");
		free(input);
		return (1);
	}
	return (0);
}

char	**msparser_inits(char *input, t_data *data)
{
	char	**cmds;

	cmds = ft_calloc(sizeof(char **) * ft_strlen(input), sizeof(cmds));
	cmds[0] = NULL;
	if (ft_strchr(input, '$'))
		cmds[0] = handle_dollar(input, data);
	else
		cmds[0] = ft_strdup(input);
	free(input);
	return (cmds);
}
