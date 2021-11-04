CC = clang

NAME = philo

LIB = lib/

LIBFT = $(LIB)libft

DIR_S = srcs/

HEADER = includes/

SOURCES =	main.c

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I $(HEADER)

FLAGS = -L $(LIBFT) -lft -D NUM_THREADS=3

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
#	NUM_THREADS = $(shell sysctl -n hw.ncpu)
	CFLAGS += $(MACOS_MACRO)
endif
ifeq ($(UNAME),Linux)
#	NUM_THREADS = $(shell nproc --all)
	CFLAGS += $(LINUX_MACRO)
endif

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)

norme:
	norminette ./$(LIB)
	@echo
	norminette ./$(HEADER)
	@echo
	norminette ./$(DIR_S)

bonus: all

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
