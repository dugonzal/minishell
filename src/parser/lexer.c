/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/14 08:31:01 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lexer_errors(char **str)
{
	if (check_quotes(str, "\'\""))
		return (err_msg(RED"minishell: syntax error quotes \" <-> \'"RESET));
	if (check_pipe(str, '|'))
		return (err_msg(RED"minishe.ll: syntax error pipe '|'"RESET));
	else if (handle_input_redireccion(str, '<')
		|| handle_input_redireccion(str, '>'))
		return (err_msg(RED"minishell: syntax error parse near \
		'>' or '<'"RESET));
	else if (check_semicolon(str))
		return (err_msg(RED"minishell: syntax error parse near ';;' "RESET));
	return (0);
}

int	lexer(t_data *data)
{
	if (!data->line[0])
		return (1);
	data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
	if (!ft_strlen(data->line))
		return (1);
	data->bufer = split_token(data->line, " \t\v\f\r", ">|<;", "\"\'");
	if (!data->bufer[0])
	{
		g_status = 1;
		add_history (data->line);
		free (data->line);
		return (1);
	}
	expanser(data);
	if (lexer_errors(data->bufer))
	{
		add_history (data->line);
		free (data->line);
		free_array(data->bufer);
		g_status = 1;
		return (1);
	}
	add_history (data->line);
	free (data->line);
	return (0);
}
