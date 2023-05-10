/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:13:58 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:29:26 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_split_command_condition1(const char *s, t_temp *temp, t_context *context)
{
	if (!check_dd_quote(temp, s))
	{
		temp->commands[temp->j][temp->k] = '\0';
		temp->commands[temp->j + 1] = 0;
		context->command_error = 1;
		ft_arr_free(temp->commands);
		return (1);
	}
	return (0);
}

int	ft_split_command_condition2(const char *s, t_temp *temp, t_context *context)
{
	if (!check_ss_quote(temp, s))
	{
		temp->commands[temp->j][temp->k] = '\0';
		temp->commands[temp->j + 1] = 0;
		context->command_error = 1;
		ft_arr_free(temp->commands);
		return (1);
	}
	return (0);
}

void	split_command_end(t_temp *temp)
{
	if (temp->j != -1)
		temp->commands[temp->j][temp->k] = '\0';
	temp->commands[temp->j + 1] = 0;
}

void	function_two_end(t_temp *context, t_context *g_context)
{
	context->i--;
	context->commands[context->j][context->k] = '\0';
	context->commands[context->j] = split_replace_env(g_context,
			context->commands[context->j], context->index);
	context->k = ft_strlen(context->commands[context->j]);
	context->k--;
}
