NAME			=	pipex

SRCS_DIR		=	srcs/

GNL_DIR		=	GNL/

SRCS			=	${SRCS_DIR}main.c				\
					${SRCS_DIR}here_doc.c			\
					${SRCS_DIR}struct.c				\
					${SRCS_DIR}split.c				\
					${SRCS_DIR}utils.c				\
					${SRCS_DIR}utils2.c				\
					${SRCS_DIR}free.c				\
					${GNL_DIR}get_next_line.c		\
					${GNL_DIR}get_next_line_utils.c

OBJS			=	$(SRCS:%.c=%.o)

RED				=	\033[1;31m
GREEN			=	\033[1;32m
DEFAULT			=	\033[0m

CFLAGS			=	-Wall -Werror -Wextra -fstandalone-debug -g3 -I.

CC				=	clang

all: $(NAME) $(NAME_B)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)##### Pipex est compilé! #####$(DEFAULT)"

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -f $(NAME)
	@echo "\n${RED}#### Tout est supprime! ####${DEFAULT}"

re : fclean all

.PHONY : all clean fclean re
