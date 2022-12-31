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
#include "spi_3wire_io.h"

__attribute__((always_inline)) static inline void _spi_3wire_delay()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_scl_high()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_scl_low()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_sdo_high()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_sdo_low()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_cs_high()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_cs_low()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_a0_high()
{

}

__attribute__((always_inline)) static inline void _spi_3wire_a0_low()
{

}

void spi_3wire1a0_send_byte(uint8_t byte, uint8_t mode)
{
    uint8_t i = 8;

    _spi_3wire_cs_low();
    if (mode == DATA_MODE)
    {
        _spi_3wire_a0_high();
    }
    else if (mode == CMD_MODE)
    {
        _spi_3wire_a0_low();
    }

    while (i--)
    {

        if (byte & 0x80)
        {
            _spi_3wire_sdo_high();
        }
        else
        {
            _spi_3wire_sdo_low();
        }
        _spi_3wire_scl_low();
        _spi_3wire_delay();
        _spi_3wire_scl_high();
        _spi_3wire_delay();
        byte <<= 1;
    }
    _spi_3wire_cs_high();

}




