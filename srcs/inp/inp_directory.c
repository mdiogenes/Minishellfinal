/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_directory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:09:14 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/16 15:14:37 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*ft_directory(int i)
{
	static char	*command[] = {"'", "\"", "$", "pwd", "cd",
		"echo", "export", "unset", "env",
		"exit", "./", "=", " =", " = ",
		"= ", "|", ">", ">>", "<",
		"<<", ";", "||", "&&", "(", ")"};

	return (command[i]);
}

int	ft_read_from_node(char *token)
{
	int			i;
	size_t		len;
	size_t		sizes;

	i = 0;
	len = ft_strlen(token);
	while (ft_directory(i))
	{
		sizes = ft_strlen(ft_directory(i));
		if (len == sizes
			&& ft_strncmp_fnc(token, ft_directory(i), sizes, ft_tolower) == 0)
			return (i + 1);
		if (len > 2 && (i + 1) == CMD_EXE
			&& ft_strncmp_fnc(token, ft_directory(i), sizes, ft_tolower) == 0)
			return (i + 1);
		if (token[0] == '\'' && token[len - 1] == '\'')
			return (CMD_LITERAL);
		if (token[0] == '\"' && token[len - 1] == 34)
			return (CMD_EXPAND);
		if (token[0] == '$')
			return (CMD_ENV_VAR);
		i++;
	}
	return (NO_TYPE);
}

int	ft_get_meta_type(int type)
{
	if (type <= CMD_ENV_VAR)
		return (MTA_ARGS);
	if (type > CMD_ENV_VAR && type <= CMD_EXIT)
		return (MTA_BUILDIN);
	if (type > CMD_EXIT && type <= CMD_EXE)
		return (MTA_OUTEXE);
	if (type >= CMD_ASSIGN && type <= CMD_ASSIGN_LE)
		return (MTA_ASSIGN);
	if (type >= CMD_ASSIGN_BE && type <= CMD_ASSIGN_RE)
		return (MTA_ASSIGN_EMPTY);
	if (type == RDR_PIPE)
		return (MTA_REDIR);
	if (type >= RDR_TO_FILE && type <= IMP_HEREDOC)
		return (MTA_REDIR_FILE);
	if (type == NEXT_CMD)
		return (MTA_NEXT);
	if (type >= OPR_OR && type <= OPR_AND)
		return (MTA_OPERATOR);
	if (type >= OPR_OPEN_K && type <= OPR_CLOSE_K)
		return (MTA_KEYS);
	return (MTA_NOTYPE);
}
