/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/01 22:03:24 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_token(char *prompt, char *set, char *specials, char *quotes)
{
	char	**tmp;
	int		word;

	tmp = (char **)malloc(sizeof(char *) * \
	(count_word(prompt, set, quotes, specials) + 1));
	if (!tmp)
		return (NULL);
	word = 0;
	while (*prompt)
	{
		if (*prompt && search(specials, *prompt))
			tmp[word++] = fun_check(ft_strndup(prompt, specials_token(prompt)));
		else if (*prompt && !search(specials, *prompt)
			&& !search(quotes, *prompt) && !search(set, *prompt))
			tmp[word++] = fun_check(ft_strndup(prompt, \
			caracteres_token(prompt, set, quotes, specials)));
		else if (*prompt && search(quotes, *prompt))
			tmp[word++] = fun_check(ft_strndup(prompt, \
			quotes_token(prompt, *prompt)));
		prompt += ft_strlen(tmp[word - 1]);
		if (*prompt && search(set, *prompt))
			prompt++;
	}
	tmp[word] = NULL;
	return (tmp);
}
