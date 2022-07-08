/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:32:19 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 01:32:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_shlvl(t_ms *mini)
{
	t_token	*env;
	t_token	*prev;

	env = ft_find_envar("SHLVL", &prev, mini);
	ft_delete_env(env, prev, mini);
}

int	ft_sct_shlvl(t_ms *mini)
{
	if (ft_find_envar_export("SHLVL", mini) == NULL)
	{
		ft_export_var("SHLVL", "0", mini);
		return (1);
	}
	return (0);
}

static inline char	*ft_no_shlvl(t_token *env)
{
	char	*rst;

	if (env->args == NULL)
		rst = ft_strdup(env->token);
	else
		rst = ft_strjoin_char(env->token, env->args->token, '=');
	return (rst);
}

static inline int	ft_shlvl_rst(char *value)
{
	int	level;

	level = 0;
	if (ft_send_to_atoi(value) == 1)
	{
		level = ft_atoi(value);
		if (level > 999)
			level = ft_shlvl_err();
		if (level < 0)
			level = -1;
	}
	else
		level = 0;
	return (level);
}

char	*ft_shlvl_check(char *cmd, t_token *env)
{
	char	*rst;
	int		level;
	char	*tmp;

	if (ft_strict_cmp(cmd, "./minishell") != 0
		|| ft_strict_cmp(env->token, "SHLVL") != 0)
		return (ft_no_shlvl(env));
	if (env->args == NULL)
		level = 0;
	else
		level = ft_shlvl_rst(env->args->token);
	tmp = ft_itoa(++level);
	rst = ft_strjoin_char(env->token, tmp, '=');
	free(tmp);
	return (rst);
}
