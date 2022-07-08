/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_child_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:31:02 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 14:19:30 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_signals_msg(int signum)
{
	static char		*msg[] = {"", "SIGINT", "SIGNAL2",
		"SIGFPE", "", "", "Bus error", "Segmentation fault",
		"SIGPIPE", "SIGALARM", "", "SIGUSR1", "SIGUSR2"};
	char			*sign;

	if (signum == 2)
		return ;
	sign = ft_itoa(signum);
	ft_putstr_fd("[ms-42 ", MS_STDERR);
	ft_putstr_fd(msg[signum], MS_STDERR);
	ft_putstr_fd(" : ", MS_STDERR);
	ft_putstr_fd(sign, MS_STDERR);
	ft_putstr_fd("]\n", MS_STDERR);
	if (sign)
		free(sign);
}
