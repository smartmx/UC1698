/*
 * Copyright (c) 2022, smartmx - smartmx@qq.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#ifndef __UC1698_H_
#define __UC1698_H_

#include "spi_3wire_io.h"

#define UC1698_CONTRAST             0x55

extern void uc1698_init(void);

extern void uc1698_show_str(uint8_t x, uint8_t y, uint8_t *src);

extern void uc1698_bsp_init(void);

extern void uc1698_Draw_Picture(u8 Wide, u8 High, u8 Column, u8 Row, const u8 *p);

extern void uc1698_Lattice(u8 Data1, u8 Data2, u8 Data3, u8 Data4, u8 Data5, u8 Data6);

extern void uc1698_show_string(uint8_t x, uint8_t y, uint8_t *src);

extern void uc1698_show_qrcode(uint8_t x, uint8_t y, int side, uint8_t *src);

#endif /* __UC1698_H_ */
