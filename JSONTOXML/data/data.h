/* data.h -- prototypes shared by jtox subroutines. 
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

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXBUF 255

enum Type
{
	Null,
	Bool,
	Number,
	String,
	Obj,
	Arr
};

struct DataNode
{
	char *label;
	int type;
	void *data;
	struct DataNode *next;
};

struct ArrNode
{
	int type;
	void *data;
	struct ArrNode *next;
};

struct ArrNode *processArr(FILE *fp);
struct DataNode *processObject(FILE *fp);
char *cleanData(char *data);
int getDataType(char *data);
void XmlPrintObj(struct DataNode *head, int level);
void XmlPrintArr(struct ArrNode *head, int level);
void indent(int n);
struct DataNode *loadJson(FILE *fp);

#endif /* DATA_H */