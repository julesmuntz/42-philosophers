# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 22:08:46 by julmuntz          #+#    #+#              #
#    Updated: 2022/12/13 22:08:46 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR		= 	src/
SRC			=	philo.c				\
				p_atoi.c			\
				p_strcmp.c			\

# B_SRCDIR	= 	bonus/
# B_SRC		=	philo_bonus.c		\

OBJDIR		= 	obj/
OBJ			= 	$(addprefix $(OBJDIR), $(SRC:.c=.o))

# B_OBJDIR	= 	$(OBJDIR)
# B_OBJ		= 	$(addprefix $(B_OBJDIR), $(B_SRC:.c=.o))

NAME		= 	philo
# B_NAME		= 	philo_bonus

CC			= 	cc
RM			= 	rm -f
CFLAGS		= 	-Wall -Wextra -Werror -g

$(OBJDIR)%.o:	$(SRCDIR)%.c
					@mkdir -p $(OBJDIR)
					$(CC) $(CFLAGS) -c $< -o $@

# $(B_OBJDIR)%.o:	$(B_SRCDIR)%.c
# 					@mkdir -p $(B_OBJDIR)
# 					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
					@$(CC) -g $^ -o $@

# $(B_NAME):		$(B_OBJ)
# 					@$(CC) -g $^ -o $@

all:			$(NAME) # $(B_NAME)

# bonus:			$(B_NAME)

clean:
					$(RM) -r $(OBJDIR)

fclean:			clean
					$(RM) $(NAME)
#					$(RM) $(B_NAME)

re:				fclean all

.PHONY:			all bonus clean fclean re