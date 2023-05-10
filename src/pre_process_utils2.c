/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:19:27 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_simple_output_redirect(t_context *context, int i,
		char *out_content)
{
	int	fd;

	fd = open(context->redirects[i].ref, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (ft_output_redirect_len(context->redirects) == i)
		write(fd, out_content, ft_strlen(out_content));
	close(fd);
}

void	process_double_output_redirect(t_context *context, int i,
		char *out_content)
{
	int	fd;

	fd = open(context->redirects[i].ref, O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR);
	if (ft_output_redirect_len(context->redirects) == i)
		write(fd, out_content, ft_strlen(out_content));
	close(fd);
}

int	process_output_redirects(t_context *context, char *out_content,
		int **pipefds)
{
	int	i;
	int	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		close_pipes(pipefds);
		exit(0);
	}
	else
	{
		while (context->redirects[i].ref)
		{
			if (context->redirects[i].type == 0)
				process_double_output_redirect(context, i, out_content);
			else if (context->redirects[i].type == 2)
				process_simple_output_redirect(context, i, out_content);
			i++;
		}
		return (pid);
	}
	return (0);
}

int	process_out_clone(t_context *context, int pipe_desc[2], char *out_content,
		int **pipefds)
{
	int	pid;

	if (pipe_desc && ft_arr_len(context->pipes) > 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!context->redirects[0].ref && context->process_index > 0)
				dup2(pipefds[context->process_index - 1][0], 0);
			if (ft_arr_len(context->pipes) != context->process_index + 1
				&& ft_arr_len(context->pipes) > 1)
				dup2(pipefds[context->process_index][1], 1);
			close_pipes(pipefds);
			printf("%s", out_content);
			exit(0);
		}
		else
			return (pid);
	}
	else
	{
		printf("%s", out_content);
		return (0);
	}
	return (0);
}
