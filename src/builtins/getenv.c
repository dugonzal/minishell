/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:55:54 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/12 19:56:28 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv_builtins(char	*cmd, char	**env) // funcion para crear enviroment, la voy a utilizar 
{
	int		i;
	int		j;
	char	*cmd2;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	cmd2 = ft_strjoin(cmd, "=", 0); //se une los elementos de var utilizando el = como separador. El resultado se almacena en var2
	len = ft_strlen(cmd2); // tengo que darle a len la longitud de var2.
	while (env[i])
	{
		if (ft_strncmp(env[i], cmd2, len) == 0) // comparo var2 en toda su len con envp (que lo itero con la i). Si hay coincidencia-> entra while
		{
			while (env[i][j] != '=' && env[i][j]) // el while iteramos mimentras = no este en env (i). la vble j se incrementa hasta que encuentre = o llegue al final de la cadena
				j++;
			str = ft_substr(env[i], j + 1, ft_strlen(env[i]) - len); //str se declara porque ya se ha encontrado el caracter = empieza en j+1 que es justo detrás del igual, y la longitud de str es envp descontando la len de var2
			free(cmd2); //segun el subject se puede usar la función free de c pero hay que declararla y meterla en 
			return (str);
		}
		i++;
	}
	free(cmd2);
	return (NULL);
}