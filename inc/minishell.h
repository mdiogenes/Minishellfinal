/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:36:51 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:51:41 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <sys/param.h>
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>

# define DEBUG 0
# define MS_STDOUT STDERR_FILENO
# define MS_STDIN STDIN_FILENO
# define MS_STDERR STDERR_FILENO
# define IS_TRUE  1
# define IS_FALSE 0
# define SUCCESS 0
# define ERROR 1
# define IS_CMD 1
# define NO_CMD 0
# define ERR_CD 0
# define ERR_CMD 1
# define ERR_EXIT 2
# define ERR_PIPE 3
# define ERR_GEN 4
# define MSG_MANY_ARG "too many arguments"
# define MSG_NUM_ARG "numeric argument required"
# define MSG_SYNTAX "syntax error"
# define MSG_SYNTAX_UNX "syntax error near unexpected token "
# define MSG_ERR_IDNT "not a valid identifier"
# define MSG_ERR_CMD "command not found"
# define MSG_ERR_NOVALID "not a valid identifier"
# define MSG_ERR_UNSET "not set"
# define MSG_ERR_EOF "unexpected end of file"
# define MSG_ERR_CD "No such file or directory"
# define PIPE_WRITE 1
# define PIPE_READ 0
# define TKN_STDIN 0
# define TKN_PIPEIN 1
# define TKN_STDOUT 0
# define TKN_PIPEOUT 1
# define SYS_VAR 1
# define SYS_HIDDEN 2
# define FROM_PARSE 0
# define FROM_WILDCARD 2
# define FROM_EXPAND 3
# define FROM_NO_PATH 4
# define SILENCED_CHECK 5
# define FROM_NBSP 1
# define FROM_EXP_ARG 1
# define TO_EXP_ARG 2
# define FIRST_PIPE 6

typedef enum e_cmd
{
	NO_TYPE,
	CMD_LITERAL,
	CMD_EXPAND,
	CMD_ENV_VAR,
	CMD_PWD,
	CMD_CD,
	CMD_ECHO,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_EXE,
	CMD_ASSIGN,
	CMD_ASSIGN_LE,
	CMD_ASSIGN_BE,
	CMD_ASSIGN_RE,
	RDR_PIPE,
	RDR_TO_FILE,
	RDR_APP_FILE,
	IMP_FROM_FILE,
	IMP_HEREDOC,
	NEXT_CMD,
	OPR_OR,
	OPR_AND,
	OPR_OPEN_K,
	OPR_CLOSE_K
}	t_cmd;

typedef enum e_meta
{
	MTA_NOTYPE,
	MTA_NULL_TOKEN,
	MTA_ASSIGN,
	MTA_ASSIGN_EMPTY,
	MTA_TO_EXPORT,
	MTA_ARGS,
	MTA_BUILDIN,
	MTA_OUTEXE,
	MTA_REDIR_FILE,
	MTA_REDIR,
	MTA_NEXT,
	MTA_OPERATOR,
	MTA_KEYS
}	t_meta;

typedef struct s_token
{
	char			*token;
	int				type;
	int				meta;
	char			in;
	char			out;
	char			status;
	int				special_tkn;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*args;
}	t_token;

typedef struct s_ms
{
	int				**pipes;
	int				status;
	long long int	exitstatus;
	int				level;
	int				pid;
	int				pid_child;
	int				status_tkn;
	char			*homecons;
	char			*line;
	char			*prompt;
	char			*path;
	struct s_token	*first_token;
	struct s_token	*last_token;
	struct s_token	*env;
	char			**bin_paths;
}	t_ms;

t_ms	*g_mini;

