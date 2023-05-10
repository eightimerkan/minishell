/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:08:58 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 06:19:40 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	if ((!ft_isdigit(str[0]) && str[0] != '-') || (str[0] == '-' && !str[1]))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_error_check(t_context *context)
{
	if (context->commands[0][1] && context->commands[0][2])
	{
		write(2, "exit: too many arguments\n", 25);
		update_status_without_pid(context, 1);
		return (1);
	}
	if (context->commands[0][1] && !ft_isnumber(context->commands[0][1]))
	{
		write(2, "exit: numeric argument required\n", 32);
		update_status_without_pid(context, 255);
		exit(-1);
		return (1);
	}
	return (0);
}

int	assign_control(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	export_control(char *str)
{
	int	i;
	int	is;

	is = assign_control(str);
	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '_'))
	{
		i++;
		if (i == is)
			return (0);
	}
	if (ft_strlen(str) != (size_t)i)
		return (1);
	return (0);
}

int	empty_control(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			return (1);
		i++;
	}
	return (0);
}
