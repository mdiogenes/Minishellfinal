/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:25:12 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 13:47:38 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_null(t_ms *mini)
{
	if (ft_find_envar_export("HOME", mini) == NULL)
	{
		ft_error_comands(ERR_CD, "HOME", MSG_ERR_UNSET, mini);
		return (NULL);
	}
	else
		return (ft_find_envar_export("HOME", mini)->args->token);
}

static char	*ft_get_to_go(t_ms *mini)
{
	t_token	*oldpath;

	if (!mini->first_token->args)
	{
		return (ft_null(mini));
	}
	if (ft_strict_cmp(mini->first_token->args->token, "-") == 0)
	{
		oldpath = ft_find_envar_export("OLDPWD", mini);
		if (oldpath && oldpath->args && oldpath->args->token)
		{
			ft_putstr_fd(oldpath->args->token, MS_STDERR);
			ft_putstr_fd("\n", MS_STDERR);
			return (oldpath->args->token);
		}
		else
			ft_error_comands(ERR_CD, "cd", "OLDPWD not set", mini);
		return (NULL);
	}
	else if (ft_strict_cmp(mini->first_token->args->token, ".") == 0)
		return (mini->path);
	else
		return (mini->first_token->args->token);
}

int	ft_cd(t_ms *mini)
{
	int		move_dir;
	char	*path_to;

	if (ft_size_branch(mini->first_token->args) > 1)
		return (ft_error_comands(ERR_CD, "cd", MSG_MANY_ARG, mini));
	path_to = ft_get_to_go(mini);
	if (path_to == NULL)
	{
		ft_process_branch(mini);
		return (ERROR);
	}
	move_dir = chdir(path_to);
	if (move_dir != 0)
		return (ft_error_handler(errno, mini));
	ft_export_var("OLDPWD", mini->path, mini);
	ft_get_path_prompt(mini);
	ft_export_var("PWD", mini->path, mini);
	ft_process_branch(mini);
	return (SUCCESS);
}
