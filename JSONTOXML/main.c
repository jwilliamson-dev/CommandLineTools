/* 'jtox' JSON to XML converter program. 
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data/data.h"

int
main(int argc, char *argv[])
{
	FILE *fp;
	struct DataNode *root;
	int i;

	for(i = 1; i < argc; i++)
	{
		if(fp = fopen(argv[i], "r"))
		{
			root = loadJson(fp);
			fclose(fp);
			XmlPrintObj(root, 0);
			free(root);
		}
		else
		{
			fprintf(stderr, "Unable to open %s. Skipping file.\n", argv[i]);
		}
	}

	return 0;
}