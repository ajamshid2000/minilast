NAME = minishell
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ./includes/ -I /usr/include/readline
LIB = ./libft/libft.a
SRCS = ./src/env.c ./src/pipe.c ./src/path_finder.c ./src/cd.c ./src/echo.c ./src/redirection.c ./src/ft.c ./src/export.c ./src/create.c ./src/free_all.c ./src/execute_builtin.c ./src/redirect_here_in.c ./src/env_and_export.c ./src/errors.c ./src/main2.c ./src/main.c ./src/execute.c ./src/parsing.c ./src/util.c ./src/util2.c ./src/util3.c ./src/util4.c ./src/signals.c ./src/test_print.c ./src/util_quote.c ./src/util_string.c ./src/util_init_commands.c ./src/checker.c ./src/util_table.c ./src/util_table_2.c ./src/initialize_commands.c ./src/add_redirection.c ./src/add_redirection_2.c ./src/add_redirection_3.c ./src/init_fcommands.c ./src/add_cmd.c ./src/add_cmd_2.c ./src/expand_variable.c ./src/expand_variable_2.c ./src/quotes_checks.c ./src/my_free.c ./src/process_commands.c ./src/heredoc.c ./src/heredoc_2.c ./src/split.c ./src/split_2.c ./src/split_3.c ./src/split_4.c ./src/heredoc_3.c ./src/exit.c ./src/checker_2.c
OBJS = $(SRCS:.c=.o)
# Libraries to link
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C ./libft
	cc $(CFLAGS) $(OBJS) $(LIB) $(LIBS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -s -C ./libft clean

fclean: clean
	rm -f $(NAME)
	@make -s -C ./libft fclean

re: fclean all

.PHONY: all bonus clean fclean re