CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS_DB := -Wall -Werror -Wextra -g3
CFLAGS_NE := -g3
CFLAGS_REL := -Wall -Werror -Wextra -O2
DEP_FLAGS = -MMD
DEP_FILES := $(OBJ:.o=.d)

NAME := philo

SRC_DIR := src
vpath %.c $(SRC_DIR)
SRC := main.c \
	   error.c \
	   arg_to_int.c
# thread_test.c

BUILD_DIR := build
OBJ := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

all: $(BUILD_DIR) $(NAME)

noerr: CFLAGS = $(CFLAGS_NE)
noerr: all
dbg: CFLAGS = $(CFLAGS_DB)
dbg: all
rel: CFLAGS = $(CFLAGS_REL)
rel: all

-include $(DEP_FILES)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

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

.PHONY: all clean fclean re noerr dbg rel
