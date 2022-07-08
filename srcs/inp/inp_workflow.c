/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_workflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:33:06 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 10:50:55 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_workflow_params(t_token *node)
{
	t_token	*args;

	if (node->next->meta > MTA_ARGS)
		return ;
	node->args = node->next;
	args = node->next;
	while (args)
	{
		if (args->next && args->next->meta > MTA_ARGS)
			break ;
		args = args->next;
	}
	if (args)
	{
		node->next = args->next;
		args->next = NULL;
	}
	else
		node->next = NULL;
}

static inline void	ft_workflow_rdr(t_token *node, t_token *prev)
{
	if (node->type == RDR_TO_FILE || node->type == RDR_APP_FILE)
	{
		if (prev && prev->meta >= MTA_BUILDIN && prev->meta <= MTA_OUTEXE)
		{
			prev->out = TKN_PIPEOUT;
			node->in = TKN_PIPEIN;
		}
		if (prev && prev->out == TKN_PIPEOUT)
			node->in = TKN_PIPEIN;
		if (node->in && node->next && (node->next->type == RDR_TO_FILE
				|| node->next->type == RDR_APP_FILE))
			node->out = TKN_PIPEOUT;
	}
	else if ((node->type == IMP_FROM_FILE
			|| node->type == IMP_HEREDOC) && node->next)
		node->out = TKN_PIPEOUT;
}

static inline void	ft_workflow_redir(t_ms *mini, t_token *node, t_token *prev)
{
	while (node)
	{	
		if (node->meta >= MTA_REDIR_FILE && node->meta <= MTA_REDIR)
		{
			if (node->type == RDR_PIPE)
			{
				if (prev)
					prev->out = TKN_PIPEOUT;
				if (node->next)
				{
					node->next->in = TKN_PIPEIN;
					node->next->status = FIRST_PIPE;
				}
				node = ft_remove_node(node, prev, &mini->first_token);
				continue ;
			}
			else if (node->type == IMP_FROM_FILE || node->type == IMP_HEREDOC
				|| node->type == RDR_TO_FILE || node->type == RDR_APP_FILE)
				ft_workflow_rdr(node, prev);
		}
		prev = node;
		node = node->next;
	}
}

static inline void	ft_workflow_order(t_ms *mini)
{
	t_token	*prev;
	t_token	*aux;
	t_token	*node;

	node = mini->first_token;
	prev = NULL;
	while (node)
	{
		if (node->next && (node->type != IMP_FROM_FILE
				&& node->type != IMP_HEREDOC)
			&& (node->next->type == IMP_FROM_FILE
				|| node->next->type == IMP_HEREDOC))
		{
			if (prev != NULL)
				prev->next = node->next;
			else
				mini->first_token = node->next;
			aux = node->next->next;
			node->next->next = node;
			node->next = aux;
		}
		prev = node;
		node = node->next;
	}
}

int	ft_workflow(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	prev = NULL;
	if (ft_input_preprocess(mini) == ERROR)
		return (ERROR);
	ft_clean_quotes(mini);
	node = mini->first_token;
	if (!node)
		return (ERROR);
	while (node)
	{
		if (node->next && ((node->next->meta <= MTA_ARGS
					&& node->meta <= MTA_OUTEXE)
				|| (node->meta == MTA_REDIR_FILE)))
			ft_workflow_params(node);
		node = node->next;
	}
	ft_workflow_order(mini);
	ft_check_input_export(mini);
	ft_workflow_redir(mini, mini->first_token, prev);
	ft_inp_redir(mini);
	ft_workflow_check(mini);
	return (SUCCESS);
}
