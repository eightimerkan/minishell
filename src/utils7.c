/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:08:58 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:51:08 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_input_signal(t_context *context, char **lines, char *str, int j)
{
	update_status_without_pid(context, 1);
	context->ignore_redirect = 1;
	free(str);
	lines[j] = 0;
	ft_arr_free(lines);
}
