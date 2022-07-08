/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_getpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:53:10 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/08 12:26:44 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_getpid(t_ms *mini, int padrehijo)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_error_handler(0, mini);
		ft_free_exit(mini);
		exit (ERROR);
	}
	if (!pid)
	{
		ft_free_exit(mini);
		exit (ERROR);
	}
	waitpid(pid, NULL, 0);
	if (padrehijo == 0)
	{
		mini->pid = pid -1;
		mini->pid_child = pid -1;
	}
	else
		mini->pid_child = pid -1;
	return (SUCCESS);
}
