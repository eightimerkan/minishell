/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:08:58 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 04:02:29 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_word(char *str, int index)
{
	int	i;

	i = index;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quote(str, i))
			return (i);
		i++;
	}
	return (i);
}

int	ft_count_pipes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quote(str, i))
			j++;
		i++;
	}
	return (j);
}

char	**ft_pipe_split(char *str)
{
	char	**pipes;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	pipes = (char **)malloc(sizeof(char *) * (ft_count_pipes(str) + 2));
	pipes[0] = (char *)malloc(sizeof(char) * (ft_count_word(str, 0) + 1));
	while (str[i])
	{
		if (((str[i] == '|' && is_in_quote(str, i)) || str[i] != '|'))
			pipes[j][k++] = str[i];
		else if (str[i] == '|' && !is_in_quote(str, i))
		{
			pipes[j++][k] = '\0';
			k = 0;
			pipes[j] = malloc(sizeof(char) * (ft_count_word(str, i + 1) + 1));
		}
		i++;
	}
	pipes[j][k] = '\0';
	pipes[j + 1] = 0;
	return (pipes);
}

char	*search_command(t_context *context, char *key, t_envpath *env_paths)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*str;
	char	*str1;

	i = 0;
	context->not_found = 0;
	while (env_paths && env_paths[i].name)
	{
		if ((ft_strncmp(key, env_paths[i].name, ft_strlen(key)) == 0
				&& ft_strlen(key) == ft_strlen(env_paths[i].name))
			|| (ft_strncmp(key, env_paths[i].path, ft_strlen(key)) == 0
				&& ft_strlen(key) == ft_strlen(env_paths[i].path)))
			return (env_paths[i].path);
		i++;
	}
	getcwd(cwd, sizeof(cwd));
	str = ft_strjoin(cwd, "/");
	str1 = ft_strjoin(str, key);
	free(str);
	if (access(str1, X_OK) == -1 || is_directory(str1))
		context->not_found = 1;
	free(str1);
	return (str1);
}

void	print_pure_env(t_context *context)
{
	int	i;

	i = 0;
	while (context->envs[i])
	{
		if (context->envs[i][0] != '?')
			printf("declare -x %s\n", context->envs[i]);
		i++;
	}
}
