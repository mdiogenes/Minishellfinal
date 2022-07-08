/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:30:40 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 11:33:35 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_tabs(char **tab)
{
	size_t	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
	{
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
}
