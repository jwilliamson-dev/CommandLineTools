/* helpers.c -- helper functions shared by jtox subroutines. 
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
 * Function: cleanData
 * ---------------------
 * Removes quotes around a string value and a trailing comma
 * 
 * data: the string that should be cleaned
 * 
 * returns: the cleaned string
 */
char *
cleanData(char *data)
{
	int inLen = strlen(data);
	int outLen = 0;
	int i = 0;
	char prev = '\0';
	char cur = '\0';
	char out[MAXBUF] = {'\0'};
	char *final;
	int leading = 1;

	for (i = 0; i < inLen; i++)
	{
		cur = data[i];

		if(leading == 1 && (cur == ' ' || cur == '\t')) // Ignore leading white space
		{
			;
		}
		else if (cur == '\"' && prev != '\\')
		{
			leading = 0;
		}
		else if (cur == '\n' && prev == ',')
		{
			outLen--;
		}
		else if (cur == '\n')
		{
			;
		}
		else
		{
			leading = 0;
			out[outLen] = cur;
			outLen++;
		}

		prev = cur;
	}

	final = (char *)malloc(sizeof(char) * (outLen+1));
	snprintf(final, outLen+1, "%s", out);

	return final;
}

/*
 * Function: getDataType
 * ---------------------
 * Identifies the type of data stored in a DataNode or an ArrNode
 * 
 * data: the string for which the data type should be identified
 * 
 * returns: the int corrensponding to the Type enum
 */
int 
getDataType(char *data)
{
	int len = strlen(data);
	int i;

	for (i = 0; i < len; i++)
	{
		if (data[i] == 'n')
		{
			return Null;
		}
		if (data[i] == 't' || data[i] == 'f')
		{
			return Bool;
		}
		if (isdigit(data[i]) != 0)
		{
			return Number;
		}
		if (data[i] == '\"')
		{
			return String;
		}
		if (data[i] == '{')
		{
			return Obj;
		}
		if (data[i] == '[')
		{
			return Arr;
		}
	}

	fprintf(stderr, "ENCOUNTERED PROBLEM WITH value: %s\n", data);
	return -1;
}

/*
 * Function: indent
 * -----------------------
 * Prints specified number of tab characters
 * 
 * n: number of tabs
 * 
 * returns: void
 */
void indent(int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        printf("\t");
    }
}