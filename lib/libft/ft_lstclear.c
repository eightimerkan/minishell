/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:10:39 by mcosar            #+#    #+#             */
/*   Updated: 2022/11/24 01:10:42 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*iter;

	iter = *lst;
	while (iter != NULL)
	{
		temp = iter->next;
		del(iter->content);
		free(iter);
		iter = temp;
	}
	*lst = NULL;
}
