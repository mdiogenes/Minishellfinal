/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:54:43 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 11:10:11 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_clear_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
		i++;
	return (i);
}

static inline char	*ft_strdup_input(char *src, size_t len,
	size_t i, t_ms *mini)
{
	char	*dst;

	if (i > 0)
	{
		if (ft_is_space(src[i - 1]) == 1 || (src[i + len]
				&& ft_is_space(src[i + len]) == 1))
			mini->status_tkn = FROM_NBSP;
	}
	else
	{
		if (src[i + len] && ft_is_space(src[i + len]) == 1)
			mini->status_tkn = FROM_NBSP;
	}
	dst = (char *)ft_calloc(sizeof(char), (len + 1));
	if (dst == NULL)
		ft_error_free(errno, mini);
	dst[len] = '\0';
	while (len--)
		dst[len] = src[i + len];
	return (dst);
}

static inline size_t	ft_strlen_chars(const char *s, char c)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = -1;
	while (s[i] && flag < 1)
	{
		if (flag == 1)
			break ;
		if (s[i] == c)
			flag++;
		if (flag < 1 && !s[i + 1])
		{
			return (i + 1);
			break ;
		}
		i++;
	}
	return (i);
}

int	ft_load_input(t_ms *mini)
{
	size_t		i;
	size_t		len;

	i = 0;
	mini->line = ft_strtrim_clean(mini->line, " \n\t");
	while (mini->line[i])
	{
		i = ft_clear_spaces(mini->line, i);
		if (mini->line[i] == '\'' || mini->line[i] == '\"')
			len = ft_strlen_chars(&mini->line[i], mini->line[i]);
		else
		{
			if (ft_load_strlen(mini, &mini->line[i],
					ft_is_reserved(mini->line[i]), &len) == ERROR)
				return (ERROR);
		}
		if (mini->line[i] == '(' || mini->line[i] == ')')
			len = 1;
		if (mini->line[i] == '=' && mini->line[i - 1])
			ft_export_fix(&mini->line[i - 1], &len, &i);
		ft_new_token(mini, ft_inp_new(
				ft_strdup_input(mini->line, len, i, mini), mini));
		i = i + len;
	}
	return (SUCCESS);
}
