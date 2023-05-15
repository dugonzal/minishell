/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:41:17 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/15 16:31:03 by sizquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BLUE "\033[0;34m"
# include "../libft/include/libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_cmd
{
	int				fd[2];// in out I/O
	char			**cmd;
	int				type;
	char 			*file;
	int				io;
	struct s_cmd	*next;
	struct s_cmd	*prev;

} t_cmd;

typedef struct s_data
{
	char			*line;
	char			**bufer;
	char			**path;
	char			**env;
	int				status;
} t_data;

static int g_status;

void	handler(int sig, siginfo_t *info, void *context);
void	signals(void);
char	*prompt(void);
int		bin_execute(t_cmd *cmd, t_data *data);
// builtins
int		verify_quotes(t_data *data);
void	print(char **str);
int	export_pwd(char *var, char **envp[]);
int	cd_argument(char **envp[]);

// utils
void	*free_array(char **array);
void	print(char **str);
char	*fun_check(char *str);
int		search(char *set, char c);

//lexer
int		lexer(t_data *data);
char	**split_token(const char *prompt, char *set, char *quotes, char *special);
int		count_word(const char *prompt, char *set, char *quotes, char *specials);
int		quotes_token(const char *str, char quote);
int		caracteres_token(const char *prompt, char *set, char *quotes, char *specials);
int		specials_token(const char *prompt);

// lexer utils
int		err_msg(char *str);
int		check_redir(char **prompt, char redir);
int		check_pipe(char **prompt, char pipe);
int		check_quotes(char **prompt, char *quotes);
int		check_semicolon(char **prompt, char );
int		expanser(t_data *data);
int		lexer_errors(char **str);

// parser
int		parser(t_data *data);
int		builtins(t_cmd *cmd, t_data *data);
void	handler_execute(t_data *data, t_cmd *cmd);

// parser utils

t_cmd	**last_back_node(t_cmd **cmd, t_cmd *new);
t_cmd	*new_node(char **str, int size);
int		size_node(char **str);
int		type(char *str);
void	quotes_quit(char **str, char *quotes);
int		ft_open(char *str, int i);
void	exec_redir(t_cmd *cmd);
int		ft_echo(char **str);
int		ft_pwd(void);
void	ft_execute_echo(char **cmd);
void	ft_echo_builtin(t_cmd *cmd);
int		ft_exit(t_cmd  *cmd);
void	ft_env_builtin(char **envp);


#endif
