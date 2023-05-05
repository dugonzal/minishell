/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/05 18:44:28 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_argv(char **str)
{
  int	i;

  i = 0;
  while (str[i] && !search("|;", str[i][0]))
	i++;
  if (str[i] == NULL)
	return (i);
  return (i + 1);
}

int type(char *str)
{
	if (!str) // end
	  return (3);
	else if (search(str, ';')) // break
	  return (4);
	else if (search(str, '|'))// pipe
	  return (5);
	else 
	  return (-1); // no type
}

// con esta funcion los voy metiendo en un puntero puntero mientras no sea null;|
t_cmd **last_back(t_cmd **cmd, t_cmd *new)
{
  t_cmd	*tmp;

  if (!new)
	return (cmd);
  tmp = *cmd;
  if (!*cmd)
  {
	*cmd = new;
	return (cmd);
  }
  while (tmp->next)
	  tmp = tmp->next;
  tmp->next = new;
  new->prev = tmp;
  return (cmd);
}

t_cmd *new_cmd(char **str, int size)
{
  t_cmd *cmd;
  int	i;

  cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
  if (!str)
	return (NULL);
  cmd->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
  i = 0;
  while (i < size)
  {
	cmd->cmd[i] = str[i];
	i++;
  }
  cmd->next = NULL;
  cmd->prev = NULL;
  cmd->type = type(str[i]);
  printf ("cmd->type = %d\n", cmd->type);
  cmd->size = size;
  printf (" = %d\n", cmd->size);
  return (cmd);
}

// quiero ir metiendo los comandos primero en una arrray y
// luego a un puntero puntero

int	parser(t_data *data)
{
  t_cmd	*cmd;

  cmd = ft_calloc(1, sizeof(t_cmd));
cmd = new_cmd(data->bufer, size_argv(data->bufer));
if (!cmd)
	return (1);
print (cmd->cmd);
 // printf ("%zu %d", arr_size(cmd->cmd), cmd->size);
  //  if (cmd->cmd[i - 1] == NULL)
//	cmd->type = 0;
 // else if (cmd->cmd[i - 1][0] == ';')
//	cmd->type = 1;
///	else
//	cmd->type = 2;
 // printf ("cmd->type = %d\n", cmd->type);
  return (0);
}
