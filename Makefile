# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 05:17:24 by pollivie          #+#    #+#              #
#    Updated: 2024/06/14 05:17:25 by pollivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
# CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -Werror -O3
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -Werror -fsanitize=address -fsanitize=integer -fsanitize=undefined -g3 -fno-omit-frame-pointer
LIBRARY_DIR = library
MLX_DIR = mlx
SRC_DIR = src
INCLUDE_DIR = include
TARGET = fdf
LIBS = -L$(LIBRARY_DIR) -lslib -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lbsd

# Use find to locate all .c files and store them in SRC_SRCS
SRC_SRCS := $(shell find $(SRC_DIR) -name "*.c")

# Convert .c files to .o files
OBJ_FILES := $(SRC_SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

# Counting the number of source files for progress reporting
TOTAL := $(words $(SRC_SRCS))
CURRENT := 0

define PRINT_PROGRESS
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@PROGRESS=$$(echo "scale=2; 100 * $(CURRENT) / $(TOTAL)" | bc -l); \
	if [ $(CURRENT) -le $(TOTAL) ]; then \
		printf "\r\033[K\033[1;34m[\033[0m"; \
		BAR_SIZE=$$(echo "$$PROGRESS / 2" | bc); \
		for i in $$(seq 1 50); do \
			if [ $$BAR_SIZE -ge $$i ]; then \
				printf "\033[1;32m#\033[0m"; \
			else \
				printf " "; \
			fi; \
		done; \
		printf "\033[1;34m] %.2f%%\033[0m" $$PROGRESS; \
	fi
endef

.PHONY: all clean fclean re run

all: $(TARGET)

$(TARGET): $(LIBRARY_DIR)/libslib.a $(MLX_DIR)/libmlx.a $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ $(LIBS)
	$(call PRINT_PROGRESS)

$(LIBRARY_DIR)/libslib.a:
	@$(MAKE) -s -C $(LIBRARY_DIR)
	$(call PRINT_PROGRESS)

$(MLX_DIR)/libmlx.a:
	@$(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1 || true

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) 
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call PRINT_PROGRESS)

clean:
	@$(MAKE) -s -C $(LIBRARY_DIR) clean
	@find $(SRC_DIR) -name "*.o" -exec rm -f {} +
	@rm -f $(TARGET)

fclean: clean
	@$(MAKE) -s -C $(LIBRARY_DIR) fclean
	@rm -f $(LIBRARY_DIR)/libslib.a
	@rm -f $(MLX_DIR)/libmlx.a
	@rm -rf .cache 
	@rm -f compile_commands.json 

re: fclean all

run:
	@./run.sh
