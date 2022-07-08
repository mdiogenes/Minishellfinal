/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_expand_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:45:19 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/05 14:45:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*ft_cdbichito(t_ms *mini)
{
	if (ft_find_envar_export("HOME", mini) == NULL)
		return (mini->homecons);
	else
		return (ft_find_envar_export("HOME", mini)->args->token);
}

int	ft_bichito(t_ms *mini, t_token *node)
{
	char	*temp;

	if (ft_strncmp(node->token, "~/", 2) == 0 && node->type != CMD_EXPAND)
	{
		temp = ft_strdup(ft_cdbichito(mini));
		temp = ft_strjoin_clean(temp, &node->token[1], 1);
		free(node->token);
		node->token = temp;
		return (1);
	}
	if (ft_strict_cmp(node->token, "~") == 0 && node->type != CMD_EXPAND)
	{
		free (node->token);
		node->token = ft_strdup(ft_cdbichito(mini));
		return (1);
	}
	return (0);
}
