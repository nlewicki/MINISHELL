CFILES = src/main.c \

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -g
OBJ_DIR = Obj
OFILES = $(addprefix $(OBJ_DIR)/,$(notdir $(CFILES:.c=.o)))

$(NAME): $(OBJ_DIR) $(OFILES)
	@$(CC) $(OFILES) -o $(NAME)
	clear
	@$(MAKE)	loading
	clear
	@$(MAKE)	banner
	@./$(NAME)


$(OBJ_DIR)/%.o: src/%.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

loading:
		@for i in {1..42}; do \
			printf '%s' "██"; \
			sleep 0.01; \
		done

banner:
		@echo "                                                                                                  "
		@echo "   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       "
		@echo " ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       "
		@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       "
		@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       "
		@echo " ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       "
		@echo " ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       "
		@echo " ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ "
		@echo "  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ "
		@echo "                                                                              ▀         ▀         "
		@echo "                                                                                                  "
		@echo " by mhummel & nlewicki                                                                            "
		@echo "                                                                                                  "


all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OFILES)
	@echo "\033[33mclean\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33mand\033[0m"
	@echo "\033[33mfclean\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re, loading
