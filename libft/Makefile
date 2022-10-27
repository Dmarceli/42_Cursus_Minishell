# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danielsequeira <danielsequeira@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:15:37 by dmarceli          #+#    #+#              #
#    Updated: 2022/10/07 03:40:38 by danielseque      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -f

HEADER = ./


SRC	= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
ft_isprint.c ft_memcmp.c ft_striteri.c\
ft_memcpy.c ft_memmove.c ft_memset.c ft_putendl_fd.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c\
ft_strchr.c ft_strlcpy.c ft_strmapi.c\
ft_strdup.c ft_split.c ft_calloc.c ft_itoa.c\
ft_strlen.c ft_strncmp.c ft_substr.c ft_strtrim.c\
ft_strnstr.c ft_strrchr.c ft_strjoin.c \
ft_tolower.c ft_toupper.c ft_strlcat.c 


OBJ	=	$(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(HEADER)


GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET       =   \033[0m

all:	$(NAME)

$(NAME):    $(OBJ)
	@echo "$(YELLOW)[Compiling libft]$(RESET)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)[Libft.a has been created!]$(RESET)"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)[libft.a has been removed!]$(RESET)"

re: fclean $(NAME)