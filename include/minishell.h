/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:41:17 by ciclo             #+#    #+#             */
/*   Updated: 2023/03/14 21:17:01 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BLUE "\033[0;34m"

#ifndef libft_h

#define libft "../libft/include/libft.h"
#include libft
#endif

# include <dirent.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_mini
{
	char **bufer;
	char **env;
	char *line_buffer;
} t_mini;
void	handler(int sig, siginfo_t *info, void *context);

#endif
