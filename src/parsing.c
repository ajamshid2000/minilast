/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/19 16:32:11 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to allocate and initialize the result buffer */
char	*allocate_result_buffer(const char *str)
{
	size_t	initial_size;
	char	*result;

	initial_size = ft_strlen(str) + 1;
	result = malloc(initial_size);
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	result[0] = '\0';
	return (result);
}
void print_commands_fcommand(t_commands *commands);
 void	print_commands(t_commands *commands);
 void	print_split(char **splited_command);
/* eval2 */
/*
int	eval2(char *input, t_env *env, int *status)
{
	char		*spaced;
	char		**splited_command;
	t_commands	*commands;
	int			exit_flag;

	
	if(is_only_space(input)==1){
		free(input);
		*status=0;
		return (0);
	}
	
	if(is_pipe_empty(input)==1 ){
		free(input);
		*status=2;
		return (0);
	}
	
	if( is_redirect_empty(input)==1){
		free(input);
		*status=2;
		return (0);
	}
	if (!allocate_and_check_memory(input, &spaced, &splited_command))
	{
		free(input);
		*status=2;
		return (1);
	}
	
	if (!check_redirections_and_pipes(splited_command, spaced))
	{
		free_input_split(input, splited_command);
		free(spaced);
		*status=2;
		return (1);
	}
	free(spaced);
	initialize_commands_and_env(&commands, &env, splited_command);
	process_commands(env, commands, splited_command, *status);
	add_line_heredoc(commands);
	//print_split(splited_command);
	free_input_split(input, splited_command);
	g_ctrl_c_status = 1;
	//print_commands_fcommand(commands);
	exit_flag = execute_pipes(commands);
	*status = commands->status;
	my_free_cmd(commands);
	return (exit_flag);
}
*/

int eval2(char *input, t_env *env, int *status)
{
    char        *spaced;
    char        **splited_command;
    t_commands  *commands;
    int         exit_flag;

    // Check if the input is only spaces
    if (is_only_space(input) == 1)
    {
        free(input);
        *status = 0;
        return 0;
    }
	int start=0;
	int check=rec_check(input,&start);
	if (check!=-1){
		ft_putstr_fd(" syntax error near unexpected token `",2);
		if(input[check+start]==0){
			ft_putstr_fd("newline",2);
		}else{
			ft_putchar_fd(input[check+start],2);
			if(input[check+start]==input[check+start+1])
				ft_putchar_fd(input[check+start],2);
		}
		ft_putstr_fd("'\n",2);
		free(input);
        *status = 2;
        return 0;
	}


    if (!allocate_and_check_memory(input, &spaced, &splited_command))
    {
        free(input);
        *status = 2;
        return 1;
    }

    if (!check_redirections_and_pipes(splited_command, spaced))
    {
        free_input_split(input, splited_command);
        free(spaced);
        *status = 2;
        return 1;
    }

    free(spaced);
    initialize_commands_and_env(&commands, &env, splited_command);
    process_commands(env, commands, splited_command, *status);
    add_line_heredoc(commands);
    free_input_split(input, splited_command);
    g_ctrl_c_status = 1;
    exit_flag = execute_pipes(commands);
    *status = commands->status;
    my_free_cmd(commands);
    return exit_flag;
}
