#ifndef DECOMP_H
#define DECOMP_H

#include "../common.h"
#include "error.h"

// Markers
#define MARK		0xFF
#define BEGIN		0xD8	// Begin Image Mark
#define END			0xD9	// Finish Image Mark
#define COMMENT		0xFE	// Comment Mark
#define DQT			0xDB	// Quatization Table
#define SOF0		0xC0	// Basic encode method. Baseline DCT
#define DHT			0xC4	// Haffman's Table
#define SOS			0xDA	// Start of Scan
#define JFIF		0xE0	// JPEG FILE INTERCHANGE FORMAT

typedef enum {
							// Length value in table
	DC_0	= 0x00,			// 1 byte
	AC_0	= 0x01,			// 2 byte
							// Identificator of table
	DC_1	= 0x10,			// Y
	AC_1	= 0x11			// Cb & Cr
}i_DHT;

typedef struct {			// Haffman's table
	uint16_t segment_lenght;
	uint8_t id_table;
	uint8_t * count_code;
}_DHT, *P_DHT;

typedef struct tree {
	uint8_t value;
	uint8_t level;
	struct tree * root;
	struct tree * left_item;
	struct tree * right_item;
}DTH_TREE, *P_DTH_TREE;

typedef struct header_SOS {			// Header scan segment
	uint16_t header_lenght;
	uint8_t num_comp;
}_SOS, *P_SOS;

uint64_t lenght_file;

MESSAGE ValidImage(IMAGE * ptr_file, uint64_t lenght);
MESSAGE Decopmresion(IMAGE * ptr_file, uint64_t lenght);
MESSAGE ParseMark(IMAGE * ptr_file);
MESSAGE GetCode(_DHT table, uint64_t * src);

P_DTH_TREE Initialize(uint8_t * new_value, uint8_t level, P_DTH_TREE root);
void BuildTree(P_DTH_TREE tree, uint32_t count, uint8_t current_level);
uint32_t ExtractWords(P_DTH_TREE tree, uint32_t count);

#endif 

