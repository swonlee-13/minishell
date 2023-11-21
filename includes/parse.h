#ifndef PARSE_H
# define PARSE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../srcs/libft/libft.h"
# include <readline/readline.h>
# define TRUE 1
# define FALSE 0
# define SYNTAX_ERROR 258           //이거 숫자 나중에 회의해서 바꿔야함;

typedef enum e_type	 //tree 구조에서 상태를 구분하기 위해 만든 열거형 편의성을 위해 << 다음에 < 를받는다 주의
{
	PASS = 0,
	REDIR_DOUBLE_IN,
	REDIR_SINGLE_IN,
	REDIR_DOUBLE_OUT,
	REDIR_SINGLE_OUT,
	ARGS,
	REDIRECTION_ROOT,
	ARGUMENT_ROOT,
	CMD,
	PIPE,
}	t_type;

typedef struct s_node	//parsing 에서 사용할 node. tree 와 임시 queue에 이용할 예정.
{
	t_type				type;
	char				*data;
	struct s_node		*left;
	struct s_node		*right;
	int					pipe_index;
}	t_node;

typedef struct s_queue
{
	t_node	*front;
	t_node	*rear;
	int		node_count;
	int		total_pipe_num;
}	t_queue;

typedef struct s_tree	//이걸 최종적으로 쓸지는 고민중
{
	t_node	*root;
	int		pipe_count;
}	t_root;

//tokenizer.c
int		redirection_tokenizer(char *cmd, int i, char *token_string, char c);
int		pipe_tokenizer(int i, char *token_string);
int		space_tokenizer(int i, char *cmd, char *token_string);
int		quote_tokenizer(char *cmd, int i, char *token_string, char c);
int 	normal_tokenizer(char *cmd, int i, char *token_string);
char	*tokenizer(char *cmd);

//lexer.c
int		redir_lexer_count(char *token_string, int i, char c);
int		redir_lexer(char *token_string);
int		quote_lexer_find_end(char *token_string, int i, char c);
int		quote_lexer(char *token_string);
int		file_lexer_argument_check(char *token_string, int i, char c);
int		file_lexer(char *token_string);
int		pipe_lexer_double_check(char *token_string, int i);
int		pipe_lexer(char *token_string);
int 	token_lexer(char *cmd, char *token_string);

//data_structure/queue.c
void	queue_init(t_queue *q);
void	node_enqueue(t_queue *q, t_node *new);
void	empty_queue(t_queue *q);
t_node	*node_init(void);


//parse_utils.c
int		ft_is_redirection(char c);
int		ft_is_op_token(char c);
int		ft_is_op_redirection(char c);	

//setter.c
void	file_name_setter_value_set(char *token_string, int i, char c, int count);
int		file_name_setter_sub(char *token_string, int i);
void	file_name_setter(char *token_string);
int		dollar_sign_setter_quote(char *cmd, char *token_string, int i);
void	dollar_sign_setter(char *cmd, char *token_string);
void	token_setter(char *cmd, char *token_string);

//split_dollar.c
char	**shell_split_dollar(char *str);

//split_quote.c
char	**shell_split_quote(char *str);

char	*merge_splitted_cmd(char **strs);
//temp
void	print_queue(t_queue *q);

#endif
