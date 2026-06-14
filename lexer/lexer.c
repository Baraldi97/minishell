/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:54:32 by rcosta            #+#    #+#             */
/*   Updated: 2026/06/13 20:30:30 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir(char *input, int i, t_token **tokens)
{
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			add_token(tokens, new_token(TOKEN_HEREDOC, "<<"));
			return (2);
		}
		add_token(tokens, new_token(TOKEN_REDIR_IN, "<"));
		return (1);
	}
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			add_token(tokens, new_token(TOKEN_APPEND, ">>"));
			return (2);
		}
		add_token(tokens, new_token(TOKEN_REDIR_OUT, ">"));
		return (1);
	}
	return (0);
}

int	handle_word(char *input, int i, t_token **tokens)
{
	int		start;
	char	*word;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '\t'
		&& input[i] != '|' && input[i] != '<' && input[i] != '>'
		&& input[i] != '\'' && input[i] != '"')
		i++;
	word = ft_substr(input, start, i - start);
	add_token(tokens, new_token(TOKEN_WORD, word));
	free(word);
	return (i - start);
}

int	handle_quotes(char *input, int i, t_token **tokens)
{
	char	quote;
	int		start;
	char	*word;

	quote = input[i];
	start = i;
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
		return (-1);
	i++;
	word = ft_substr(input, start, i - start);
	add_token(tokens, new_token(TOKEN_WORD, word));
	free(word);
	return (i - start);
}

static int	process_token(char *input, int *i, t_token **tokens)
{
	int	consumed;

	if (input[*i] == ' ' || input[*i] == '\t')
		return ((*i)++, 0);
	if (input[*i] == '\'' || input[*i] == '"')
	{
		consumed = handle_quotes(input, *i, tokens);
		if (consumed == -1)
			return (-1);
		*i += consumed;
		return (0);
	}
	if (input[*i] == '|')
		return (add_token(tokens, new_token(TOKEN_PIPE, "|")), (*i)++, 0);
	if (input[*i] == '<' || input[*i] == '>')
		return (*i += handle_redir(input, *i, tokens), 0);
	*i += handle_word(input, *i, tokens);
	return (0);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (process_token(input, &i, &tokens) == -1)
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	add_token(&tokens, new_token(TOKEN_EOF, "EOF"));
	return (tokens);
}
