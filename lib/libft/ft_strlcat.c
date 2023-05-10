/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:12:30 by mcosar            #+#    #+#             */
/*   Updated: 2022/11/24 01:12:31 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j] && j < n)
		j++;
	while ((src[k]) && ((j + k + 1) < n))
	{
		dest[j + k] = src[k];
		k++;
	}
	if (j != n)
		dest[j + k] = '\0';
	return (j + ft_strlen(src));
}
