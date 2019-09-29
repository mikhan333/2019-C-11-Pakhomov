/**
 * @file main.c
 * @author Pakhomov Mikhail
 * @brief Program for triple sorting poem
 * @version 0.1
 * @date 2019-09-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Struct for one line from the poem
 * 
 */
typedef struct
{
    char *start;
    size_t len;
} Line;

/**
 * @brief Get the count lines in the poem
 * 
 * @param text Long input buffer with the poem
 * @return int Count of lines in the poem
 */
int get_count_lines(const char *text)
{
    int count_lines = 0;
    for (int i = 1; text[i]; i++)
    {
        if (text[i] == '\n')
        {
            if (text[i - 1] != '\n')
                count_lines++;
        }
    }
    return count_lines;
}

/**
 * @brief Create a mas lines object
 * 
 * @param text Input buffer
 * @param count_lines Count of lines
 * @return Line* Massive of (Line*) lines from the poem
 */
Line *create_mas_lines(char *text, int count_lines)
{
    Line *lines = (Line *)calloc(count_lines, sizeof(Line));
    int i = 0;

    char *line_prev = text - 1;
    int len = 0;
    for (char *line = strchr(text, '\n'); line; line = strchr(line + 1, '\n'))
    {
        len = line - line_prev;
        if (len != 1)
        {
            lines[i].start = line_prev + 1;
            lines[i++].len = len - 1;
            // *line = '\0';
        }
        line_prev = line;
    }
    return lines;
}

/**
 * @brief Compare 2 object (Line *) by start of line
 * 
 * @param first_v 
 * @param second_v 
 * @return int 
 */
int str_cmp_start(const void *first_v, const void *second_v)
{
    Line *first = (Line *)first_v;
    Line *second = (Line *)second_v;
    const char *a = first->start;
    const char *b = second->start;
    while (*a != '\n' && *b != '\n')
    {
        if (tolower(*a) == tolower(*b))
            ++a, ++b;
        else if(!isalpha(*a))
            ++a;
        else if(!isalpha(*b))
            ++b;
        else
            break;
    }
    return tolower(*a) - tolower(*b);
}

/**
 * @brief Compare 2 object (Line *) by end of line
 * 
 * @param first_v 
 * @param second_v 
 * @return int 
 */
int str_cmp_end(const void *first_v, const void *second_v)
{
    Line *first = (Line *)first_v;
    Line *second = (Line *)second_v;
    const char *a = first->start + first->len;
    const char *b = second->start + second->len;
    int res;
    while (a > first->start && b > second->start)
    {
        if (tolower(*a) == tolower(*b))
            --a, --b;
        else if(!isalpha(*a))
            --a;
        else if(!isalpha(*b))
            --b;
        else
            break;
    }
    return (res = tolower(*a) - tolower(*b)) == 0 ? first->len - second->len : res;
}

/**
 * @brief Read data from file in buffer
 * 
 * * Add '\n' in the buffer before last char '\0'
 * 
 * @param path_file_in Input file
 * @return char* Buffer
 */
char *read_file(const char *path_file_in)
{
    FILE *file_in = fopen(path_file_in, "rb");
    if (file_in == NULL)
    {
        puts("ERROR: read_file(): problem with opening the file.");
        exit(EXIT_FAILURE);
    }

    fseek(file_in, 0, SEEK_END);
    size_t len_file_in = ftell(file_in);
    rewind(file_in);

    char *text = (char *)calloc(len_file_in + 2, sizeof(char));
    if (fread(text, sizeof(char), len_file_in, file_in) != len_file_in)
    {
        puts("ERROR: read_file(): problem with reading the file.");
        exit(EXIT_FAILURE);
    }
    text[len_file_in] = '\n';

    fclose(file_in);
    return text;
}

/**
 * @brief Triple sorting data and write data in file
 * 
 * @param path_file_out Output file
 * @param text Buffer with poem
 * @param lines List of lines
 * @param count_lines Count of lines
 */
void write_file(const char *path_file_out, char *text, Line *lines, int count_lines)
{
    FILE *file_out = fopen(path_file_out, "wb+");
    if (file_out == NULL)
    {
        puts("ERROR: sort_write_text(): problem with opening the file.");
        exit(EXIT_FAILURE);
    }

    fputs("---------------------------------------------\nBY START OF STRING\n\n", file_out);
    qsort(lines, count_lines, sizeof(Line), str_cmp_start);
    for (int i = 0; i < count_lines; i++)
    {
        fwrite(lines[i].start, sizeof(char), lines[i].len, file_out);
        fputs("\n", file_out);
    }

    fputs("---------------------------------------------\nBY END OF STRING\n\n", file_out);
    qsort(lines, count_lines, sizeof(Line), str_cmp_end);
    for (int i = 0; i < count_lines; i++)
    {
        fwrite(lines[i].start, sizeof(char), lines[i].len, file_out);
        fputs("\n", file_out);
    }

    fputs("---------------------------------------------\nORIGINAL\n\n", file_out);
    fputs(text, file_out);

    fclose(file_out);
}

/**
 * @brief The main() - entry point
 * 
 * @return int Program exit status
 */
int main()
{
    puts("-----------------------------------------------\n");
    puts("This is a program for tripple sorting Eugene Onegin:\n"
         "1. start of line; 2. end of line; 3. none\n"
         "Created by Mikhail Pakhomov.\n");
    // File paths 
    char *path_file_in = "/home/mikhan/2019-C-11-Pakhomov/SortLongText/poem.txt";
    char *path_file_out = "/home/mikhan/2019-C-11-Pakhomov/SortLongText/sorted_poem.txt";

    // Read data from file and count lines in this
    char *text = read_file(path_file_in);
    int count_lines = get_count_lines(text);

    // Create mass of lines, in which we have pointer on data-lines in text and length of this lines 
    Line *lines = create_mas_lines(text, count_lines);

    // Sort the text and write this in the output file
    write_file(path_file_out, text, lines, count_lines);

    // Clear memory
    free(lines);
    free(text);
    puts("-----------------------------------------------\n");
    return 0;
}
