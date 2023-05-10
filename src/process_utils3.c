/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 04:48:54 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_env_match(char ***commands, t_context *context, int is_effect)
{
	if (!commands[0][1])
	{
		if (is_effect)
			print_pure_env(context);
		return (0);
	}
	if (is_effect && commands[0][1][0] == '=')
	{
		printf("no matches found: %s\n", commands[0][1]);
		return (0);
	}
	return (1);
}

int	export_env_condition(t_context *context, int *i)
{
	char	**env;
	char	**command;

	while (context->envs[*i])
	{
		env = ft_split(context->envs[*i], '=');
		command = ft_split(context->commands[0][1], '=');
		if (ft_strncmp(env[0], command[0], ft_strlen(context->envs[*i])) == 0)
		{
			free(context->envs[*i]);
			context->envs[*i] = ft_strdup(context->commands[0][1]);
			context->envs[*i + 1] = 0;
			ft_arr_free(env);
			ft_arr_free(command);
			setup_envpaths_dirs(context);
			return (1);
		}
		ft_arr_free(env);
		ft_arr_free(command);
		*i += 1;
	}
	return (0);
}

int	export_env(t_context *context, int is_effect)
{
	int	i;

	i = 0;
	if (ft_strncmp(context->commands[0][0], "export", 6) == 0
		&& ft_strlen(context->commands[0][0]) == 6)
	{
		if (check_env_match(context->commands, context, is_effect) == 0
			|| !is_effect)
			return (1);
		if (export_env_condition(context, &i))
			return (1);
		if (export_control(context->commands[0][1]))
			write(2, "not a valid identifier\n", 23);
		free(context->envs[i]);
		context->envs[i] = ft_strdup(context->commands[0][1]);
		context->envs[i + 1] = 0;
		setup_envpaths_dirs(context);
		return (1);
	}
	return (0);
}

void	unset_environment(t_context *context, char *key)
{
	int		i;
	int		j;
	char	**str;
	char	**env;

	i = 0;
	j = 0;
	str = init_unset_environment(context);
	while (str[i])
	{
		env = ft_split(str[i], '=');
		if (ft_strncmp(env[0], key, ft_strlen(key)) != 0)
		{
			free(context->envs[j]);
			context->envs[j] = ft_strdup(str[i]);
			if (env[0][0] == '?')
				context->status_index = j;
			j++;
		}
		ft_arr_free(env);
		i++;
	}
	free(context->envs[j]);
	context->envs[j] = 0;
	ft_arr_free(str);
}

int	unset_env(t_context *context, int is_effect)
{
	if (ft_strncmp(context->commands[0][0], "unset", 5) == 0
		&& ft_strlen(context->commands[0][0]) == 5)
	{
		if (!context->commands[0][1])
			return (1);
		if (!is_effect || !context->commands[0][1]
			|| ft_strlen(context->commands[0][1]) <= 0
			|| context->commands[0][1][0] == '?')
			return (1);
		unset_environment(context, context->commands[0][1]);
		setup_envpaths_dirs(context);
		return (1);
	}
	return (0);
}
