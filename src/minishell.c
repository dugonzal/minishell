/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/06 10:34:33 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// quotes = "\"\'"
// whitespaces = " \t\v\f\r\n"
// lexer -> parser -> expanser -> builtins -> bin_execute -> waitpid
int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac > 1)
	  err("minishell: too many arguments");
	(void)av;
	ft_bzero (&data, sizeof(t_data));
	data.status = 1;
	data.path = ft_split(getenv("PATH"), ':');
	signals();
	while (data.status)
	{
		data.line = readline (prompt());
		if (!data.line)
			break;
		data.env = env;
		if (lexer(&data))
			continue ;
		parser(&data);
		handler_execute(&data);
		//print (data.bufer);
		free_array (data.bufer);
	}
	free (data.path);
	exit(EXIT_SUCCESS);
}
