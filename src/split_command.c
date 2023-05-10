/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:13:58 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:43:18 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_d_quote(int *is_d_quote, size_t *j)
{
	if (*is_d_quote)
	{
		*is_d_quote = 0;
		*j += 1;
	}
	else
		*is_d_quote = 1;
}

void	check_s_quote(int *is_s_quote, size_t *j)
{
	if (*is_s_quote)
	{
		*is_s_quote = 0;
		*j += 1;
	}
	else
		*is_s_quote = 1;
}

size_t	ft_count_commands(const char *s)
{
	size_t	i;
	size_t	j;
	int		is_d_quote;
	int		is_s_quote;
	int		c;

	i = 0;
	j = 0;
	is_d_quote = 0;
	is_s_quote = 0;
	c = ' ';
	while (s[i])
	{
		if (!is_s_quote && !is_d_quote && s[i] != '"' && s[i] != '\''
			&& !((s[i] <= 13 && s[i] >= 9) || s[i] == 32) && ((c <= 13
					&& c >= 9) || c == 32))
			j++;
		if (s[i] == '"')
			check_d_quote(&is_d_quote, &j);
		if (s[i] == '\'')
			check_s_quote(&is_s_quote, &j);
		c = s[i];
		i++;
	}
	return (j);
}

char	**ft_split_command(const char *s, t_context *context,
	int is_replace_env)
{
	t_temp	temp;

	setup_func(&temp, s);
	while (s[temp.i])
	{
		if (!temp.is_s_quote && !temp.is_d_quote && !((s[temp.i] <= 13
					&& s[temp.i] >= 9) || s[temp.i] == 32) && ((temp.c <= 13
					&& temp.c >= 9) || temp.c == 32))
			func_one(&temp);
		if (s[temp.i] == '"' && ft_split_command_condition1(s, &temp, context))
			return (0);
		if (s[temp.i] == '\'' && ft_split_command_condition2(s, &temp, context))
			return (0);
		temp.c = s[temp.i];
		if (!temp.is_d_quote && !temp.is_s_quote && !((s[temp.i] <= 13
					&& s[temp.i] >= 9) || s[temp.i] == 32) && temp.j >= 0
			&& temp.k >= 0 && s[temp.i] != '\'' && s[temp.i] != '"')
			func_two(&temp, s, context, is_replace_env);
		temp.i++;
		if (((temp.is_d_quote && s[temp.i] != '"') || (temp.is_s_quote
					&& s[temp.i] != '\'')) && temp.j >= 0 && temp.k >= 0)
			func_two(&temp, s, context, is_replace_env);
	}
	split_command_end(&temp);
	return (temp.commands);
}
