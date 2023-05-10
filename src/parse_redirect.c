/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:35:57 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 04:52:18 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ref_length(char *line, int index)
{
	int	i;

	i = 0;
	while (line[index] && !((line[index] <= 13 && line[index] >= 9)
			|| line[index] == 32) && line[index] != '<' && line[index] != '>')
	{
		index++;
		i++;
	}
	return (i);
}

int	quote_utils(t_temp2 *temp, const char *line, int index)
{
	if (!temp->is_d_quote && !temp->is_s_quote)
	{
		if (!is_have_peer(line, temp->i + 1, '"'))
			return (0);
		if (is_have_peer(line, temp->i + 1, '"') && index > temp->i
			&& index < is_have_peer(line, temp->i + 1, '"'))
			return (1);
		temp->is_d_quote = 1;
	}
	else if (temp->is_d_quote)
		temp->is_d_quote = 0;
	return (2);
}

int	quote_utils2(t_temp2 *temp, const char *line, int index)
{
	if (!temp->is_s_quote && !temp->is_d_quote)
	{
		if (!is_have_peer(line, temp->i + 1, '\''))
			return (0);
		if (is_have_peer(line, temp->i + 1, '\'') && index > temp->i
			&& index < is_have_peer(line, temp->i + 1, '\''))
			return (1);
		temp->is_s_quote = 1;
	}
	else if (temp->is_s_quote)
		temp->is_s_quote = 0;
	return (2);
}

int	is_in_quote(const char *line, int index)
{
	t_temp2	temp;
	int		a;
	int		b;

	temp.i = 0;
	temp.is_d_quote = 0;
	temp.is_s_quote = 0;
	a = 2;
	b = 2;
	while (line[temp.i])
	{
		if (line[temp.i] == '"')
			a = quote_utils(&temp, line, index);
		if (a != 2)
			return (a);
		if (line[temp.i] == '\'')
			b = quote_utils2(&temp, line, index);
		if (b != 2)
			return (b);
		temp.i++;
	}
	return (0);
}

int	parse_redirections(t_context *context)
{
	t_temp3	temp;

	if (check_redirect_ref(context) || check_reverse_redirect(context))
	{
		context->commands[0] = 0;
		return (0);
	}
	setup_func2(&temp, context);
	while (context->line[temp.i])
	{
		temp.k = 0;
		if (parse_redirect_condition3(context, &temp) == 0)
		{
			context->redirects[temp.j + 1].ref = 0;
			context->commands[0] = 0;
			ft_redirects_free(context);
			free(temp.new_line);
			return (0);
		}
	}
	redirect_utils6(context, &temp);
	return (1);
}
