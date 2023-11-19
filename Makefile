CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIB = -Llibft -lft
NAME = pipex

ifdef BONUS
	OBJS = $(BONUS_OBJS)
else
	OBJS = $(MAN_OBJS)
endif

MAN_DIR = ./srcs
BONUS_DIR = ./bonus
MAN_FILE = main.c
BONUS_FILE = main_bonus.c here_doc_bonus.c
MAN_SRCS = $(addprefix $(MAN_DIR)/, $(MAN_FILE))
BONUS_SRCS = $(addprefix $(BONUS_DIR)/, $(BONUS_FILE))
MAN_OBJS = $(MAN_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT_NAME = libft
LIBFT_DIR = ./libft
LIBFT = $(addprefix $(LIBFT_DIR)/, libft.a)

all: $(NAME)

%.o:%.c
	${CC} $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(CC) $(CFLAGS) $(CLIB) $^ -o $@

$(BONUS_NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(CC) $(CFLAGS) $(CLIB) $^ -o $@

bonus:
	@$(MAKE) BONUS=1 $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(MAN_OBJS)
	@rm -f $(BONUS_OBJS)

fclean: clean
	@rm -f pipex

re:	
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re

gcc -g parser.c parser_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c tokenize.c lexer.c setter.c data_structure/queue.c -lreadline -fsanitize=address
