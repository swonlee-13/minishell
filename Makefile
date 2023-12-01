# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yeolee2 <yeolee2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 22:14:25 by yeolee2           #+#    #+#              #
#    Updated: 2023/12/01 19:29:52 by yeolee2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	srcs/data_structure/queue.c \
					srcs/data_structure/linked_list.c \
					srcs/data_structure/tree.c \
					srcs/parse/parse_parser.c \
					srcs/parse/split_dollar.c \
					srcs/parse/parse_lexer.c \
					srcs/parse/parse_utils.c \
					srcs/parse/split_quote.c \
					srcs/parse/parse_tokenize.c \
					srcs/parse/parse_vector_conversion.c \
					srcs/parse/parse_tree.c \
					srcs/parse/parse_formatting.c \
					srcs/parse/parse_setter.c \
					srcs/utils/copy_env_list.c \
					srcs/heredoc/main.c \
					srcs/builtins/exit.c \
					srcs/builtins/unset.c \
					srcs/builtins/env.c \
					srcs/builtins/pwd.c \
					srcs/builtins/export.c \
					srcs/builtins/cd.c \
					srcs/builtins/echo.c \

OBJS			=	${SRCS:.c=.o}

NAME			=	minishell

LIBFT			=	srcs/libft

ARCHIVE			=	libft.a

CC				=	cc

INCLUDES		=	./includes/

CFLAGS			=	-Werror -Wall -Wextra -g

Black   		=	\033[0;30m

Red     		=	\033[1;31m

Green   		=	\033[0;32m

Yellow  		=	\033[0;33m

Blue    		=	\033[0;34m

Purple  		=	\033[1;35m

Cyan    		=	\033[0;36m

White   		=	\033[1;37m

Gray    		=	\033[0;90m

DEF_COLOR 		=	\033[0;39m

LF				=	\e[1K\r

TOTAL_FILES 	=	 $(words $(SRCS))

CURRENT_FILE 	=	 1

progress_bar 	=	printf "$(LF)$(Red)[ ♔Compiling...♔ ]$(DEF_COLOR) $(Cyan)[$(1)/$(2)]$(DEF_COLOR) [$(Yellow)%0.1f%%$(DEF_COLOR)] $(DEF_COLOR)\b" $(shell echo "scale=1; ($(1) / $(2)) * 100" | bc); \
        			printf " $(White)[%-*s%s]$(DEF_COLOR)" 25 "$(shell printf '%0.*s' $$(($(1) * 25 / $(2))) '=========================================================================')>" ""; \
					printf "\n\033[2K$(DEF_COLOR)  ✔️ $(Cyan)Compiling... $< $(DEF_COLOR) \033[A\033[999C\e[?25l" \

all			: 	$(NAME)

%.o			: 	%.c $(INCLUDES)
				@echo "$(YELLOW)Compiling..."
				@$(CC) $(CFLAGS) -I$(INCLUDES) -c -o $@ $<
				@$(call progress_bar,$(CURRENT_FILE),$(TOTAL_FILES))
				@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
				@sleep 0.05

$(NAME)		: 	$(OBJS) $(LIBFT)/$(ARCHIVE)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft
				@echo "$(GREEN)Mandatory Compilation done"
				@printf "$(LF)"
				@printf "\n\033[1;32m✅ Compilation complete. $(NAME) has been created. ✅\033[0m\n\n\e[?25h"

ifdef BONUS
				@sleep 0.5
				@echo "$(Green)===============================================$(DEF_COLOR)"
				@echo "$(Green)|    🎉 minishell bonus compile succsess. 🎉    |$(DEF_COLOR)"
				@echo "$(Green)===============================================$(DEF_COLOR)"
else
				@sleep 0.5
				@echo "$(Green)===============================================$(DEF_COLOR)"
				@echo "$(Green)|  🥳 minishell mandatory compile succsess. 🥳  |$(DEF_COLOR)"
				@echo "$(Green)===============================================$(DEF_COLOR)"
endif

# $(BOBJS)	:	$(BINCLUDES)

# bonus		: 	$(BOBJS) $(LIBFT)/$(ARCHIVE)
# 				@$(CC) $(CFLAGS) -o minishell $^ -L$(LIBFT) -lft
# 				@echo "$(GREEN)Bonus compilation done"

$(LIBFT)/$(ARCHIVE):
				@make -C $(LIBFT)

clean		:
				@$(RM) $(OBJS) $(BOBJS)
				@make clean -C $(LIBFT)
				@printf "$(LF)🚧 $(Yellow)Cleaning...🚨 $(Purple)libft$(White) $(OBJ) $(DEF_COLOR)\n"

fclean		: 	clean
				@$(RM) $(NAME)
				@$(RM) minishell
				@make fclean -C $(LIBFT)
				@echo "\n🚧 $(Yellow)Cleaning...🚨 $(White)$(NAME)\n"
				@echo "$(Cyan)Clearing terminal in [3seconds]...$(DEFAULT_COLOR)"
				@sleep 1
				@clear

re			:	fclean all
				@sleep 0.5
				@clear
				@printf "$(Purple)♻️ REBUILD ♻️\n\n"
				@$(MAKE) all

bonus		:
				@make BONUS=1 $(NAME)
				
.PHONY		: 	all clean fclean re bonus .c.o