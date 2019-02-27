CC = gcc

NAME = malloc_checker
CFLAGS = -Wall -Wextra

VPATH = ./:./srcs
#./
SRCS			= main.c
#./srcs
SRCS += test_0.c \
		test_1.c \
		test_2.c \
		test_3.c \
		test_4.c \
		test_5.c \
		test_6.c \
		test_7.c \
		test_8.c \
		test_9.c \
		test_10.c \
		test_11.c \
		test_12.c

INCS_PATH		= ./
INCS			= $(addprefix -I,$(INCS_PATH))

OBJS_PATH		= ./.objs/
OBJS_NAME		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) $^ -o $@ 

$(OBJS_PATH)%.o: %.c Makefile
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

clean:
	@rm -rf $(OBJS_PATH)

fclean:
	@rm -rf $(OBJS_PATH)
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) $(NAME)
