NAME = rip

CFLAGS = -Wall -Werror -Wextra -g

SRC_NAME = main.c

RM = rm -f

all: $(NAME)

fclean:
	@rm -rf ./*.dSYM
	@$(RM) $(NAME)

re: fclean all

$(NAME):
	cc $(CFLAGS) -o $@ $(SRC_NAME) 

.PHONY: all fclean re 
