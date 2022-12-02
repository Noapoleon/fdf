# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 02:07:52 by nlegrand          #+#    #+#              #
#    Updated: 2022/12/01 19:45:10 by nlegrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Structure
NAME	=	fdf
LIBFT	=	libft
MINILIB	=	minilibx-linux
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs
LIBDIR	=	libs

SRCS	:=	fdf.c \
			bresenham.c \
			fdf_utils.c \
			parser.c \
			parser2.c \
			hook_utils.c \
			test_utils.c
OBJS	:=	$(SRCS:.c=.o)
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))

# Compiler Options
CC			=	cc
CFLAGS		=	-g3 -Wall -Wextra -Werror
INCFLAGS	=	-I./$(INCDIR)
LIBFLAGS	=	-L./$(LIBDIR) -lft -lmlx -lm -lX11 -lXext

# Utils
RM	=	rm -rf

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

all: ascii $(LIBDIR)/$(LIBFT).a $(LIBDIR)/libmlx.a $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCFLAGS) $(LIBFLAGS) -o $(NAME)

$(LIBDIR)/$(LIBFT).a:
	make -C $(LIBFT)
	cp $(LIBFT)/$(LIBFT).a $(LIBDIR)/

$(LIBDIR)/libmlx.a:
	make -C $(MINILIB)
	cp $(MINILIB)/libmlx.a $(LIBDIR)/

$(OBJDIR):
	mkdir objs

clean:
	make clean -C $(LIBFT)
	make clean -C $(MINILIB)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)/$(LIBFT).a
	$(RM) $(LIBDIR)/$(LIBFT).a
	$(RM) $(LIBDIR)/libmlx.a
	$(RM) $(NAME)

re: fclean all

ascii:
	@echo "\
\033[0;33m⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤\n\
⣿                                   ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⠀⣤⣴⣶⣶⣶⣶⣾⣿⣿⣿⣶⣶⣿⣿⣿⣿⣶⡄⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⢀⣴⣦⣄⣀⣀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣄⣀⣠⣴⣆ ⣿\n\
⣿ ⠈⠛⠻⠿⠿⠿⡿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⠿⠿⣿⠿⠿⠿⠿⠿ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠤⠤⠤⠄⠀⠐⠂⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣁⣀⣀⣀⣀⣿⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⠀⠀⡜⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⠃⠈⠀⠀⢡⠸⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⢹⠙⠛⠛⠉⠉⠁⢀⠄⠀⠀⠘⢀⠈⠛⠛⠛⠛⠉⡞⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀⠀⠀⢠⡉⠒⠢⡠⠔⠈⣑⠀⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⠀⢸⠰⣿⣿⣿⢿⢾⣿⣿⣿⡷⠁⠄⢠⠃⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⢸⠀⠍⠈⠀⠒⠒⠒⠒⠒⠂⠘⢠⠏⠀⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠦⢤⣀⣀⣀⣀⡠⠤⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⣿\n\
⣿                                   ⣿\n\
⣿     i am the danger squidward     ⣿\n\
⣿                                   ⣿\n\
⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛\033[0m"
ascii2:
	@echo "\
⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⢰⡿⠋⠁⠀⠀⠈⠉⠙⠻⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⢀⣿⠇⠀⢀⣴⣶⡾⠿⠿⠿⢿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⣀⣀⣸⡿⠀⠀⢸⣿⣇⠀⠀⠀⠀⠀⠀⠙⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⣾⡟⠛⣿⡇⠀⠀⢸⣿⣿⣷⣤⣤⣤⣤⣶⣶⣿⠇⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀\n\
⢀⣿⠀⢀⣿⡇⠀⠀⠀⠻⢿⣿⣿⣿⣿⣿⠿⣿⡏⠀⠀⠀⠀⢴⣶⣶⣿⣿⣿⣆\n\
⢸⣿⠀⢸⣿⡇⠀⠀⠀⠀⠀⠈⠉⠁⠀⠀⠀⣿⡇⣀⣠⣴⣾⣮⣝⠿⠿⠿⣻⡟\n\
⢸⣿⠀⠘⣿⡇⠀⠀⠀⠀⠀⠀⠀⣠⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠉⠀\n\
⠸⣿⠀⠀⣿⡇⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠉⠀⠀⠀⠀\n\
⠀⠻⣷⣶⣿⣇⠀⠀⠀⢠⣼⣿⣿⣿⣿⣿⣿⣿⣛⣛⣻⠉⠁⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⢸⣿⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⢸⣿⣀⣀⣀⣼⡿⢿⣿⣿⣿⣿⣿⡿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠙⠛⠛⠛⠋⠁⠀⠙⠻⠿⠟⠋⠑⠛⠋⠀         "

.PHONY: all clean fclean re ascii ascii2
