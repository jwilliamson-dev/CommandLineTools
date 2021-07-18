/* procs.c -- data processing functions for jtox. 
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
 * Function: processObject
 * -----------------------
 * Creates a DataNode representation of a JSON object
 * 
 * fp: pointer to the file being read
 * 
 * returns: pointer to the first attribute in the JSON object
 */
struct DataNode *
processObject(FILE *fp)
{
	char buf[MAXBUF];
	struct DataNode *head = (struct DataNode *)malloc(sizeof(struct DataNode));
	struct DataNode *cur = head;
	struct DataNode *next = NULL;
	char *token;
	int done = 0;

	fgets(buf, sizeof(buf), fp);
	while (!done)
	{
		strtok(buf, "\"");
		token = strtok(NULL, "\"");
		cur->label = (char *)malloc(sizeof(char) * (strlen(token)+1));
		strcpy(cur->label, token);
		token = strtok(NULL, ":");
		cur->type = getDataType(token);

		if (cur->type != Obj && cur->type != Arr)
		{
			cur->data = cleanData(token);
		}
		if (cur->type == Obj)
		{
			cur->data = processObject(fp);
		}
		if (cur->type == Arr)
		{
			cur->data = processArr(fp);
		}

		fgets(buf, sizeof(buf), fp);
		if (strstr(buf, "}"))
		{

			done = 1;
		}
		else
		{
			next = (struct DataNode *)malloc(sizeof(struct DataNode));
			cur->next = next;
			cur = next;
		}
	}

	cur->next = NULL;
	return head;
}

/*
 * Function: processArr
 * -----------------------
 * Creates a ArrNode representation of a JSON array
 * 
 * fp: pointer to the file being read
 * 
 * returns: pointer to the first attribute in the JSON array
 */
struct ArrNode *
processArr(FILE *fp)
{
	char buf[MAXBUF];
	struct ArrNode *head = (struct ArrNode *)malloc(sizeof(struct ArrNode));
	struct ArrNode *cur = head;
	struct ArrNode *next = NULL;
	int done = 0;
	char *token;
	int type;

	fgets(buf, sizeof(buf), fp);

	while (!done)
	{
		cur->type = getDataType(buf);
		if (cur->type != Obj && cur->type != Arr)
		{
			cur->data = cleanData(buf);
		}
		if (cur->type == Obj)
		{
			cur->data = processObject(fp);
		}
		if (cur->type == Arr)
		{
			cur->data = processArr(fp);
		}

		fgets(buf, sizeof(buf), fp);

		if (strstr(buf, "]"))
		{
			done = 1;
		}
		else
		{
			next = (struct ArrNode *)malloc(sizeof(struct ArrNode));
			cur->next = next;
			cur = next;
		}
	}
	cur->next = NULL;
	return head;
}

/*
 * Function: loadJson
 * -----------------------
 * Creates a data structure representation of JSON data from a file.
 * 
 * fp: pointer to the file being read
 * 
 * returns: pointer to the root node of the data object.
 */
struct DataNode *
loadJson(FILE *fp)
{
	char buf[MAXBUF];
	struct DataNode *root = malloc(sizeof(struct DataNode));
	root->next = NULL;
	root->label = malloc(sizeof(char *) * 5);
	strcpy(root->label, "root");

	while (fgets(buf, sizeof(buf), fp))
	{

		if (strcmp(buf, "{\n") == 0)
		{
			root->type = Obj;
			root->data = processObject(fp);
		}
		if (strcmp(buf, "[\n") == 0)
		{
			root->type = Arr;
			root->data = processArr(fp);
		}
	}

	return root;
}