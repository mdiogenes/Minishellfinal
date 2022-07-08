/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:05:50 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 10:52:59 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(t_ms *mini)
{
	if (ft_load_input(mini) == ERROR)
		return (ERROR);
	if (mini->first_token == NULL)
		return (ERROR);
	if (ft_workflow(mini) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	ft_fix_args(t_token *token)
{
	t_token	*arg;

	if (token->type == CMD_EXPORT)
		return ;
	arg = token->args;
	while (arg)
	{
		arg->special_tkn = 0;
		arg = arg->next;
	}
}

void	ft_prepare_node(t_ms *mini, t_token *token)
{
	if (!token || !token->args || token->status == MTA_NULL_TOKEN)
		return ;
	ft_fix_args(token);
	if (token->args)
		ft_get_expand(mini, token->args);
	ft_solve_wildcards(mini, token, token->args);
}

static inline void	ft_null_to_export(t_token **token,
		t_token *prev, t_ms *mini)
{
	t_token	*node;
	t_token	*next;

	node = *token;
	next = node->next;
	if (!next)
		return ;
	if (next->type == CMD_ASSIGN)
		next->type = CMD_ASSIGN_LE;
	if (next->type == CMD_ASSIGN_RE)
		next->type = CMD_ASSIGN_BE;
	*token = ft_remove_node(node, prev, &mini->first_token);
}

void	ft_clean_quotes(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	while (node)
	{
		if (node->type == CMD_LITERAL || node->type == CMD_EXPAND)
		{
			if (ft_count_char(node->token, '"') > 0
				|| ft_count_char(node->token, '\'') > 0)
			{
				node->token = ft_strtrim_clean(node->token, "\"\'");
				if (ft_strlen(node->token) == 0)
					node->meta = MTA_NULL_TOKEN;
				if (node->next
					&& (node->next->meta == MTA_ASSIGN
						|| node->next->meta == MTA_ASSIGN_EMPTY))
					ft_null_to_export(&node, prev, mini);
			}
		}
		prev = node;
		node = node->next;
	}
}
