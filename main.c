/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:04:49 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 15:46:17 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_signal = 0;

static	void	run_tokens(t_token *tokens, t_shell *sh)
{
	sh->cmds = parse(tokens);
	if (sh->cmds)
	{
		expand(sh->cmds, sh);
		execute(sh->cmds, sh);
	}
	free_commands(sh->cmds);
	sh->cmds = NULL;
	free_tokens(tokens);
	sh->tokens = NULL;
}

static	void	process_line(char *line, t_shell *sh)
{
	t_token	*tokens;

	tokens = tokenize(line);
	sh->tokens = tokens;
	if (!tokens)
	{
		sh->exit_status = 2;
		return ;
	}
	if (validate_tokens(tokens) == -1)
	{
		sh->exit_status = 2;
		free_tokens(tokens);
		sh->tokens = NULL;
		return ;
	}
	run_tokens(tokens, sh);
}

static	void	shell_loop(t_shell *sh)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (g_signal == SIGINT)
		{
			sh->exit_status = 128 + SIGINT;
			g_signal = 0;
		}
		if (*line)
			add_history(line);
		process_line(line, sh);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh.env = env_init(envp);
	sh.cmds = NULL;
	sh.tokens = NULL;
	sh.exit_status = 0;
	setup_signals();
	shell_loop(&sh);
	free_env(sh.env);
	write(1, "exit\n", 5);
	return (sh.exit_status);
}
