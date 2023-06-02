/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/02 19:46:25 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_access(char *path, char *bin)
{
	char	*tmp;
	int		i;
	int		j;

	if (!path || !bin)
		return (NULL);
	tmp = (char *)ft_calloc((ft_strlen(path) \
	+ ft_strlen(bin) + 2), sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	while (path[++i])
		tmp[i] = path[i];
	tmp[i++] = '/';
	j = 0;
	while (bin[j])
	  tmp[i++] = bin[j++];
	tmp[i] = 0;
	if (!access(tmp, F_OK | X_OK))
		return (tmp);
	free (tmp);
	return (NULL);
}

void execute_relative_or_absolute(t_cmd *cmd, t_data *data)
{
	execve(cmd->cmd[0], cmd->cmd, data->env);
	ft_putendl_fd(RED"Error : comand no found"RESET, 2);
	data->status = 127;
}

void execute_path(t_cmd *cmd, t_data *data)
{
	int		i;
	
	i = -1;
	while (data->path[++i] != 0)
	  execve(check_access(data->path[i], cmd->cmd[0]), \
		cmd->cmd, data->env);
	cmd->status = 127;
	ft_putendl_fd(RED"Error : comand no found"RESET, 2);
}

void ft_dup2(int *fd, int io)
{
  if (dup2(fd[io], io) < 0)
  {
	perror(RED"dup2"RESET);
	exit(EXIT_FAILURE);
  }
  close(fd[io ^ 1]);
}

int	bin_execute(t_cmd *cmd, t_data *data)
{
	if (cmd->type == 5)
		if (pipe (cmd->pipe) < 0)
			return(err_msg(RED"eeee pipe xd :"RESET));
	cmd->pid = fork();
	if (cmd->pid < 0)
	  return(err_msg(RED"errrr fork"RESET));
	if (!cmd->pid)
	{
	  	if (cmd->type == 5)
		  ft_dup2(cmd->pipe, 1);
		if (builtins(cmd, data))
		  ;
		else if (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/')
		 execute_relative_or_absolute(cmd, data);
		else
		  execute_path(cmd, data);
		exit (EXIT_SUCCESS);
	}
	if (cmd->pid > 0)
	  waitpid(cmd->pid, &cmd->status, 0);
  return (0);
}





























