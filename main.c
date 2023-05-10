/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:59:20 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/13 23:03:43 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_context	context;

	(void)argc;
	(void)argv;
	setup_term(&context);
	setup_envs(&context, envp);
	setup_envpaths_dirs(&context);
	worker(&context);
	return (0);
}
