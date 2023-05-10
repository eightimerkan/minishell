/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:54:10 by eightimerka       #+#    #+#             */
/*   Updated: 2023/03/18 06:53:19 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_environment_variable(t_context *context, char *key)
{
	int		i;
	char	**env;
	char	*str;

	i = 0;
	while (context->envs[i])
	{
		env = ft_split(context->envs[i], '=');
		if (ft_strncmp(env[0], key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(env[0]))
		{
			str = ft_strdup(env[1]);
			ft_arr_free(env);
			return (str);
		}
		ft_arr_free(env);
		i++;
	}
	return (0);
}

void	ft_arr_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	ft_redirects_free(t_context *context)
{
	size_t	i;

	i = 0;
	while (context->redirects[i].ref)
	{
		free(context->redirects[i].ref);
		i++;
	}
	free(context->redirects);
	return ;
}

void	ft_env_path_free(t_context *context)
{
	int	i;

	i = 0;
	while (context->envpaths[i].path)
	{
		free(context->envpaths[i].path);
		free(context->envpaths[i].name);
		i++;
	}
	free(context->envpaths);
	return ;
}

void	ft_pipefds_free(int **pipefds)
{
	int	i;

	i = 0;
	while (pipefds[i])
	{
		free(pipefds[i]);
		i++;
	}
	free(pipefds);
	return ;
}
