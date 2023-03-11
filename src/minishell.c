/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/03/11 00:04:02 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char *line;
	int status;

	(void)av;
	(void)ac;
	(void)env;
	status = 1;
	while (status)
	{
		line = readline (BLUE"minishell$> "RESET);
		read_history (line);
		if (ft_strncmp(line, "exit", 4) == 0)
			status = 0;
		printf ("[%s]\n", line);
	}
	return (0);
}
