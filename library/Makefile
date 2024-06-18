# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 05:59:44 by pollivie          #+#    #+#              #
#    Updated: 2024/06/14 05:59:44 by pollivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Iinclude -Wall -Wextra -O3
# CFLAGS = -Iinclude -Wall -Wextra -g3 -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
SRC_DIR = src
INCLUDE_DIR = include
TARGET_LIB = libslib.a
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
TOTAL := $(words $(SRCS))
CURRENT := 0

define PRINT_PROGRESS
	$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	PROGRESS=$$(echo "scale=2; 100 * $(CURRENT) / $(TOTAL)" | bc -l); \
	printf "\r\033[K\033[1;34m[\033[0m"; \
	BAR_SIZE=$$(echo "$$PROGRESS / 2" | bc); \
	for i in $$(seq 1 50); do \
		if [ $$BAR_SIZE -ge $$i ]; then \
			printf "\033[1;32m#\033[0m"; \
		else \
			printf " "; \
		fi; \
	done; \
	printf "\033[1;34m] %.2f%%\033[0m" $$PROGRESS
endef

.PHONY: all clean fclean re release

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	@ar rcs $@ $^ >/dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ >/dev/null 2>&1; \
	$(call PRINT_PROGRESS)

# %.o: %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(SRC_DIR)/*.o >/dev/null 2>&1

fclean: clean
	@rm -f $(TARGET_LIB) >/dev/null 2>&1

re: fclean all

release: CFLAGS += -O3 -DNDEBUG
release: fclean all
