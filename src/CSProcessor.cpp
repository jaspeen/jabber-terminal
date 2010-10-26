/*
 * CSProcessor.cpp
 *
 *  Created on: Oct 11, 2010
 *      Author: jaspeen
 */

#include "CSProcessor.h"
#include <ctype.h>
#include <stdio.h>

void CSProcessor::process(std::string & out, char * buf, int size){
	int p = 0;
	bool es = false;
	bool spec_case = false;
	for (int i = 0; i < size; i++) {
		//printf("L[%i,%i,%i,%i,%i]'%s'\n",p,i,es,spec_case,buf[i],out.c_str());
	    if (spec_case && buf[i] == '\n') {
			spec_case = false;
			p = i+1;
		} else if (buf[i] == 27 && !spec_case) {
			out.append(buf + p, i - p);
			if (i < (size - 1) && buf[i + 1] == ']')
				spec_case = true;
			else
				es = true;
		} else if (!spec_case && es && (buf[i] <= 126 && buf[i] >= 64 && buf[i] != 91
				&& buf[i] != 93)) {
			p = i + 1;
			es = false;
		} else if(buf[i] == 7)
			continue;
	}
	if (p < (size - 1) && !es && !spec_case)
		out.append(buf + p, size - p);
}
