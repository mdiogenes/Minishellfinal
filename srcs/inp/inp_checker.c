/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:25:23 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 10:54:45 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_imp_file_test(t_token *token, t_ms *mini)
{
	int	fd_file;

	if (token->args)
	{
		fd_file = open(mini->first_token->args->token,
				O_EVTONLY | O_RDWR, S_IRWXU);
		if (fd_file < 0)
			return (ft_redir_error(errno, token->args->token, mini));
		close (fd_file);
	}
	return (SUCCESS);
}

static inline void	ft_update_branch(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	while (node && node->next && node->next->meta <= MTA_REDIR
		&& node->status != FIRST_PIPE)
	{
		node->status = SILENCED_CHECK;
		node = node->next;
	}
	if (node && node->status != FIRST_PIPE && node->next == NULL)
		node->status = SILENCED_CHECK;
}

int	ft_check_branch(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	while (node && (!node->next
			|| (node->next && node->next->meta <= MTA_REDIR)))
	{
		if (node->type == IMP_FROM_FILE)
		{
			if (ft_imp_file_test(node, mini) == ERROR)
			{
				ft_update_branch(mini);
				mini->exitstatus = 1;
				return (ERROR);
			}
		}
		node = node->next;
	}
	return (SUCCESS);
}
