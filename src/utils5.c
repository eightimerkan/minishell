/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:08:58 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 01:03:31 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_directory(char *str)
{
	int	fd;

	fd = open(str, O_DIRECTORY);
	if (fd == -1)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

void	update_status(t_context *context, int pid)
{
	int		status;
	char	*num;

	waitpid(pid, &status, 0);
	num = ft_itoa((status >> 8) & 0x000000ff);
	free(context->envs[context->status_index]);
	context->envs[context->status_index] = ft_strjoin("?=", num);
	free(num);
}

int	check_line_is_empty(t_context *context)
{
	int	i;
	int	is_match;

	i = 0;
	is_match = 0;
	while (context->base_line[i])
	{
		if (!((context->base_line[i] <= 13 && context->base_line[i] >= 9)
				|| context->base_line[i] == 32))
			is_match = 1;
		i++;
	}
	if (!is_match)
		return (1);
	return (0);
}

void	close_pipes_except_output(int **pipefd)
{
	int	a;

	a = 0;
	while (pipefd[a + 1])
	{
		close(pipefd[a][1]);
		a++;
	}
}

void	update_status_without_pid(t_context *context, int status)
{
	char	*num;

	num = ft_itoa(status);
	free(context->envs[context->status_index]);
	context->envs[context->status_index] = ft_strjoin("?=", num);
	free(num);
}
