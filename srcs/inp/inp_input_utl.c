/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_input_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:58:05 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/28 14:25:40 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_fix(const char *s, size_t *len, size_t *i)
{
	size_t	k;

	k = 0;
	if (s[k] != ' ' && (s[k + 2] && s[k + 2] != ' '))
	{
		*(len) = 1;
		return ;
	}
	if (s[k] == ' ')
	{
		*(len) = *(len) + 1;
		*(i) = *(i) - 1;
	}
	if (s[k + 2] && s[k + 2] == ' ')
		*(len) = *(len) + 1;
}

static inline size_t	ft_strlen_to(const char *s, int scn)
{
	size_t	i;
	char	test;

	i = 0;
	test = s[0];
	while (s[i] && s[i] != ' ' && ft_is_reserved(s[i]) == (1 * scn))
		i++;
	return (i);
}

static inline void	ft_fix_reserved(char *s, size_t *len)
{
	size_t	i;
	char	c;

	i = 0;
	c = s[0];
	while (s[i] == c && i < *len)
		i++;
	if (*len == i)
		return ;
	*(len) = *(len) - i;
}

int	ft_load_strlen(t_ms *mini, char *s, int scn, size_t *len)
{
	*(len) = ft_strlen_to(s, scn);
	if (s[0] == '>' || s[0] == '<' || s[0] == '|' || s[0] == '&')
	{
		ft_fix_reserved(s, len);
		if (*(len) >= 3)
		{
			if (*(len) >= 4)
				return (ft_syntax_error(mini, s[0], 2));
			return (ft_syntax_error(mini, s[0], 1));
		}
		return (SUCCESS);
	}
	if (s[0] == ';')
	{
		if (*(len) > 1)
			return (ft_syntax_error(mini, s[0], 2));
		return (SUCCESS);
	}
	return (SUCCESS);
}
