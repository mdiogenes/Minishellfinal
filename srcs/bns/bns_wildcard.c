/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:00:37 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 14:55:05 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*ft_files_to_input(DIR *dir, char *pattern)
{
	struct dirent	*files;
	char			*to_rst;
	char			scn;

	to_rst = NULL;
	scn = 0;
	if (ft_strict_cmp(pattern, "*") == 0
		|| ft_count_char(pattern, '*') == ft_strlen(pattern))
		scn = 1;
	while (1)
	{
		files = readdir(dir);
		if (!files)
			break ;
		if (scn == 1 && ft_strncmp(files->d_name, ".", 1) == 0)
			continue ;
		if (ft_regex(files->d_name, pattern) != IS_FALSE)
		{
			to_rst = ft_strjoin_clean(to_rst, " ", 1);
			to_rst = ft_strjoin_clean(to_rst, files->d_name, 1);
		}
	}
	return (to_rst);
}

static inline void	ft_insert_results(t_ms *mini, char *rst, t_token *node)
{
	char	**hits;
	t_token	*end;
	t_token	*new;
	size_t	i;

	hits = ft_split(rst, ' ');
	if (!hits || !hits[0])
		return ;
	ft_sort_str_tab(hits);
	i = 0;
	end = node->next;
	node->next = NULL;
	free(node->token);
	node->token = ft_strdup(hits[0]);
	node->status = FROM_WILDCARD;
	while (hits[++i])
	{
		new = ft_inp_new(ft_strdup(hits[i]), mini);
		new->status = FROM_WILDCARD;
		ft_inp_append(&node, new);
	}
	ft_inp_append(&node, end);
	ft_clear_tabs(hits);
}

static inline int	ft_change_wildcard(t_ms *mini, t_token *cmd, t_token *node)
{
	DIR		*dir;
	char	*rst;
	size_t	i;

	i = 0;
	if (node->status == FROM_WILDCARD || node->meta == MTA_NULL_TOKEN)
		return (IS_FALSE);
	if (node->type == CMD_LITERAL)
		return (IS_FALSE);
	if (ft_bichito(mini, node))
		return (IS_TRUE);
	if (ft_count_char(node->token, '*') == 0)
		return (IS_FALSE);
	dir = opendir(mini->path);
	if (dir == NULL)
		return (ERROR);
	rst = ft_files_to_input(dir, node->token);
	if (rst == NULL)
		return (IS_FALSE);
	ft_insert_results(mini, rst, node);
	free(rst);
	cmd->status = FROM_WILDCARD;
	return (IS_TRUE);
}

int	ft_solve_wildcards(t_ms *mini, t_token *cmd, t_token *node)
{
	if (!node)
		return (IS_FALSE);
	if (!node->args && !node->next)
		return (ft_change_wildcard(mini, cmd, node));
	if (node->args && node->next)
		return (ft_solve_wildcards(mini, cmd, node->args)
			+ ft_solve_wildcards(mini, cmd, node->next)
			+ ft_change_wildcard(mini, cmd, node));
	if (!node->args && node->next)
		return (ft_solve_wildcards(mini, cmd, node->next)
			+ ft_change_wildcard(mini, cmd, node));
	return (ft_solve_wildcards(mini, cmd, node->args)
		+ ft_change_wildcard(mini, cmd, node));
}
