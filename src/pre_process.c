/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:41:08 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pre_process(t_context *context)
{
	if (!context->redirects[0].ref)
	{
		if (ft_arr_len(context->pipes) > 1)
			process_command(context);
		else
			process_command_direct(context);
		return (0);
	}
	return (1);
}

int	pre_process_ignore_check(t_context *context, t_temp5 *temp, int **pipefds,
		int pipe_desc[2])
{
	if ((context->process_index > 0 || ft_is_input_exist(context->redirects))
		&& context->commands[0])
		process_clone_inputs(context, temp);
	if (temp->is_out)
	{
		temp->pid = process_out_clone(context, pipe_desc, temp->out_content,
				pipefds);
		if (temp->pid)
		{
			free(temp->out_content);
			return (temp->pid);
		}
	}
	temp->pid = process_output_redirects(context, temp->out_content, pipefds);
	free(temp->out_content);
	return (temp->pid);
}

int	pre_process(t_context *context, int pipe_desc[2], int **pipefds)
{
	t_temp5	temp;

	if (check_pre_process(context) == 0)
		return (0);
	temp.out_content = (char *)malloc(sizeof(char) * 10000);
	temp.is_out = 1;
	pipe(temp.pipefd);
	pipe(temp.pipefd1);
	process_input_redirects(context, &temp);
	if (!ft_is_input_exist(context->redirects) && !context->ignore_redirect)
	{
		process_output_command_direct(context, &temp);
		process_output_command_redirects(context, temp.pipefd, pipefds);
	}
	if (!context->ignore_redirect)
		return (pre_process_ignore_check(context, &temp, pipefds, pipe_desc));
	if (ft_arr_len(context->pipes) <= 1)
		context->ignore_redirect = 0;
	free(temp.out_content);
	return (0);
}
