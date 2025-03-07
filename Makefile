# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 18:30:46 by mait-you          #+#    #+#              #
#    Updated: 2025/03/06 20:50:25 by mait-you         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### dirs
OBJS_DIR	:= obj
LIBFT_DIR	:= libft

### Compiler and Flags
CC			:= cc
AR			:= ar rsc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf

### Executable Name
NAME_1		:= server
NAME_2		:= client
NAME_1_B	:= server_bonus
NAME_2_B	:= client_bonus
LIBFT		:= $(LIBFT_DIR)/libft.a

### Source Files 
LIBFT_SRCS	:= $(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_memset.c

BONUS_SRCS	:= bonus/minitalk_utils_bonus.c

SRCS		:= mandatory/minitalk_utils.c

OBJS		:= $(SRCS:%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS	:= $(BONUS_SRCS:%.c=$(OBJS_DIR)/%.o)
LIBFT_OBJS	:= $(LIBFT_SRCS:%.c=$(OBJS_DIR)/%.o)

### Colors and Formatting
RESET		:= \033[0m
BLACK		:= \033[30m
RED			:= \033[31m
GREEN		:= \033[32m
YELLOW		:= \033[33m
BLUE		:= \033[34m
PURPLE		:= \033[35m
CYAN		:= \033[36m
WHITE		:= \033[37m
BOLD		:= \033[1m
UP			:= \033[F

### Rules
all: $(NAME_1) $(NAME_2) mandatory/minitalk.h

$(NAME_1): $(LIBFT) $(OBJS) mandatory/server.c
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) mandatory/server.c -o $(NAME_1)
	@echo "$(RED)$(BOLD)$(NAME_1) $(GREEN)Compiled successfully!$(RESET)"

$(NAME_2): $(LIBFT) $(OBJS) mandatory/client.c
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) mandatory/client.c -o $(NAME_2)
	@echo "$(RED)$(BOLD)$(NAME_2) $(GREEN)Compiled successfully!$(RESET)"

$(LIBFT): $(LIBFT_OBJS)
	@$(AR) $(LIBFT) $(LIBFT_OBJS)
	@echo "$(CYAN)Building libft ...$(RESET)"
	@echo "$(CYAN)╚═ Built $(PURPLE)$(BOLD)$(LIBFT)$(RESET)"

# libft $(LIB_DIR) Object file compilation rules
$(OBJS_DIR)/$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c $(LIBFT_DIR)/libft.h | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $(WHITE)$<$(RESET)"

# minitalk $(SRCS) Object file compilation rules
$(OBJS_DIR)/mandatory/%.o: mandatory/%.c mandatory/minitalk.h $(LIBFT_DIR)/libft.h | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $(WHITE)$<$(RESET)"

bonus: $(NAME_1_B) $(NAME_2_B) bonus/minitalk_bonus.h

$(NAME_1_B): $(LIBFT) $(BONUS_OBJS) bonus/server_bonus.c
	@$(CC) $(CFLAGS) $(LIBFT) $(BONUS_OBJS) bonus/server_bonus.c -o $(NAME_1_B)
	@echo "$(RED)$(BOLD)$(NAME_1_B) $(GREEN)Compiled successfully!$(RESET)"

$(NAME_2_B): $(LIBFT) $(BONUS_OBJS) bonus/client_bonus.c
	@$(CC) $(CFLAGS) $(LIBFT) $(BONUS_OBJS) bonus/client_bonus.c -o $(NAME_2_B)
	@echo "$(RED)$(BOLD)$(NAME_2_B) $(GREEN)Compiled successfully!$(RESET)"

# minitalk_bonus $(BONUS_SRCS) Object file compilation rules
$(OBJS_DIR)/bonus/%.o: bonus/%.c bonus/minitalk_bonus.h $(LIBFT_DIR)/libft.h | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $(WHITE)$<$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(RM) $(OBJS_DIR) $(LIBFT)
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME_1) $(NAME_2) $(NAME_1_B) $(NAME_2_B)
	@echo "$(RED)$(UP)Cleaned object files and $(RED)$(BOLD)$(NAME)$(RESET)"

re: fclean all

.PHONY: clean