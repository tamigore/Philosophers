CC = clang

NAME = philo

DIR_S = srcs/

HEADER = includes/

SOURCES =	main.c		\
			utils_lib.c	\
			utils_phi.c	\
			init.c		\
			start.c

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I $(HEADER)

FLAGS = -lpthread #-g -fsanitize=thread

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

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)

norme:
	norminette ./$(HEADER)
	@echo
	norminette ./$(DIR_S)

bonus: all

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean bonus norme all