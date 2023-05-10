/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:37:41 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/16 01:32:02 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_have_peer(const char *s, int index, char c)
{
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (0);
}

void	ft_arr_bzero(char **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][j])
		{
			tab[i][j] = 0;
			j++;
		}
		tab[i] = 0;
		j = 0;
		i++;
	}
	return ;
}

void	print_env(t_context *context)
{
	int	i;

	i = 0;
	while (context->envs[i])
	{
		if (context->envs[i][0] != '?' && ft_strchr(context->envs[i], '=') != 0)
			printf("%s\n", context->envs[i]);
		i++;
	}
}

int	ft_output_redirect_len(t_redirect *redirects)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (redirects[len].ref)
	{
		if (redirects[len].type == 0 || redirects[len].type == 2)
			index = len;
		len++;
	}
	return (index);
}

int	init_setup_dirs(t_context *context, char *str, char ***paths)
{
	if (str)
	{
		*paths = ft_split(str, ':');
		if (context->envpaths)
			ft_env_path_free(context);
		free(str);
	}
	else
	{
		if (context->envpaths)
			ft_env_path_free(context);
		context->envpaths = 0;
		free(str);
		return (1);
	}
	return (0);
}
