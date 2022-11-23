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
# define EXIT_STATUS(status)	(((status) & 0xff00) >> 8)

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif


typedef struct s_data
{
	char	**env;
	char 	**cmdtable;
	char 	**exec;
	int		envlen;
	int		lastexec;
	int		fd[2];
	pid_t	*pid;
	int		pipe_fd;
}	t_data;


int		main(int ac, char **av, char **env);
void	minishellparser(char* input, t_data *data);
void	initenv(char **envs, t_data *data);
int		checkquotation(char *input);
void	ignore_signal(void);
void 	ignore_signal_i(void);
void	sighandler(int sig);
void	sighandler_i(int sig);
void	ctrl_c_handler(int j);
int		ms_pwd(char *cmd);
int		ms_cd(char *cmd, t_data *data);
int		cdwithpath(char *cmd);
int		is_builtin(char *value, t_data *data);
int		execbuiltin(char *value, t_data *data);
int		checkechoflag(char *cmd);
int 	check_emptyprompt(char *cmd);
int 	echo(char *cmd);
int 	env(t_data *data);
char 	*getpath(t_data *data);
void	handle_cmd(t_data *data);
int 	ms_export(char *cmd , t_data *data);
int		ms_unset(char *cmd, t_data *data);
int		executecmd(char *cmd, t_data *data);
int 	look_for_var_in_array(char *cmd, t_data *data);
int 	clear_screen(void);
char 	*handle_dollar(char *cmd, t_data *data);
void 	freearray(char **arr);
int		big_len(char **str);
void	free_split(char **sp);
void	handle_pipes(char **cmds, t_data *data);
void	 multiple_child(char **cmds, t_data *data, int counter);
int		overwrite(char *cmd);
int		ft_index(char *str, char ch);
char	*return_trim(char *bush);
int		special_quote(char *input, int index);
char 	*removequotes(char *cmd);
int		check_special(char *input, char chr);
int		give_inputfd(char *input);
int 	is_numeric(char *value);
int		ft_exit(char *cmd, t_data *data);
char	*get_infilename(char *cmd);
int		output(char *cmd);
int		count_output(char *cmd);
char	*get_outfilename(char *cmd, int counter);
int		special_index(char *str);
int		trimmer(char *bush, int counter);
void 	child_process(char **cmds, t_data *data, int counter);
int		input_red(char *cmd);
char	*ft_free(char *buffer, char *buf);
char	*ft_next(char *buffer);
char	*ft_line(char *buffer);
char	*read_file(int fd, char *ret);
char	*get_next_line(int fd);
void	redirect(char *cmd, t_data *data);
int	heredoc(char *eof);

char	*ft_free(char *buffer, char *buf);
char	*ft_next(char *buffer);
char	*ft_line(char *buffer);
char	*read_file(int fd, char *res);
char	*get_next_line(int fd);

#endif