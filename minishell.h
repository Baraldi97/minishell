/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdavid-b <bdavid-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:02:24 by bdavid-b          #+#    #+#             */
/*   Updated: 2026/06/13 21:00:44 by bdavid-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "libft/printf/ft_printf.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	int		pp[2];
	int		prev;
	pid_t	last;
}	t_pipe;

//lexer_structs
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

//parser
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_env		*env;
	t_command	*cmds;
	int			exit_status;
}	t_shell;

//executor
extern sig_atomic_t	g_signal;
int			setup_redirections(t_command *cmd, t_shell *sh);
int			create_heredoc(t_redir *redir, t_shell *sh);
char		*find_path(char *cmd, t_env *env);
void		free_all(t_shell *sh);
void		execute(t_command *cmds, t_shell *sh);
//builtins
int			is_builtin(char *cmd);
int			run_builtin(t_command *cmd, t_shell *sh);
int			builtin_cd(char **args, t_env *env);
int			builtin_echo(char **args);
int			builtin_exit(char **args, t_shell *sh);
int			builtin_export(char **args, t_env *env);
int			builtin_pwd(void);
int			builtin_env(t_env *env);
int			builtin_unset(char **args, t_shell *sh);
//env
t_env		*env_new(char *key, char *value);
void		env_add_back(t_env **list, t_env *node);
t_env		*env_init(char **envp);
int			env_size(t_env *env);
char		*get_env_value(t_env *env, char *key);
char		**env_to_array(t_env *env);
void		update_env(t_env *env, char *key, char *value);
void		free_env(t_env *env);
//pipelines
void		exec_pipeline(t_command *cmds, t_shell *sh);
//signals
void		handle_sigint(int sig);
void		setup_signals(void);
void		signals_exec_mode(void);
//lexer
t_token		*new_token(t_token_type type, char *value);
void		add_token(t_token **lst, t_token *new);
void		free_tokens(t_token *tokens);
int			handle_redir(char *input, int i, t_token **tokens);
int			handle_word(char *input, int i, t_token **tokens);
int			handle_quotes(char *input, int i, t_token **tokens);
t_token		*tokenize(char *input);
//parser
void		free_commands(t_command *cmds);
void		free_redirs(t_redir *redirs);
t_command	*new_command(void);
void		add_command(t_command **list, t_command *new);
t_redir		*new_redir(t_token_type type, char *file);
void		add_redir(t_redir **list, t_redir *new);
int			validate_tokens(t_token *tokens);
t_command	*parse(t_token *tokens);
t_command	*parse_command(t_token **tokens);
void		parse_args(t_token **tokens, t_command *cmd);
void		parse_redir(t_token **tokens, t_command *cmd);
//expander
void		expand(t_command *cmds, t_shell *sh);
void		expand_command(t_command *cmd, t_shell *sh);
void		expand_redirs(t_redir *redir, t_shell *sh);
char		*expand_line(char *str, t_shell *sh);
char		*get_var_value(char *str, int *i, t_shell *sh);
char		*append_str(char *result, char *piece);
int			is_var_char(char c);

#endif