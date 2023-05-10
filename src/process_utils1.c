/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:07 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 01:35:24 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	clear_history_command(t_context *context, int is_effect)
{
	if (ft_strncmp((context->commands)[0][0], "history", 7) == 0
		&& ft_strlen(context->commands[0][0]) == 7)
	{
		if (!is_effect)
			return (1);
		if (ft_strncmp((context->commands)[0][1], "-c", 2) == 0)
			clear_history();
		return (1);
	}
	return (0);
}

int	print_pwd(t_context *context)
{
	char	cwd[PATH_MAX];

	if (ft_strncmp((context->commands)[0][0], "pwd", 3) == 0
		&& ft_strlen(context->commands[0][0]) == 3)
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
		return (1);
	}
	return (0);
}

int	clear_term(t_context *context)
{
	if (ft_strncmp(context->commands[0][0], "clear", 5) == 0
		&& ft_strlen(context->commands[0][0]) == 5)
	{
		system("clear");
		return (1);
	}
	return (0);
}

int	exit_term(t_context *context, int is_effect)
{
	if (ft_strncmp(context->commands[0][0], "exit", 4) == 0
		&& ft_strlen(context->commands[0][0]) == 4)
	{
		if (exit_error_check(context))
			return (1);
		free(context->prompt_name);
		ft_arr_free(context->envs);
		if (is_effect)
			printf("exit\n");
		if (context->commands[0][1])
			exit(ft_atoi(context->commands[0][1]));
		else
			exit(0);
		return (1);
	}
	return (0);
}

int	run_builtin(t_context *context)
{
	int	result;

	interpret_echo_newline(context);
	result = execve(search_command(context, context->commands[0][0],
				context->envpaths), context->commands[0], context->envs);
	if (result == -1)
	{
		context->command_not_found = 1;
		if (context->not_found)
			return (0);
		return (1);
	}
	return (0);
}
