/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:38:16 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:39:32 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_line_argv(t_ms *mini, char *argv[])
{
	char	*rst;
	int		i;

	rst = NULL;
	if (ft_strict_cmp(argv[1], "-c") == 0)
		i = 2;
	else
		i = 1;
	while (argv[i])
	{
		if (rst == NULL)
			rst = ft_strtrim(argv[i], " \n\t");
		else
			rst = ft_strjoin_clean_char(rst,
					ft_strtrim(argv[i], " \n\t"), ' ', 0);
		i++;
	}
	mini->line = rst;
}

char	**ft_get_rst_argv(t_ms *mini, t_token *token, size_t *i)
{
	size_t	size;
	char	**rst;
	int		scn;

	scn = 0;
	size = ft_size_branch(mini->first_token->args) + 1;
	if (ft_strict_cmp(ft_strrchr(token->token, '/'), "/minishell") == 0)
	{
		size += 2;
		scn = 1;
	}
	rst = (char **)malloc(sizeof(char *) * (size + 1));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst[size] = NULL;
	rst[0] = ft_strdup(token->token);
	if (scn == 1)
	{
	rst[1] = ft_strdup("-p");
	rst[2] = ft_strdup("PID");
	*(i) = *(i) + 2;
	}
	*(i) = *(i) + 1;
	return (rst);
}

char	**ft_build_argv(t_ms *mini, t_token *token)
{
	size_t	i;
	t_token	*node;
	char	**rst;

	i = 0;
	rst = ft_get_rst_argv(mini, token, &i);
	node = token->args;
	while (node)
	{
		if (token->status == FROM_EXPAND)
			rst[i] = ft_strjoin(mini->path, token->token);
		else
			rst[i] = ft_strdup(node->token);
		node = node->next;
		i++;
	}
	return (rst);
}

char	**ft_build_arenv(t_ms *mini, t_token *cmd)
{
	int		size;
	size_t	i;
	t_token	*node;
	char	**rst;
	int		scn;

	scn = ft_sct_shlvl(mini);
	size = ft_size_branch(mini->env);
	i = 0;
	rst = (char **)malloc(sizeof(char *) * (size + 1));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst[size] = NULL;
	node = mini->env;
	while (node)
	{
		rst[i] = ft_shlvl_check(cmd->token, node);
		node = node->next;
		i++;
	}
	if (scn == 1)
		ft_unset_shlvl(mini);
	return (rst);
}

int	ft_delete_args(t_token *node)
{
	if (!node)
		return (SUCCESS);
	if (!node->args && !node->next)
		return (ft_delete_node(node));
	if (node->args && node->next)
		return (ft_delete_args(node->args)
			+ ft_delete_args(node->next)
			+ ft_delete_node(node));
	if (!node->args && node->next)
		return (ft_delete_args(node->next)
			+ ft_delete_node(node));
	return (ft_delete_args(node->args)
		+ ft_delete_node(node));
}
