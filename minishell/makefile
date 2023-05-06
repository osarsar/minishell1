SRCS = minishell.c	\
	minishell_utils1.c	\

NAME = libft.a

%.o : %.c pipex.h minishell.h
	@echo "Compiling: $<"
	@cc -Wall -Werror -Wextra  -c $< -o $@

$(NAME) : $(SRCS:.c=.o)
	@make -C pipex_bonus
	@ar -r $(NAME) $(SRCS:.c=.o)
	@cc minishell.c libft.a -lreadline -o minishell

	
all : $(NAME)

clean :
	@rm -f $(SRCS:.c=.o)
	@make clean -C pipex_bonus

fclean : clean
	@rm -f libft.a
	@make fclean -C pipex_bonus

re : fclean all
