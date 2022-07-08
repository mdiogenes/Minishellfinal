/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:28:46 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/30 23:28:50 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnstr_len(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	len_needle;
	char	*sheaf;

	if (haystack == needle)
		return (len);
	i = 0;
	len_needle = ft_strlen(needle);
	sheaf = (char *)haystack;
	if (len_needle == 0)
		return (0);
	while (sheaf[i] && i < len)
	{
		if (sheaf[i] == needle[0])
		{
			k = 0;
			while (sheaf[i + k] && sheaf[i + k] == needle[k] && i + k < len)
				k++;
			if (k == len_needle)
				return (i);
		}
		i++;
	}
	return (0);
}
