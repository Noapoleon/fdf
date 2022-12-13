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
			utils3.c \
			hooks.c \
			hooks2.c \
			model_manip.c \
			model_manip2.c \
			project.c \
			projections.c \
			bresenham.c \
			parser.c \
			parser2.c
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

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBDIR)/libft.a $(LIBDIR)/libmlx.a $(OBJS)
	$(CC) $(DEBUG) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(LIBDIR)/libft.a: | $(LIBDIR)
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a $(LIBDIR)/

$(LIBDIR)/libmlx.a: | $(LIBDIR)
	make -C $(MLX)
	cp $(MLX)/libmlx.a $(LIBDIR)/

resrcs: cleansrcs $(OBJS)

cleansrcs:
	$(RM) $(OBJS)

relibft:
	make re -C $(LIBFT)
	cp $(LIBFT)/libft.a $(LIBDIR)/

remlx:
	make re -C $(MLX)
	cp $(MLX)/libmlx.a $(LIBDIR)/

clean:
	make clean -C $(LIBFT)
	make clean -C $(MLX)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)/libft.a $(LIBDIR)/libft.a
	$(RM) $(MLX)/libmlx.a $(LIBDIR)/libmlx.a
	$(RM) $(NAME)
	

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus resrcs cleansrcs relibft remlx

showlists:
	echo $(SRCS)
	echo $(OBJS)
