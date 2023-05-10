/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:10:31 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/17 23:53:12 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_count(t_context *context)
{
	char	**pipes;
	int		i;

	i = 0;
	pipes = ft_split(context->base_line, '|');
	while (pipes[i])
		i++;
	ft_arr_free(pipes);
	return (i);
}

int	check_double_pipe(t_context *context)
{
	int	i;

	i = 0;
	while (context->base_line[i + 1] != '\0')
	{
		if (context->base_line[i] == '|' && context->base_line[i + 1] == '|'
			&& !is_in_quote(context->base_line, i))
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe_is_empty(t_context *context)
{
	int	i;
	int	j;
	int	is_match;

	i = 0;
	while (context->pipes[i])
	{
		j = 0;
		is_match = 0;
		while (context->pipes[i][j])
		{
			if (!((context->pipes[i][j] <= 13 && context->pipes[i][j] >= 9)
					|| context->pipes[i][j] == 32))
				is_match = 1;
			j++;
		}
		if (!is_match)
			break ;
		i++;
	}
	if (ft_count_pipes(context->base_line) + 1 != i)
		return (1);
	return (0);
}

int	parse_pipes(t_context *context)
{
	context->pipes = ft_pipe_split(context->base_line);
	if (check_pipe_is_empty(context) || check_double_pipe(context))
		return (0);
	return (1);
}

int	parser(t_context *context)
{
	int	result;

	free(context->commands);
	context->commands = (char ***)malloc(sizeof(char **) * (pipe_count(context)
				+ 2));
	result = parse_pipes(context);
	if (result == 0)
		return (0);
	return (1);
}
