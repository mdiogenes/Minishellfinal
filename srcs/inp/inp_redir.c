/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:52:04 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 10:26:16 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_update_cmd(t_token *node)
{
	node->type = ft_read_from_node(node->token);
	node->meta = ft_get_meta_type(node->type);
	node->args = node->next;
}

static inline void	ft_fix_inp_file(t_token *command, t_token *node, t_ms *mini)
{
	t_token	*tmp;
	char	*cmd;

	tmp = node;
	while (tmp && tmp->type == IMP_FROM_FILE && tmp->next
		&& tmp->next->type == IMP_FROM_FILE && tmp->next->status != FIRST_PIPE)
		tmp = tmp->next;
	if (tmp)
		tmp->out = TKN_PIPEOUT;
	command->next = tmp->next;
	tmp->next = command;
	command->in = TKN_PIPEIN;
	if (command->next && command->next->in == TKN_PIPEIN)
		command->out = TKN_PIPEOUT;
	if (command->meta <= MTA_ARGS)
	{
		command->meta = MTA_OUTEXE;
		cmd = ft_is_bin_exe(command->token, mini, command);
		if (cmd != NULL)
		{
			free(command->token);
			command->token = cmd;
		}
	}
}

static inline void	ft_find_place(t_token *command, t_token *node, t_ms *mini)
{
	if (node->type >= RDR_TO_FILE && node->type <= RDR_APP_FILE)
	{
		command->next = node;
		command->out = TKN_PIPEOUT;
		node->in = TKN_PIPEIN;
		if (node == mini->first_token)
			mini->first_token = command;
	}
	if (node->type == IMP_FROM_FILE)
		ft_fix_inp_file(command, node, mini);
}

static inline void	ft_fix_cmd(t_token *node, t_token **cmd, t_ms *mini)
{
	if (*cmd != NULL)
		node->in = TKN_PIPEIN;
	if (node->next && node->next->type >= RDR_TO_FILE
		&& node->next->type <= RDR_APP_FILE)
		node->out = TKN_PIPEOUT;
	if (ft_size_branch(node->args) > 1)
	{
		if (*cmd == NULL)
		{
			*cmd = node->args->next;
			ft_update_cmd(*cmd);
			ft_find_place(*cmd, node, mini);
		}
		else
			ft_inp_append(&(*cmd)->args, node->args->next);
		node->args->next = NULL;
	}
}

int	ft_inp_redir(t_ms *mini)
{
	t_token	*node;
	t_token	*cmd;
	t_token	*prev;

	node = mini->first_token;
	cmd = NULL;
	prev = NULL;
	while (node)
	{
		if (node->type >= IMP_FROM_FILE && node->type <= IMP_HEREDOC)
		{
			if (node->next)
				node->next->in = TKN_PIPEIN;
		}
		if (node->type >= RDR_TO_FILE && node->type <= IMP_FROM_FILE)
			ft_fix_cmd(node, &cmd, mini);
		if (node->meta >= MTA_BUILDIN && node->meta <= MTA_OUTEXE)
			cmd = node;
		if (node->meta >= MTA_REDIR)
			cmd = NULL;
		prev = node;
		node = node->next;
	}
	return (SUCCESS);
}
