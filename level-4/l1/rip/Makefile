NAME = rip

SRC_NAME = main.c

RM = rm -f

all: $(NAME)

fclean:
	@rm -rf ./*.dSYM
	@$(RM) $(NAME)

re: fclean all

$(NAME):
	cc -g -o $@ $(SRC_NAME) 

.PHONY: all fclean re 
