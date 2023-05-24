/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:48:35 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/23 19:54:50 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_arraylen(char **envp) //necesito la len de un arreglo de cadenas de caracteres
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/* función de lógica de unset, cuando se elimina un elemento del enviroment, se crea un nuevo envoriment sin la vble que se desea eliminar. Para ello defino una funicón que recibe como parametro la vble a eliminar(var), dentro del puntero a un arreglo de cadena de caracteres
para ello, necesito definir una nueva vbble new_envp que no incluya la vble que deseo eliminar*/
int	ft_unset_builtin2(char *var, char ***envp) // funcion que recibe dos parametros, la vble var que deseo eliminar dentro del puntero a un arreglo de cadena de caracteres. tengo que iterar en envp para ver 
{
	int		i;
	int		j;
	char	**new_envp;
	char	*var2;

	i = 0;
	j = 0;
	g_status = 0;
	if (!var)
		return (0);
	new_envp = (char **) malloc((ft_arraylen(*envp) + 1) * sizeof(char *));
	var2 = ft_strjoin(var, "=", 0); //var2 une los elementos de var y el signo =, esdecir, voy a concatenar de tal forma que var2 incluya "var="  y asi utilizarlo en las comparaciones posteriores.
	//hago un bucle para comparar con la condición utilizando ft_strncmp la cadena de caracteres (*envp)[i] con las variables var2 y var. Lo comparo en el if, y si cumple creo una nuva vble. y tras su ejecución avanzo en el siguiente elemento del env(i)
	while ((*envp)[i]) // mientras exista envpi
	{
		if ((ft_strncmp((*envp)[i], var2, ft_strlen(var2)) != 0) && (ft_strncmp((*envp)[i], var, ft_strlen(var) + 1) != 0))
		//comparo env(i) con var2 en toda la longittud de var, si son distintos
				 //comparo env(i) con var en toda su longitud más el caracter null, si son ddistinos
			new_envp[j++] = ft_strdup((*envp)[i]);// si se cumple el if, es decir que son todas distintas->duplicar la cadena de caracteres (*envp)[i] y asignarla a new_envp[j], donde j es el índice de new_envp que se incrementa después de la iteracion.
		i++; // despues de ejecutar el if, para avanzar en el siguiente elemento de envp(i)
	}
	new_envp[j] = NULL; // fin del arreglo creado con strdup
	free_dblearray((void **)envp); // Duvan, he visto que tenias esta funcion, y la he utilizado"
	*envp = new_envp;
	free(var2);
	return (0);
}
/*funcion para eliminar multiples vbles del entorno, de manera individualizada. El arreglo var contiene las vbles a eliminar, del arreglo de vbles del entorno (envp)*/
int	ft_unset_builtin(char	**var, char	**envp)
{
	int	i;

	i = 1;
	while (var[i])
	{
		ft_unset_builtin2(var[i++], &envp);
	}
	return (0);
}
