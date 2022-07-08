/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_cleaning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:27:39 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/20 17:39:53 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_delete_node(t_token *node)
{
	if (!node)
		return (SUCCESS);
	if (node->token)
		free (node->token);
	node->next = NULL;
	node->prev = NULL;
	node->args = NULL;
	free (node);
	return (SUCCESS);
}

int	ft_process_branch(t_ms *mini)
{
	t_token	*node;

	if (!mini->first_token)
		return (SUCCESS);
	node = mini->first_token;
	ft_delete_args(node->args);
	mini->first_token = node->next;
	if (mini->last_token == node)
		mini->last_token = NULL;
	ft_delete_node(node);
	return (SUCCESS);
}

t_token	*ft_remove_node(t_token *node, t_token *prev, t_token **head)
{
	t_token	*rst;

	if (!node)
		return (NULL);
	if (prev == NULL)
		*head = node->next;
	else
		prev->next = node->next;
	rst = node->next;
	if (rst)
		rst->prev = prev;
	ft_delete_args(node->args);
	ft_delete_node(node);
	return (rst);
}

void	ft_clear_nodes(t_ms *mini)
{
	t_token	*node;

	if (mini->first_token)
	{
		while (mini->first_token)
		{
			node = mini->first_token->next;
			ft_process_branch(mini);
			mini->first_token = node;
		}
		mini->last_token = NULL;
	}
}
