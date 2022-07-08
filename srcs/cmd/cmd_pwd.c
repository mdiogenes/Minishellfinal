/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:21:15 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/17 15:36:14 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_ms *mini)
{
	ft_putendl_fd(mini->path, MS_STDOUT);
	ft_process_branch(mini);
	mini->exitstatus = 0;
	return (SUCCESS);
}
