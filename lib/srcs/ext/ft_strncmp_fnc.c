/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_fnc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:48:23 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 10:48:28 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_fnc(char *s1, char *s2, size_t n, int (*str_to)(int))
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && (s1[i] || s2[i]))
	{
		if (str_to(s1[i]) != str_to(s2[i]))
			return (str_to(s1[i]) != str_to(s2[i]));
		i++;
	}
	return (str_to(s1[i]) != str_to(s2[i]));
}
