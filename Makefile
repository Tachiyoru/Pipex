NAME			=	pipex
NAME_B			=	pipex_bonus

SRCS_DIR		=	srcs/
SRCS_B_DIR		=	bonus/

GNL_DIR		=	GNL/

SRCS			=	${SRCS_DIR}main.c				\
					${SRCS_DIR}here_doc.c			\
					${SRCS_DIR}struct.c				\
					${SRCS_DIR}split.c				\
					${SRCS_DIR}utils.c				\
					${SRCS_DIR}utils2.c				\
					${SRCS_DIR}utils3.c				\
					${SRCS_DIR}free.c				\
					${GNL_DIR}get_next_line.c		\
					${GNL_DIR}get_next_line_utils.c

SRCS_B			=	${SRCS_B_DIR}main.c				\
					${SRCS_B_DIR}here_doc.c			\
					${SRCS_B_DIR}struct.c				\
					${SRCS_B_DIR}split.c				\
					${SRCS_B_DIR}utils.c				\
					${SRCS_B_DIR}utils2.c				\
					${SRCS_B_DIR}utils3.c				\
					${SRCS_B_DIR}free.c				\
					${GNL_DIR}get_next_line.c		\
					${GNL_DIR}get_next_line_utils.c

OBJS			=	$(SRCS:%.c=%.o)
OBJS_B			=	$(SRCS_B:%.c=%.o)

DEFAULT			=	\033[0m
RED				=	\033[1;31m
GREEN			=	\033[1;32m

CFLAGS			=	-Wall -Werror -Wextra -fstandalone-debug -g3 -I.

CC				=	clang

all: $(NAME)

bonus: $(NAME_B)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)##### Pipex est compilé! #####$(DEFAULT)"

$(NAME_B): $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B)
	@echo "$(GREEN)##### Pipex est compilé avec bonus! #####$(DEFAULT)"

clean :
	rm -rf $(OBJS)
	rm -rf $(OBJS_B)

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_B)
	@echo "\n${RED}#### Tout est supprime! ####${DEFAULT}"

re : fclean all

.PHONY : all clean fclean re
