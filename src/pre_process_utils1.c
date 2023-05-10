/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:45:57 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_simple_input_redirect(t_context *context, int i, int pipefd[2])
{
	int		byte_read;
	int		fd;
	char	*buffer;

	fd = open(context->redirects[i].ref, O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
		write(2, "No such file or directory\n", 26);
	if (fd != -1)
	{
		buffer = malloc(sizeof(char) * 11);
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
		close(fd);
	}
}

void	fork_utils(int pipefd[2], char **lines)
{
	int	j;

	j = 0;
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	while (lines[j])
	{
		printf("%s\n", lines[j]);
		j++;
	}
	exit(0);
}

void	double_input_process(char *str, char **lines, int pipefd[2])
{
	int	pid;

	pid = fork();
	if (pid == 0)
		fork_utils(pipefd, lines);
	else
	{
		waitpid(pid, 0, 0);
		ft_arr_free(lines);
		free(str);
	}
}

void	process_input_redirects(t_context *context, t_temp5 *temp)
{
	int	i;

	i = 0;
	while (context->redirects[i].ref)
	{
		if (context->redirects[i].type == 0 || context->redirects[i].type == 2)
			temp->is_out = 0;
		if (context->redirects[i].type == 1 && context->ignore_redirect)
			break ;
		if (context->redirects[i].type == 1)
			process_double_input_redirect(context, i, temp->pipefd);
		else if (context->redirects[i].type == 3
			&& ft_input_redirect_len(context->redirects) == i)
			process_simple_input_redirect(context, i, temp->pipefd);
		i++;
	}
}
