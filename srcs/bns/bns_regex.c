/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_regex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:17:26 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/28 14:33:22 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_regex_wc(char *haystack,
		char *pattern, size_t *it, size_t *len_h_p)
{
	if (it[1] < len_h_p[1])
	{
		it[1] += 1;
		while (haystack[it[0]] && haystack[it[0]] != pattern[it[1]])
			it[0] += 1;
		if (it[0] == 0 && it[1] > 0)
			return (IS_FALSE);
		return (IS_TRUE);
	}
	else
		return (IS_TRUE);
}

static int	ft_regex_lit(char *haystack, char *pattern, size_t *ih, size_t *ip)
{
	if (haystack[*(ih)] != pattern[*(ip)])
		return (IS_FALSE);
	while (haystack[*(ih)] && pattern[*(ip)] && pattern[*(ip)] != '*')
	{
		if (haystack[*(ih)] != pattern[*(ip)])
			return (IS_FALSE);
		*(ih) += 1;
		*(ip) += 1;
	}
	return (IS_TRUE);
}

static void	ft_init_lens(char *haystack,
		char *pattern, size_t *lens, size_t *iter)
{
	lens[1] = ft_strlen(pattern);
	lens[0] = ft_strlen(haystack);
	iter[1] = 0;
	iter[0] = 0;
}

int	ft_regex(char *haystack, char *pattern)
{
	size_t	len_h_p[2];
	size_t	i_h_p[2];

	ft_init_lens(haystack, pattern, &len_h_p[0], &i_h_p[0]);
	if (len_h_p[1] > len_h_p[0])
		return (IS_FALSE);
	while (pattern[i_h_p[1]])
	{
		if (pattern[i_h_p[1]] == '*')
		{
			if (ft_regex_wc(haystack, pattern, &i_h_p[0], &len_h_p[0])
				== IS_FALSE)
				return (IS_FALSE);
		}
		else
		{
			if (ft_regex_lit(haystack, pattern, &i_h_p[0], &i_h_p[1])
				== IS_FALSE)
				return (IS_FALSE);
		}
		if (i_h_p[1] == len_h_p[1] && i_h_p[0] == len_h_p[0])
			return (IS_TRUE);
	}
	return (IS_FALSE);
}
