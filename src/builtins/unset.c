/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:48:35 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/24 16:56:52 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_arraylen(char **env) //necesito la len de un arreglo de cadenas de caracteres
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/* función de lógica de unset, cuando se elimina un elemento del enviroment, se crea un nuevo envoriment sin la vble que se desea eliminar. Para ello defino una funicón que recibe como parametro la vble a eliminar(var), dentro del puntero a un arreglo de cadena de caracteres
para ello, necesito definir una nueva vbble new_envp que no incluya la vble que deseo eliminar*/
int	ft_unset_builtin2(char *cmd, char ***env) // funcion que recibe dos parametros, la vble var que deseo eliminar dentro del puntero a un arreglo de cadena de caracteres. tengo que iterar en envp para ver 
{
	int		i;
	int		j;
	char	**new_env;
	char	*cmd2;

	i = 0;
	j = 0;
	g_status = 0;
	if (!cmd)
		return (0);
	new_env = (char **) malloc((ft_arraylen(*env) + 1) * sizeof(char *));
	cmd2 = ft_strjoin(cmd, "=", 0); //var2 une los elementos de var y el signo =, esdecir, voy a concatenar de tal forma que var2 incluya "var="  y asi utilizarlo en las comparaciones posteriores.
	//hago un bucle para comparar con la condición utilizando ft_strncmp la cadena de caracteres (*envp)[i] con las variables var2 y var. Lo comparo en el if, y si cumple creo una nuva vble. y tras su ejecución avanzo en el siguiente elemento del env(i)
	while ((*env)[i]) // mientras exista envpi
	{
		if ((ft_strncmp((*env)[i], cmd2, ft_strlen(cmd2)) != 0) && (ft_strncmp((*env)[i], cmd, ft_strlen(cmd) + 1) != 0))
		//comparo env(i) con var2 en toda la longittud de var, si son distintos
				 //comparo env(i) con var en toda su longitud más el caracter null, si son ddistinos
			new_env[j++] = ft_strdup((*env)[i]);// si se cumple el if, es decir que son todas distintas->duplicar la cadena de caracteres (*envp)[i] y asignarla a new_envp[j], donde j es el índice de new_envp que se incrementa después de la iteracion.
		i++; // despues de ejecutar el if, para avanzar en el siguiente elemento de envp(i)
	}
	new_env[j] = NULL; // fin del arreglo creado con strdup
	free_dblearray((void **)*env); 
	*env = new_env;
	free(cmd2);
	return (0);
}
/*funcion para eliminar multiples vbles del entorno, de manera individualizada. El arreglo var contiene las vbles a eliminar, del arreglo de vbles del entorno (envp)*/
int	ft_unset_builtin(char	**cmd, char	***env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_unset_builtin2(cmd[i++], env);
	}
	return (0);
}
