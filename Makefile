GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET		=	\033[0m

NAME			=	minishell

CC				:=	gcc
CFLAGS			:=  -lreadline -g -Wall -Wextra #-Werror 

PATH_SRC		:=	./src
PATH_INCLUDES	:=	./incs
PATH_BUILD		:= ./build
PATH_OBJS		:= $(PATH_BUILD)/objs
BIN				:=	./$(NAME)
SRCS			:= $(PATH_SRC)/main.c \
					
OBJ				:= $(subst .c,.o,$(subst $(PATH_SRC), $(PATH_OBJS), $(SRCS)))

all:$(BIN)

$(BIN): $(OBJ)
		@$(CC) $(CFLAGS) $(INCS) -o $(@) $^ -I$(PATH_INCLUDES)
		@printf "\033[44m[$(NAME) built!]\033[0m\n"



$(PATH_OBJS)/%.o: $(PATH_SRC)/%.c | $(PATH_BUILD)
		@$(CC) $(INCS) $(CFLAGS) -shared $(^) -o $@
		@printf "\033[36m[Building ${@F}]\033[0m\n"


$(PATH_BUILD):
		@mkdir -p $(PATH_BUILD)
		@mkdir -p $(PATH_OBJS) 

clean:
		@printf "\033[38;5;1m[Cleaning objects!]\033[0m\n"
		@rm -rf $(PATH_OBJS)

fclean: clean
		@rm -rf $(PATH_BUILD) $(NAME)
		@rm -rf $(BIN)
		@printf "\033[38;5;1m[Cleaning Bin!]\033[0m\n"

re: fclean all

.PHONY: all clean