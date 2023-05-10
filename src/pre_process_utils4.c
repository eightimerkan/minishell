/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:12:04 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_output_command_direct_child(t_context *context, int pipefd1[2])
{
	close(pipefd1[0]);
	dup2(pipefd1[1], 1);
	close(pipefd1[1]);
	if (empty_control(context->line) && context->line[0] && context->commands
		&& context->commands[0])
		process_command(context);
	exit(0);
}

void	process_output_command_direct_parent(t_temp5 *temp)
{
	int		byte_read;
	char	*buffer;
	char	*str;

	buffer = malloc(sizeof(char) * 11);
	byte_read = 1;
	while (byte_read)
	{
		byte_read = read(temp->pipefd1[0], buffer, 10);
		if (byte_read <= 0)
			break ;
		buffer[byte_read] = 0;
		str = ft_strjoin(temp->out_content, buffer);
		free(temp->out_content);
		temp->out_content = str;
		ft_bzero(buffer, 11);
	}
	free(buffer);
	close(temp->pipefd1[0]);
}

void	process_output_command_direct(t_context *context, t_temp5 *temp)
{
	int	pid;

	if (context->process_index == 0)
	{
		pid = fork();
		if (pid == 0)
			process_output_command_direct_child(context, temp->pipefd1);
		else
		{
			waitpid(pid, 0, 0);
			close(temp->pipefd1[1]);
			close(temp->pipefd[0]);
			close(temp->pipefd[1]);
			process_output_command_direct_parent(temp);
			if (empty_control(context->line) && context->line[0]
				&& context->commands && context->commands[0])
				process_command_effect(context);
		}
	}
}

void	process_output_command_redirects_parent(t_context *context,
												int pipefd[2],
												int **pipefds)
{
	char	*buffer;
	int		byte_read;
	int		fd;

	buffer = malloc(sizeof(char) * 11);
	close(pipefds[context->process_index - 1][1]);
	fd = pipefds[context->process_index - 1][0];
	byte_read = 1;
	while (byte_read)
	{
		byte_read = read(fd, buffer, 10);
		write(pipefd[1], buffer, ft_strlen(buffer));
		if (byte_read <= 0)
			break ;
		buffer[byte_read] = 0;
		ft_bzero(buffer, 11);
	}
	free(buffer);
	close(pipefds[context->process_index - 1][0]);
	exit(0);
}

void	process_output_command_redirects(t_context *context, int pipefd[2],
		int **pipefds)
{
	int	pid;

	if (context->process_index > 0)
	{
		close_pipes_except_output(pipefds);
		pid = fork();
		if (pid == 0)
			process_output_command_redirects_parent(context, pipefd, pipefds);
		else
		{
			close(pipefds[context->process_index - 1][0]);
			waitpid(pid, 0, 0);
		}
	}
}
