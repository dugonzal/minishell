/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:05:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/01 19:52:21 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int builtins(t_cmd *cmd, t_data *data)
{
  if (!ft_strncmp(cmd->cmd[0], "exit", 5))
  {
    ft_exit(cmd);
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
  {
    ft_pwd();
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "echo", 5))
  {
    ft_echo_builtin(cmd);
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "env", 4))
  {
    ft_env(data->env);
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
  {
	  ft_cd_builtin(cmd, data);
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "export", 7))
  {
	ft_export_general_builtin(cmd->cmd, data);
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
  {
	ft_unset_builtin(cmd->cmd, &data->env);
    return (1);
  }
  return (0);
}

