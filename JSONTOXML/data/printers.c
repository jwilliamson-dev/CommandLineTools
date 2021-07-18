/* printers.c -- printing functions for jtox subroutines. 
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

#include "data.h"

/*
 * Function: XmlPrintObj
 * -----------------------
 * Prints an object in XML format
 * 
 * head: Pointer to the head of object to be printed
 * level: Depth of object within entire data structure
 * 
 * returns: void
 */
void XmlPrintObj(struct DataNode *head, int level)
{
    struct DataNode *cur = head;
    struct DataNode *prev = NULL;

    while (cur != NULL)
    {
        if (cur->type < 0 || cur->type > Arr)
        {
            fprintf(stderr, "Invalid Type %d in Object\n(XmlPrintObj) %s\n", cur->type, cur->label);
            exit(1);
        }
        else if (cur->type == Arr)
        {
            indent(level);
            printf("<%s>\n", cur->label);
            XmlPrintArr(cur->data, level + 1);
            indent(level);
            printf("</%s>\n", cur->label);
        }
        else if (cur->type == Obj)
        {
            indent(level);
            printf("<%s>\n", cur->label);
            XmlPrintObj(cur->data, level + 1);
            indent(level);
            printf("</%s>\n", cur->label);
        }
        else
        {
            indent(level);
            printf("<%s>%s</%s>\n", cur->label, (char *)cur->data, cur->label);
        }

        prev = cur;
        cur = cur->next;

        free(prev->label);
        free(prev->data);

        if(prev != head)
        {
            free(prev);
        }
    }
}

/*
 * Function: XmlPrintArr
 * -----------------------
 * Prints an array in XML format
 * Assumes label for members is "item"
 * 
 * head: Pointer to the head of array to be printed
 * level: Depth of array within entire data structure
 * 
 * returns: void
 */
void XmlPrintArr(struct ArrNode *head, int level)
{
    struct ArrNode *cur = head;
    struct ArrNode *prev = NULL;

    while (cur != NULL)
    {
        if (cur->data == NULL)
        {
            fprintf(stderr, "Malformed Object");
        }
        if (cur->type < 0 || cur->type > Arr)
        {
            fprintf(stderr, "Invalid Type %d in Object\n(XmlPrintArr)\n", cur->type);
        }
        else if (cur->type == Arr)
        {
            indent(level);
            printf("<item>\n");
            XmlPrintArr(cur->data, level + 1);
            indent(level);
            printf("</item>\n");
        }
        else if (cur->type == Obj)
        {
            indent(level);
            printf("<item>\n");
            XmlPrintObj(cur->data, level + 1);
            indent(level);
            printf("</item>\n");
        }
        else
        {
            indent(level);
            printf("<item>%s</item>\n", (char *)cur->data);
        }

        prev = cur;
        cur = cur->next;

        free(prev->data);

        if(prev != head)
        {
            free(prev);
        }
    }
}
