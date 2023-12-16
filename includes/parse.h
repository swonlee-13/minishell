/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:33:04 by seongwol          #+#    #+#             */
/*   Updated: 2023/12/16 19:32:32 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../srcs/libft/libft.h"
# include <readline/readline.h>
# define TRUE 1
# define FALSE 0
# define SYNTAX_ERROR -1

typedef enum e_type
{
	PASS = 0,
	REDIR_DOUBLE_IN,
	REDIR_SINGLE_IN,
	REDIR_DOUBLE_OUT,
	REDIR_SINGLE_OUT,
	REDIRECTION_ROOT,
	CMD,
	ARGUMENT_ROOT,
	ARGS,
	PIPE,
}	t_type;

typedef struct s_node
{
	t_type				type;
	char				*data;
	struct s_node		*left;
	struct s_node		*right;
	int					pipe_index;
	int					fd;
}	t_node;

typedef struct s_queue
{
	t_node	*front;
	t_node	*rear;
	int		node_count;
	int		total_cmd_num;
}	t_queue;

//parse_tokenizer.c
int		redirection_tokenizer(char *cmd, int i, char *token_string, char c);
int		pipe_tokenizer(int i, char *token_string);
int		space_tokenizer(int i, char *cmd, char *token_string);
int		quote_tokenizer(char *cmd, int i, char *token_string, char c);
int		normal_tokenizer(char *cmd, int i, char *token_string);
char	*tokenizer(char *cmd);
//parse_tokenizer2.c
int 	pipe_tokenizer(int i, char *token_string);

//lexer.c
int		redir_lexer_count(char *token_string, int i, char c);
int		redir_lexer(char *token_string);
int		quote_lexer_find_end(char *token_string, int i, char c);
int		quote_lexer(char *token_string);
int		file_lexer_argument_check(char *token_string, int i, char c);
int		file_lexer(char *token_string);
int		pipe_lexer_double_check(char *token_string, int i);
int		pipe_lexer(char *token_string);
int		token_lexer(char *cmd, char *token_string);

//lexer_utils2.c
int dollar_sign_lexer(char *cmd, char *token_string);
int dollar_sign_lexer_double(char *cmd, int i);

//data_structure/queue.c
void	queue_init(t_queue *q);
void	node_enqueue(t_queue *q, t_node *new);
void	empty_queue(t_queue *q);
t_node	*node_init(void);
t_node	*dequeue(t_queue *q);
t_node	*enqueue(t_queue *q);

//data_structure/tree.c
void	tree_insert(t_node **root, t_node *node);
void	tree_insert_pipe(t_node **root, t_node *target);
void	free_tree(t_node *root);

//parse_parser.c
t_node	*parser(char *cmd, char **env_copy);

//parse_utils.c
int		ft_is_redirection(char c);
int		ft_is_op_token(char c);
int		ft_is_op_redirection(char c);

//setter.c
void	file_name_setter_valueset(char *token_string, int i, char c, int count);
int		file_name_setter_sub(char *token_string, int i);
void	file_name_setter(char *token_string);
int		dollar_sign_setter_quote(char *cmd, char *token_string, int i);
void	dollar_sign_setter(char *cmd, char *token_string);
void	token_setter(char *cmd, char *token_string);

//parse_formatting.c
void	node_data_formatting(t_queue *q, char **env_copy);
char	*here_doc_formatting(char *str, char **env_copy);
//parse_formatting_utils.c
char    *env_var_replace(char *str, char **env);
void    remove_and_replace(char **strs, char **env);
//split_dollar.c
char	**shell_split_dollar(char *str);

//parse_tree.c
t_node	*switch_to_tree(t_queue *q);
t_node	*get_command_tree(t_node *root, int idx);

//split_quote.c
char	**shell_split_quote(char *str);
char	*merge_splitted_cmd(char **strs);

//parse_vector_conversion.c
char	**vector_conversion(t_node **root, int cmd_num);

//split_here_doc.c
char	**shell_split_here_doc(char *str);

//temp
void	print_queue(t_queue *q);

//utils
t_node	*find_redirection_root(t_node *root, int cmd_idx);

//heredoc/limiter_formatting.c
char	*limiter_formatting(char *data);
#endif
