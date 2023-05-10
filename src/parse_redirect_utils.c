/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:38:27 by eightimerka       #+#    #+#             */
/*   Updated: 2023/03/18 03:28:47 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_utils(t_context *context, t_temp3 *temp)
{
	char	**command_ref;

	if (init_redirect_utils(context, temp))
		return (0);
	while (context->line[temp->i] && !((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9) || context->line[temp->i] == 32)
		&& context->line[temp->i] != '<' && context->line[temp->i] != '>')
	{
		context->redirects[temp->j].ref[temp->k] = context->line[temp->i];
		temp->i++;
		temp->k++;
	}
	context->redirects[temp->j].ref[temp->k] = '\0';
	if (temp->k == 0)
		return (0);
	command_ref = ft_split_command(context->redirects[temp->j].ref, context, 0);
	if (command_ref == 0)
		return (0);
	temp->new_ref = ft_strdup(command_ref[0]);
	ft_strlcpy(context->redirects[temp->j].ref, temp->new_ref,
		ft_strlen(temp->new_ref) + 1);
	free(temp->new_ref);
	ft_arr_free(command_ref);
	temp->j++;
	return (1);
}

int	redirect_utils2(t_context *context, t_temp3 *temp)
{
	char	**command_ref;

	if (init_redirect_utils2(context, temp))
		return (0);
	while (context->line[temp->i] && !((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9) || context->line[temp->i] == 32)
		&& context->line[temp->i] != '<' && context->line[temp->i] != '>')
	{
		context->redirects[temp->j].ref[temp->k] = context->line[temp->i];
		temp->i++;
		temp->k++;
	}
	context->redirects[temp->j].ref[temp->k] = '\0';
	if (temp->k == 0)
		return (0);
	command_ref = ft_split_command(context->redirects[temp->j].ref, context, 0);
	if (command_ref == 0)
		return (0);
	temp->new_ref = ft_strdup(command_ref[0]);
	ft_strlcpy(context->redirects[temp->j].ref, temp->new_ref,
		ft_strlen(temp->new_ref) + 1);
	free(temp->new_ref);
	ft_arr_free(command_ref);
	temp->j++;
	return (1);
}

int	redirect_utils3(t_context *context, t_temp3 *temp)
{
	char	**command_ref;

	if (init_redirect_utils3(context, temp))
		return (0);
	while (context->line[temp->i] && !((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9) || context->line[temp->i] == 32)
		&& context->line[temp->i] != '<' && context->line[temp->i] != '>')
	{
		context->redirects[temp->j].ref[temp->k] = context->line[temp->i];
		temp->i++;
		temp->k++;
	}
	context->redirects[temp->j].ref[temp->k] = '\0';
	if (temp->k == 0)
		return (0);
	command_ref = ft_split_command(context->redirects[temp->j].ref, context, 0);
	if (command_ref == 0)
		return (0);
	temp->new_ref = ft_strdup(command_ref[0]);
	ft_strlcpy(context->redirects[temp->j].ref, temp->new_ref,
		ft_strlen(temp->new_ref) + 1);
	free(temp->new_ref);
	ft_arr_free(command_ref);
	temp->j++;
	return (1);
}

int	redirect_utils4(t_context *context, t_temp3 *temp)
{
	char	**command_ref;

	if (init_redirect_utils4(context, temp))
		return (0);
	while (context->line[temp->i] && !((context->line[temp->i] <= 13
				&& context->line[temp->i] >= 9) || context->line[temp->i] == 32)
		&& context->line[temp->i] != '<' && context->line[temp->i] != '>')
	{
		context->redirects[temp->j].ref[temp->k] = context->line[temp->i];
		temp->i++;
		temp->k++;
	}
	context->redirects[temp->j].ref[temp->k] = '\0';
	if (temp->k == 0)
		return (0);
	command_ref = ft_split_command(context->redirects[temp->j].ref, context, 0);
	if (command_ref == 0)
		return (0);
	temp->new_ref = ft_strdup(command_ref[0]);
	ft_strlcpy(context->redirects[temp->j].ref, temp->new_ref,
		ft_strlen(temp->new_ref) + 1);
	free(temp->new_ref);
	ft_arr_free(command_ref);
	temp->j++;
	return (1);
}
