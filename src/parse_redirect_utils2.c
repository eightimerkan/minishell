/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:55:46 by eightimerka       #+#    #+#             */
/*   Updated: 2023/03/18 04:52:09 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_func2(t_temp3 *temp, t_context *context)
{
	temp->i = 0;
	temp->j = 0;
	temp->l = 0;
	temp->new_line = malloc(sizeof(char) * (ft_strlen(context->line) + 1));
	context->redirects = malloc(sizeof(t_redirect) * 1000);
}

void	redirect_utils5(t_context *context, t_temp3 *temp)
{
	temp->new_line[temp->l] = context->line[temp->i];
	temp->l++;
	temp->i++;
}

void	redirect_utils6(t_context *context, t_temp3 *temp)
{
	temp->new_line[temp->l] = '\0';
	free(context->line);
	if (!temp->new_line[0])
	{
		free(temp->new_line);
		context->line[0] = 0;
		return ;
	}
	context->line = ft_strdup(temp->new_line);
	free(temp->new_line);
	context->redirects[temp->j].ref = 0;
}
