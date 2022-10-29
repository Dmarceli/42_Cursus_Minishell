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


typedef struct s_data
{
	char	**env;
	char 	**cmdtable;
	char 	**exec;
	int		envlen;
}	t_data;


int		main(int ac, char **av, char **env);
void	minishellparser(char* input, t_data *data);
void	initenv(char **envs, t_data *data);
int		checkquotation(char *input);
void	ignore_signal(void);
void	ctrl_c_handler(int j);
int		ms_pwd(char *cmd);
int		ms_cd(char *cmd);
void	cdwithpath(char *cmd);
int		is_builtin(char *value, t_data *data);
int		execbuiltin(char *value, t_data *data);
int		checkechoflag(char *cmd);
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

#endif