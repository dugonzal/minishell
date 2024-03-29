/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:58:16 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/14 15:20:19 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		kill(0, 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		g_status = 0;
		kill(0, SIGQUIT);
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
}
