/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:05:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/25 19:54:50 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export_general_builtin(char	**cmd, char	***env);

int builtins(t_cmd *cmd, t_data *data)
{
  if (!ft_strncmp(cmd->cmd[0], "exit", ft_strlen(cmd->cmd[0])))
  {
    ft_exit(cmd);
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "pwd", ft_strlen(cmd->cmd[0])))
  {
    ft_pwd();
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "echo", ft_strlen(cmd->cmd[0])))
  {
    ft_echo_builtin(cmd);
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "env", ft_strlen(cmd->cmd[0])))
  {
    ft_env(data->env);
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "cd", ft_strlen(cmd->cmd[0])))
  {
	;
    return (1);
  }
   else if (!ft_strncmp(cmd->cmd[0], "export", 7))
  {
	ft_export_general_builtin(cmd->cmd, &data->env);
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "unset", ft_strlen(cmd->cmd[0])))
  {
	ft_unset_builtin(cmd->cmd, &data->env);
    return (1);
  }
  return (0);
}

