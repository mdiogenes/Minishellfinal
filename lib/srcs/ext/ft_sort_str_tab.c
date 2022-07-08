/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_str_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 22:45:37 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/06 22:45:40 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_str_tab(char **tab)
{
	int		i;
	int		k;
	char	*temp;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != 0)
	{
		k = i;
		while (tab[k] != 0)
		{
			if (ft_strcmp(tab[i], tab[k]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[k];
				tab[k] = temp;
			}
			k++;
		}
		i++;
	}
}
