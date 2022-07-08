/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:17:56 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/30 15:53:22 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ms *mini)
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
		if (node->args)
		{
			ft_putstr_fd(node->token, MS_STDERR);
			ft_putstr_fd("=", MS_STDERR);
			ft_putstr_fd(node->args->token, MS_STDERR);
			ft_putstr_fd("\n", MS_STDERR);
		}
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}
