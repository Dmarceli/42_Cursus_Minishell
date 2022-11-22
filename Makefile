GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET		=	\033[0m

NAME			:=	minishell
CC				:=	cc
CFLAGS			:= -g -Wall -Wextra -Werror 
LIBS			:=  -lreadline 


INCS			=	-I .brew/opt/readline/include -I$(LIBFT_DIR)

PATH_SRC		:=	./src
PATH_INCLUDES	:=	./incs
PATH_BUILD		:= ./build

TMP_FILES		:= ./.tmp

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
					$(PATH_SRC)/dollarvar.c \
					$(PATH_SRC)/exec.c \
					$(PATH_SRC)/export.c \
					$(PATH_SRC)/unset.c \
					$(PATH_SRC)/pipes.c \
					$(PATH_SRC)/msutils.c \
					$(PATH_SRC)/redirect.c \
					$(PATH_SRC)/quotes.c \
					$(PATH_SRC)/special_check.c \
					$(PATH_SRC)/msexit.c \
					$(PATH_SRC)/redirect_util.c \
					$(PATH_SRC)/get_next_line.c
					

OBJ				:= $(subst .c,.o,$(subst $(PATH_SRC), $(PATH_OBJS), $(SRCS)))

all:$(BIN) $(TMP_FILES)

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
	@printf "\033[4;32m[Building Libft]\033[0m\n"
	@ $(MAKE) -C ./libft --silent

$(TMP_FILES):
	@mkdir $@

clean:
		@printf "\033[38;5;1m[Cleaning objects!]\033[0m\n"
		@rm -rf $(PATH_OBJS)

fclean: clean
		@ $(MAKE) fclean -C $(LIBFT_DIR) --silent
		@rm -rf $(PATH_BUILD) $(NAME)
		@rm -rf $(BIN) $(TMP_FILES)
		@printf "\033[38;5;1m[Cleaning Bin!]\033[0m\n"

re: fclean all

.PHONY: all clean
