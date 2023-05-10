/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:59:46 by eightimerka       #+#    #+#             */
/*   Updated: 2023/03/18 05:43:17 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_func(t_temp *context, const char *s)
{
	context->i = 0;
	context->j = -1;
	context->k = 0;
	context->is_d_quote = 0;
	context->is_s_quote = 0;
	context->is_space = 0;
	context->c = ' ';
	context->commands = (char **)malloc(sizeof(char *) * (ft_count_commands(s)
				+ 2));
}

int	check_dd_quote(t_temp *context, const char *s)
{
	if (!context->is_d_quote && !context->is_s_quote)
	{
		if (!s[context->i + 1] || !is_have_peer(s, context->i + 1, '"'))
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
		if ((s[context->i + 1] <= 13 && s[context->i + 1] >= 9) || s[context->i
				+ 1] == 32)
			context->is_space = 1;
		else
			context->is_space = 0;
		context->is_d_quote = 0;
	}
	return (1);
}

int	check_ss_quote(t_temp *context, const char *s)
{
	if (!context->is_s_quote && !context->is_d_quote)
	{
		if (!s[context->i + 1] || !is_have_peer(s, context->i + 1, '\''))
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
		if ((s[context->i + 1] <= 13 && s[context->i + 1] >= 9) || s[context->i
				+ 1] == 32)
			context->is_space = 1;
		else
			context->is_space = 0;
		context->is_s_quote = 0;
	}
	return (1);
}

void	func_one(t_temp *context)
{
	if (context->j >= 0)
		context->commands[context->j][context->k] = '\0';
	context->k = 0;
	context->j++;
	context->commands[context->j] = malloc(1000);
	context->is_space = 0;
}

void	func_two(t_temp *context, const char *s, t_context *g_context,
		int is_replace_env)
{
	context->commands[context->j][context->k] = s[context->i];
	if (is_replace_env && !context->is_s_quote && s[context->i] == '$'
		&& s[context->i + 1] && s[context->i + 1] != '$'
		&& !ft_isdigit(s[context->i]))
	{
		context->index = context->k;
		context->i++;
		context->k++;
		while (s[context->i])
		{
			if (s[context->i] == '?')
			{
				context->commands[context->j][context->k++] = s[context->i++];
				break ;
			}
			if (((s[context->i] <= 13 && s[context->i] >= 9)
					|| s[context->i] == 32) || s[context->i] == '$'
				|| (!ft_isalpha(s[context->i]) && !ft_isdigit(s[context->i])
					&& s[context->i] != '_'))
				break ;
			context->commands[context->j][context->k++] = s[context->i++];
		}
		function_two_end(context, g_context);
	}
	context->k++;
}
