/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:52:25 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/01 16:32:14 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
********CONTROL ERRORES**********************
	En Bash, las variables que se pueden exportar deben cumplir con ciertas reglas :

	Deben comenzar con una letra o un guion bajo (_).
	Después del primer carácter, pueden contener letras, números o guiones bajos.
	No pueden contener espacios ni caracteres especiales, como signos de puntuación o símbolos.
	Son sensibles a mayúsculas y minúsculas. Por lo tanto, las cmdiables MY_VARIABLE y my_variable son distintas.
	Aquí hay algunos ejemplos de variables válidas para exportar en Bash:

	ejemplo de control de errores

	bash-3.2$ export HOME =/yo
	bash: export: `=/yo': not a valid identifier
	bash-3.2$ echo $?
	1 -> por eso el valor de g_status es 1


	****Funciones necesarias CONTROL DE ERRORES:
		1)ft_cmd_isalnum(char	*str):crear una función que reciba como argumento un char *str y que mientras se esté iterando sobre ella, que controle que si el primer caracter recibido NO ES ALFANUMERICO, y es distinto de = -> retorne 1 que es el valor de error.
		2)void	ft_invalid(char *c):Crear una función que printee que el argumento recibido (char *c) no es valido, y que pinte que el valor de salida de g_status es 1

*/
int	ft_cmd_isalnum(char	*str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


void	ft_invalid(char *c)
{
	ft_printf("export: `%s': not a valid identifier\n", c);
	//g_status = 1;
	return ;
}
void	free_dblearray(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}