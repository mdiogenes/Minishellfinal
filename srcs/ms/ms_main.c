/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:34 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:41:56 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_process_inputs(t_ms *mini)
{
	if (mini->first_token == NULL)
		return (ERROR);
	while (mini->first_token)
		ft_token_dir(mini);
	ft_clear_nodes(mini);
	return (SUCCESS);
}

static inline int	ft_parser_process(t_ms *mini)
{
	if (ft_parse(mini) == ERROR)
	{
		ft_clear_nodes(mini);
		return (ERROR);
	}
	if (mini->first_token == NULL)
		return (ERROR);
	ft_process_inputs(mini);
	return (mini->exitstatus);
}

static inline int	ft_get_input(t_ms *mini, int argc, char *argv[])
{
	using_history();
	while (mini->status == 1)
	{
		ft_get_path_prompt(mini);
		if (mini->line)
			free(mini->line);
		if (argc > 2 && ft_strict_cmp(argv[1], "-c") == 0)
			ft_get_line_argv(mini, argv);
		else
			mini->line = readline(mini->prompt);
		if (!mini->line)
			signal_ctrld(mini);
		if (mini->line)
		{
			add_history(mini->line);
			ft_parser_process(mini);
		}
		if (argc > 2 && ft_strict_cmp(argv[1], "-c") == 0)
			mini->status = 0;
	}
	return (mini->exitstatus);
}

int	main(int argc, char *argv[], char **envp)
{
	t_ms	mini;
	t_token	*home;

	if (ft_init_minishell(&mini) == ERROR)
		ft_error_general("Init error: main struct could not be init", &mini);
	mini_getpid(&mini, 0);
	if (argv[2] && ft_strict_cmp(argv[1], "-p") == 0)
		mini.pid = ft_atoi(argv[2]);
		g_mini = &mini;
	if (ft_env_to_list(envp, &mini) == ERROR)
		ft_error_general("Initerror:env variables could not be loaded", &mini);
	home = ft_find_envar_export("HOME", &mini);
	if (home)
		mini.homecons = ft_strdup(home->args->token);
	else
		ft_error_general("Initerror:env variables could not be loaded", &mini);
	if (ft_get_bin_paths(&mini) == ERROR)
		ft_error_general("Init error: bin paths could not be loaded", &mini);
	if (set_signal(&mini) == ERROR)
		return (ERROR);
	ft_get_input(&mini, argc, argv);
	return (mini.exitstatus);
}	
