/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:51:22 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/16 15:52:25 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_id_error(t_ms *mini, char *token)
{
	ft_putstr_fd("ms-42 : export `", MS_STDERR);
	ft_putstr_fd(token, MS_STDERR);
	ft_putstr_fd("': not a valid identifier\n", MS_STDERR);
	mini->exitstatus = 1;
	return (ERROR);
}

int	ft_error_export(t_token *token, t_ms *mini)
{
	if (token->type == CMD_ASSIGN)
		return (SUCCESS);
	ft_putstr_fd("ms-42 ", MS_STDERR);
	ft_putstr_fd("export : `", MS_STDERR);
	if (token->type == CMD_ASSIGN_RE)
	{
		if (token->next)
			ft_putstr_fd(token->next->token, MS_STDERR);
	}
	if (token->type == CMD_ASSIGN_LE || token->type == CMD_ASSIGN_BE)
	{
		ft_putstr_fd(token->token, MS_STDERR);
		if (token->next && token->type == CMD_ASSIGN_LE)
			ft_putstr_fd(token->next->token, MS_STDERR);
	}
	ft_putstr_fd("' ", MS_STDERR);
	ft_putstr_fd(MSG_ERR_IDNT, MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	if (token->type == CMD_ASSIGN_BE)
	{
		token->type = CMD_ASSIGN_RE;
		return (ft_error_export(token, mini));
	}
	mini->exitstatus = 1;
	return (ERROR);
}

int	ft_error_export_var(t_token *token, t_ms *mini)
{
	ft_putstr_fd("ms-42 ", MS_STDERR);
	ft_putstr_fd("export : `", MS_STDERR);
	if (token->token)
		ft_putstr_fd(token->token, MS_STDERR);
	if (token->args)
	{
		ft_putstr_fd("=", MS_STDERR);
		ft_putstr_fd(token->args->token, MS_STDERR);
	}
	ft_putstr_fd("' ", MS_STDERR);
	ft_putstr_fd(MSG_ERR_IDNT, MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	mini->exitstatus = 1;
	return (ERROR);
}
