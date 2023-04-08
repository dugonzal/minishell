/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:41:17 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/08 21:47:34 by ciclo            ###   ########.fr       */
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
	char *line;
} t_cmd;

typedef struct s_data
{
	char			**path;
	char			**bufer;
	char			**env;
	char			*line;
	pid_t			pid;
	int				status;
	struct s_cmd	*cmd;
} t_data;

void	handler(int sig, siginfo_t *info, void *context);
void	signals(void);

#endif
