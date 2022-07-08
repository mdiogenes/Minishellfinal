/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:28:40 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/06 13:15:57 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	all_isdigit(t_token *token)
{
	int	n;

	n = ft_strlen(token->token) - 1;
	while (n > 0 && ft_isdigit(token->token[n]))
		n--;
	return (ft_isdigit(token->token[n]));
}

int	check_args(t_token *token, int size, t_ms *mini)
{
	int	temp;

	temp = 0;
	while (token)
	{
		if (all_isdigit(token) || token->token[0] == '-')
		{	
			temp = 1;
			if (ft_send_to_atoi(token->token) == 1)
				mini->exitstatus = ft_atoi(token->token);
			else
				exit(ft_error_comands(ERR_EXIT,
						mini->first_token->token, MSG_NUM_ARG, mini));
		}
		else if (temp == 0)
		{
			ft_putstr_fd("exit\n", MS_STDERR);
			exit(ft_error_comands(ERR_EXIT,
					mini->first_token->token, MSG_NUM_ARG, mini));
		}
		token = token->next;
		size ++;
	}
	return (size);
}

static inline int	normalize_number_exit(t_ms *mini)
{
	int	n;

	n = 0;
	if (mini->exitstatus >= 256)
		n = (mini->exitstatus - ((mini->exitstatus / 256) * 256));
	if (mini->exitstatus < 0)
		n = (256 - (((mini->exitstatus / 256) * 256) - mini->exitstatus));
	if (mini->exitstatus < 256 && mini->exitstatus >= 0)
		n = mini->exitstatus;
	return (n);
}

int	ft_exit(t_ms *mini)
{
	t_token	*token;
	size_t	size;

	size = 0;
	token = mini->first_token->args;
	size = check_args(token, size, mini);
	if (size == 0)
	{
		mini->exitstatus = 0;
		ft_free_exit(mini);
		exit(mini->exitstatus);
	}
	if (size == 1)
	{
		mini->exitstatus = normalize_number_exit(mini);
		ft_free_exit(mini);
		exit(mini->exitstatus);
	}
	if (size > 1)
		ft_error_comands(ERR_EXIT, mini->first_token->token,
			MSG_MANY_ARG, mini);
	return (mini->exitstatus);
}
