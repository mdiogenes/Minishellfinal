/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/08 12:26:26 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_change_var(char **dst, int *i_j, char **str, t_ms *mini)
{
	t_token	*node;
	char	*var;
	char	*sub_str;

	var = NULL;
	i_j[0] = i_j[0];
	i_j[1] = i_j[1];
	ft_join_str(dst, str, i_j[1], i_j[0] - i_j[1]);
	i_j[0] = i_j[0] + 1;
	i_j[1] = i_j[0];
	while ((*str)[i_j[0]] != ' ' && (i_j[0] < (int)ft_strlen(*str))
		&& (*str)[i_j[0]] != '$')
		i_j[0] = i_j[0] + 1;
	sub_str = ft_substr((*str), i_j[1], i_j[0] - i_j[1]);
	node = ft_find_envar_export(sub_str, mini);
	free (sub_str);
	if (!node)
		var = NULL;
	else if (node->args->token)
		var = node->args->token;
	if (var)
		*dst = ft_strjoin_clean(*dst, var, 1);
	else
		*dst = ft_strjoin_clean(*dst, "\0", 1);
	i_j[1] = i_j[0];
}

static inline void	ft_caseinterr_digit(char *str,
		char **dst, int *i_j, t_ms *mini)
{
	char	*tmp;

	(void)mini;
	if ((str[i_j[0]] == '$') && (str[i_j[0] + 1] == '?'))
	{
		if (!*dst)
		{
			tmp = ft_substr(str, i_j[1], i_j[0] - i_j[1]);
			*dst = ft_strjoin_clean(tmp, ft_itoa(mini->exitstatus), 0);
		}
		else
		{
			tmp = ft_strjoin_clean(*dst,
					ft_substr(str, i_j[1], i_j[0] - i_j[1]), 0);
			*dst = ft_strjoin_clean(tmp, ft_itoa(mini->exitstatus), 0);
		}
		i_j[0] = i_j[0] + 1;
		i_j[1] = i_j[0] + 1;
	}
	if ((str[i_j[0]] == '$') && (ft_isdigit(str[i_j[0] + 1])))
	{
		ft_join_str(dst, &str, i_j[1], i_j[0] - i_j[1]);
		i_j[0] = i_j[0] + 2;
		i_j[1] = i_j[0];
	}
}

static inline void	ft_rarecase(char *str, char **dst, int *i_j, t_ms *mini)
{
	int		len;

	len = ft_strlen(str);
	if (i_j[0] + 1 < len)
	{
		if ((str[i_j[0]] == '$') && (str[i_j[0] + 1] == '$'))
		{
			join_dst_pid(str, dst, &i_j[0], mini);
			i_j[0] = i_j[0] + 1;
			i_j[1] = i_j[0] + 1;
			i_j[0] = i_j[0] +1;
		}
		if (((str[i_j[0]] == '$') && (str[i_j[0] + 1] == ' '))
			|| ((str[i_j[0]] == '$') && (i_j[0] + 1 == len)))
		{
			ft_join_str(dst, &str, i_j[1], i_j[0] - i_j[1] + 2);
			i_j[1] = i_j[0] + 1;
			i_j[0] = i_j[0] + 1;
		}
		ft_caseinterr_digit(str, dst, &i_j[0], mini);
	}
}

int	ft_do_expand(t_ms *mini, t_token *node)
{
	char		*dst;
	int			i_j[2];

	dst = NULL;
	if (node->type == CMD_LITERAL || node->meta == MTA_NULL_TOKEN)
		return (ERROR);
	ft_init_vector(&i_j[0], 0, 2);
	while (i_j[0] < (int)ft_strlen(node->token))
	{
		if ((node->token[i_j[0]] == '$') && (node->token[i_j[0] +1] != '?')
			&& (i_j[0] + 1 < (int)ft_strlen(node->token))
			&& (node->token[i_j[0] + 1] != '$')
			&& (node->token[i_j[0] + 1] != ' ')
			&& (!ft_isdigit(node->token[i_j[0] + 1])))
			ft_change_var(&dst, &i_j[0], &node->token, mini);
		ft_rarecase(node->token, &dst, &i_j[0], mini);
		if (node->token[i_j[0]] != '$' || !node->token[i_j[0] + 1])
			i_j[0]++;
	}
	if (i_j[0] > i_j[1])
		ft_join_str(&dst, &node->token, i_j[1], i_j[0] - i_j[1]);
	if (node->token)
		free(node->token);
	node->token = dst;
	return (SUCCESS);
}

int	ft_get_expand(t_ms *mini, t_token *node)
{
	if (!node)
		return (SUCCESS);
	if (!node->args && !node->next)
		return (ft_expand_node(mini, node));
	if (node->args && node->next)
		return (ft_get_expand(mini, node->args)
			+ ft_get_expand(mini, node->next)
			+ ft_expand_node(mini, node));
	if (!node->args && node->next)
		return (ft_get_expand(mini, node->next)
			+ ft_expand_node(mini, node));
	return (ft_get_expand(mini, node->args)
		+ ft_expand_node(mini, node));
}
