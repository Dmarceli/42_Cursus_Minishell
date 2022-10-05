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
#include <readline/readline.h>
# include <readline/history.h>
# include <histedit.h>

# define CYAN "\e[1;36m"
# define BLANK "\e[0m"
# define CLEAR_SCREEN "\033[?1049h\033[H"

// # ifndef PATH_MAX
// #  define PATH_MAX 2048 
// # endif

typedef struct s_data
{
	char	**env;
	char 	**cmdtable;
	char 	**exec;

}	t_data;


int		main(int ac, char **av, char **env);
void	minishellparser(char* input, t_data *data);
void	initenv(char **envs, t_data *data);
int		checkquotation(char *input);
void	ignore_signal(void);
void	ctrl_c_handler(int j);
int		ms_pwd(void);
int		ms_cd(char *cmd);
void	cdwithpath(char *cmd);
int		is_builtin(char *value, t_data *data);
int		execbuiltin(char *value, t_data *data);
int		checkechoflag(char *cmd);
int 	echo(char *cmd);
int 	env(t_data *data);
char 	*getpath(t_data *data);
void	handle_cmd(t_data *data);
int		executecmd(char *cmd, t_data *data);

#endif