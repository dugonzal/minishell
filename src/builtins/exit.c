/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:04:21 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/25 18:26:57 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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
*/
	return (0);
}
