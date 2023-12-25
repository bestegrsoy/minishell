/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgursoy <bgursoy@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:21:39 by bgursoy           #+#    #+#             */
/*   Updated: 2023/12/21 16:48:04 by bgursoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# define W_ARGS "Error! Only needs program name."
# define A_ERR "Error! Allocation init error."
# define EXEC 0
# define HEREDOC 1
# define PIPE 2
# define GREAT 3
# define GREATER 4
# define LESS 5
# define STDINN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_data
{
	char			*read_data;
}					t_data;

typedef struct s_lexer
{
	t_list			*lex;
}					t_lexer;

typedef struct s_parse
{
	char			*cmd;
	char			**text;
	int				type;
	int				outfile;
	int				infile;
	int				fd;
	int				pid;
	int				control;
	int				std_in;
	struct s_parse	*next;
}					t_parse;

typedef struct s_mini
{
	t_list			*env;
	char			*cmd;
	t_lexer			*lex_list;
	t_parse			*parse;
	char			*heredoc;
	int				exec_status;
}					t_mini;

extern int			g_heredoc_sig;

void				free_init_check(t_mini *mini);
void				lexer(t_mini *mini);
int					ignore_quote(char const *cmd, int i);
int					check_quote(char *before, char *after);
int					is_count_odd(char *before, char c);
char				*get_env(t_list *env, char *key);
int					ft_ultimatestrcmp(char *key, char *tmp, int i, int *flag);
void				expand_question_mark(t_mini *mini, t_list *lex,
						char **temp, char *before);
void				expand_dollar_variable(t_mini *mini, t_list *lex,
						char **temp, char *before);
void				expander(t_mini *mini);
void				mini_parse(t_list *lex, t_mini *m_mini,
						int a[3], char *str);
void				flag_free(t_parse *parse);
void				parse_text_m(t_parse *parse, char *str, int *j, int *flag);
void				tokenize_type_for_meta(t_parse **parse, const char *str);
t_parse				*parse_init(size_t len);
int					our_parser(t_mini *m_mini);
void				free_node(t_list *node);
void				_free_env(t_list *tmp2, t_mini *m_mini);
void				free_env(t_mini *m_mini);
void				builtin_exit(t_mini **m_mini);
void				free_(t_mini *m_mini);
void				free_loop(int control, t_mini *m_mini);
void				execve_child_free(char **str, t_mini *m_mini);
void				free_text(char **text);
void				free_parses_cmd_text(t_parse *parse);
void				free_parser(t_mini *m_mini);
int					*create_pipe(void);
void				run_command(char **env, t_parse *tmp, int *fd,
						t_mini *m_mini);
void				only_single_command(char **env, t_parse *parse,
						t_mini *m_mini);
void				multi_command_(t_parse *parse, char **env, t_mini *m_mini,
						int *fd);
void				multi_command(char **env, int x, t_parse *parse,
						t_mini *m_mini);
void				exec(char **env, t_mini *m_mini);
char				*search_command(char *cmd, char **value);
char				*_search_path(t_mini *m_mini);
void				search_path(t_parse *data, int i, t_mini *m_mini);
void				run_execve(t_parse *parse, char **env, int *fd,
						t_mini *m_mini);
void				exec_others(t_parse *parse, char **env, int *fd,
						t_mini *m_mini);
char				**get_args(t_parse *parse);
int					single_or_multi_command(t_mini *m_mini);
t_parse				*_next_command(t_parse **parse);
void				execute_builtin_command(t_parse *parse, t_mini *m_mini);
int					is_builtin(t_parse *data);
void				run_echo(t_parse *data, int *i);
void				exec_echo(t_parse *data, t_mini *m_mini);
void				print_list(void *data, t_mini *m_mini);
void				exec_env(t_mini *m_mini);
void				edit_env(t_list *node, char *key, char *value,
						t_mini *m_mini);
void				declare_export(void *data, t_mini *m_mini);
int					exec_export(t_parse *data, t_mini *m_mini);
int					unset_edit(t_list **node, t_list **prev_node,
						t_mini *m_mini);
void				exec_unset(t_parse *data, t_mini *m_mini, int i, int x);
void				change_old(char *str, t_mini *m_mini);
void				_change_pwd(t_env **env);
void				change_pwd(t_parse *data, t_mini *m_mini);
void				exec_cd1(char *str, t_parse *data, t_mini *m_mini);
void				exec_cd(t_parse *data, t_mini *m_mini);
void				edit_env_(t_list *node, char *key, char *value,
						t_mini *m_mini);
void				exec_pwd(t_parse *data, t_mini *m_mini);
char				*get_home(t_mini *m_mini);
int					export_key_control(char *text);
int					ft_strchrindex_0(char *s, int c);
void				signals(int sig);
void				signals_control(void);
void				error_free(t_list **node);
void				go_parser(t_mini *mini, char **env, int control);
void				get_readline(t_mini *mini);
int					mini_init(t_mini **mini);
int					env_get(char **env, t_mini **mini);
void				free_str(char **str);
void				killer(int sig);
void				set_heredoc(int sig);
void				loop_heredoc(t_mini *m_mini);
void				heredoc(t_parse *parse, t_mini *m_mini);
void				get_input(t_parse *parse, int *fd);
void				get_var(int *fd, t_mini *m_mini);
char				*add_char(char *str, char a);
void				_create_dup(t_mini *m_mini);
void				create_dup(t_mini *m_mini, t_parse *parse);
void				create_dup_one(t_parse *parse, int *fd);
void				create_dup_two(t_parse *parse, int *fd);
int					is_space(char *cmd);
int					print_error(void);
int					quote_check(char *data, char a, char b);
int					check(t_mini *mini);
int					quote_len1(char *data);
int					cmd_is_valid(t_lexer *lex_list, char *a, char *b);
int					is_valid_other(char *a, char *b);
void				_multi_command(t_parse **parse);
void				ft_newlstiter(t_list *lst, void (*f)(), t_mini *mini);
char				*ft_m_strdup2(size_t len, char *s, int i,
						const char *str);
void				clear_pipe(int *fd);
void				wait_all(t_mini *m_mini);
int					create_files_for_meta(t_mini *m_mini);
void				create_out_files_meta(t_parse *current_parse,
						t_parse *first_parse, t_mini *m_mini);
void				other_text_create_meta(t_parse *current_parse,
						t_mini *m_mini);
void				other_out_files_meta(t_parse *parse, t_mini *m_mini);
void				handle_relative_path(char **pwd, t_parse *current_parse);
int					create_in_files_meta(t_parse *parse, t_mini *mini);
void				start_minishell(t_mini *mini, char **env, int control);
void				expand_tilde(t_mini *mini);
void				expand_dollar(t_mini *mini);
void				expand_dollar_internal(t_mini *mini, t_list *lex);
int					null_init(t_mini **mini);
void				expander_tilde(t_mini *mini, t_list *lex);
void				expand_question_mark(t_mini *mini, t_list *lex, char **temp,
						char *before);
void				expand_dollar_variable(t_mini *mini, t_list *lex,
						char **temp, char *before);
#endif