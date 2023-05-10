/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/16 01:32:04 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_fork_main(t_context *context)
{
	int		i;
	char	**env;
	char	cwd[PATH_MAX];

	if (context->commands[0][1][0] == '/')
		chdir(context->commands[0][1]);
	else
	{
		getcwd(cwd, sizeof(cwd));
		cd_absolute_path(context, cwd);
	}
	getcwd(cwd, sizeof(cwd));
	i = 0;
	while (context->envs[i])
	{
		env = ft_split(context->envs[i], '=');
		if (ft_strncmp(env[0], "PWD", 3) == 0 && ft_strlen(env[0]) == 3)
		{
			free(context->envs[i]);
			context->envs[i] = ft_strjoin("PWD=", cwd);
		}
		ft_arr_free(env);
		i++;
	}
}

int	init_cd(t_context *context)
{
	int		i;
	char	cwd[PATH_MAX];
	char	**env;
	char	*str;

	i = 0;
	str = get_environment_variable(context, "HOME");
	chdir(str);
	free(str);
	getcwd(cwd, sizeof(cwd));
	while (context->envs[i])
	{
		env = ft_split(context->envs[i], '=');
		if (ft_strncmp(env[0], "PWD", 3) == 0 && ft_strlen(env[0]) == 3)
		{
			free(context->envs[i]);
			context->envs[i] = ft_strjoin("PWD=", cwd);
			ft_arr_free(env);
			break ;
		}
		ft_arr_free(env);
		i++;
	}
	return (1);
}

void	cd_process(t_context *context)
{
	int	pid;
	int	result;

	pid = fork();
	if (pid == 0)
	{
		result = execve(search_command(context, context->commands[0][0],
					context->envpaths), context->commands[0], 0);
		if (result == -1)
			exit(0);
	}
	else
		cd_fork_main(context);
	wait(0);
}

int	cd_term(t_context *context, int is_effect)
{
	if (ft_strncmp(context->commands[0][0], "cd", 2) == 0 &&
		ft_strlen(context->commands[0][0]) == 2)
	{
		if (!is_effect)
			return (1);
		if (!context->commands[0][1])
		{
			init_cd(context);
			return (1);
		}
		cd_process(context);
		return (1);
	}
	return (0);
}

int	env_term(t_context *context)
{
	if (ft_strncmp(context->commands[0][0], "env", 3) == 0
		&& ft_strlen(context->commands[0][0]) == 3 && !context->commands[0][1])
	{
		print_env(context);
		return (1);
	}
	return (0);
}
