#include <iostream>
#include <bitset>

void computeDecimalRepresentationOf(uint32_t number) {
	std::cout << "Original: " << std::bitset<32>(number) << "\n";

	uint8_t bytes[4];
	for (int i = 0; i < 4; i++) bytes[i] = (number >> (i * 8)) & 0xFF;

	std::cout << "Little endian: ";
	for (int i = 3; i >= 0; i--) std::cout << std::bitset<8>(bytes[i]) << " ";
	std::cout << "\n";

	std::cout << "Big endian: ";
	for (int i = 0; i < 4; i++) std::cout << std::bitset<8>(bytes[i]) << " ";
	std::cout << "\n";

	uint32_t bigEndian = 0;
	for (int i = 0; i < 4; i++) bigEndian |= bytes[i] << ((3 - i) * 8);

	// in case it's required to know/show how converting from big endian to decimal works:
	// the formula is: result = bits[0] * 2^31 + bits[1] * 2^30 + ... + bits[31] * 2^0
	std::cout << "Decimal: " << bigEndian << "\n\n";
}

void task6() {
	computeDecimalRepresentationOf(0b00111111000110011001100110011010);
	computeDecimalRepresentationOf(0b01000010111101110011100110010011);
	computeDecimalRepresentationOf(0b11000011010111101001110011001010);
}