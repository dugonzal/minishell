/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:58:16 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/12 19:27:28 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	sig_handler(int signum)
{
	/*bash-3.2$ hola
	bash-3.2$
	bash-3.2$ echo $?
	1-> es el valor que le doy a g_exit_status.*/
	if (signum == SIGINT)
	{
		if(rl_on_new_line() == -1)// si la nueva linea está creada, no la crees
			exit(-1); //salgo de la función
		g_status = 1; // el valor de salida en este caso es 1
		ft_printf("\n");
		rl_replace_line("", 0); // creame una nueva linea vacia
		rl_redisplay();// muestramela.
	}
	if (signum == SIGQUIT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		rl_redisplay();//muestrame la linea, no la crees porque sigquit no la necesita.
	}

}


void	sig_handler_child_input(int signum)
{
	if (signum == SIGQUIT)
	{
		printf ("Quit: 3\n");
	}
	/*bash-3.2$ cat
	^C
	bash-3.2$ echo $?
	130-> esto va al else if
*/
	else if (signum == SIGINT)
	{
		g_status = 130;
		ft_printf("\n");
	}
}

void	handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	sig_handler(sig);
	sig_handler_child_input(sig);

}

void signals(void)
{
	
	struct sigaction sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
