/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:56:30 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/28 14:18:08 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_token	*ft_new_env(char *token, t_ms *mini)
{
	t_token	*rst;

	rst = (t_token *)malloc(sizeof(t_token));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst->token = token;
	rst->type = 0;
	rst->meta = 0;
	rst->in = 0;
	rst->out = 0;
	rst->next = NULL;
	rst->args = NULL;
	return (rst);
}

t_token	*ft_find_envar_export(char *needle, t_ms *mini)
{
	t_token	*node;
	size_t	len;

	node = mini->env;
	while (node)
	{
		len = ft_strlen(node->token);
		if (len == ft_strlen(needle)
			&& ft_strncmp(node->token, needle, len) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	ft_export_var(char *var, char *val, t_ms *mini)
{
	t_token	*new;
	t_token	*dst;

	dst = ft_find_envar_export(var, mini);
	if (dst == NULL)
	{
		new = ft_new_env(ft_strdup(var), mini);
		if (val != NULL)
			new->args = ft_new_env(ft_strdup(val), mini);
		ft_env_sort(&mini->env, new);
	}
	else
	{
		if (val == NULL)
			return ;
		ft_delete_node(dst->args);
		dst->args = ft_new_env(ft_strdup(val), mini);
	}
	if (ft_strict_cmp(var, "PATH") == 0)
	{
		ft_clear_tabs(mini->bin_paths);
		mini->bin_paths = ft_split(val, ':');
	}
}

int	ft_env_to_list(char **env, t_ms *mini)
{
	char	**var;
	t_token	*new;
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strrchr(env[i], '=') == NULL)
			new = ft_new_env(ft_strdup(env[i]), mini);
		else
		{
			var = ft_split(env[i], '=');
			new = ft_new_env(ft_strdup(var[0]), mini);
			new->type = SYS_VAR;
			if (ft_strict_cmp(new->token, "OLDPWD") != 0)
				new->args = ft_new_env(ft_strdup(var[1]), mini);
			ft_clear_tabs(var);
		}
		ft_env_sort(&mini->env, new);
		i++;
	}
	return (SUCCESS);
}
