/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 00:27:30 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:24:17 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_node(t_ms *mini, t_token *node)
{
	int		i;
	char	**rst;
	char	*tmp;

	i = 0;
	ft_do_expand(mini, node);
	if (node->special_tkn == FROM_EXP_ARG)
		return (SUCCESS);
	if (ft_strict_cmp(node->token, "\0") == 0)
		return (SUCCESS);
	rst = ft_split(node->token, ' ');
	tmp = NULL;
	while (rst[i])
	{
		if (tmp == NULL)
			tmp = ft_strdup(rst[i]);
		else
			tmp = ft_strjoin_clean_char(tmp, ft_strdup(rst[i]), ' ', 0);
		i++;
	}
	if (node->token)
		free (node->token);
	node->token = tmp;
	ft_clear_tabs(rst);
	return (SUCCESS);
}
