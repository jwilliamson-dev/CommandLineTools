/* 'jsonpretty' JSON Pretty Printer
 *
 * Copyright (C) 2021 Jacob Williamson. 
 * 
 * This program is free software. You can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundatio version 3 of the License.
 * 
 * This program is distributed in the hope that is will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */

#include <stdio.h>

void 
indent(int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("\t");
    }
}

int 
main(int argc, char *argv[])
{
    int i, c, n, level = 0, inStr = 0;
    FILE *fp;

    for (int i = 1; i < argc; i++)
    {
        if (fp = fopen(argv[i], "r"))
        {
            c = fgetc(fp);
            n = fgetc(fp);

            while (c != EOF)
            {
                if ((char)c == '"')
                {
                    inStr = (inStr + 1) % 2;
                    printf("%c", c);
                }
                else if ((char)c == '\\' && (char)n == '"')
                {
                    printf("%c%c", c, n);
                    c = n;
                    n = fgetc(fp);
                }
                else if (inStr)
                {
                    printf("%c", c);
                }
                else if ((char)c == '{' || (char)c == '[')
                {
                    printf("%c\n", c);
                    indent(++level);
                }
                else if ((char)c == ',')
                {
                    printf("%c\n", c);
                    indent(level);
                }
                else if ((char)c == '}' || (char)c == ']')
                {
                    printf("\n");
                    indent(--level);
                    printf("%c", c);
                }
                else if((char)c == ' ' || (char)c == '\n' || (char)c == '\t')
                {
                    ;
                }
                else if((char)c == ':')
                {
                    printf("%c ", c);
                }
                else
                {
                    printf("%c", c);
                }

                c = n;
                if (n != EOF)
                {
                    n = fgetc(fp);
                }
            }
        }
        else
        {
            fprintf(stderr, "Unable to open file %s", argv[i]);
        }

        printf("\n");
    }

    return 0;
}