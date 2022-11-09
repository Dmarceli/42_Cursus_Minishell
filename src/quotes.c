#include "../incs/minishell.h"

int	checkquotation(char *input)
{
	int	i;
	int	onequote;
	int	doublequote;

	i = 0;
	onequote = 0;
	doublequote = 0;
	while (input[i])
	{
		if (input[i] == '\"' && doublequote == 0 && onequote == 0)
			doublequote = 1;
		else if (input[i] == '\"' && doublequote == 1 && onequote == 0)
			doublequote = 0;
		else if (input[i] == '\'' && onequote == 0 && doublequote == 0)
			onequote = 1;
		else if (input[i] == '\'' && onequote == 1 && doublequote == 0)
			onequote = 0;
		i++;
	}
	if (onequote && !doublequote)
		return (1);
	if (!onequote && doublequote)
		return (2);
	else
		return (0);
}

char *removequotes(char *cmd)
{
	int j = 0;
	int i = -1;
    if (ft_strchr(cmd, '\"'))
    {
        while (++i < (int)ft_strlen(cmd))
        {
            if (cmd[i] == '\\')
            {
                cmd[j++] = cmd[i++];
                cmd[j++] = cmd[i];
                if (cmd[i] == '\0')
                    break;
            }
            else if (cmd[i] != '"')
                cmd[j++] = cmd[i];
        }
        cmd[j] = '\0';
        return (cmd);
    }
    else if (ft_strchr(cmd, '\''))
    {
        while (++i < (int)ft_strlen(cmd))
        {
            if (cmd[i] == '\\')
            {
                cmd[j++] = cmd[i++];
                cmd[j++] = cmd[i];
                if (cmd[i] == '\0')
                    break;
            }
            else if (cmd[i] != '\'')
                cmd[j++] = cmd[i];
        }
        cmd[j] = '\0';
        return (cmd);
    }
    else 
        return (0);
}