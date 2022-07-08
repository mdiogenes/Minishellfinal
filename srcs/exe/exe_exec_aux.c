/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.exec_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:47:43 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/08 12:55:39 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pid_child(t_ms *mini, char **argv)
{
	if (ft_strict_cmp(ft_strrchr(mini->first_token->token,
				'/'), "/minishell") == 0)
	{
		if (argv[2])
			free(argv[2]);
		argv[2] = ft_itoa(mini->pid_child);
	}	
}
