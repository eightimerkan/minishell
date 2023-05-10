/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 03:47:13 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 07:09:20 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_is_signal;

void	ctl_plus_c_handler(int sig)
{
	(void)sig;
	g_is_signal = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctl_plus_backslash_handler(int sig)
{
	(void)sig;
	g_is_signal = 2;
	write(1, "\033[s", 3);
	ioctl(STDIN_FILENO, TIOCSTI);
	write(1, "\033[u\033[0K", 7);
}

void	worker(t_context *context)
{
	char	*str;

	while (1)
	{
		g_is_signal = 0;
		signal(SIGINT, ctl_plus_c_handler);
		signal(SIGQUIT, ctl_plus_backslash_handler);
		str = readline(context->prompt_name);
		if (str != 0)
			context->base_line = str;
		else
			exit_on_ctrl_d(str, context);
		if (g_is_signal == 0 && !check_line_is_empty(context)
			&& ft_strlen(context->base_line) > 0 && context->base_line != 0
			&& context->base_line)
		{
			g_is_signal = 2;
			add_history(context->base_line);
			run_pipe(context);
		}
		g_is_signal = 0;
		free(str);
	}
}

char	**process_double_input_loop(t_context *context, char **str, int i,
		int *j)
{
	char	**lines;

	lines = (char **)malloc(sizeof(char *) * 100000);
	while (1)
	{
		g_is_signal = 0;
		signal(SIGINT, ctl_plus_c_handler);
		*str = readline(HERE_DOC);
		if (g_is_signal)
		{
			double_input_signal(context, lines, *str, *j);
			return (0);
		}
		if (*str == 0 || (ft_strncmp(*str, context->redirects[i].ref,
					ft_strlen(*str)) == 0
				&& ft_strlen(*str) == ft_strlen(context->redirects[i].ref)))
			break ;
		else if (ft_input_redirect_len(context->redirects) == i)
			lines[*j] = ft_strdup(*str);
		*j += 1;
		free(*str);
	}
	return (lines);
}

void	process_double_input_redirect(t_context *context, int i, int pipefd[2])
{
	char	**lines;
	char	*str;
	int		j;

	j = 0;
	lines = process_double_input_loop(context, &str, i, &j);
	if (!g_is_signal || !context->ignore_redirect)
	{
		lines[j] = 0;
		double_input_process(str, lines, pipefd);
	}
}
