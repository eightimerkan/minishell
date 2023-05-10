/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:59:46 by eightimerka       #+#    #+#             */
/*   Updated: 2023/03/11 17:57:59 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_dd_quote(t_temp *context, const char *s)
{
	if (!context->is_d_quote && !context->is_s_quote)
	{
		if (!is_have_peer(s, context->i + 1, '"'))
			return (0);
		context->is_d_quote = 1;
		if (context->is_space)
		{
			if (context->j >= 0)
				context->commands[context->j][context->k] = '\0';
			context->k = 0;
			context->j++;
			context->commands[context->j] = malloc(1000);
		}
	}
	else if (context->is_d_quote)
	{
		if (s[context->i + 1] == '|')
			context->is_space = 1;
		else
			context->is_space = 0;
		context->is_d_quote = 0;
	}
	return (1);
}

int	check_pipe_ss_quote(t_temp *context, const char *s)
{
	if (!context->is_s_quote && !context->is_d_quote)
	{
		if (!is_have_peer(s, context->i + 1, '\''))
			return (0);
		context->is_s_quote = 1;
		if (context->is_space)
		{
			if (context->j >= 0)
				context->commands[context->j][context->k] = '\0';
			context->k = 0;
			context->j++;
			context->commands[context->j] = malloc(1000);
		}
	}
	else if (context->is_s_quote)
	{
		if (s[context->i + 1] == '|')
			context->is_space = 1;
		else
			context->is_space = 0;
		context->is_s_quote = 0;
	}
	return (1);
}

void	pipe_func_one(t_temp *context)
{
	if (context->j >= 0)
		context->commands[context->j][context->k] = '\0';
	context->k = 0;
	context->j++;
	context->commands[context->j] = malloc(1000);
}

void	pipe_func_two(t_temp *context, const char *s)
{
	context->commands[context->j][context->k] = s[context->i];
	context->k++;
}
