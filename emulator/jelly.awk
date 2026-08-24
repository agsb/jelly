#!/usr/bin/awk 

BEGIN {

	}

END {


	clock = clock + 1;

	u8.byte = u8.byte % 16;

	u1.byte = u1.rom[u1.addr]

	u3.byte = u3.rom[u3.addr]

	u2.byte = u2.rom[u2.addr]

	c0 = u1.byte & 0x01
	c1 = u1.byte & 0x02
	c2 = u1.byte & 0x04
	c3 = u1.byte & 0x08
	c4 = u1.byte & 0x10

	if (u4.cko == 0 && u4.cka == 1) {
		u4.byte = db.byte
		}

	if (u5.cko == 0 && u5.cka == 1) {
		u5.byte = db.byte
		}

	if (u6.cko == 0 && u6.cka == 1) {
		u6.byte = u2.byte
		}
	
	u1.addr = ((u4.byte % 16) * 16) + u8.byte; 

	u3.addr = ((u4.byte % 16) * 16) + u8.byte; 
	
	u2.addr = (( u5.byte ) + M0 * 256 + M1 * 512 + M2 * 1024;

	}
