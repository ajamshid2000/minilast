/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/30 13:04:08 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
/*my include*/
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_env
{
	char			**env;
	struct s_env	*next;
}					t_env;

typedef struct s_redirnctions
{
	int				last_in;
	int				last_out;
	char			*last_in_name;
	char			*last_out_name;
	char			*here;
	char			**append;
	char			**in;
	char			**out;
}					t_redirections;

typedef struct s_fcommand
{
	int				error;
	char			**command;
	t_redirections	*redirections;
}					t_fcommand;

typedef struct s_commands
{
	int				status;
	int				j;
	int				last_fd;
	t_env			*env;
	t_fcommand		**fcommand;
	int				**pipe_fd;
	int				pipe_count;
}					t_commands;

int					pipe_replica(t_commands *commands);
char				*find_path(t_env *env, char **args);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strjoin_free(char const *s1, char const *s2);
char				**ft_split_one(char const *s, char c);
int					free_redirections(t_commands *commands);
void				print_pwd(char *pwd, int out_fd, t_commands *commands);
int					export_one(t_env *env, char *name, char *value, int out_fd);
int					export_multiple(t_env *env, t_commands *commands, int i,
						int out_fd);
int					echo(char **command, int out_fd, t_commands *commands);
int					echo_here(char *here, t_commands *commands);
int					cd(t_env *env, char **command, int out_fd,
						t_commands *commands);
int					is_builtin(char **command);

int					print_env(t_env *env, int out_fd);
int					env_remove(t_env *env, char **name, t_commands *commands);
char				*find_path(t_env *env, char **args);
t_env				*locate_env(t_env *env, char *keyword);
char				*find_value_of_env(t_env *env, char *name);
char				*find_value_of_env2(t_env *env, char *name);
int					env_add_last(t_env *env, char *name, char *value);
int					free_env_stack(t_env *env);
char				**create_env_array(t_env *env);
t_env				*create_env_stack(void);

int					out_and_append(t_fcommand *command, int read_end,
						int write_end);
int					set_fd(t_fcommand *command, int write_end);
int					execute_builtin(t_env *env, t_commands *commands, int i,
						int out_fd);
int					execute_pipes(t_commands *commands);
void				execute_command(t_commands *commands, int i, int in_fd,
						int out_fd);

int					print_error_execve(char *name);
void				print_error_read(char *name);
void				print_error_write(char *name);

int					free_table(char **env);
int					free_pipe(t_commands *commands);
int					free_all(t_commands *commands, char **environ);
int					exit_minishell(t_commands *commands, int i);
void				knock_out_char(char *str, char c);
int					check_name(char *name);
void				redirect_commands(t_commands *commands, int i, int in_fd,
						int out_fd);

/* -----------*/
extern int			g_ctrl_c_status;

typedef struct s_parsed_data
{
	char			*command;
	char			**args;
	char			**args_with_redirect;
	char			*input_redirection;
	char			*output_redirection;
	int				append_output;
	int				pipe;
	char			*input;
}					t_parsed_data;

/* Structure to hold the state variables */
typedef struct s_expand_state
{
	const char		*src;
	char			*dst;
	int				in_single_quotes;
	int				in_double_quotes;
	size_t			initial_size;
}					t_expand_state;

/* Structure to hold the context for variable expansion */
typedef struct s_expansion_context
{
	const char		**src;
	char			**dst;
	char			*result;
	size_t			*initial_size;
}					t_expansion_context;

/*signals.c*/
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				disable_quit_signal(void);
void				setup_signal_handlers(void);

/*util_quote.c*/
int					is_in_double_quote(char *string, size_t i);
int					is_escaped(char *string, size_t i);
int					is_in_quote_simple(char *string, size_t i);
int					is_quote_escaped(char *string, size_t i);

/*util_init_commands.c*/
int					count_pipes(char **cmd);
t_commands			*initialize_commands_and_env(t_commands **commands,
						t_env **env, char **splited_command);
t_commands			*create_and_init_commands(void);
void				init_commands(t_commands *commands);

/*checker.c*/
int					pipe_checker(char **cmd);
int					allocate_and_check_memory(char *input, char **spaced,
						char ***splited_command);
int					check_redirections_and_pipes(char **splited_command,
						char *spaced);
int					check_redirection(char *s);
/*util_table.c*/
char				**allocate_initial_table(char *new_string);
int					count_strings_in_table(char **table);
char				**reallocate_table(char **table, int count);
int					add_string_to_table_helper(char **table, char *new_string,
						int count);
char				**add_string_to_table(char **table, char *new_string);

/*util_table_2.c*/

char				**ft_realloc_table(char **table, int new_count,
						int old_count);
size_t				get_array_size(char **array);
char				*duplicate_string(char *source);
char				**reallocate_string_array(char **array, size_t new_size);
char				**add_string_to_array(char **array, char *new_string);
/*util_string.c*/
size_t				my_strcpy(char *dst, const char *src);
char				*clone_string(const char *str);

/*initialize_commands.c*/
t_commands			*initialize_fcommand_array(t_commands *commands);
t_commands			*initialize_fcommand_element(t_commands *commands,
						int id_cmd);
