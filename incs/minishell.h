#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <pwd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <histedit.h>
# define CYAN "\e[1;36m"
# define BLANK "\e[0m"


int main(int ac, char **av, char **env);
void minishellparser(char* input);
int	checkquotation(char *input);

#endif