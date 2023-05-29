/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:03:50 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/29 19:00:50 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*

En Bash export tiene dos funciones:
1) Crear variables de entorno
2) exportar variables de entorno.
3)La ultima función es que si se escribe sólo export en bash se printea el texto declare -x + 

Pero hay que verificar unos controles de errores-> este apartado se ha llevado a builtin_extra


********CREAR VARIABLES DE ENTORNO**********************
	La creación de cmdiables de entorno sigue la siguiente estructura:
	Si es una vble de entorno predefinada de bash-> se "machaca" el valor que tenía previo a la ejecución de export-> Para ello función->check_replace
	Si no es vble de entorno predefinida de bash-> se crea nueva en el enviroment en el que ha sido creado (es decir, se se crea en el padre, no se propaga al hijo)

	****Funciones necesarias CREAR VARIABLES DE ENTORNO:

	3)función para generar la expor con las vbles de env + la que quiero agregar al env
	4)static char	*export_namecmd(char	*cmd)->función para recoger el nombre de la vble que voy a asignar después del = 
	5) una característica de export, es que si utilizo una vble de entorno con el mismo nombre que cmd (que es un puntero a una cadena de caracteres)->debe reemplazar su valor

*/


/*versión con triple puntero, manteniendose como estática.
El parámetro env se pasa como un puntero a un puntero a un puntero a char (char ***env). 
Esto permite modificar el valor de *env dentro de la función y reflejar los cambios fuera de ella. 
La idea es diseñar una función que prepare para la exportación haciendo lo siguiente:
1)verificando que cmd es un str con caracteres validos (se llama a control de errores)
2)declaramos un new_env, con len = a la longitud del arreglo de punteros a caracteres *env más 2 (para la nueva cmdiable de entorno y el finalización nulo).
3)hay que copiar todas las cadenas de caracteres de  *env en new_env, para ello usamos un bucle while

static void	ft_generate_export(char	*cmd, char	***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (ft_isdigit(cmd[0]) || !ft_cmd_isalnum(cmd))
		return (ft_invalid(cmd));
	new_env = (char **) malloc((arr_size(*env) + 2) * sizeof(char *));
	while ((*env)[i])
	{
		new_env[j++] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[j++] = ft_strdup(cmd);
	new_env[j] = NULL;
	free_dblearray((void **)*env);
	*env = new_env;
}
en bash debemos ejecutar un nombre= para que el sistema interprete que ahi comienza mi declaración. Por ejemplo 
bash-3.2$ export MYNAME='susana' -> esta función pretende controlar la parte 'MYNAME=' ¿porque? porque si la primera parte , se llama igual que una vble de entorno -> reemplaza el valor (de ahi función siguiente)
La funcion substr se utiliza para extraer los i caracteres desde que cmd es == '=', desde la posición 0 despues del igual

*/
void	ft_generate_export(char	*cmd, t_data *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
/* 	if (ft_isdigit(cmd[0]) || !ft_cmd_isalnum(cmd))
	{
		printf("Hello\n");
		return (ft_invalid(cmd));
	} */
	new_env = (char **) malloc((arr_size(data->env) + 2) * sizeof(char *));
	while (data->env[i])
	{
		new_env[j++] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[j++] = ft_strdup(cmd);
//	printf("My added var:%s\n", new_env[j - 1]);
	new_env[j] = NULL;
	if (data->init_env == 0)
		free_dblearray((void **)data->env);
	data->init_env = 0;
//	printf("data env ptr pre %p\n", data->env);
	data->env = new_env;
//	printf("export result: %s\n", data->env[j - 1]);
}

char	*ft_export_namecmd(char	*cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (ft_substr(cmd, 0, i + 1));
		i++;
	}
	return (NULL);
}
/*versión con triple puntero, manteniendose como estática.
El parámetro env se pasa como un puntero a un puntero a un puntero a char (char ***env). 
Esto permite modificar el valor de *env dentro de la función y reflejar los cambios fuera de ella. 
La idea es diseñar una función que prepare para la exportación haciendo lo siguiente:
1)verificando que cmd es un str con caracteres validos (se llama a control de errores)
2)declaramos un new_env, con len = a la longitud del arreglo de punteros a caracteres *env más 2 (para la nueva cmdiable de entorno y el finalización nulo).
3)hay que copiar todas las cadenas de caracteres de  *env en new_env, para ello usamos un bucle while
*/

int	ft_check_replace(char	*cmd, t_data *data)
{
	int		i;
	char	*name_cmd;

	i = 0;
	name_cmd = ft_export_namecmd(cmd);
	if (cmd == NULL) //caso que cmd no tenga valor
		name_cmd = ft_strdup(cmd);
	while (data->env[i]) // caso que cmd tenga valor
	{
		if (ft_strncmp(data->env[i], name_cmd, ft_strlen(name_cmd)) == 0)
		{
			free((data->env)[i]);
			printf("hola");
			data->env[i] = ft_strdup(cmd);
			free(name_cmd);
			return (1);
		}
		i++;
	}
//	free(name_cmd);
	
	if (name_cmd)
	{
		free(name_cmd);
		name_cmd = NULL;
	}
	
	return (0);
}
/*
La función export_builtin_individual se encarga de manejar un argumento individual del comando export. 
Mira que cmd es válido-> if primer caracter cmd == '=' -> no es valido y salida error = 1.
Si el primer carácter de cmd no es un signo igual (=), se llama a la función check_replace para verificar si cmd ya existe como una vble entorno.Entonces mira si hay coincidencia,, si la hay, la reemplaza con la fucnion
check_replacerealiza el reemplazo 

Si check_replace devuelve 0, no se encontró una coincidencia, se llama a la función ft_generate_export para crear una nueva cmdiable de entorno utilizando cmd y env.*/
int	ft_export_builtin_individual(char *cmd, t_data *data)
{
	int	found;

	if (cmd[0] == '=')
	{
		//g_status = 1;
		ft_printf("export: '%s': not a valid identifier\n", cmd);
		return (1);
	}
	found = ft_check_replace(cmd, data);
	
	if (found == 0)
	{
		printf("Enterning generate export\n");
		ft_generate_export(cmd, data);
	}
	return (0);
}
/*función general export builtin. Esta función permite manejar cada argumento individualmente (llamando ) y despues agregar y/o manejar las vbles del entorno
1)no hay argumentos adicionales después de export-> muestra todas las variables precedidas del texto: declare -x
2)si hay argumentos-> recorre y llama a la funcion export_builtin_individual con cada argumento y al env*/
int	ft_export_general_builtin(char	**cmd, t_data *data)
{
	int	i;

	i = 1;
	//g_status = 0;
	printf("data env ptr %p\n", data->env);
	if (!cmd[1])
	{
		i = 0;
		while (data->env[i])
			printf("declare -x %s\n", data->env[i++]);
		printf("data env ptr %p\n", data->env);
		return (1);
	}
	while (cmd[i])
	{
//		printf("%s\n", cmd[i]);
		ft_export_builtin_individual(cmd[i++], data);
	}
/* 	printf("data env ptr post 2%p\n\n\n", data->env);
	i = 0;
	while (data->env[i])
		printf("declare -x %s\n", data->env[i++]); */
//	printf("data env ptr %p\n", data->env);
//	free_dblearray((void **)*env);
	return (1);
}