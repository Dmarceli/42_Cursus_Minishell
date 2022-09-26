GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET		=	\033[0m

NAME			=	minishell
CC				:=	gcc
CFLAGS			:= -g -Wall -Wextra -Werror 
LIBS			:=  -lreadline 


INCS		=	-I .brew/opt/readline/include -I$(LIBFT_DIR)

PATH_SRC		:=	./src
PATH_INCLUDES	:=	./incs
PATH_BUILD		:= ./build

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

PATH_OBJS		:= $(PATH_BUILD)/objs
BIN				:=	./$(NAME)
SRCS			:= $(PATH_SRC)/main.c \
					$(PATH_SRC)/msparser.c \
					$(PATH_SRC)/signals.c \
					$(PATH_SRC)/cmdhandler.c \
					$(PATH_SRC)/echo.c \
					$(PATH_SRC)/cd.c \
					$(PATH_SRC)/env.c \
					$(PATH_SRC)/exec.c \


OBJ				:= $(subst .c,.o,$(subst $(PATH_SRC), $(PATH_OBJS), $(SRCS)))

all:$(BIN)

$(BIN): $(LIBFT) $(OBJ)
		@$(CC) -o $(@) $^ -I$(PATH_INCLUDES) $(LIBFT) $(INCS) $(LIBS)
		@printf "\033[44m[$(NAME) built!]\033[0m\n"



$(PATH_OBJS)/%.o: $(PATH_SRC)/%.c | $(PATH_BUILD)
		@$(CC) $(CFLAGS) -c $(^) -o $@ 
		@printf "\033[36m[Building ${@F}]\033[0m\n"


$(PATH_BUILD):
		@mkdir -p $(PATH_BUILD)
		@mkdir -p $(PATH_OBJS)

$(LIBFT):
	@ $(MAKE) -C ./libft --silent

clean:
		@printf "\033[38;5;1m[Cleaning objects!]\033[0m\n"
		@rm -rf $(PATH_OBJS)

fclean: clean
		@ $(MAKE) fclean -C $(LIBFT_DIR) --silent
		@rm -rf $(PATH_BUILD) $(NAME)
		@rm -rf $(BIN)
		@printf "\033[38;5;1m[Cleaning Bin!]\033[0m\n"

re: fclean all

.PHONY: all clean