/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:29:28 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 10:20:07 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_print_vars(t_ms *mini)
{
	t_token	*node;

	node = mini->env;
	while (node)
	{
		if (node->type == SYS_HIDDEN)
		{
			node = node->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", MS_STDERR);
		ft_putstr_fd(node->token, MS_STDERR);
		if (node->args)
		{
			ft_putstr_fd("=\"", MS_STDERR);
			ft_putstr_fd(node->args->token, MS_STDERR);
			ft_putstr_fd("\"", MS_STDERR);
		}
		ft_putstr_fd("\n", MS_STDERR);
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}

int	ft_export_cmd(t_ms *mini)
{
	t_token	*token;
	char	*value;

	if (!mini->first_token->args)
		return (ft_print_vars(mini));
	token = mini->first_token->args;
	while (token)
	{
		if (ft_var_valid_name(token->token[0]) == IS_FALSE)
			ft_export_id_error(mini, token->token);
		else
		{
			if (token->args)
			value = token->args->token;
			else
				value = NULL;
			ft_export_var(token->token, value, mini);
		}
		token = token->next;
	}
	ft_process_branch(mini);
	return (mini->exitstatus);
}
