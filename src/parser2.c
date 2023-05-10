/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:10:31 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/13 22:49:42 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env_utils(char *command, t_temp4 *temp)
{
	while (command[temp->k])
	{
		if (((command[temp->k] <= 13 && command[temp->k] >= 9)
				|| command[temp->k] == 32) || command[temp->k] == '$')
			break ;
		temp->env[temp->j] = command[temp->k];
		temp->j++;
		temp->k++;
	}
}

void	env_utils(t_context *context, char *command, t_temp4 *temp)
{
	temp->k++;
	init_env_utils(command, temp);
	temp->env[temp->j] = 0;
	temp->j = 0;
	temp->env_var = get_environment_variable(context, temp->env);
	if (temp->env_var)
	{
		while (temp->env_var[temp->j])
		{
			temp->str[temp->i] = temp->env_var[temp->j];
			temp->i++;
			temp->j++;
		}
	}
	ft_bzero(temp->env, ft_strlen(temp->env));
	if (temp->env_var)
		free(temp->env_var);
	temp->j = 0;
}

char	*replace_env(t_context *context, char *command)
{
	t_temp4	temp;

	temp.i = 0;
	temp.j = 0;
	temp.k = 0;
	temp.str = (char *)malloc(sizeof(char) * ft_strlen(command) * 1000);
	while (command[temp.k])
	{
		temp.env = malloc(10000);
		if (command[temp.k] == '$' && command[temp.k + 1] && command[temp.k
				+ 1] != '$')
			env_utils(context, command, &temp);
		else
		{
			temp.str[temp.i] = command[temp.k];
			temp.i++;
			temp.k++;
		}
		free(temp.env);
	}
	temp.str[temp.i] = '\0';
	free(command);
	return (temp.str);
}
