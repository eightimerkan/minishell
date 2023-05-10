/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/17 21:09:19 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_builtin_direct(t_context *context)
{
	int	pid;

	search_command(context, context->commands[0][0], context->envpaths);
	pid = fork();
	if (pid == 0)
	{
		interpret_echo_newline(context);
		if (execve(search_command(context, context->commands[0][0],
				context->envpaths), context->commands[0], context->envs) == -1)
		{
			context->command_not_found = 1;
			if (context->not_found)
				exit(127);
			exit(1);
		}
	}
	else
	{
		update_status(context, pid);
		if (context->not_found)
			return (2);
		return (1);
	}
	return (0);
}

char	**init_unset_environment(t_context *context)
{
	char	**str;
	int		i;

	str = malloc(sizeof(char *) * 10000);
	i = 0;
	while (context->envs[i])
	{
		str[i] = ft_strdup(context->envs[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

void	cd_absolute_path(t_context *context, char cwd[PATH_MAX])
{
	char	*str0;
	char	*str;

	str0 = ft_strjoin(cwd, "/");
	str = ft_strjoin(str0, context->commands[0][1]);
	free(str0);
	chdir(str);
	free(str);
}

void	init_interpret_echo_new_line(t_context *context, int *i, int *j)
{
	int	is_interrupt;

	while (context->commands[0][*i])
	{
		*j = 0;
		is_interrupt = 0;
		if (context->commands[0][*i][*j] == '-' && context->commands[0][*i][*j
			+ 1])
		{
			*j += 1;
			while (context->commands[0][*i][*j])
			{
				if (context->commands[0][*i][*j] != 'n')
					is_interrupt = 1;
				*j += 1;
			}
			if (is_interrupt)
				break ;
		}
		else
			break ;
		*i += 1;
	}
}

void	interpret_echo_newline(t_context *context)
{
	char	**commands;
	int		i;
	int		j;

	if (context->commands[0][1])
	{
		if (ft_strncmp(context->commands[0][0], "echo", 4) != 0
			|| !is_only_n(context->commands[0][1]))
			return ;
		commands = (char **)malloc(sizeof(char *)
				* (ft_count_commands(context->line) * 10000));
		commands[0] = ft_strdup(context->commands[0][0]);
		commands[1] = ft_strdup("-n");
		i = 1;
		init_interpret_echo_new_line(context, &i, &j);
		j = 2;
		while (context->commands[0][i])
			commands[j++] = ft_strdup(context->commands[0][i++]);
		commands[j] = 0;
		ft_arr_free(context->commands[0]);
		context->commands[0] = commands;
	}
}
