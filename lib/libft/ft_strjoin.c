/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:03:59 by mcosar            #+#    #+#             */
/*   Updated: 2023/02/28 22:07:49 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		s1len;
	int		s2len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	i = 0;
	new = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!new)
		return (0);
	while (i < s1len + s2len)
	{
		if (i < s1len)
			new[i] = *s1++;
		else
			new[i] = *s2++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
