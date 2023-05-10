/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:38:27 by eightimerka       #+#    #+#             */
/*   Updated: 2023/03/12 23:55:28 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_redirect_utils(t_context *context, t_temp3 *temp)
{
	context->redirects[temp->j].type = 0;
	temp->i += 2;
	while (context->line[temp->i] && ((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9)
			|| context->line[temp->i] == 32))
		temp->i++;
	if (!context->line[temp->i])
		return (1);
	context->redirects[temp->j].ref = malloc(sizeof(char)
			* (ref_length(context->line, temp->i) + 1));
	return (0);
}

int	init_redirect_utils2(t_context *context, t_temp3 *temp)
{
	context->redirects[temp->j].type = 1;
	temp->i += 2;
	while (context->line[temp->i] && ((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9)
			|| context->line[temp->i] == 32))
		temp->i++;
	if (!context->line[temp->i])
		return (1);
	context->redirects[temp->j].ref = malloc(sizeof(char)
			* (ref_length(context->line, temp->i) + 1));
	return (0);
}

int	init_redirect_utils3(t_context *context, t_temp3 *temp)
{
	context->redirects[temp->j].type = 2;
	temp->i += 1;
	while (context->line[temp->i] && ((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9)
			|| context->line[temp->i] == 32))
		temp->i++;
	if (!context->line[temp->i])
		return (1);
	context->redirects[temp->j].ref = malloc(sizeof(char)
			* (ref_length(context->line, temp->i) + 1));
	return (0);
}

int	init_redirect_utils4(t_context *context, t_temp3 *temp)
{
	context->redirects[temp->j].type = 3;
	temp->i += 1;
	while (context->line[temp->i] && ((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9)
			|| context->line[temp->i] == 32))
		temp->i++;
	if (!context->line[temp->i])
		return (1);
	context->redirects[temp->j].ref = malloc(sizeof(char)
			* (ref_length(context->line, temp->i) + 1));
	return (0);
}
