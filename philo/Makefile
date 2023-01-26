# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 22:08:46 by julmuntz          #+#    #+#              #
#    Updated: 2023/01/26 17:09:36 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR		= 	src/
SRC			=	philo.c				\
				utils.c				\
				routine.c			\
				life.c				\

OBJDIR		= 	obj/
OBJ			= 	$(addprefix $(OBJDIR), $(SRC:.c=.o))

NAME		= 	philo

CC			= 	cc
RM			= 	rm -f
CFLAGS		= 	-Wall -Wextra -Werror -g

$(OBJDIR)%.o:	$(SRCDIR)%.c
					@mkdir -p $(OBJDIR)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
					@$(CC) -g $^ -pthread -o $@

all:			$(NAME)

clean:
					$(RM) -r $(OBJDIR)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re