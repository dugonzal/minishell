/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:02:47 by sizquier          #+#    #+#             */
/*   Updated: 2023/06/01 20:13:44 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* se plantea cd con tres funciones:
Funcion para exportar el directorio de trabajo actual
Función para el caso de uso que después del comando cd no se utiliza ningún argumento
Función de entrada del comando cd.
Libreria #include <errno.h>*/

#include "../../include/minishell.h"


/*función para exportar el directorio de trabajo actual, toma como argumento un puntero que indica la vble del entorno y un puntero a un puntureo que se refiere a las vbles del entorno
la función getcwd es para el directorio actual y se almacena en pwd. Si getcwd falla-> return 1.
ft_strjoin une var con pwd y asigna a la vble path. Si la asignación de path falla-> vaolor 1 y error.
verificamos con export_builtin_individual que se exporta path utilizando env. Si falla-> hay que liberar memoria ew pwd y path y asignado el valor 1. Mientras que si todo va bien, se libera memoria utilizand el valor 0
Al utilizar la variable de entorno, se evita tener que especificar el directorio completo en cada comando y puedes acceder al directorio actual de manera más agil.
Veamos un ejemplo, (esto me lo han explicado y lo imprimo tal cual), en bash escribo este comando, para que cuando escriba cd, me vaya a mi directorio actual

cd:
  if [ -d "$PWD" ]; then
    cd "$PWD"
  else
    echo "Directory does not exist"
  fi

Esto hace que aunque no esté en mi prompt al escribir cd me vaya a el.
Si export_builtin_individual retorna un valor distinto de 0, indica que ocurrió un error al agregar la variable de entorno, por lo que se liberan las memorias asignadas a pwd y path y retorna 1.
*/
int	export_pwd(char *cmd, t_data *data)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	path = ft_strjoin(cmd, pwd,0);
	if (!path)
		return (1);
	if (ft_export_builtin_individual(path, data)) 
		return (free(pwd), free(path), 1);
	return (free(pwd), free(path), 0);
}

/*función para cuando no se ejecute ningún comando después de cd: Casos de uso:
Sino existe home-> no hay vble entorno y devuelve 1
verificamos si se puede exportar el valor del directorio anterior con export_pwd-> si hay fallo devuelve 1
chdir (permitida en el subject), cambia el directorio de trabajo actual a home. si falla devuelve 1
Si la llamada a chdir falla, mensaje de error utilziando la función permitida strerror*/
int	cd_argument(t_data *data)
{
	char	*home;

	home = ft_getenv_builtins("HOME", data->env);
	if (!home)
		return (1);
	if (export_pwd("OLDPWD=", data))
		return (1);
	if (chdir(home) != 0)
	{
		ft_printf("cd: %s: %s\n", home, strerror(errno)); //errno es una variable global que se utiliza para almacenar el número del último error ocurrido en el sistema. strerror() es una función que convierte el número del error almacenado en errno en una cadena de caracteres legible . Por ejemplo, si errno es igual a 2, strerror(errno) devolverá una cadena que dice "No such file or directory", que es el mensaje de error correspondiente al código de error 2 en la mayoría de los sistemas operativos tipo Unix. La función strerror() es muy útil para depurar programas y comprender los errores que ocurren durante la ejecución.
		free(home);
		perror("cd: ~");
		return (1);
	}
	if (export_pwd("PWD=", data))
		return (1);
	free(home);
	return (0);
}

/* función que devuelve ok o no ok a los argumentos que se reciben de cmd es una estructura que contiene el comando que se esta ejecutando, puntero a un puntero de un arreglo de cadenas */
int	ft_cd_builtin(t_cmd *cmd, t_data *data)
{
	char	*path;
/*caso de uso que no existe ningún argumento->se llama a cd_argument*/
	if (!cmd->cmd[1] || (cmd->cmd[1][0] == '~' && cmd->cmd[1][1] == '\0'))
		return (cd_argument(data));
		/*caso uso - tras cd, que te devuelve al pwd anterior*/
	if (cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == '\0')
		path = ft_getenv_builtins("OLDPWD", data->env);
	else
		path = cmd->cmd[1];
	if (export_pwd("OLDPWD=", data))
		return (1);
	if (chdir(path) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (export_pwd("PWD=", data))
		return (1);
	return (0);
}
