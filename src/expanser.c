/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:03:30 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/23 21:16:22 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int count_expanser(char *str)
{
  int i;

  i = -1;
  while (str[++i] && !search(" \t\v\f\r\"\'", str[i]))
	;
  return (i);
}
/*
char *ft_getenv(char *str, char **env)
{
  char *tmp;
(void)env;
  if (!str)
	return (NULL);
  tmp = getenv(str);
  free (str);
  if (tmp)
	return (ft_strdup(tmp));
  return (NULL);
}
*/

int	expanser(t_data *data)
{
  int	i;
  int	j;
  char	*env;
  int	size;

  if (!data->bufer)
	return (1);
  i = -1;
  while (data->bufer[++i])
	if (data->bufer[i] && search(data->bufer[i], '$') \
	  && !search(data->bufer[i], '\''))
	{
	  j = 0;
	  while (data->bufer[i][j] != '$')
		  j++;
	  if (data->bufer[i][j] == '$' && !search(" \t\v\f\r\"\'", data->bufer[i][j + 1]))
	  {
		j++;
		size = count_expanser(&data->bufer[i][j]);
		env = ft_getenv(ft_strndup(&data->bufer[i][j], size), &env); // expanser
		if (!env)
		  return(err_msg(RED"Error: Environment variable not found."RESET));
		if (j > 1)
			env = ft_strjoin(ft_strndup(data->bufer[i], j - 1), env, 1);//antes
		if (data->bufer[i][j + size] != 0)
			env = ft_strjoin(env, &data->bufer[i][j + size], 1);
		if (!j)
		  free (data->bufer[i]);
		data->bufer[i] = env;
		if (search(data->bufer[i], '$'))
		  expanser(data);
	  }
	}
  return (0);
}


