/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_bns_open_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:28:29 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/01 11:41:58 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_brakets(t_ms *mini)
{
	t_token	*node;
	int		opened;
	int		closed;

	opened = 0;
	closed = 0;
	node = mini->first_token;
	while (node)
	{
		if (node->type == OPR_OPEN_K)
			opened++;
		if (node->type == OPR_CLOSE_K)
			closed++;
		node = node->next;
	}
	return (opened - closed);
}

int	ft_open_brakets(t_ms *mini)
{
	if (mini->line)
		free (mini->line);
	mini->line = readline("\e[32mms-42_brakets>\e[0m ");
	if (!mini->line)
		return (ft_error_comands(ERR_GEN, MSG_SYNTAX, MSG_ERR_EOF, mini));
	return (ft_load_input(mini));
}

int	ft_open_logic(t_ms *mini)
{
	if (mini->line)
		free (mini->line);
	mini->line = readline("\e[32mms-42_logic>\e[0m ");
	if (!mini->line)
		return (ft_error_comands(ERR_GEN, MSG_SYNTAX, MSG_ERR_EOF, mini));
	return (ft_load_input(mini));
}
