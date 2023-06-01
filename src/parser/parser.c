/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/31 18:25:32 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int parser_cmds(char **bufer, t_cmd **cmd)
{
  int	size;

  size = size_node(bufer);
  last_back_node(cmd, new_node(bufer, size));
  return (size);
}

void error_fd(t_data *data)
{
	perror("dup");
	data->status = 1; // error
	return ;
}

void copy_fd(t_data *data)
{
  int fd;

  fd = dup(0);
  if (fd == -1)
	error_fd(data);
  data->fd[0] = fd;
  fd = dup(1);
  if (fd == -1)
	error_fd(data);
  data->fd[1] = fd;
}

void reset_fd(t_data *data)
{
	if (dup2(data->fd[0], 0) == -1)
	{
	  perror("dup2");
	  data->status = 1;
	  close(data->fd[0]);
	  close(data->fd[1]);
	  return ;
	}
	close (data->fd[0]);
  	if (dup2(data->fd[1], 1) == -1)
	{
	  perror("dup2");
	  data->status = 1;
	  close(data->fd[0]);
	  return ;
	}
	close (data->fd[1]);
}

void exec(t_cmd *cmd, t_data *data)
{
  t_cmd *tmp;

  tmp = cmd;
  copy_fd(data);
  while (tmp)
  {
	seach_quotes(tmp->cmd, "\"\'");
	redir (cmd);
	if (builtins(cmd, data))
		;
	else
		bin_execute(tmp, data);
	if (tmp->type != 5)
	  reset_fd(data);
	tmp = tmp->next;
  }
}

int parser(t_data *data)
{
  t_cmd		*cmd;
  int		i;

  i = 0;
  ft_bzero (&cmd, sizeof(cmd));
  while (data->bufer[i])
	 if (search("|;", data->bufer[i][0]))
		i++;
	else if (data->bufer[i])
		i += parser_cmds(&data->bufer[i], &cmd);
  free (data->bufer);
  if (cmd)
	exec(cmd, data);
  free_cmd(cmd);
  return (0);
}


