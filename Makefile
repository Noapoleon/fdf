# Project Structure
NAME	=	fdf
LIBDIR	=	libs
OBJDIR	=	objs
INCDIR	=	incs
SRCDIR	=	srcs

# Deps
LIBFT	=	libft
MLX		=	minilibx-linux

# Files
SRCS	:=	fdf.c \
			setup.c \
			utils.c \
			utils2.c \
			parser.c \
			parser2.c \
			hooks.c \
			bresenham.c \
			test_utils.c
OBJS	:=	$(SRCS:.c=.o)
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))

# Compiler Options
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
LIBS	=	-L./$(LIBDIR) -lft -lmlx -lm -lX11 -lXext
INCS	=	-I./$(INCDIR)

# Other
RM	=	rm -rf

# REMOVE G3 AFTERWARDS
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -g3 $(CFLAGS) $(INCS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

libft:
	make re -C $(LIBFT)
	cp $(LIBFT)/libft.a $(LIBDIR)/

mlx:
	make re -C $(MLX)
	cp $(MLX)/libmlx.a $(LIBDIR)/

clean:
	make clean -C $(LIBFT)
	make clean -C $(MLX)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)/libft.a
	$(RM) $(MLX)/libmlx.a
	$(RM) $(NAME)
	

re: fclean libft mlx all

bonus: all

.PHONY: all clean fclean re bonus libft mlx

showlists:
	echo $(SRCS)
	echo $(OBJS)
