/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_rare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:30:41 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/30 11:45:11 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_fork_err(t_ms *mini)
{
	ft_putstr_fd("ms-42 : fork: Resource temporarily unavailable\n",
		MS_STDERR);
	mini->exitstatus = 1;
	ft_clear_nodes(mini);
	return (-1);
}

int	ft_shlvl_err(void)
{
	ft_putstr_fd("ms-42 : shell level too high. It will be restored to 1\n",
		MS_STDERR);
	return (SUCCESS);
}

int	ft_error_free(int error, t_ms *mini)
{
	ft_putstr_fd("ms-42 Error:", MS_STDERR);
	ft_putstr_fd(strerror(error), MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	ft_free_exit(mini);
	mini->exitstatus = 1;
	exit (mini->exitstatus);
	return (mini->exitstatus);
}

int	ft_redir_error(int error, char *name, t_ms *mini)
{
	if (error == 0)
		return (ERROR);
	ft_putstr_fd("ms-42 Error: ", MS_STDERR);
	ft_putstr_fd(name, MS_STDERR);
	ft_putstr_fd(" : ", MS_STDERR);
	ft_putstr_fd(strerror(error), MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	mini->exitstatus = 1;
	return (ERROR);
}
