/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:36:10 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 07:04:21 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_error_free(t_context *context, int result)
{
	if (result == 0)
	{
		ft_arr_free(context->pipes);
		printf("parse error\n");
		return (1);
	}
	return (0);
}

void	run_pipe_end(t_context *context, int **pipefd, int *pids)
{
	close_pipes(pipefd);
	wait_pids(context, pids);
	free_pipes(pipefd, pids, context);
}
