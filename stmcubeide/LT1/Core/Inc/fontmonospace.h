/*
 * fontmonospace.h
 *
 *  Created on: 16.09.2023
 *      Author: Martin
 */

#ifndef INC_FONTMONOSPACE_H_
#define INC_FONTMONOSPACE_H_

#define FONT_CHAR_SEPARATOR	(0x00)
// nb cols each char
// separater space, nb cols
const uint8_t font[96][5] = {
	{0x00, 0x00, 0x00, 0x00, 0x00}, // ' ' (space)
	{0x00, 0x00, 0x7D, 0x00, 0x00}, // !
	{0x00, 0x60, 0x00, 0x60, 0x00}, // "
	{0x14, 0x7F, 0x14, 0x7F, 0x14}, // #
	{0x00, 0x39, 0x46, 0x44, 0x28}, // ç
	{0x23, 0x54, 0x2A, 0x15, 0x62}, // %
	{0x02, 0x35, 0x4D, 0x4A, 0x35}, // &
	{0x00, 0x00, 0x60, 0x00, 0x00}, // '
	{0x00, 0x1C, 0x22, 0x41, 0x00}, // (
	{0x00, 0x41, 0x22, 0x1C, 0x00}, // )
	{0x12, 0x0C, 0x38, 0x0C, 0x12}, // *
	{0x08, 0x08, 0x3E, 0x08, 0x08}, // +
	{0x00, 0x10, 0x20, 0x00, 0x00}, // ´
	{0x00, 0x08, 0x08, 0x08, 0x08}, // -
	{0x00, 0x00, 0x01, 0x00, 0x00}, // .
	{0x01, 0x02, 0x0C, 0x30, 0x40}, // /
	{0x3E, 0x45, 0x49, 0x51, 0x3E}, // 0
	{0x00, 0x21, 0x7F, 0x01, 0x00}, // 1
	{0x21, 0x43, 0x45, 0x49, 0x31}, // 2
	{0x22, 0x41, 0x49, 0x49, 0x36}, // 3
	{0x08, 0x18, 0x28, 0x7F, 0x08}, // 4
	{0x7A, 0x49, 0x49, 0x49, 0x46}, // 5
	{0x3E, 0x49, 0x49, 0x49, 0x26}, // 6
	{0x40, 0x41, 0x42, 0x4C, 0x70}, // 7
	{0x36, 0x49, 0x49, 0x49, 0x36}, // 8
	{0x32, 0x49, 0x49, 0x49, 0x3E}, // 9
	{0x00, 0x00, 0x22, 0x00, 0x00}, // :
	{0x00, 0x00, 0x23, 0x00, 0x00}, // ;
	{0x08, 0x14, 0x22, 0x41, 0x00}, // <
	{0x00, 0x14, 0x14, 0x14, 0x00}, // =
	{0x00, 0x41, 0x22, 0x14, 0x08}, // >
	{0x30, 0x40, 0x45, 0x48, 0x30}, // ?
	{0x3E, 0x41, 0x41, 0x41, 0x22}, // @
	{0x1F, 0x24, 0x44, 0x24, 0x1F}, // A
	{0x7F, 0x49, 0x49, 0x49, 0x36}, // B
	{0x3E, 0x41, 0x41, 0x41, 0x22}, // C
	{0x7F, 0x41, 0x41, 0x41, 0x3E}, // D
	{0x7F, 0x49, 0x49, 0x41, 0x41}, // E
	{0x7F, 0x48, 0x48, 0x40, 0x40}, // F
	{0x3E, 0x41, 0x41, 0x45, 0x27}, // G
	{0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
	{0x00, 0x41, 0x7F, 0x41, 0x00}, // I
	{0x02, 0x41, 0x41, 0x7E, 0x00}, // J
	{0x7F, 0x08, 0x14, 0x22, 0x41}, // K
	{0x7F, 0x01, 0x01, 0x01, 0x01}, // L
	{0x7F, 0x20, 0x10, 0x20, 0x7F}, // M
	{0x7F, 0x10, 0x08, 0x04, 0x7F}, // N
	{0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
	{0x7F, 0x48, 0x48, 0x48, 0x30}, // P
	{0x3E, 0x41, 0x45, 0x42, 0x3D}, // Q
	{0x7F, 0x48, 0x4C, 0x4A, 0x31}, // R
	{0x32, 0x49, 0x49, 0x49, 0x26}, // S
	{0x40, 0x40, 0x7F, 0x40, 0x40}, // T
	{0x7E, 0x01, 0x01, 0x01, 0x7E}, // U
	{0x70, 0x0E, 0x01, 0x0E, 0x70}, // V
	{0x7E, 0x01, 0x06, 0x01, 0x7E}, // W
	{0x41, 0x36, 0x08, 0x36, 0x41}, // X
	{0x60, 0x18, 0x07, 0x18, 0x60}, // Y
	{0x41, 0x47, 0x49, 0x71, 0x41}, // Z
	{0x00, 0x7F, 0x41, 0x41, 0x00}, // [
	{0x40, 0x30, 0x08, 0x06, 0x01}, // '\'
	{0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
	{0x00, 0x30, 0x40, 0x30, 0x00}, // ^
	{0x01, 0x01, 0x01, 0x01, 0x01}, // _
	{0x00, 0x40, 0x20, 0x00, 0x00}, // `
	{0x16, 0x29, 0x29, 0x29, 0x1F}, // a
	{0x7F, 0x09, 0x09, 0x09, 0x06}, // b
	{0x06, 0x09, 0x09, 0x09, 0x00}, // c
	{0x06, 0x09, 0x09, 0x09, 0x7F}, // d
	{0x0E, 0x15, 0x15, 0x15, 0x08}, // e
	{0x00, 0x3F, 0x48, 0x48, 0x20}, // f
	{0x00, 0x19, 0x25, 0x25, 0x1E}, // g
	{0x00, 0x7F, 0x08, 0x08, 0x07}, // h
	{0x00, 0x09, 0x4F, 0x09, 0x00}, // i
	{0x02, 0x01, 0x01, 0x4E, 0x00}, // j
	{0x00, 0x7F, 0x04, 0x0A, 0x11}, // k
	{0x00, 0x7F, 0x01, 0x00, 0x00}, // l
	{0x07, 0x08, 0x04, 0x08, 0x07}, // m
	{0x00, 0x0F, 0x08, 0x08, 0x07}, // n
	{0x06, 0x09, 0x09, 0x06, 0x00}, // o
	{0x00, 0x1F, 0x12, 0x12, 0x0C}, // p
	{0x00, 0x0C, 0x12, 0x12, 0x1F}, // q
	{0x00, 0x1F, 0x08, 0x10, 0x00}, // r
	{0x00, 0x12, 0x29, 0x29, 0x06}, // s
	{0x00, 0x7E, 0x21, 0x02, 0x00}, // t
	{0x00, 0x0E, 0x01, 0x01, 0x0F}, // u
	{0x0C, 0x02, 0x01, 0x02, 0x0C}, // v
	{0x0E, 0x01, 0x06, 0x01, 0x0E}, // w
	{0x11, 0x0A, 0x04, 0x0A, 0x11}, // x
	{0x11, 0x0A, 0x04, 0x08, 0x10}, // y
	{0x11, 0x13, 0x15, 0x19, 0x11}, // z
	{0x00, 0x08, 0x36, 0x41, 0x00}, // {
	{0x00, 0x00, 0x7F, 0x00, 0x00}, // |
	{0x00, 0x41, 0x36, 0x08, 0x00}, // }
	{0x08, 0x10, 0x08, 0x04, 0x08}, // ~
	{0x00, 0x00, 0x00, 0x00, 0x00}, // (DEL)
};

#endif /* INC_FONTMONOSPACE_H_ */