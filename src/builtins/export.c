/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:03:50 by sizquier          #+#    #+#             */
/*   Updated: 2023/05/18 13:48:18 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
En Bash, las variables que se pueden exportar deben cumplir con ciertas reglas :

Deben comenzar con una letra o un guion bajo (_).
Después del primer carácter, pueden contener letras, números o guiones bajos.
No pueden contener espacios ni caracteres especiales, como signos de puntuación o símbolos.
Son sensibles a mayúsculas y minúsculas. Por lo tanto, las variables MY_VARIABLE y my_variable son distintas.
Aquí hay algunos ejemplos de variables válidas para exportar en Bash:

bash
Copy code
valid_variable="value"
_underscore_variable="value"
MY_VARIABLE="value"

Funciones necesarias:
1)ft_cmd_isalnum(char	*str):crear una función que reciba como argumento un char *str y que mientras se esté iterando sobre ella, que controle que si el primer caracter recibido NO ES ALFANUMERICO, y es distinto de = -> retorne 1 que es el valor de error.
2)void	ft_invalid(char *c):Crear una función que printee que el argumento recibido (char *c) no es valido, y que pinte que el valor de salida de g_status es 1
3)función para generar la expor con las vbles de envp + la que quiero agregar al envp
4)static char	*export_namevar(char	*var)->función para recoger el nombre de la vble que voy a asignar después del = 

5) una característica de export, es que si utilizo una vble de entorno con el mismo nombre que var (que es un puntero a una cadena de caracteres)->debe reemplazar su valor
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

/* ejemplo si en bas escribimos (es error porque he dejado un espacio delante del =)
bash-3.2$ export HOME =/yo
bash: export: `=/yo': not a valid identifier
bash-3.2$ echo $?
1 -> por eso el valor de g_status es 1
bash-3.2$*/
void	ft_invalid(char *c)
{
	ft_printf("export: `%s': not a valid identifier\n", c);
	g_status = 1;
	return ;
}

/*
Si 
se ha declarado como estática la función porque sólo se declara una vez, y me comentan que es una buena práctica por encapsulamiento y modularidad
Sin embargo, me indican que no es correcto que sea doble puntero El parámetro envp se pasa por valor y se intenta modificar en la función, pero esos cambios no se reflejarán fuera de la función. Para que los cambios sean visibles fuera de la función, debes pasar envp como un puntero a un puntero a char (char **) (aqui me pierdo un poco), 
tb me indican que la definición de new_envp es erroneo que sea un solo puntero a char y que al asignarle memoria con malloc
la declaración de new_envp debiera ser un puntero a un puntero a char, es decir, char ***new_envp, para corregir esto, es mejor declarar la función como env triple puntero, que es la opción de abajo;*/
static void	generate_export(char	*var, char	**envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	if (ft_isdigit(var[0]) || !ft_cmd_isalnum(var))
		return (ft_invalid(var));
	new_envp = (char **) malloc((ft_arraylen(*envp) + 2) * sizeof(char *));
	while ((envp)[i])
	{
		new_envp[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[j++] = ft_strdup(var);
	new_envp[j] = NULL;
	free_array((void **)envp)
	//free_double_array((void **)*envp);
	*envp = new_envp;
}

/* 
Ponemos 2 en el malloc  porque se necesita un espacio adicional para la vlbe var que se agregará al conjunto de vables de entorno:

Un espacio adicional para la nueva variable var que se agregará al conjunto de variables de entorno. Se asigna memoria utilizando ft_strdup(var) y se agrega al final del bloque de memoria new_envp en la línea new_envp[j++] = ft_strdup(var). Esto requiere un elemento adicional en el bloque de memoria.

Un elemento final establecido como NULL para indicar el final del conjunto de variables de entorno. Es una convención común en las representaciones de variables de entorno utilizar un puntero NULL como señal de finalización. Por lo tanto, se asigna un elemento adicional en new_envp[j] = NULL para marcar el final del conjunto de variables de entorno.



*/

/*versión con triple puntero, manteniendose como estática.
El parámetro envp se pasa como un puntero a un puntero a un puntero a char (char ***envp). 
Esto permite modificar el valor de *envp dentro de la función y reflejar los cambios fuera de ella. Si la opción fuera sin triple puntero, 

*/
static void	generate_export(char	*var, char	***envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	if (ft_isdigit(var[0]) || !ft_cmd_isalnum(var))
		return (ft_invalid(var));
	new_envp = (char **) malloc((ft_arraylen(*envp) + 2) * sizeof(char *));
	while ((*envp)[i])
	{
		new_envp[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[j++] = ft_strdup(var);
	new_envp[j] = NULL;
	free_dblearray((void **)*envp); //habría que declararla y ya no serviría tu función free_array
	*envp = new_envp;
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
La funcion substr se utiliza para extraer los i caracteres desde que var es == '=', desde la posición 0 despues del igual

*/
static char	*export_namevar(char	*var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (ft_substr(var, 0, i));
		i++;
	}
	return (NULL);
}

/*función para verificar si existe una variable de entorno con el mismo nombre que var y reemplazar su valor si procede. De ahi que como puede ser necesario realizar una modificación de la cadena de caracteres, el hacer la copia con strdup es una buena practica
dos casos de uso:
VAR es nulo
VAR tien valor
Si var es nulo, var_name (vble utiliziada para no trabajar con var directamente), no tendría información, con lo que para evitar problemas de memoria hacemos strup a var listo
si var tiene valor, es importante comparar el valor var_name por lo comentado antes, ya que si la vble de entorno exite-> se modifica, sino se crea nueva. De ahi que haya que iterar en todos los elementos del enviroment  que contenga variables de entorno almacenadas como cadenas de caracteres.
Para comprar, se debe comparar toda la longitud del var_name, con las vbles del entorno (envp[i]). Si coincide, entonces se machaca su valor, de ahí, que se libere enpv, y se haga la copia de var con strdup


*/
static int	check_replace(char	*var, char	***envp)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = export_varname(var);
	if (var == NULL) //caso que var no tenga valor
		var_name = ft_strdup(var);
	while ((*envp)[i]) // caso que var tenga valor
	{
		if (ft_strncmp((*envp)[i], var_name, ft_strlen(var_name)) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(var);
			free(var_name);
			return (1);
		}
		i++;
	}
	if (var_name)
		free(var_name);
	return (0);
}
/*control de errores, si var =="="
bash-3.2$ export =
bash: export: `=': not a valid identifier
bash-3.2$

Si el primer carácter de var no es un signo igual (=), se llama a la función check_replace para verificar si var ya existe como una vble entorno.Entonces mira si hay coincidencia,, si la hay, la reemplaza con la fucnion
check_replacerealiza el reemplazo 

Si check_replace devuelve 0, no se encontró una coincidencia, se llama a la función export_create para crear una nueva variable de entorno utilizando var y envp.*/
int	export_builtin1(char *var, char ***envp)
{
	int		exists;

	if (var[0] == '=')
	{
		g_status = 1;
		ft_printf("export: '%s': not a valid identifier\n", var);
		return (1);
	}
	exists = check_replace(var, envp);
	if (exists == 0)
		export_create(var, envp);
	return (0);
}
