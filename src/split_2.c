/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/14 09:38:50 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to handle the split action and update results */
int	handle_split_action(t_split_context *ctx)
{
	ctx->result[*ctx->num_split] = ft_substr(ctx->s, ctx->start, ctx->count
			+ ((ctx->s[ctx->i + 1] == '\0') && (ctx->s[ctx->i] != ctx->c
					|| (ctx->s[ctx->i] == ctx->c && is_escaped(ctx->s,
							ctx->i)))));
	if (ctx->result[*ctx->num_split] == 0)
	{
		free_all_from(ctx->result, *ctx->num_split);
		return (0);
	}
	(*ctx->num_split)++;
	return (1);
}

/* Function to update count based on conditions */
int	should_update_count(t_split_context *ctx)
{
	return (ctx->s[ctx->i] != ctx->c || is_escaped(ctx->s, ctx->i)
		|| is_in_double_quote(ctx->s, ctx->i) || is_in_quote_simple(ctx->s,
			ctx->i));
}

void	process_split_logic(t_split_context *ctx)
{
	while (ctx->s[++ctx->i])
	{
		if (ctx->count == 0)
			ctx->start = ctx->i;
		if (is_split_condition(ctx->s, ctx->c, ctx->count, ctx->i))
		{
			if (!handle_split_action(ctx))
				return ;
			ctx->count = 0;
		}
		else if (should_update_count(ctx))
			ctx->count++;
	}
}

void	fill_result(char *s, char c, char **result)
{
	t_split_context	ctx;

	ctx.s = s;
	ctx.c = c;
	ctx.result = result;
	ctx.num_split = (int *)malloc(sizeof(int));
	if (ctx.num_split == NULL)
		return ;
	*ctx.num_split = 0;
	ctx.i = -1;
	ctx.count = 0;
	ctx.start = 0;
	process_split_logic(&ctx);
	free(ctx.num_split);
}

char	**custom_ft_split(char *s, char c)
{
	int		num_split;
	char	**result;

	if (s == 0)
		return (0);
	num_split = ft_count_split(s, c);
	result = malloc((num_split + 1) * sizeof(char *));
	if (result == 0)
		return (0);
	fill_result(s, c, result);
	result[num_split] = 0;
	return (result);
}
