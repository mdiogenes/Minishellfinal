/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_comands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:04:14 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/05 16:33:03 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_putstr_end_comand(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, MS_STDERR);
	ft_putstr_fd(" : ", MS_STDERR);
	ft_putstr_fd(msg, MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
}

static inline long long int	ft_error_empty_exec(t_ms *mini, char *cmd)
{
	ft_putstr_fd("ms-42 : ", MS_STDERR);
	ft_putstr_fd(cmd, MS_STDERR);
	if (mini->first_token->status == FROM_NO_PATH)
		ft_putstr_fd(": No such file or directory\n", MS_STDERR);
	else
		ft_putstr_fd(": command not found\n", MS_STDERR);
	mini->exitstatus = 127;
	ft_process_branch(mini);
	return (127);
}

int	ft_error_comands(int error, char *cmd, char *msg, t_ms *mini)
{
	size_t	size;

	if (error == ERR_CMD)
		return (ft_error_empty_exec(mini, cmd));
	size = ft_strlen(msg);
	ft_putstr_fd("ms-42: ", MS_STDERR);
	if (error == ERR_CD)
		mini->exitstatus = 1;
	if (error == ERR_PIPE)
		mini->exitstatus = 2;
	if (error == ERR_GEN)
		mini->exitstatus = 258;
	if (error == ERR_EXIT)
	{
		if (ft_strncmp(msg, MSG_MANY_ARG, size))
			mini->exitstatus = 255;
		if (ft_strncmp(msg, MSG_NUM_ARG, size))
			mini->exitstatus = 1;
	}
	ft_putstr_end_comand(cmd, msg);
	ft_process_branch (mini);
	return (mini->exitstatus);
}
