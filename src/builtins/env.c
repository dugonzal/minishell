/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:19:41 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/23 20:03:40 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_builtin(char **envp)
{
	int	i;

	i = 1;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') != NULL)
			ft_printf("%s\n", envp[i]);
		i++;
	}
	g_status = 0;
	exit(0);
}