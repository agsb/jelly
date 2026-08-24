#!/usr/bin/awk 

BEGIN {

	}

function circuit () {
	
	if (u4.cko == 0 && u4.cka == 1) {
		u4.byte = db.byte
		}

	if (u5.cko == 0 && u5.cka == 1) {
		u5.byte = db.byte
		}

	if (u6.cko == 0 && u6.cka == 1) {
		u6.byte = u2.byte
		}
	
	u1.lowaddr = u8.lowaddr
	u3.lowaddr = u8.lowaddr
	
	u1.higaddr = u4.byte
	u3.higaddr = u4.byte
	u2.addr = u5.byte
	u2.

	}
END {
	}
