/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:36:10 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 07:16:47 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_pipes(t_context *context, int i, int result)
{
	int	redirect_result;

	redirect_result = 1;
	context->line = ft_strdup(context->pipes[i]);
	redirect_result = parse_redirections(context);
	if (context->line && context->line[0] && redirect_result)
	{
		context->commands[0] = ft_split_command(context->line, context, 1);
		if (!empty_control(context->line))
		{
			free(context->commands[0][0]);
			free(context->commands[0]);
		}
		if (context->command_error)
		{
			free(context->commands[0]);
			result = 0;
		}
	}
	if (redirect_result == 0 || result == 0 || context->command_error)
	{
		pipe_error_free(context, redirect_result);
		return (1);
	}
	return (0);
}

int	**init_pipefd(t_context *context)
{
	int	**pipefd;
	int	i;

	i = 0;
	pipefd = malloc(sizeof(int) * ft_arr_len(context->pipes) * 3);
	while (i < ft_arr_len(context->pipes))
	{
		pipefd[i] = malloc(sizeof(int) * 3);
		pipe(pipefd[i]);
		i++;
	}
	pipefd[i] = 0;
	return (pipefd);
}

void	free_pipes(int **pipefd, int *pids, t_context *context)
{
	free(pids);
	ft_arr_free(context->pipes);
	ft_pipefds_free(pipefd);
}

void	pipe_process_free(t_context *context)
{
	ft_redirects_free(context);
	if (empty_control(context->line) && context->line[0] && context->commands
		&& context->commands[0] && context->commands[0][0])
		ft_arr_free(context->commands[0]);
	if (context->line[0])
		free(context->line);
}

void	pipe_error_free(t_context *context, int redirect_result)
{
	printf("parse error\n");
	if (redirect_result)
		ft_redirects_free(context);
	if (empty_control(context->line) && !context->command_error
		&& context->commands && context->commands[0] && context->commands[0][0])
		ft_arr_free(context->commands[0]);
	if (context->line)
		free(context->line);
	context->command_error = 0;
}
