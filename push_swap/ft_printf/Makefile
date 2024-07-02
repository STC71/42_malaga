NAME = libftprintf.a

SRC = ft_printf.c ft_write_chr.c ft_write_dns.c ft_write_hxl.c ft_write_hxu.c \
      ft_write_nbr.c ft_write_ptr.c ft_write_str.c ft_strlen.c

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) -csr $@ $?

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# This Makefile defines the following variables:

# NAME: The name of the resulting library.
# SRC: A list of C source files to compile.
# OBJS: A list of object files corresponding to the source files.
# CC: the C compiler to use.
# CFLAGS: The compilation options to pass to the compiler.

# Additionally, the Makefile defines the following rules:

# all: the default rule, which builds the library.
# $(NAME): The rule that builds the library from the object files.
# %.o: The rule that compiles a source file into an object file.
# clean: The rule that removes the object files.
# fclean: The rule that deletes the library and object files.
# re: the rule that calls fclean and all in sequence.

# The Makefile also defines the following macros:

# .PHONY: A list of targets that do not produce files.

# With this Makefile, the static library libftprintf.a is built by running make. 
# Also clean the object files with make clean and remove the library and object files with make fclean. 
# Finally, a complete rebuild of the library can be forced with make re.