# Resumo — Expander (concluído: aspas + $VAR/$?)

> Documento de contexto pra continuar o trabalho no Claude Code / VS Code.
> Parte do Minishell (42). Responsável por lexer, parser, expander: **rcosta**.

---

## Status atual

✅ **Expander implementado, integrado e já está na branch `master`** (push feito em 2026-06-13).
Build limpo (`-Wall -Wextra`, zero warnings), valgrind 0 leaks, norminette OK.

Arquivos:
- `expander.c` — `expand_line`, `expand_redirs`, `expand_command`, `expand`
- `expander_utils.c` — `get_var_value`, `append_str`, `is_var_char`, `get_var_name`

## O que faz

Roda em `main.c` entre `parse()` e `execute()`, via `expand(sh->cmds, sh)`.

Por string (args e redirs), uma máquina de estado de aspas (`quote = 0 / ' / "`)
faz **remoção de aspas + expansão de `$VAR` e `$?` na mesma passada**:
- dentro de `'...'`: nada expande, conteúdo literal
- dentro de `"..."`: `$VAR`/`$?` expandem
- fora de aspas: `$VAR`/`$?` expandem
- `$VAR` não definida → string vazia
- `$?` → `sh->exit_status` via `ft_itoa`
- `$` sozinho (sem nome válido depois) → fica `$` literal

Construção da string de saída é incremental via `ft_strjoin`/`append_str`
(não dá mais pra pré-alocar com `strlen`, porque `$VAR` pode crescer o tamanho).

Casos testados e OK: `echo "hello $USER world"`, `echo '$USER'`,
`echo "exit code is $?"`, `echo '"$USER"'`, `echo "'$USER'"`,
`cat > "arq.txt"`, `> arquivo.txt` (só redir), heredoc com `$USER`.

## Bugs pré-existentes corrigidos no caminho (na `master`, não eram meus)

- `minishell.h`: `t_command` era usado antes de declarado (reordenado);
  faltava `;` no protótipo de `create_heredoc`.
- `main.c`: chamava `tokenize(line, sh->exit_status)` mas a função real
  só aceita 1 arg — corrigido para `tokenize(line)`.
- `main.c`: faltava `free_tokens(tokens)` no loop — leak em todo comando.
- `parser_utils.c`: `new_redir` não inicializava `redir->expand`
  (lido sem init em `create_heredoc`) — agora inicializa com `1`.
- `lexer/main_lexer.c`: era um `main()` de debug duplicado, conflitava
  com `main.c` — removido.

## Pendências / próximos passos possíveis

- **Heredoc + `redir->expand`**: hoje todo heredoc expande `$VAR` (default `1`
  em `new_redir`). O bash só expande se o delimitador do heredoc **não** está
  entre aspas (`<<EOF` expande, `<<'EOF'` não). Detectar isso exigiria o
  parser/lexer marcar `redir->expand` conforme o delimitador veio com aspas —
  ainda não implementado.
- Resto (lexer, parser, remoção de aspas) está pronto e validado conforme
  combinado com a dupla (executor é responsabilidade deles).
