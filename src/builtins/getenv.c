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

char	*ft_getenv(char	*var, char	**envp) // funcion para crear enviroment, la voy a utilizar 
{
	int		i;
	int		j;
	char	*var2;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	var2 = ft_strjoin(var, "=", 1); //se une los elementos de var utilizando el = como separador. El resultado se almacena en var2
	len = ft_strlen(var2); // tengo que darle a len la longitud de var2.
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var2, len) == 0) // comparo var2 en toda su len con envp (que lo itero con la i). Si hay coincidencia-> entra while
		{
			while (envp[i][j] != '=' && envp[i][j]) // el while iteramos mimentras = no este en env (i). la vble j se incrementa hasta que encuentre = o llegue al final de la cadena
				j++;
			str = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - len); //str se declara porque ya se ha encontrado el caracter = empieza en j+1 que es justo detrás del igual, y la longitud de str es envp descontando la len de var2
			free(var2); //segun el subject se puede usar la función free de c pero hay que declararla y meterla en 
			return (str);
		}
		i++;
	}
	free(var2);
	return (NULL);
}