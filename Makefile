-include ./Configuration/Sources.mk
-include ./Configuration/Includes.mk
-include ./Configuration/Bonus.mk

NAME		= minishell

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -I $(INCLUDES_DIR) -I Libft

OBJS		= $(SRCS:.c=.o)
OBJS_DIR 	= Objects
OBJS_PATH	= $(addprefix $(OBJS_DIR)/, $(OBJS))

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[2K\r\033[3;35m$<: \033[3;36mloading..\033[0m"

B_OBJS		= $(BONUS:.c=.o)
B_OBJS_DIR 	= Objects
B_OBJS_PATH	= $(addprefix $(B_OBJS_DIR)/, $(B_OBJS))

$(B_OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[2K\r\033[3;35m$<: \033[3;36mloading..\033[0m"

$(NAME): $(OBJS_PATH)
	@$(MAKE) --no-print-directory -C Libft/
	@$(CC) $(CFLAGS) $(OBJS_PATH) Libft/libft.a -lreadline -o $(NAME)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;32mCompiled [√]\033[0m\n"

all: $(NAME)

bonus:  $(B_OBJS_PATH)
	@$(MAKE) --no-print-directory -C Libft/
	@$(CC) $(CFLAGS) $(B_OBJS_PATH) Libft/libft.a -lreadline -o $(NAME)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;32mCompiled [√]\033[0m\n"

clean:
	@$(MAKE) --no-print-directory -C Libft/ clean
	@rm -rf $(OBJS_DIR)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;31mObject Delete \033[1;32m[√]\033[0m\n"

fclean: clean
	@$(MAKE) --no-print-directory -C Libft/ fclean
	@rm -rf $(NAME)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;31m$(NAME) Delete \033[1;32m[√]\033[0m\n"

re: fclean all

norme:
	@touch tmp
	@norminette -R CheckForbiddenSourceHeader $(SRCS) | grep "Error" | cut -d' ' -f1,3-20 | tr -s "\t" " " | sed 's,$(SRCS_DIR),\x1b[31m⇒ &,' | sed 's,Error,\x1b[93m&,' > tmp
	@norminette -R CheckDefine $(INCLUDES) | grep "Error" | cut -d' ' -f1,3-20 | tr -s "\t" " " | sed 's,$(INCLUDES_DIR),\x1b[31m⇒ &,' | sed 's,Error,\x1b[93m&,' >> tmp
	@cat tmp
	@printf "\e[1m\e[4m\e[31m"
	@cat tmp | grep "⇒" | wc -l | tr "\n" " " | sed 's,0,\x1b[92m&,'
	@printf "Norminette error !\n\033[0m"
	@rm -rf tmp

.PHONY: all bonus clean fclean re norme
