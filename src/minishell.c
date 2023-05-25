/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/25 18:10:16 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// quotes = "\"\'"
// whitespaces = " \t\v\f\r\n"
// lexer -> parser -> expanser -> builtins -> bin_execute -> waitpid
//
int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*user;

	if (ac > 1 && arr_size(av) > 1)
	  err("minishell: too many arguments");
	ft_bzero (&data, sizeof(t_data));
	data.status = 1;
	data.path = ft_split(getenv("PATH"), ':', 0);
	user = prompt();		
	data.env = env;
	while (42)
	{
		signals();
		data.line = readline (user);
		if (!data.line)
			break ;
		if (lexer(&data))
			continue ;
		parser(&data);
	}
	free (user);
	free (data.path);
	exit(EXIT_SUCCESS);
}
