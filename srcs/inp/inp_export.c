/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:42:06 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/28 14:28:33 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_upd_re(t_token *node, t_token *prev)
{
	t_token	*tmp;

	tmp = node->next;
	free (node->token);
	node->token = ft_strdup("\0");
	node->meta = MTA_NULL_TOKEN;
	prev->meta = MTA_TO_EXPORT;
	prev->args = node;
	prev->next = node->next;
	prev->args->next = NULL;
	return (SUCCESS);
}

static inline int	ft_upd_le(t_token *node, t_token *prev, t_token **head)
{
	if (node->next == NULL)
	{
		node->meta = MTA_TO_EXPORT;
		return (SUCCESS);
	}
	node = ft_remove_node(node, prev, head);
	if (node)
	{
		node->token = ft_strjoin_clean("=", node->token, 2);
		node->meta = MTA_TO_EXPORT;
	}
	return (SUCCESS);
}

static inline int	ft_upd_assign(t_token *node, t_token *prev, t_token **head)
{
	if (prev == NULL && node->next == NULL)
	{
		node->meta = MTA_TO_EXPORT;
		return (SUCCESS);
	}
	if (prev == NULL)
		return (ft_upd_le(node, prev, head));
	if (node->next == NULL)
		return (ft_upd_re(node, prev));
	prev->meta = MTA_TO_EXPORT;
	prev->args = node->next;
	prev->next = node->next->next;
	prev->args->next = NULL;
	ft_delete_node(node);
	node = prev;
	return (SUCCESS);
}

static inline void	ft_fix_args(t_token **args, t_token *node, t_token *prev)
{
	node = *args;
	prev = NULL;
	while (node)
	{
		if (node->args)
			node->args->special_tkn = FROM_EXP_ARG;
		if (node->meta == MTA_ASSIGN || node->meta == MTA_ASSIGN_EMPTY)
		{
			if (node->type == CMD_ASSIGN)
				ft_upd_assign(node, prev, args);
			else if (node->type == CMD_ASSIGN_LE)
				ft_upd_le(node, prev, args);
			else if (node->type == CMD_ASSIGN_RE)
				ft_upd_re(node, prev);
			else if (node->type == CMD_ASSIGN_BE)
				node->meta = MTA_TO_EXPORT;
			node = *args;
			prev = NULL;
			continue ;
		}
		node->meta = MTA_TO_EXPORT;
		prev = node;
		node = node->next;
	}
}

int	ft_check_input_export(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;
	t_token	*aux;
	t_token	*prev_aux;

	node = mini->first_token;
	prev = NULL;
	aux = NULL;
	prev_aux = NULL;
	while (node)
	{
		if (node->type == CMD_EXPORT)
			ft_fix_args(&node->args, aux, prev_aux);
		prev = node;
		node = node->next;
	}
	return (SUCCESS);
}
