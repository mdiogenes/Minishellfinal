/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:30:44 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/22 13:46:09 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_branch(t_token *lst)
{
	t_token	*node;
	int		i;

	if (lst == NULL)
		return (0);
	node = lst;
	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

size_t	ft_count_node(t_ms *mini)
{
	size_t	i;
	t_token	*node;

	i = 0;
	node = mini->first_token;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

void	ft_inp_append(t_token **lst, t_token *new)
{
	t_token	*node;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
		new->prev = node;
	}
}

void	ft_new_token(t_ms *mini, t_token *new)
{
	ft_inp_append(&mini->first_token, new);
	new->special_tkn = mini->status_tkn;
	mini->status_tkn = 0;
	mini->last_token = new;
}

t_token	*ft_inp_new(char *cmd, t_ms *mini)
{
	t_token	*rst;

	if (cmd == NULL)
		return (NULL);
	rst = (t_token *)malloc(sizeof(t_token));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst->token = cmd;
	rst->type = ft_read_from_node(cmd);
	rst->meta = ft_get_meta_type(rst->type);
	rst->in = TKN_STDIN;
	rst->out = TKN_STDOUT;
	rst->status = FROM_PARSE;
	rst->next = NULL;
	rst->prev = NULL;
	rst->args = NULL;
	return (rst);
}
