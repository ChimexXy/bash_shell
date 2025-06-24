NAME = minishell

# CFLAGS = -Wextra -Wall -Werror 

SRC = pars/parsing.c pars/parsing1.c pars/parsing2.c pars/tokenizer.c\
	  utils/ft_free.c utils/ft_split.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_substr.c\
	  pars/envirement.c pars/redirection.c pars/path.c pars/parsing3.c\
	  pars/check_red.c pars/expand.c utils/ft_strjoin.c utils/ft_strcmp.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) ../inc/minishell.h
	$(CC) $(OBJ) -lreadline -fsanitize=address -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean   
	rm -rf $(NAME)

re : fclean all