t_commands			*initialize_redirections(t_commands *commands, int id_cmd);

/*add_redirection.c*/
t_commands			*add_output_redirection(t_commands *commands, int id_cmd,
						char *filename);
t_commands			*add_out(t_commands *commands, int id_cmd, char *filename);
t_commands			*add_append_redirection(t_commands *commands, int id_cmd,
						char *filename);
t_commands			*add_append(t_commands *commands, int id_cmd,
						char *filename);
t_commands			*add_input_redirection(t_commands *commands, int id_cmd,
						char *filename);
/*add_redirection_2.c*/
t_commands			*add_in(t_commands *commands, int id_cmd, char *filename);
int					validate_inputs(t_commands *commands,
						char *heredoc_content);
int					ensure_redirections_initialized(t_commands *commands,
						int id_cmd);
void				allocate_or_append_heredoc_content(char **here_field,
						char *heredoc_content);
int					check_validity_of_infile(char *name);
/*util4.c*/
void				*my_realloc(void *ptr, size_t new_size, size_t old_size);

/*add_redirection_3.c*/
t_commands			*add_end_text(t_commands *commands, int id_cmd,
						char *heredoc_content);
void				handle_heredoc_content(t_commands *commands, int id_cmd,
						char *heredoc_content);
void				knock_out_char(char *str, char c);
int					check_validity_of_outfile(char *name, int i);

/*init_fcommands.c*/
int					calculate_current_size(t_commands *commands);
void				initialize_new_slots(t_fcommand **fcommand, int start_index,
						int end_index);
t_fcommand			**reallocate_fcommand_array(t_fcommand **fcommand,
						int required_size, int current_size);
int					ensure_fcommand_capacity(t_commands *commands,
						int required_size);
t_fcommand			*initialize_fcommand(void);

/*add_cmd.c*/
t_commands			*add_cmd_tab(t_commands *commands, int id_cmd,
						char *cmd_arg);
int					ensure_command_capacity(t_commands *commands,
						int required_capacity);
int					initialize_command_if_needed(t_commands *commands,
						int id_cmd);
char				*process_command_argument(char *cmd_arg);
t_commands			*add_processed_command_to_array(t_commands *commands,
						int id_cmd, char *cmd_to_add, char *cmd_arg);

/*add_cmd_2.c*/
int					allocate_fcommand_array_if_null(t_commands *commands,
						int required_size);
int					validate_arguments(t_commands *commands, char *cmd_arg);
/*expand_variable.c*/
void				append_character_with_space(const char **src, char **dst);
void				append_character_without_space(const char **src,
						char **dst);
void				process_character(t_env *env, t_expand_state *state,
						char **result, int status);
char				*find_value_of_env(t_env *env, char *name);
void				expand_and_replace_variables(t_env *env,
						char **splited_command, int i, int status);
/*expand_variable_2.c*/
const char			*extract_variable_name(const char **src, size_t *var_len);
char				*allocate_and_initialize_var_name(const char *var_start,
						size_t var_len);
char				*expand_variable_and_adjust_result(char *var_value,
						char **dst, char *result, size_t *initial_size);
t_expansion_context	initialize_expansion_context(const char **src, char **dst,
						char *result, size_t *initial_size);
char				*process_variable_expansion(t_env *env,
						t_expansion_context *ctx, int status);
/*expand_variable_3.c*/
char				*expand_variables2(t_env *env, const char *str, int status);
t_expand_state		initialize_expand_state(const char *str);
/*quotes_checks.c*/
int					is_quote(char c);
int					is_escape_char(char c);
int					toggle_quote(char c, int *in_single_quotes,
						int *in_double_quotes);
int					handle_escape(const char *str, size_t *i, char *new_str,
						size_t *j);
/*my_free.c*/
void				my_free_cmd(t_commands *commands);
void				free_input_split(char *input, char **splited_command);
void				free_split(char **splited_command);

