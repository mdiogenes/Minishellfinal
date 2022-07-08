/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:17 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 10:33:17 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_error(t_ms *mini, char token, int rpt)
{
	ft_putstr_fd("ms-42 : syntax error near unexpected token `", MS_STDERR);
	if (token == '\n')
		ft_putstr_fd("newline", MS_STDERR);
	else
	{
		while (rpt--)
			ft_putchar_fd(token, MS_STDERR);
	}
	ft_putstr_fd("'\n", MS_STDERR);
	mini->exitstatus = 258;
	return (ERROR);
}

int	ft_error_unset_var(char *msg, t_token *token, t_ms *mini)
{
	ft_putstr_fd("ms-42 ", MS_STDERR);
	ft_putstr_fd("unset : `", MS_STDERR);
	if (token->token)
		ft_putstr_fd(token->token, MS_STDERR);
	if (token->args)
	{
		ft_putstr_fd("=", MS_STDERR);
		ft_putstr_fd(token->args->token, MS_STDERR);
	}
	ft_putstr_fd("' ", MS_STDERR);
	ft_putstr_fd(msg, MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	mini->exitstatus = 1;
	ft_process_branch(mini);
	return (mini->exitstatus);
}

int	ft_error_handler(int error, t_ms *mini)
{
	if (error == 0)
		return (ERROR);
	ft_putstr_fd("ms-42 Error: ", MS_STDERR);
	ft_putstr_fd(strerror(error), MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	ft_process_branch(mini);
	mini->exitstatus = 1;
	return (ERROR);
}

void	ft_error_general(char *msg, t_ms *mini)
{
	ft_putstr_fd("ms-42 Error:", MS_STDERR);
	ft_putstr_fd(msg, MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	ft_free_exit(mini);
	mini->exitstatus = 1;
	exit (mini->exitstatus);
}
