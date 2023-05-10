/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 03:57:17 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/15 02:58:14 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_on_ctrl_d(char *src, t_context *context)
{
	if (!src)
	{
		free(context->prompt_name);
		ft_arr_free(context->envs);
		printf("exit\n");
		exit(0);
	}
}
