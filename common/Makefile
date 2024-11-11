NAME = _  # replace NAME

SRC_NAME = main.c  # replace main.c

RM = rm -f

all: $(NAME)

fclean:
	@rm -rf ./*.dSYM
	@$(RM) $(NAME)

re: fclean all

$(NAME):
	cc -g -o $@ $(SRC_NAME) 

.PHONY: all fclean re 
