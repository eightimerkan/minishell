/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcosar <mcosar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:51:53 by mcosar            #+#    #+#             */
/*   Updated: 2023/03/18 05:48:57 by mcosar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include "readline/history.h"
# include "readline/readline.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/cdefs.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# ifndef HERE_DOC
#  define HERE_DOC "heredoc> "
# endif

# ifndef PIPE_HERE_DOC
#  define PIPE_HERE_DOC "pipe heredoc> "
# endif

typedef struct s_temp
{
	size_t		i;
	int			j;
	size_t		k;
	int			is_d_quote;
	int			is_s_quote;
	int			is_space;
	int			c;
	int			index;
	char		**commands;
}				t_temp;

typedef struct s_temp2
{
	int			i;
	int			is_d_quote;
	int			is_s_quote;
}				t_temp2;

typedef struct s_temp3
{
	int			i;
	int			j;
	int			k;
	int			l;
	char		*new_line;
	char		*new_ref;
	char		*new_ref_env;
}				t_temp3;

typedef struct s_temp4
{
	int			i;
	int			j;
	int			k;
	char		*str;
	char		*env;
	char		*env_var;
}				t_temp4;

typedef struct s_temp5
{
	int			pipefd[2];
	int			pipefd1[2];
	char		*out_content;
	int			is_out;
	int			pid;
}				t_temp5;

typedef struct s_envpath
{
	char		*name;
	char		*path;
}				t_envpath;

typedef struct s_redirect
{
	int			type;
	char		*ref;
}				t_redirect;

typedef struct s_context
{
	char		**pipes;
	int			*pipes_status;
	int			process_index;
	char		*base_line;
	char		*line;
	int			command_not_found;
	char		**envs;
	char		***commands;
	int			status_index;
	t_envpath	*envpaths;
	t_redirect	*redirects;
	char		*prompt_name;
	int			command_error;
	int			ignore_redirect;
	int			not_found;
	char		cwd[PATH_MAX];
}				t_context;

void			setup_term(t_context *context);
int				setup_envpaths_files(t_context *context, DIR *dp, int index,
					int i);
void			setup_envpaths_dirs(t_context *context);
void			setup_envs(t_context *context, char **envp);
int				ft_arr_len(char **arr);
int				ft_redirect_len(t_redirect *redirects);
int				ft_input_redirect_len(t_redirect *redirects);
int				ft_is_double_input_exist(t_redirect *redirects);
int				ft_output_redirect_len(t_redirect *redirects);
void			exit_on_ctrl_d(char *src, t_context *context);
void			worker(t_context *context);
int				clear_history_command(t_context *context, int is_effect);
int				print_pwd(t_context *context);
int				parse_checker(t_context *context);
int				parse_pipes(t_context *context);
int				ft_split_is_matched(int start_index, char *string,
					char *seperator);
int				is_have_peer(const char *s, int index, char c);
void			parser_core(t_context *context);
int				parser(t_context *context);
char			**ft_split_redirection(char *string, char **seperator,
					int is_include_seperator);
int				parse_redirections(t_context *context);
char			*get_environment_variable(t_context *context, char *key);
int				process_command(t_context *context);
int				process_command_effect(t_context *context);
void			ft_arr_free(char **tab);
char			**ft_split_command(const char *s, t_context *context,
					int is_replace_env);
int				clear_term(t_context *context);
int				exit_term(t_context *context, int is_effect);
int				run_builtin(t_context *context);
char			*search_command(t_context *context, char *key,
					t_envpath *env_paths);
int				cd_term(t_context *context, int is_effect);
void			print_env(t_context *context);
int				env_term(t_context *context);
int				export_env(t_context *context, int is_effect);
int				unset_env(t_context *context, int is_effect);
int				pre_process(t_context *context, int pipe_desc[2],
					int **pipefds);
int				run_builtin_direct(t_context *context);
char			*replace_env(t_context *context, char *command);
void			ft_arr_bzero(char **tab);
void			run_pipe(t_context *context);
void			process_simple_input_redirect(t_context *context, int i,
					int pipefd[2]);
void			process_double_input_redirect(t_context *context, int i,
					int pipefd[2]);
void			process_input_redirects(t_context *context, t_temp5 *temp);
void			process_simple_output_redirect(t_context *context, int i,
					char *out_content);
void			process_double_output_redirect(t_context *context, int i,
					char *out_content);
int				process_output_redirects(t_context *context, char *out_content,
					int **pipefds);
int				process_out_clone(t_context *context, int pipe_desc[2],
					char *out_content, int **pipefds);
void			process_clone_inputs_child(t_context *context, int pipefd[2],
					int pipefd1[2]);
void			process_clone_inputs_parent(int pipefd[2], int pipefd1[2],
					int *pid, char **out_content);
void			process_clone_inputs(t_context *context, t_temp5 *temp);
void			setup_func(t_temp *context, const char *s);
int				check_dd_quote(t_temp *context, const char *s);
int				check_ss_quote(t_temp *context, const char *s);
void			func_one(t_temp *context);
void			func_two(t_temp *context, const char *s, t_context *g_context,
					int is_replace_env);
void			func_three(t_temp *context, const char *s);
size_t			ft_count_commands(const char *s);
int				redirect_utils(t_context *context, t_temp3 *temp);
int				redirect_utils2(t_context *context, t_temp3 *temp);
int				redirect_utils3(t_context *context, t_temp3 *temp);
int				redirect_utils4(t_context *context, t_temp3 *temp);
void			redirect_utils5(t_context *context, t_temp3 *temp);
void			redirect_utils6(t_context *context, t_temp3 *temp);
int				ref_length(char *line, int index);
void			setup_func2(t_temp3 *temp, t_context *context);
void			ft_env_path_free(t_context *context);
void			ft_redirects_free(t_context *context);
void			ft_pipefds_free(int **pipefds);
int				check_pipe_dd_quote(t_temp *context, const char *s);
int				check_pipe_ss_quote(t_temp *context, const char *s);
void			pipe_func_one(t_temp *context);
void			pipe_func_two(t_temp *context, const char *s);
char			**ft_pipe_split(char *string);
int				is_in_quote(const char *line, int index);
void			print_pure_env(t_context *context);
int				ft_count_pipes(char *str);
char			*split_replace_env(t_context *context, char *command,
					int index);
void			free_pipes(int **pipefd, int *pids, t_context *context);
void			pipe_process_free(t_context *context);
void			pipe_error_free(t_context *context, int redirect_result);
int				parse_error_free(t_context *context, int result);
int				**init_pipefd(t_context *context);
int				init_pipes(t_context *context, int i, int result);
int				init_redirect_utils(t_context *context, t_temp3 *temp);
int				init_redirect_utils2(t_context *context, t_temp3 *temp);
int				init_redirect_utils3(t_context *context, t_temp3 *temp);
int				init_redirect_utils4(t_context *context, t_temp3 *temp);
int				check_reverse_redirect(t_context *context);
int				check_redirect_ref(t_context *context);
int				parse_redirect_condition1(t_context *context, t_temp3 *temp);
int				parse_redirect_condition2(t_context *context, t_temp3 *temp);
int				ft_split_command_condition1(const char *s, t_temp *temp,
					t_context *context);
int				ft_split_command_condition2(const char *s, t_temp *temp,
					t_context *context);
void			split_command_end(t_temp *temp);
int				parse_redirect_condition3(t_context *context, t_temp3 *temp);
char			**init_unset_environment(t_context *context);
void			function_two_end(t_temp *context, t_context *g_context);
void			double_input_process(char *str, char **lines, int pipefd[2]);
void			close_pipes(int **pipefd);
void			process_output_command_direct(t_context *context,
					t_temp5 *temp);
void			process_output_command_redirects(t_context *context,
					int pipefd[2], int **pipefds);
int				ft_is_input_exist(t_redirect *redirects);
int				process_command_direct(t_context *context);
void			cd_absolute_path(t_context *context, char cwd[PATH_MAX]);
void			run_pipe_end(t_context *context, int **pipefd, int *pids);
void			wait_pids(t_context *context, int *pids);
void			interpret_echo_newline(t_context *context);
int				is_only_n(char *str);
int				init_setup_dirs(t_context *context, char *str, char ***paths);
int				is_directory(char *str);
void			update_status(t_context *context, int pid);
int				check_line_is_empty(t_context *context);
int				exit_error_check(t_context *context);
int				ft_isnumber(char *str);
void			close_pipes_except_output(int **pipefd);
void			update_status_without_pid(t_context *context, int status);
int				export_control(char *str);
int				empty_control(char *str);
void			double_input_signal(t_context *context, char **lines,
					char *str, int j);

#endif