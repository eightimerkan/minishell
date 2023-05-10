/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:37:41 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/16 16:29:50 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int	ft_redirect_len(t_redirect *redirects)
{
	int	len;

	len = 0;
	while (redirects[len].ref)
		len++;
	return (len);
}

int	ft_is_input_exist(t_redirect *redirects)
{
	int	len;

	len = 0;
	while (redirects[len].ref)
	{
		if (redirects[len].type == 1 || redirects[len].type == 3)
			return (1);
		len++;
	}
	return (0);
}

int	ft_is_double_input_exist(t_redirect *redirects)
{
	int	len;

	len = 0;
	while (redirects[len].ref)
	{
		if (redirects[len].type == 1)
			return (1);
		len++;
	}
	return (0);
}

int	ft_input_redirect_len(t_redirect *redirects)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (redirects[len].ref)
	{
		if (redirects[len].type == 1 || redirects[len].type == 3)
			index = len;
		len++;
	}
	return (index);
}
