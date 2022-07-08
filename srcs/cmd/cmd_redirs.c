/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:59:49 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 11:06:29 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_data(int in_fd, int out_fd)
{
	char	*line;

	line = get_next_line(in_fd);
	while (line)
	{
		ft_putstr_fd(line, out_fd);
		free (line);
		line = get_next_line(in_fd);
	}
}

int	ft_inp_from_file(t_ms *mini)
{
	int		fd_file;

	fd_file = open(mini->first_token->args->token, O_RDONLY, S_IRWXU);
	if (fd_file < 0 && mini->first_token->status == SILENCED_CHECK)
		return (mini->exitstatus);
	else if (fd_file < 0)
		return (ERROR);
	if (mini->first_token->out == TKN_PIPEOUT)
		ft_get_data(fd_file, MS_STDOUT);
	close(fd_file);
	return (mini->exitstatus);
}

int	ft_dup_file(t_ms *mini)
{
	int		fd_file;
	int		fd;

	if (mini->first_token->type == RDR_TO_FILE)
		fd_file = open(mini->first_token->args->token,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd_file = open(mini->first_token->args->token,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		return (ft_error_handler(errno, mini));
	if (mini->first_token->out == TKN_STDOUT)
		fd = fd_file;
	else
	{
		fd = MS_STDOUT;
		close (fd_file);
	}
	if (mini->first_token->in != TKN_STDIN)
		ft_get_data(STDIN_FILENO, fd);
	close (fd);
	return (mini->exitstatus);
}

static inline void	free_strings(char *rst, char *line)
{
	if (rst)
		free (rst);
	if (line)
		free (line);
}	

int	ft_heredoc(t_ms *mini)
{
	char	*line;
	char	*lim;
	char	*rst;
	size_t	len_lim;

	lim = mini->first_token->args->token;
	len_lim = ft_strlen(lim);
	rst = NULL;
	while (1)
	{
		write(STDIN_FILENO, "\e[32mms-42_heredoc>\e[0m ", 24);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strlen(line) == (len_lim + 1)
			&& ft_strncmp(line, lim, len_lim) == 0)
			break ;
		rst = ft_strjoin_clean(rst, line, 0);
	}
	if (mini->first_token->out == TKN_PIPEOUT)
		ft_putstr_fd(rst, MS_STDOUT);
	free_strings(rst, line);
	return (SUCCESS);
}
