/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:13:02 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 04:48:57 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_command_two(t_context *context, int status)
{
	char	*str;

	if (!status)
		status = cd_term(context, 0);
	if (!status)
		status = export_env(context, 0);
	if (!status)
		status = unset_env(context, 0);
	if (!status)
		status = run_builtin(context);
	if (status)
		exit(0);
	str = ft_strjoin("command not found: ", context->commands[0][0]);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(str);
	exit(127);
}

int	process_command(t_context *context)
{
	int	status;

	status = 0;
	if (!status)
		status = print_pwd(context);
	if (!status)
		status = exit_term(context, 0);
	if (!status)
		status = env_term(context);
	process_command_two(context, status);
	return (0);
}

int	process_command_effect(t_context *context)
{
	if (exit_term(context, 1))
		return (1);
	if (cd_term(context, 1))
		return (1);
	if (export_env(context, 1))
		return (1);
	if (unset_env(context, 1))
		return (1);
	return (-1);
}

int	process_command_direct(t_context *context)
{
	char	*str;

	if (print_pwd(context))
		return (1);
	if (clear_history_command(context, 1))
		return (1);
	if (exit_term(context, 1))
		return (1);
	if (env_term(context))
		return (1);
	if (cd_term(context, 1))
		return (1);
	if (export_env(context, 1))
		return (1);
	if (unset_env(context, 1))
		return (1);
	if (run_builtin_direct(context) == 1)
		return (1);
	str = ft_strjoin("command not found: ", context->commands[0][0]);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(str);
	return (-1);
}
