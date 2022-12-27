/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:21:32 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/12/26 18:01:35 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <pwd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CYAN "\e[1;36m"
# define BLANK "\e[0m"
# define CLEAR_SCREEN "\033[?1049h\033[H"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

extern int	g_exitvalue;

typedef struct s_data
{
	char	**env;
	char	**cmdtable;
	char	**exec;
	int		envlen;
	int		lastexec;
	int		fd[2];
	pid_t	*pid;
	int		pipe_fd;
}	t_data;

// Main and init
int		main(int ac, char **av, char **env);
void	initenv(char **envs, t_data *data);
int		msparser_checks(char *input);
int		exit_status(int status);
char	**ms_init_pipes(char *input, t_data *data);

// Parser
void	minishellparser(char *input, t_data *data);
int		check_emptyprompt(char *cmd);
char	*removequotes(char *cmd);
char	**msparser_inits(char *input, t_data *data);

// Handle dollar var
char	*handle_dollar(char *cmd, t_data *data);
char	*join_strs(char **str_chunks, char *sep, int limiter);
char	*no_var_to_expand(char **j, int i, char *value);
char	*justthevar(char *str);
char	*norm_findvar(char *cmd);
int		look_for_var_in_array(char *cmd, t_data *data);

// Commands
int		ms_pwd(char *cmd);
int		ms_cd(char *cmd, t_data *data);
int		cdwithpath(char *cmd);
int		is_builtin(char *value, t_data *data);
int		execbuiltin(char *value, t_data *data);
int		checkechoflag(char *cmd);
int		echo(char *cmd);
int		env(t_data *data);
char	*getpath(t_data *data);
void	handle_cmd(t_data *data);
int		ms_export(char *cmd, t_data *data);
int		ms_unset(char *cmd, t_data *data);
int		executecmd(char *cmd, t_data *data);
int		clear_screen(void);
int		ft_exit(char *cmd, t_data *data);

// Redirections && pipes
void	handle_pipes(char **cmds, t_data *data);
void	multiple_child(char **cmds, t_data *data, int counter);
char	*return_trim(char *bush);
int		special_quote(char *input, int index);
int		check_special(char *input, char chr);
int		give_inputfd(char *input);
char	*get_infilename(char *cmd);
int		output(char *cmd);
int		count_redir(char *cmd, char red);
char	*get_outfilename(char *cmd, int counter);
int		special_index(char *str);
int		trimmer(char *bush, int counter);
void	child_process(char **cmds, t_data *data, int counter);
int		input_red(char *cmd);
char	*get_next_line(int fd);
void	redirect(char *cmd, t_data *data);
int		heredoc(char *eof);
int		is_parent(char *cmd, t_data *data);
void	child_input(char **cmds, t_data *data, int counter);
void	wait_pid(t_data *data, int counter);
int		output_util(char *cmd, int outs, int counter);
char	*trim_util(char *old);
int		input_util(char *cmd, int ins, int counter);
int		has_redirect(char *cmd);

// Utils
int		check_inquotes(char *cmd);
int		checkquotation(char *input);
char	*ft_free(char *buffer, char *buf);
char	*ft_next(char *buffer);
char	*ft_line(char *buffer);
char	*read_file(int fd, char *ret);
char	*remove_escape(char *cmd);
void	freearray(char **arr);
int		big_len(char **str);
int		ft_index(char *str, char ch);
int		is_numeric(char *value);
int		norm_inquotes(char *tmp, int len);
// Signals
void	ignore_signal(void);
void	ignore_signal_i(void);
void	sighandler(int sig);
void	sighandler_i(int sig);
void	ctrl_c_handler(int j);

#endif