/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:58:16 by ciclo             #+#    #+#             */
/*   Updated: 2023/03/13 15:36:02 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
		kill (0, 0);
		write (1, "\n", 1);
		rl_replace_line("", 0); // handle signal ctrl + c
		rl_on_new_line(); // handle signal ctrl + c
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		printf ("recibido ctrl + d");
		//exit(0); // handle signal ctrl + d

	}
	// handle signal ctrl + c and ctrl + d

}
