/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:27:39 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:34:12 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	ft_is_reserved(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '='
		|| c == ';' || c == '(' || c == ')' || c == '\'' || c == '\"');
}

void	ft_join_str(char **dst, char **str, int in, int fin)
{
	char	*tmp;

	if (!*dst)
		*dst = ft_substr(*str, in, fin);
	else
	{
		tmp = ft_strjoin_clean(*dst, ft_substr(*str, in, fin), 0);
		*dst = tmp;
	}
}

void	join_dst_pid(char *str, char **dst, int *i_j, t_ms *mini)
{
	char	*tmp;

	if (!*dst)
	{
		tmp = ft_substr(str, i_j[1], i_j[0] - i_j[1]);
		*dst = ft_strjoin_clean(tmp, ft_itoa(mini->pid), 0);
	}
	else
	{
		tmp = ft_strjoin_clean(*dst,
				ft_substr(str, i_j[1], i_j[0] - i_j[1]), 0);
		*dst = ft_strjoin_clean(tmp, ft_itoa(mini->pid), 0);
	}
}

int	ft_var_valid_name(char c)
{
	if (ft_isalpha(c) != 0)
		return (IS_TRUE);
	if (c == '_' || c == '$')
		return (IS_TRUE);
	return (IS_FALSE);
}
