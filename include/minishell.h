/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:41:17 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/24 12:01:59 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BLUE "\033[0;34m"
# include "../libft/include/libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	pid_t			*pid; // si lo declaro como un puntero tengo que hacer malloc
	char *line;
	struct s_cmd	*next;

} t_cmd;

typedef struct s_data
{
	// deberia tener una variable que de las cadenas de la linea de comando
	char			**bufer;
	char			**cmd;
	char			**path;
	char			**env;
	int				*delimits;
	char			*line;
	int				*fd;
	int				flag;
	int				status;
	pid_t 			pid;
	//struct s_cmd	s_cmd;
} t_data;

void	handler(int sig, siginfo_t *info, void *context);
void	signals(void);
void	parser(t_data *data);
char	*prompt(void);
void	bin_execute(t_data *mini);
// builtins
int		verify_quotes(t_data *data);
void	ft_exit(t_data  *data);
void	print(char **str);

#endif
