CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS_DB := -Wall -Werror -Wextra -g3
CFLAGS_AS := -Wall -Werror -Wextra -g3 -fsanitize=address
CFLAGS_NE := -g3
CFLAGS_REL := -Wall -Werror -Wextra -O2

NAME := philo

SRC_DIR := src
vpath %.c $(SRC_DIR)
SRC := main.c \
	   time.c \
	   utils.c \
	   deinit.c \
	   parsing.c \
	   error.c \
	   print.c \
	   threads_init.c \
	   routine_fork_utils.c \
	   routine_fork_take.c \
	   routine.c
# thread_test.c

BUILD_DIR := build
OBJ := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

DEP_FLAGS = -MMD
DEP_FILES := $(OBJ:.o=.d)

all: $(BUILD_DIR) $(NAME)

noerr: CFLAGS = $(CFLAGS_NE)
noerr: all
dbg: CFLAGS = $(CFLAGS_DB)
dbg: all
asan: CFLAGS = $(CFLAGS_AS)
asan: cc = clang
asan: all
rel: CFLAGS = $(CFLAGS_REL)
rel: all

-include $(DEP_FILES)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEP_FLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

fclean:
	rm -rf $(BUILD_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re noerr dbg asan rel
