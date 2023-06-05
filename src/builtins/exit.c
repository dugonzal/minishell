/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:04:21 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/05 19:14:07 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
//Exit g_status:
//  125  if the env command itself fails
//  126  if COMMAND is found but cannot be invoked
//  127  if COMMAND cannot be found
//  -    the exit g_status of COMMAND otherwise

int	ft_numeric_error(t_cmd	*cmd)
{
	//g_status = 255;
	printf("exit: %s: numeric argument required\n", \
			cmd->cmd[1]);
	return (0);
}
/*bash-3.2$ exit 12 23 (mas de un argumento)
exit
bash: exit: too many cmd (printf sin salto de linea)
bash-3.2$ echo $?
1
bash-3.2$
*/
int	ft_exit(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		//g_status = 1;
		ft_printf("exit: too many arguments\n");
		return (1); // es el valor que devuelve tras echo $?
	}
	if (cmd->cmd[1])
	{
		while (cmd->cmd[1][++i])
		{
			if (ft_isalpha(cmd->cmd[1][i]))
				return (ft_numeric_error(cmd));
		}
		//g_status = ft_atoi(cmd->cmd[1]);
	}
/*	
	else
	{
		g_status = 0;
		printf("%d", g_status);
	}

	return (0);
}
*/

int	ft_numeric_error(t_cmd	*cmd, t_data *data)
{
	data->status = 255;
	printf(RED"exit: %s: numeric argument required\n"RESET, \
		cmd->cmd[1]);
	return (0);
}

void	free_program(t_cmd *cmd, t_data *data)
{
	free (data->user);
	free_cmd(cmd);
	free(data->path);
	free (data->env);
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	int	i;

	if (cmd->cmd[1] && cmd->cmd[2])
	{
		data->status = 1;
		ft_printf(RED"exit: too many arguments\n"RESET);
		return (1);
	}
	i = -1;
	if (cmd->cmd[1])
	{
		while (cmd->cmd[1][++i])
			if (ft_isalpha(cmd->cmd[1][i]))
				return (ft_numeric_error(cmd, data));
		data->status = ft_atoi(cmd->cmd[1]);
	}
	else
		data->status = 0;
	free_program(cmd, data);
	exit (data->status);
	return (0);
}
