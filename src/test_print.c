/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/17 10:16:45 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_args(char **args)
{
	int	i;

	ft_printf("\n\n");
	i = 0;
	while (args[i] != 0)
	{
		ft_printf("args[%d]=%s\n", i, args[i]);
		i++;
	}
	printf("\n\n");
}

// needs remove
// Function to print commands for debugging purposes needs to be commented out before release
void	print_commands(t_commands *commands)
{
	if (commands == NULL || commands->fcommand == NULL)
		return ;
	for (int j = 0; commands->fcommand[j] != NULL; j++)
	{
		ft_printf("Command %d:\n", j);
		if (commands->fcommand[j]->command)
		{
			for (int k = 0; commands->fcommand[j]->command[k] != NULL; k++)
			{
				ft_printf("  Arg %d: %s\n", k,
					commands->fcommand[j]->command[k]);
			}
		}
		if (commands->fcommand[j]->redirections)
		{ // Check if redirections is not NULL
			if (commands->fcommand[j]->redirections->in)
			{
				for (int k = 0; commands->fcommand[j]->redirections->in[k] != NULL; k++)
				{
					ft_printf("  Input Redirection: %s\n",
						commands->fcommand[j]->redirections->in[k]);
				}
			}
			if (commands->fcommand[j]->redirections->out)
			{
				for (int k = 0; commands->fcommand[j]->redirections->out[k] != NULL; k++)
				{
					ft_printf("  Output Redirection: %s\n",
						commands->fcommand[j]->redirections->out[k]);
				}
			}
			if (commands->fcommand[j]->redirections->append)
			{
				for (int k = 0; commands->fcommand[j]->redirections->append[k] != NULL; k++)
				{
					ft_printf("  Append Redirection: %s\n",
						commands->fcommand[j]->redirections->append[k]);
				}
			}
			if (commands->fcommand[j]->redirections->here)
			{
				ft_printf("  Here Document:\n%s\n",
					commands->fcommand[j]->redirections->here);
			}
		}
	}
}

/*needs remove*/
/* Function to print each command in the split array, handling NULLs clearly */
void	print_split(char **splited_command)
{
	// Check if the argument is NULL
	if (splited_command == NULL)
	{
		ft_printf("Error: The argument 'splited_command' is NULL.\n");
		return ;
	}

	int i = 0; // Initialize index to 0

	// Iterate over the array
	while (splited_command[i] != NULL)
	{
		if (splited_command[i] == NULL)
			ft_printf("Command %d: (null)\n", i);
		else
			ft_printf("Command %d: %s\n", i, splited_command[i]);
		i++; // Move to the next command
	}

	// After the loop, print the total number of commands
	ft_printf("Total commands printed: %d\n", i);
}


#include <stdio.h>

/* Helper function to print strings safely */
void print_string(const char *label, char *str)
{
    if (str)
        printf("%s: %s\n", label, str);
    else
        printf("%s: (null)\n", label);
}

/* Helper function to print string arrays safely */
void print_string_array(const char *label, char **array)
{
    if (!array)
    {
        printf("%s: (null)\n", label);
        return;
    }

    int i = 0;
    while (array[i])
    {
        printf("%s[%d]: %s\n", label, i, array[i]);
        i++;
    }
    if (i == 0) // If array is empty
        printf("%s: (empty)\n", label);
}

/* Function to print t_redirections structure */
void print_redirections(t_redirections *redirections)
{
    if (!redirections)
    {
        printf("redirections: (null)\n");
        return;
    }

    print_string("here", redirections->here);
    print_string_array("append", redirections->append);
    print_string_array("in", redirections->in);
    print_string_array("out", redirections->out);
}

/* Function to print t_fcommand structure */
void print_fcommand(t_fcommand *fcommand)
{
    if (!fcommand)
    {
        printf("fcommand: (null)\n");
        return;
    }

    print_string_array("command", fcommand->command);
    print_redirections(fcommand->redirections);
}

/* Function to print t_fcommand **fcommand array within t_commands structure */
void print_commands_fcommand(t_commands *commands)
{
    if (!commands)
    {
        printf("commands: (null)\n");
        return;
    }

    if (!commands->fcommand)
    {
        printf("fcommand: (null)\n");
        return;
    }

    int i = 0;
    while (commands->fcommand[i])
    {
        printf("fcommand[%d]:\n", i);
        print_fcommand(commands->fcommand[i]);
        i++;
    }
    if (i == 0) // If fcommand array is empty
        printf("fcommand: (empty)\n");
}