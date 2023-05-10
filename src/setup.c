/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:06:01 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/17 22:02:11 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_term(t_context *context)
{
	struct termios	t;
	char			*str;

	system("clear");
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSANOW, &t);
	chdir(getenv("HOME"));
	str = ft_strjoin("$", getenv("USER"));
	context->command_error = 0;
	context->ignore_redirect = 0;
	context->command_error = 0;
	context->prompt_name = ft_strjoin(str, "@minishell % ");
	free(str);
	getcwd(context->cwd, sizeof(context->cwd));
}

int	setup_envpaths_files(t_context *context, DIR *dp, int index, int i)
{
	char			**paths;
	char			*str;
	struct dirent	*entry;

	str = get_environment_variable(context, "PATH");
	paths = ft_split(str, ':');
	free(str);
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (entry != 0)
		{
			if (entry->d_namlen && paths[index] && ft_strlen(entry->d_name) > 0
				&& entry->d_name[0] != '.' && entry->d_name[0])
			{
				context->envpaths[i].name = ft_strdup(entry->d_name);
				str = ft_strjoin("/", entry->d_name);
				context->envpaths[i++].path = ft_strjoin(paths[index], str);
				free(str);
			}
		}
		entry = readdir(dp);
	}
	ft_arr_free(paths);
	return (i);
}

void	setup_envpaths_dirs(t_context *context)
{
	char	**paths;
	int		i;
	int		j;
	char	*str;
	DIR		*dp;

	i = 0;
	j = 0;
	str = get_environment_variable(context, "PATH");
	if (init_setup_dirs(context, str, &paths))
		return ;
	context->envpaths = malloc(sizeof(t_envpath) * 10000000);
	while (paths[i])
	{
		dp = opendir(paths[i]);
		if (dp)
		{
			j = setup_envpaths_files(context, dp, i, j);
			closedir(dp);
		}
		i++;
	}
	context->envpaths[j].path = 0;
	ft_arr_free(paths);
}

void	setup_pwd(t_context *context)
{
	char	cwd[PATH_MAX];
	int		i;
	char	**env;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	while (context->envs[i])
	{
		env = ft_split(context->envs[i], '=');
		if (ft_strncmp(env[0], "PWD", 3) == 0 && ft_strlen(env[0]) == 3)
		{
			free(context->envs[i]);
			context->envs[i] = ft_strjoin("PWD=", cwd);
			ft_arr_free(env);
			return ;
		}
		ft_arr_free(env);
		i++;
	}
}

void	setup_envs(t_context *context, char **envp)
{
	int	i;

	i = 0;
	context->envs = (char **)malloc(sizeof(char *) * (ft_arr_len(envp)
				* 100000));
	while (envp[i])
	{
		context->envs[i] = ft_strdup(envp[i]);
		i++;
	}
	context->status_index = i;
	context->envs[i] = ft_strdup("?=0");
	setup_pwd(context);
}