//------------------------- >>>> BNS - bonus
int		ft_bichito(t_ms *mini, t_token *node);
int		ft_operator(t_ms *mini);
int		ft_regex(char *haystack, char *pattern);
void	ft_sub_mini(t_ms *mini);
int		ft_keys_process(t_ms *mini);
int		ft_solve_wildcards(t_ms *mini, t_token *cmd, t_token *node);
//------------------------- >>>> CMD - commands
int		ft_cd(t_ms *mini);
int		ft_echo(t_ms *mini);
int		ft_env(t_ms *mini);
int		ft_exit(t_ms *mini);
int		ft_export_cmd(t_ms *mini);
int		ft_cmd_null(t_ms *mini);
int		ft_pwd(t_ms *mini);
int		ft_dup_file(t_ms *mini);
int		ft_inp_from_file(t_ms *mini);
int		ft_heredoc(t_ms *mini);
t_token	*ft_find_envar(char *needle, t_token **prev, t_ms *mini);
t_token	*ft_delete_env(t_token *node, t_token *prev, t_ms *mini);
int		ft_unset(t_ms *mini);
//------------------------- >>>> ERR - errors
int		ft_error_comands(int error, char *cmd, char *msg, t_ms *mini);
int		ft_export_id_error(t_ms *mini, char *token);
int		ft_error_export(t_token *token, t_ms *mini);
int		ft_error_export_var(t_token *token, t_ms *mini);
int		ft_syntax_error(t_ms *mini, char token, int rpt);
int		ft_error_unset_var(char *msg, t_token *token, t_ms *mini);
int		ft_error_handler(int error, t_ms *mini);
void	ft_error_general(char *msg, t_ms *mini);
pid_t	ft_fork_err(t_ms *mini);
int		ft_shlvl_err(void);
int		ft_error_free(int error, t_ms *mini);
int		ft_redir_error(int error, char *name, t_ms *mini);
void	ft_child_signals_msg(int signum);
//------------------------- >>>> EXE - exec and pipes
int		ft_child_monitor(t_ms *mini, int total, pid_t pid);
pid_t	ft_fork_and_run(t_ms *mini, int n, int (*process)(t_ms *),
			int (*wait_exit)(t_ms *, int, pid_t));
int		ft_pipes(t_ms *mini);
void	pid_child(t_ms *mini, char **argv);
//------------------------- >>>> INP - parse and workflow
int		ft_count_brakets(t_ms *mini);
int		ft_open_brakets(t_ms *mini);
int		ft_open_logic(t_ms *mini);
int		ft_check_branch(t_ms *mini);
int		ft_read_from_node(char *token);
int		ft_get_meta_type(int type);
int		ft_check_input_export(t_ms *mini);
int		ft_load_input(t_ms *mini);
void	ft_export_fix(const char *s, size_t *len, size_t *i);
int		ft_load_strlen(t_ms *mini, char *s, int scn, size_t *len);
int		ft_open_nodes(t_ms *mini);
int		ft_parse(t_ms *mini);
void	ft_clean_quotes(t_ms *mini);
void	ft_prepare_node(t_ms *mini, t_token *token);
char	*ft_is_bin_exe(char *token, t_ms *mini, t_token *node);
int		ft_input_preprocess(t_ms *mini);
int		ft_inp_redir(t_ms *mini);
int		ft_workflow(t_ms *mini);
void	ft_workflow_check(t_ms *mini);
//------------------------- >>>> MS - main process
int		ft_do_expand(t_ms *mini, t_token *node);
int		ft_get_expand(t_ms *mini, t_token *node);
int		ft_expand_node(t_ms *mini, t_token *node);
void	ft_token_dir(t_ms *mini);
int		ft_build_in(t_ms *mini);
int		set_signal(t_ms *mini);
void	signal_ctrld(t_ms *mini);
void	signal_handler(int signum);
//------------------------- >>>> UTL - general utilities
void	ft_get_line_argv(t_ms *mini, char *argv[]);
char	**ft_build_argv(t_ms *mini, t_token *token);
char	**ft_build_arenv(t_ms *mini, t_token *token);
int		ft_delete_args(t_token *node);
int		ft_send_to_atoi(char *str);
int		ft_delete_node(t_token *node);
int		ft_process_branch(t_ms *mini);
t_token	*ft_remove_node(t_token *node, t_token *prev, t_token **head);
void	ft_clear_nodes(t_ms *mini);
int		mini_getpid(t_ms *mini, int padrehijo);
int		ft_size_branch(t_token *lst);
size_t	ft_count_node(t_ms *mini);
void	ft_inp_append(t_token **lst, t_token *new);
void	ft_new_token(t_ms *mini, t_token *new);
t_token	*ft_inp_new(char *cmd, t_ms *mini);
void	ft_unset_shlvl(t_ms *mini);
int		ft_sct_shlvl(t_ms *mini);
char	*ft_shlvl_check(char *cmd, t_token *env);
int		ft_is_space(char c);
int		ft_is_reserved(char c);
void	ft_join_str(char **dst, char **str, int in, int fin);
void	join_dst_pid(char *str, char **dst, int *i_j, t_ms *mini);
int		ft_var_valid_name(char a);
void	ft_free_exit(t_ms *mini);
void	ft_get_path_prompt(t_ms *mini);
int		ft_get_bin_paths(t_ms *mini);
int		ft_init_minishell(t_ms *mini);
//------------------------- >>>> VAR - enviroment vars
t_token	*ft_find_envar_export(char *needle, t_ms *mini);
void	ft_export_var(char *var, char *val, t_ms *mini);
int		ft_env_to_list(char **env, t_ms *mini);
void	ft_env_sort(t_token **first_env, t_token *new);

#endif
