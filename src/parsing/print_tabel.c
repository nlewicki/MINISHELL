
#include "minishell.h"

size_t  nbr_of(char **str)
{
    size_t i;

    i = 0;
    while (str[i] != NULL)
        i++;
    return (i);
}

void  print_contents(char **str)
{
    size_t i;

    i = 0;
    while (str[i] != NULL)
    {
        printf("\033[35m[%s]\033[0m", str[i]);
        i++;
    }
}

void    print_struct_tabel(t_list *tabel)
{
    if (!tabel)
    {
        printf("No content in the table\n");
        return ;
    }
    t_command   *current_cmd;

    current_cmd = (t_command *)tabel->content;
    printf("\033[32m|\033[0m");
    printf("\033[33m Nbr of args:         [%zu]\n", nbr_of(current_cmd->args));
    printf("\033[32m|\033[0m");
    printf("\033[33m Nbr of filenames:    [%zu]\n", nbr_of(current_cmd->filename));
    printf("\033[32m|\033[0m");
    printf("\033[33m Nbr of red symbols:  [%zu]\n\033[0m", nbr_of(current_cmd->red_symbol));
    printf("\033[32m|\033[0m");

    printf("\033[32m\n|\033[0m");
    printf("\033[35m ARGS:         ");
    print_contents(current_cmd->args);
    printf("\033[32m\n|\033[0m");
    printf("\033[35m FILENAMES:    ");
    print_contents(current_cmd->filename);
    printf("\033[32m\n|\033[0m");
    printf("\033[35m REDIRECTIONS: \033[0m");
    print_contents(current_cmd->red_symbol);
    printf("\033[32m\n|\033[0m");
}

void    print_tabel(t_list *tabel)
{
    t_list *tmp;
    size_t  line;

    tmp = tabel;
    line = 1;
    while (tmp != NULL)
    {
        printf("\033[32m|------------------------------------|\n");
        printf("|            [line: %zu]               |\n", line);
        printf("\033[32m|------------------------------------|\n");
        print_struct_tabel(tmp);
        printf("\033\n[32m|-------------end-of-line------------|\033[0m\n\n");

        tmp = tmp->next;
        line++;
    }
}