/*process_commands.c*/
void				append_character(const char **src, char **dst);
t_commands			*handle_redirections(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
void				handle_pipe_command(int *id_cmd);
t_commands			*handle_normal_command(t_commands *commands, int id_cmd,
						char *command);
t_commands			*process_redirection_commands(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
t_commands			*process_normal_command(t_commands *commands, int id_cmd,
						char *command);
/*process_commands_2.c*/
int					is_redirection_operator(char *cmd);
int					is_pipe_operator(char *cmd);
t_commands			*handle_redirection(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
t_commands			*handle_normal_command2(t_commands *commands, int id_cmd,
						char *cmd);
t_commands			*process_redirection(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
/*process_commands_3.c*/
void				process_pipe(int *id_cmd);
t_commands			*process_normal(t_commands *commands, int id_cmd,
						char *command);
t_commands			*process_single_command(t_commands *commands,
						char **splited_command, int *i, int *id_cmd);
t_commands			*process_commands(t_commands *commands,
						char **splited_command);

/*parsing.c*/
char				*allocate_result_buffer(const char *str);
int					eval2(char *input, t_env *env, int *status);
/*heredoc.c*/
char				*reallocate_content(char *content, size_t *capacity,
						size_t new_size);
void				append_line_to_content(char *content, const char *line,
						size_t *content_size);
int					process_line(char **content, size_t *content_size,
						size_t *content_capacity, const char *line);
int					handle_line_input(char **content, size_t *content_size,
						size_t *content_capacity, const char *stop_word);
char				*handle_heredoc(const char *stop_word);
/*heredoc_2.c*/
char				*allocate_memory(size_t *capacity);
char				*read_input_line(void);
int					is_stop_word(const char *line, const char *stop_word);
int					is_null_commands(t_commands *commands);
void				add_newline_to_heredoc(t_redirections *redir);
/*split.c*/
void				free_all_from(char **result, size_t i);
int					ft_count_split(char *s, char c);
void				init_variables(int *count, int *start, int *num_split,
						int *i);
int					is_split_condition(char *s, char c, int count, int i);
/*split_2.c*/

typedef struct s_split_context
{
	char			*s;
	char			c;
	char			**result;
	int				*num_split;
	int				start;
	int				count;
	int				i;
}					t_split_context;

int					handle_split_action(t_split_context *ctx);
int					should_update_count(t_split_context *ctx);
void				fill_result(char *s, char c, char **result);
char				**custom_ft_split(char *s, char c);
/*split_3.c*/
int					needs_space_before(const char *input, size_t i);
int					needs_space_after(const char *input, size_t i);
size_t				insert_redirection_with_spaces(char *new_str, size_t j,
						const char *input, size_t *i);
int					needs_space_before_pipe(const char *input, size_t i);
int					needs_space_after_pipe(const char *input, size_t i);
/*split_4.c*/
char				*realloc_with_spaces(const char *input);
size_t				insert_pipe_with_spaces(char *new_str, size_t j,
						const char *input, size_t *i);
char				*reallocate_if_necessary(char *new_str, size_t *new_len,
						size_t j);
size_t				copy_or_process_char(char *new_str, const char *input,
						size_t *i, size_t j);
/*util.c*/
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_isspace(int c);
char				*ft_strndup(const char *s, size_t n);
void				*my_realloc(void *ptr, size_t new_size, size_t old_size);
char				*ft_strcat(char *dest, const char *src);
/*util3.c*/

int					check_redirection_validity(char **args_with_redirect,
						int *index);
int					validate_redirection_type(char **args_with_redirect,
						int *index);
int					validate_redirection(char **args_with_redirect, int *index);
/*util4.c*/
int					file_exists(char *filename);
int					is_valid_filename(char *filename);
int					find_unescaped_unquoted_index(const char *string,
						const char *substring);
/*heredoc_3.c*/
void				apply_redirection_changes(t_fcommand *cmd);
void				traverse_commands(t_commands *commands);
void				add_line_heredoc(t_commands *commands);
/*checker_2.c*/
int					is_only_space(char *str);
int					rec_check(char *s, int start);
int					check_error2(char *s, int start);
/*expand_variable_3.c*/
char				*expand_and_replace_variables_string(t_env *env,
						char *command, int status);
t_expand_state		initialize_expand_state(const char *str);
/*expand_variable_4.c*/
char				*expand_variables2(t_env *env, const char *str, int status);
void				expand_string(t_env *env, t_expand_state *state,
						t_expansion_context *ctx, int status);
void				handle_variable_expansion(t_env *env, t_expand_state *state,
						t_expansion_context *ctx, int status);
int					should_expand_variable(t_expand_state state);
int					should_process_escape(t_expand_state state);
/*expand_variable_5.c*/
char				*allocate_initial_result(char *var_value, char **dst,
						char *result, size_t *initial_size);
int					should_reallocate_result(size_t needed_size,
						size_t initial_size);
char				*reallocate_result(char *result, char **dst,
						size_t needed_size, size_t *initial_size);
char				*copy_variable_value(char *dst, char *var_value);
char				*expand_variable_and_adjust_result(char *var_value,
						char **dst, char *result, size_t *initial_size);
/*quotes_checks_2.c*/
void				init_variable_quotes(size_t *i, size_t *j, int *in_s_q,
						int *in_d_q);
char				*remove_quotes(const char *str);
void				handle_quote_state(char ch, int *in_single_quotes,
						int *in_double_quotes);
void				process_escaped_character(const char **src, char **dst);

/*checker_3.c*/
int					rec_check(char *s, int start);
int					if_check_is_1(char *input, int check, int *status);
/*handle_redirections.c*/
t_commands			*handle_output_redirection(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
t_commands			*handle_append_redirection(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
t_commands			*handle_input_redirection(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
t_commands			*handle_heredoc_redirection(t_commands *commands,
						char **splited_command, int *i, int id_cmd);
t_commands			*handle_redirections(t_commands *commands,
						char **splited_command, int *i, int id_cmd);

/*new*/
char				*expand_and_replace_variables_string(t_env *env,
						char *command, int status);
int					check_redirection_2(char *s, int i);
int					is_quote_escaped(char *string, size_t i);

#endif
