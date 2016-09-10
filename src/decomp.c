#include "../inc/decomp.h"

MESSAGE ValidImage(IMAGE * ptr_file, uint64_t lenght) {
	return ((ptr_file[0] == MARK) && (ptr_file[lenght - 1] == MARK)
		&& (ptr_file[1] == BEGIN) && (ptr_file[lenght] == END) ?
		SUCCESSFULLY : INVALID_IMAGE);
}

MESSAGE Decopmresion(IMAGE * ptr_file, uint64_t lenght) {
	lenght_file = lenght;
}


MESSAGE ParseMark(IMAGE * ptr_file) {				// WARNING! The data and mark are not checked. Possible error. Only Y, Cb&cr
	P_IMAGE ptr = ptr_file;
	uint8_t current_number_DHT = 0;
	_DHT DHT_item[4];
	uint64_t i = 0;
	for (; i < lenght_file; i++) {
		if (ptr[i] == MARK) {
			switch (ptr[i]) {
			case DHT:
				DHT_item[current_number_DHT].segment_lenght = ptr[i + 1] * 0x100 + ptr[i + 2];
				DHT_item[current_number_DHT].id_table = ptr[i + 3];
				DHT_item[current_number_DHT].count_code = &ptr[i + 4];
				i += DHT_item[current_number_DHT].segment_lenght + 1;
				current_number_DHT++;
				break;
			case SOS:
				goto START_OF_SCAN;
			default:
				return INVALID_MARK;
			}
		}
	}
	return NOT_FOUND_SOS;
START_OF_SCAN:
	if (current_number_DHT != 3) {
		return NOT_ALL_DHT_FOUND;
	}
	// Parse SoS

}

MESSAGE GetCode(_DHT table, uint64_t * src) {
	P_DTH_TREE code_tree = Initialize(-1, 0, 0);					
	code_tree->root = &code_tree;
	P_DTH_TREE main_root = &code_tree;
	uint32_t cccw = 0;													// Common Count Code Words conatain in Haffman's tree
	// First 3 bite it is header
	for (int i = 0; i < table.segment_lenght - 3; i++) {
		Add(&code_tree, table.count_code[i], i + 1);					// Factual Address
		cccw += table.count_code[i];
	}
	code_tree = &main_root;
	uint32_t * words = ExtractWords(&code_tree, cccw);					// Factual Address. 
																		// Warning! Should the return factual address
}

uint32_t ExtractWords(P_DTH_TREE tree, uint32_t count) {

}

P_DTH_TREE Initialize(uint8_t * new_value, uint8_t level, P_DTH_TREE root) {
	P_DTH_TREE new_element = (P_DTH_TREE *)malloc(sizeof(struct tree));
	new_element->value = new_value;
	new_element->level = level;
	new_element->root = &root;
	new_element->left_item = 0;
	new_element->right_item = 0;
	return new_element;
}

void BuildTree(P_DTH_TREE tree, uint32_t count, uint8_t current_level) {
	while (count) {															// Warning! Infinity cicle or CRASH Program, if count item more than edges in tree
		// At first read a left element
		if (tree->left_item) {
			// If this element have is the valid leght
			if (tree->level == current_level) {
				tree->left_item = Initialize(0, current_level + 1, &tree);	// Factual Address 
				count--;
			}
			// Else it is fake element
			else {
				tree->left_item = Initialize(-1, tree->level + 1, &tree);	// Factual Address 
			}
		}
		else if (tree->right_item) {
			if (tree->level == current_level) {
				tree->right_item = Initialize(1, current_level + 1, &tree);	// Factual Address 
				count--;
			}
			else {
				tree->right_item = Initialize(-1, tree->level + 1, &tree);	// Factual Address 
			}
		}
		// If right and left elements are occupied, then up
		else {
			Add(&tree->root, count, current_level);
		}
	}
	
}