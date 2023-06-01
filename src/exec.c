/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/01 17:34:29 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_redir(t_cmd *cmd)
{
	if (cmd->in)
	{
	  cmd->fd[cmd->io] = ft_open(cmd->in, cmd->io);
	  free (cmd->in);
	}
	if (cmd->out)
	{
	  cmd->fd[cmd->io] = ft_open(cmd->out, cmd->io);
	  free (cmd->out);
	}
	if (cmd->fd[cmd->io] < 0)
		return (1);
	if (dup2(cmd->fd[cmd->io], cmd->io) == -1)
	{
		perror (RED"dup2222"RESET);
		close(cmd->fd[cmd->io]);
		return (1);
	}
    close(cmd->fd[cmd->io]);

	return (0);
}

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
	tmp[i] = '/';
	j = 0;
	i++;
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
	data->status = 1;
}

void execute_path(t_cmd *cmd, t_data *data)
{
	int		i;
	char 	*tmp;
	i = -1;
	while (data->path[++i] != 0)
	{
	  tmp = check_access(data->path[i], cmd->cmd[0]);
	  execve(tmp, cmd->cmd, data->env);
    }
	ft_putendl_fd(RED"Error : comand no found"RESET, 2);
	data->status = 1;
	free (tmp);
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

void redirecciones(t_cmd *cmd)
{
  if (cmd->in && cmd->out)
  {
	printf ("[%s] [%s] \n", cmd->in, cmd->out);
	ft_dup2(cmd->fd, 0);
	ft_dup2(cmd->fd, 1);
  }
}

int	bin_execute(t_cmd *cmd, t_data *data)
{
	pid_t	pid;

	if (cmd->type == 5)
		pipe (cmd->fd);
	pid = fork();
	if (pid < 0)
	  return(err_msg(RED"errrr fork"RESET));
	if (!pid)
	{
		redir(cmd);
		if (cmd->in && cmd->out)
		  redirecciones(cmd);
		else if (cmd->in || cmd->out)
		  if (exec_redir(cmd))
			return(1);
	  if (cmd->type == 5)
		  ft_dup2(cmd->fd, 1);
		else if (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/')
		  execute_relative_or_absolute(cmd, data);
		else
		  execute_path(cmd, data);
		exit (EXIT_SUCCESS); // si  lo comentamos deja de funcionar exit, y sino lo comentamos, sale cada vez que se utiliza una builtin
	}
	if (pid > 0)
	{
	  waitpid(pid, &data->status, 0);
	  if (cmd->type == 5)
		ft_dup2(cmd->fd, 0);
	} 
  return (0);
}
