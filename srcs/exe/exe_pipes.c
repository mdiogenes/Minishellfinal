/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:21:52 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 10:29:14 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_count_pipes(t_ms *mini)
{
	t_token	*token;
	int		i;

	i = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		i++;
		token = token->next;
	}
	if (i < 2)
		return (1);
	return (i - 1);
}

static inline int	**ft_build_pipes(int n, t_ms *mini)
{
	int	**rst;

	rst = (int **)malloc(sizeof(int *) * n);
	if (!rst)
		ft_error_free(errno, mini);
	while (n--)
		rst[n] = (int *)malloc(sizeof(int) * 2);
	return (rst);
}

static inline void	ft_deal_pipes(t_token *token, t_ms *mini, int n)
{
	if (token->in == TKN_PIPEIN)
		close(mini->pipes[n - 1][PIPE_READ]);
	if (token->out == TKN_PIPEOUT)
		close(mini->pipes[n][PIPE_WRITE]);
}

int	ft_pipes(t_ms *mini)
{
	t_token	*token;
	int		n;
	int		total;
	pid_t	child;

	total = ft_count_pipes(mini);
	mini->pipes = ft_build_pipes(ft_count_pipes(mini), mini);
	n = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		if (token->out == TKN_PIPEOUT)
			pipe(mini->pipes[n]);
		child = ft_fork_and_run(mini, n, NULL, NULL);
		if (child == -1)
			return (ERROR);
		ft_deal_pipes(token, mini, n);
		ft_process_branch(mini);
		token = mini->first_token;
		n++;
	}
	close(mini->pipes[n - 2][PIPE_READ]);
	ft_child_monitor(mini, total + 1, child);
	return (SUCCESS);
}
