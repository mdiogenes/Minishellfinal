/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:48:21 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/08 13:30:29 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_echo_print_token(t_token *args, int n, int opcio)
{
	if ((ft_strncmp(args->token, "-n", 2) != 0) || n == 1)
	{
		ft_putstr_fd(args->token, MS_STDOUT);
		n = 1;
	}
	if (args->next && (opcio == 0 || n == 1))
	{
		if (args->meta == MTA_NULL_TOKEN)
			return (n);
		if ((args->next->meta != MTA_NULL_TOKEN)
			|| (args->next->meta == MTA_NULL_TOKEN
				&& args->next->special_tkn == 1))
			ft_putstr_fd(" ", MS_STDOUT);
	}
	return (n);
}

static inline int	ft_echo_args(t_token *args, int opcio, int n)
{
	int		i;

	opcio = 2;
	while (args)
	{
		if (args->token != NULL)
		{
			if ((ft_strncmp(args->token, "-n", 2) == 0) && n == 0)
			{
				i = 2;
				while (args->token[i] && args->token[i] == 'n')
					i++;
				if (!args->token[i])
					opcio = opcio + 1;
				else
				n = 1;
			}
			n = ft_echo_print_token(args, n, opcio);
		}
		args = args->next;
	}
	return (opcio);
}

int	ft_echo(t_ms *mini)
{
	int		opcio;
	int		n;

	n = 0;
	opcio = 0;
	opcio = ft_echo_args(mini->first_token->args, opcio, n);
	if (opcio % 2 == 0)
		ft_putstr_fd("\n", MS_STDOUT);
	ft_process_branch(mini);
	return (SUCCESS);
}
