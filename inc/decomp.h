#ifndef DECOMP_H
#define DECOMP_H

#include "../common.h"

// Markers
#define MARK		0xFF
#define BEGIN		0xD8	// Mark of Begin Image
#define END			0xD9	// Mark of finish Image
#define COMMENT		0xFE	// Mark of comment
#define DQT			0xDB	// Quatization Table
#define SOF0		0xC0	// Basic encode method. Baseline DCT
#define DHT			0xC4	// Haffman's Table
#define SOS			0xDA	// Start of Scan

typedef enum {
	// Length value in table
	DC_0	= 0x00,		// 1 byte
	AC_0	= 0x01,		// 2 byte
	// Identificator of table
	DC_1	= 0x10,		// Y
	AC_1	= 0x11		// Cb & Cr
}i_DHT;

typedef struct {
	WORD length;
	i_DHT id_table;
	char * count_code;
}_DHT, *P_DHT;

#endif 
