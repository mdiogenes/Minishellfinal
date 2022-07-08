/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_workflow_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:15:46 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 11:57:39 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_workflow_cases(t_ms *mini, t_token *token, t_token *prev)
{
	t_token	*next;

	next = token->next;
	if (!prev && !token)
		return (ERROR);
	if (token->type == IMP_FROM_FILE
		&& next && next->meta == MTA_REDIR_FILE && !next->args)
		return (ft_syntax_error(mini, token->token[0], 1));
	if (token->type == IMP_FROM_FILE && !token->args)
		return (ft_syntax_error(mini, '\n', 1));
	if (!prev && token->meta == MTA_OPERATOR)
		return (ft_syntax_error(mini, token->token[0], 2));
	if (token->type == OPR_CLOSE_K
		&& (!prev || (prev && prev->type == OPR_OPEN_K)))
		return (ft_syntax_error(mini, token->token[0], 1));
	if (next && (token->meta == MTA_REDIR_FILE && next->meta == MTA_REDIR_FILE
			&& (!token->args || !next->args)))
		return (ft_syntax_error(mini, token->token[0], 1));
	return (SUCCESS);
}

void	ft_workflow_check(t_ms *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->first_token;
	prev = NULL;
	while (token)
	{
		if (ft_workflow_cases(mini, token, prev) == ERROR)
		{
			ft_clear_nodes(mini);
			return ;
		}
		prev = token;
		token = token->next;
	}
}
