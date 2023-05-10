/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 04:02:18 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_clone_inputs_child(t_context *context, int pipefd[2],
		int pipefd1[2])
{
	int	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd1[0]);
		dup2(pipefd1[1], 1);
		close(pipefd1[1]);
		close(pipefd[1]);
		close(pipefd[0]);
		process_command(context);
		exit(0);
	}
	else
	{
		close(pipefd1[0]);
		close(pipefd1[1]);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(0);
		waitpid(pid1, 0, 0);
	}
}

void	process_clone_inputs_parent(int pipefd[2], int pipefd1[2], int *pid,
		char **out_content)
{
	char	*buffer;
	char	*str;
	int		byte_read;

	close(pipefd1[1]);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(*pid, 0, 0);
	buffer = malloc(sizeof(char) * 11);
	byte_read = 1;
	while (byte_read)
	{
		byte_read = read(pipefd1[0], buffer, 10);
		if (byte_read <= 0)
			break ;
		buffer[byte_read] = 0;
		str = ft_strjoin(*out_content, buffer);
		free(*out_content);
		*out_content = str;
		ft_bzero(buffer, 11);
	}
	free(buffer);
	close(pipefd1[0]);
}

void	process_clone_inputs(t_context *context, t_temp5 *temp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		process_clone_inputs_child(context, temp->pipefd, temp->pipefd1);
	else
	{
		process_clone_inputs_parent(temp->pipefd, temp->pipefd1, &pid,
			&temp->out_content);
	}
}
