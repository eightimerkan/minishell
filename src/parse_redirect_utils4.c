/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:38:27 by eightimerka       #+#    #+#             */
/*   Updated: 2023/03/18 03:28:41 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_reverse_redirect(t_context *context)
{
	int	i;

	i = 0;
	while (context->line[i] && context->line[i + 1]
		&& !is_in_quote(context->line, i))
	{
		if ((context->line[i] == '>' && context->line[i + 1] == '<')
			|| (context->line[i] == '<' && context->line[i + 1] == '>'))
			return (1);
		i++;
	}
	return (0);
}

int	check_redirect_ref(t_context *context)
{
	int	i;

	i = 0;
	while (context->line[i] && context->line[i + 1]
		&& !is_in_quote(context->line, i))
	{
		if ((context->line[i] == '>' && context->line[i + 1] == '>')
			&& (!context->line[i + 2] || (context->line[i + 2]
					&& (context->line[i + 2] == '<' || context->line[i
							+ 2] == '>'))))
			return (1);
		else if ((context->line[i] == '<' && context->line[i + 1] == '<')
			&& (!context->line[i + 2] || (context->line[i + 2]
					&& (context->line[i + 2] == '<' || context->line[i
							+ 2] == '>'))))
			return (1);
		else if (context->line[i] == '>' && !context->line[i + 1])
			return (1);
		else if (context->line[i] == '<' && !context->line[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	parse_redirect_condition1(t_context *context, t_temp3 *temp)
{
	if (context->line[temp->i] == '>' && context->line[temp->i + 1] == '>'
		&& !is_in_quote(context->line, temp->i) && !is_in_quote(context->line,
			temp->i + 1))
		return (1);
	return (0);
}

int	parse_redirect_condition2(t_context *context, t_temp3 *temp)
{
	if (context->line[temp->i] == '<' && context->line[temp->i + 1] == '<'
		&& !is_in_quote(context->line, temp->i) && !is_in_quote(context->line,
			temp->i + 1))
		return (1);
	return (0);
}

int	parse_redirect_condition3(t_context *context, t_temp3 *temp)
{
	if (parse_redirect_condition1(context, temp))
	{
		if (!redirect_utils(context, temp))
			return (0);
	}
	else if (parse_redirect_condition2(context, temp))
	{
		if (!redirect_utils2(context, temp))
			return (0);
	}
	else if (context->line[temp->i] == '>' && !is_in_quote(context->line,
			temp->i))
	{
		if (!redirect_utils3(context, temp))
			return (0);
	}
	else if (context->line[temp->i] == '<' && !is_in_quote(context->line,
			temp->i))
	{
		if (!redirect_utils4(context, temp))
			return (0);
	}
	else
		redirect_utils5(context, temp);
	return (1);
}
