#ifndef MINISHELL_H
# define MINISHELL_H

// # include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum x_type
{
	// REDIRECTION,
	// ENVIROMENT,
	// SINGLE_QUOTE, // '
	// DOUBLE_QUOTE, // "
	INPUT,       // <
	OUTPUT,      // >
	HERE_DOC,    // <<
	APPEND,      // >>
	// DOLLAR_SIGN, // $
}			t_type;

typedef struct x_red
{
	char	*file;
	t_type	type;
	int		check_flag;

}			t_red;

typedef struct x_env
{
	char	*key;
	char	*value;

}			t_env;

typedef struct x_cmd
{
	char	*command;
	char	**arguments;
	int		check_red;
	int		check_env;

	t_red	**s_red;
	t_env	**s_env;

}			t_cmd;

typedef struct x_bash
{
	char	*commands;
	char	**args_pip;
	int		num_cmd;

	t_env	**path_env;
	t_cmd	**s_cmd;

}			t_bash;

/* excutions functions
 */
// char		*get_env_value(t_env *env_list, char *key);

// int	*update_env(t_bash **);


// parsing function

//->parsing:

int		select_struct1(t_bash *bash, char *cmd);
int		select_struct2(t_bash *bash);
int		select_struct3(t_bash *bash);
void	select_struct(t_bash *bash, char *cmd, char **env);

//->parsing1:

int		check_cmd(char *str);
int		check_cmd1(char *str);
int		check_cmd2(char *str);
int		check_cmd3(char *str);
int		count_pipes(char *cmd);


//->parsing2:

int		check_envirment(char *str);
int		check_redirection(char *str);
void	check_red_env(t_bash *bash);
int		check_cmd4_1(char *str);
int		check_cmd4_2(char *str);

//->parsing3:

int	red_parse(t_bash *bash);
int	check_sin_dou(char *line);

//->tokrnizer

char	**alloc_words_tk(char **ret, char *cmd, int word);
int		count_word_tk(char *cmd);
int		check_tokinzer(char c);
void	free_double_pointer_tk(char **arr, int p);
char	**tokenizer(char *cmd);

//->check_redirecton

int		check_rd(char c);
int		check_rd1(char c);
int		check_sp(char c);
int		count_redirection(char *cmd);

//->redirection:

int		alloc_s_red(t_bash *bash, int n_red, int i);
void	redirection_types(t_bash *bash, int i);
void	redirection_types1(t_bash *bash, int i);
void	redirection_files(t_bash *bash, int i);
int		parse_redirection(t_bash *bash);

//->envirement:

int 	count_env(char *str);
int 	alloc_env(t_bash *bash, int num_env, int ind);
void	parse_env_file_key(t_bash *bash, int i);
int 	parse_envirement(t_bash *bash);

//->expand

void	expand_func(t_bash *bash, char **env);
void	free_double_pointer_ex(char **arr);
int		check_sin_dou(char *line);

//->utils(libft)

char	**ft_split(char *cmd, char sep);
char	*ft_strdup(char *cmd);
int		ft_strlen(char *cmd);
char	*ft_substr(char *str, int start, int len);

//->free

void	free_redirections(t_bash *bash, int ind);
void	free_envs(t_bash *bash, int ind);
void	free_cmds(t_bash *bash);
void	free_bash(t_bash *bash);

// parsing function

#endif