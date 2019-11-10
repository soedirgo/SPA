#pragma once
#include "AbstractType.h"
#include "PKBHash.h"
#include <unordered_set>

class PKBWith {
public:

	//with 1 = s.stmt#
	//with 1 = c.value
	//with "x" = proc.varName
	//with "proc1" = proc.Name
	static STMT_LIST getWithIdentAttr(IDENT iden, ENT_TYPE ent, ATTR attr);

	//with 1 = n
	static STMT_LIST getWithIdentLine(PROG_LINE n);

	//with s1.stmt# = s2.stmt#
	//with c.value = s2.stmt#
	//with s1.stmt# = c.value
	static TABLE getWithAttrAttr(ENT_TYPE ent1, ATTR attr1, ENT_TYPE ent2, ATTR attr2);

	//with s1.stmt# = n
	static TABLE getWithAttrLine(ENT_TYPE ent, ATTR attr);
	//with n1 = n2
	static TABLE getWithLineLine();
		
};