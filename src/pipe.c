/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:36:10 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 07:11:17 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_pids(t_context *context, int *pids)
{
	int		i;
	char	*num;
	int		buffer;

	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &buffer, 0);
		num = ft_itoa((buffer >> 8) & 0x000000ff);
		free(context->envs[context->status_index]);
		context->envs[context->status_index] = ft_strjoin("?=", num);
		free(num);
		i++;
	}
}

void	close_pipes(int **pipefd)
{
	int	a;

	a = 0;
	while (pipefd[a])
	{
		close(pipefd[a][0]);
		close(pipefd[a][1]);
		a++;
	}
}

void	pipe_fork_child(t_context *context, int **pipefd, int i)
{
	if (i > 0)
		dup2(pipefd[i - 1][0], 0);
	if (ft_arr_len(context->pipes) != i + 1 && ft_arr_len(context->pipes) > 1)
		dup2(pipefd[i][1], 1);
	close_pipes(pipefd);
	pre_process(context, 0, pipefd);
}

int	pipe_fork(t_context *context, int **pipefd, int i)
{
	int	pid;

	if (ft_arr_len(context->pipes) > 1 || context->redirects[0].ref)
	{
		if (ft_is_input_exist(context->redirects))
			return (pre_process(context, pipefd[i], pipefd));
		else if (context->redirects[0].ref)
			return (pre_process(context, 0, pipefd));
		else
		{
			pid = fork();
			if (pid == 0)
				pipe_fork_child(context, pipefd, i);
			else
				return (pid);
		}
	}
	else
		pre_process(context, 0, pipefd);
	return (0);
}

void	run_pipe(t_context *context)
{
	int	i;
	int	result;
	int	**pipefd;
	int	*pids;

	result = parser(context);
	if (parse_error_free(context, result))
		return ;
	pids = malloc(sizeof(int) * (ft_arr_len(context->pipes) + 2));
	pipefd = init_pipefd(context);
	i = 0;
	context->process_index = 0;
	while (context->pipes[i])
	{
		if (init_pipes(context, i, result) == 1 || context->ignore_redirect)
			break ;
		context->process_index = i;
		pids[i] = pipe_fork(context, pipefd, i);
		pipe_process_free(context);
		i++;
	}
	context->ignore_redirect = 0;
	pids[i] = 0;
	run_pipe_end(context, pipefd, pids);
}
