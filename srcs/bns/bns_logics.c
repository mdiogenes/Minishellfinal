/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_logics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:38:59 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/16 21:39:03 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_operator(t_ms *mini)
{
	if (mini->first_token->type == OPR_OR && mini->exitstatus > 0)
		return (ft_process_branch(mini));
	if (mini->first_token->type == OPR_AND && mini->exitstatus == 0)
		return (ft_process_branch(mini));
	if (mini->first_token->next)
	{
		ft_process_branch(mini);
		ft_process_branch(mini);
	}
	return (ERROR);
}
