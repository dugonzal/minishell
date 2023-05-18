/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:03:50 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/18 20:41:37 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

En Bash export tiene dos funciones:
1) Crear cmdiables de entorno
2) exportar cmdiables de entorno.
3)La ultima función es que si se escribe sólo export en bash se printea el texto declare -x

Pero hay que verificar unos controles de errores
********CONTROL ERRORES**********************
	En Bash, las cmdiables que se pueden exportar deben cumplir con ciertas reglas :

	Deben comenzar con una letra o un guion bajo (_).
	Después del primer carácter, pueden contener letras, números o guiones bajos.
	No pueden contener espacios ni caracteres especiales, como signos de puntuación o símbolos.
	Son sensibles a mayúsculas y minúsculas. Por lo tanto, las cmdiables MY_cmdIABLE y my_cmdiable son distintas.
	Aquí hay algunos ejemplos de cmdiables válidas para exportar en Bash:

	ejemplo de control de errores

	bash-3.2$ export HOME =/yo
	bash: export: `=/yo': not a valid identifier
	bash-3.2$ echo $?
	1 -> por eso el valor de g_status es 1


	****Funciones necesarias CONTROL DE ERRORES:
		1)ft_cmd_isalnum(char	*str):crear una función que reciba como argumento un char *str y que mientras se esté iterando sobre ella, que controle que si el primer caracter recibido NO ES ALFANUMERICO, y es distinto de = -> retorne 1 que es el valor de error.
		2)void	ft_invalid(char *c):Crear una función que printee que el argumento recibido (char *c) no es valido, y que pinte que el valor de salida de g_status es 1


********CREAR VARIABLES DE ENTORNO**********************
	La creación de cmdiables de entorno sigue la siguiente estructura:
	Si es una vble de entorno predefinada de bash-> se "machaca" el valor que tenía previo a la ejecución de export-> Para ello función->check_replace
	Si no es vble de entorno predefinida de bash-> se crea nueva en el enviroment en el que ha sido creado (es decir, se se crea en el padre, no se propaga al hijo)

	****Funciones necesarias CREAR VARIABLES DE ENTORNO:

	3)función para generar la expor con las vbles de env + la que quiero agregar al env
	4)static char	*export_namecmd(char	*cmd)->función para recoger el nombre de la vble que voy a asignar después del = 
	5) una característica de export, es que si utilizo una vble de entorno con el mismo nombre que cmd (que es un puntero a una cadena de caracteres)->debe reemplazar su valor

*/

/*******CONTROL ERRORES**********************/

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
	g_status = 1;
	return ;
}


/*versión con triple puntero, manteniendose como estática.
El parámetro env se pasa como un puntero a un puntero a un puntero a char (char ***env). 
Esto permite modificar el valor de *env dentro de la función y reflejar los cambios fuera de ella. 
La idea es diseñar una función que prepare para la exportación haciendo lo siguiente:
1)verificando que cmd es un str con caracteres validos (se llama a control de errores)
2)declaramos un new_env, con len = a la longitud del arreglo de punteros a caracteres *env más 2 (para la nueva cmdiable de entorno y el finalización nulo).
3)hay que copiar todas las cadenas de caracteres de  *env en new_env, para ello usamos un bucle while
*/
static void	generate_export(char	*cmd, char	***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (ft_isdigit(cmd[0]) || !ft_cmd_isalnum(cmd))
		return (ft_invalid(cmd));
	new_env = (char **) malloc((ft_arraylen(*env) + 2) * sizeof(char *));
	while ((*env)[i])
	{
		new_env[j++] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[j++] = ft_strdup(cmd);
	new_env[j] = NULL;
	free_dblearray((void **)*env); //habría que declararla y ya no serviría tu función free_array
	*env = new_env;
	//return new_env si es doble puntero, esto me ha dicho Santi.
}


/*me corrigen y  me indican que es mejor la función con triple puntero
La función free_dblearray sería algo así:
void	ffree_dblearray(void **array)
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

*/

/* en bash debemos ejecutar un nombre= para que el sistema interprete que ahi comienza mi declaración. Por ejemplo 
bash-3.2$ export MYNAME='susana' -> esta función pretende controlar la parte 'MYNAME=' ¿porque? porque si la primera parte , se llama igual que una vble de entorno -> reemplaza el valor (de ahi función siguiente)
La funcion substr se utiliza para extraer los i caracteres desde que cmd es == '=', desde la posición 0 despues del igual

*/
static char	*export_namecmd(char	*cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (ft_substr(cmd, 0, i));
		i++;
	}
	return (NULL);
}

/*función para verificar si existe una cmdiable de entorno con el mismo nombre que cmd y reemplazar su valor si procede. De ahi que como puede ser necesario realizar una modificación de la cadena de caracteres, el hacer la copia con strdup es una buena practica
dos casos de uso:
cmd es nulo
cmd tien valor
Si cmd es nulo, name_cmd (vble utiliziada para no trabajar con cmd directamente), no tendría información, con lo que para evitar problemas de memoria hacemos strup a cmd listo
si cmd tiene valor, es importante comparar el valor name_cmd por lo comentado antes, ya que si la vble de entorno exite-> se modifica, sino se crea nueva. De ahi que haya que iterar en todos los elementos del enviroment  que contenga cmdiables de entorno almacenadas como cadenas de caracteres.
Para comprar, se debe comparar toda la longitud del name_cmd, con las vbles del entorno (env[i]). Si coincide, entonces se machaca su valor, de ahí, que se libere enpv, y se haga la copia de cmd con strdup


*/
static int	check_replace(char	*cmd, char	***env)
{
	int		i;
	char	*name_cmd;

	i = 0;
	name_cmd = export_cmdname(cmd);
	if (cmd == NULL) //caso que cmd no tenga valor
		name_cmd = ft_strdup(cmd);
	while ((*env)[i]) // caso que cmd tenga valor
	{
		if (ft_strncmp((*env)[i], name_cmd, ft_strlen(name_cmd)) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(cmd);
			free(name_cmd);
			return (1);
		}
		i++;
	}
	if (name_cmd)
		free(name_cmd);
	return (0);
}
/*
La función export_builtin_individual se encarga de manejar un argumento individual del comando export. 
Mira que cmd es válido-> if primer caracter cmd == '=' -> no es valido y salida error = 1.
Si el primer carácter de cmd no es un signo igual (=), se llama a la función check_replace para verificar si cmd ya existe como una vble entorno.Entonces mira si hay coincidencia,, si la hay, la reemplaza con la fucnion
check_replacerealiza el reemplazo 

Si check_replace devuelve 0, no se encontró una coincidencia, se llama a la función export_create para crear una nueva cmdiable de entorno utilizando cmd y env.*/
int	export_builtin_individual(char *cmd, char ***env)
{
	int		found;

	if (cmd[0] == '=')
	{
		g_status = 1;
		ft_printf("export: '%s': not a valid identifier\n", cmd);
		return (1);
	}
	found = check_replace(cmd, env);
	if (found == 0)
		export_create(cmd, env);
	return (0);
}
/*función general export builtin. Esta función permite manejar cada argumento individualmente (llamando )
1)no hay argumentos adicionales después de export-> muestra todas las variables precedidas del texto: declare -x
2)si hay argumentos-> recorre y llama a la funcion export_builtin_individual con cada argumento y al env*/
int	export_general_builtin(char	**cmd, char	***env)
{
	int	i;

	i = 1;
	g_status = 0;
	if (!cmd[1])
	{
		i = 0;
		while ((*env)[i])
			printf("declare -x %s\n", (*env)[i++]);
		return (1);
	}
	while (cmd[i])
	{
		export_builtin1(cmd[i++], env);
	}
	return (1);
}