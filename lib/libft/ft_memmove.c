/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:11:41 by mcosar            #+#    #+#             */
/*   Updated: 2022/11/24 01:11:42 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*sr;
	char	*dst;
	size_t	i;

	i = 0;
	dst = dest;
	sr = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		while (len--)
		{
			dst[len] = sr[len];
		}
	}
	else
	{
		while (len--)
		{
			dst[i] = sr[i];
			i++;
		}
	}
	return (dst);
}
