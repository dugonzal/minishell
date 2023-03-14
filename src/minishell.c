/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/03/14 21:14:40 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el
//uso de rutas relativas o absolutas)
// Ejecutar el comando con sus argumentos
// Esperar a que el comando termine su ejecución
// Mostrar el prompt de nuevo

void	init_v(t_mini *mini, char **env)
{
	mini = malloc(sizeof(t_mini));
	if (!mini)
		return ;
	ft_memset (mini, 0, sizeof(t_mini));
	while (*env)
		printf ("[%s]", *env++);

}

int	main(int ac, char **av, char **env)
{
	t_mini *mini;
	struct sigaction	sa;
	(void)av;
	(void)ac;
	status = 1;
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	init_v(mini, env);
	while (status)
	{
		sigaction(SIGINT, &sa, NULL);
		line = readline (BLUE"minishell$GUEST$> "RESET);
		add_history (line); // add to history
		if (ft_strncmp(line, "exit", 4) == 0)
			status = 0;
		mini->bufer = ft_split (line, 32); // 32 -> ' '
		//execv(mini->bufer[0], &env[0]);
		if (mini->bufer[0] && ft_strncmp(mini->bufer[0], "echo", 4) == 0)
			printf ("%s\n", mini->bufer[1]);
		//system (line);
		//printf ("[%s]\n", line);
		free (line);
		free (mini->bufer);
	}
	return (0);
}
