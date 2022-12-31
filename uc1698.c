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
#include "uc1698.h"
#include "font_source.h"

void uc1698_bsp_init(void)
{
    /* ��ʼ��spi���� */

}

/*****  дָ���   ******/
__attribute__((always_inline)) static inline void uc1698_Write_Command(u8 Command)
{
    spi_3wire1a0_send_byte(Command, CMD_MODE);
}

/*****  д���ݺ���   ******/
__attribute__((always_inline)) static inline void uc1698_Write_Data(u8 Data)
{
    spi_3wire1a0_send_byte(Data, DATA_MODE);
}

/*****  LCD��ʼ������    ******/
void uc1698_init(void)
{
    uc1698_bsp_init();
    
    nRST = 0;

    DelayMs(200);

    nRST = 1;

    DelayMs(200);

    uc1698_Write_Command(0xe2);    //(23) SYSTEM RESET

    DelayMs(50);

    uc1698_Write_Command(0x2b);    //(6) SET POWER CONTROL

    DelayMs(20);

    uc1698_Write_Command(0x81);
    uc1698_Write_Command(UC1698_CONTRAST);    //(10) SET VBIAS POTENTIOMETER    0X00~0Xff

    uc1698_Write_Command(0x84);    //(11) SET PARTIAL DISPLAY CONTROL   0x84:Disable   0x85:Enable

    uc1698_Write_Command(0x89);    //(12) SET RAM ADDRESS CONTROL ����CA��RA�ķ���
    uc1698_Write_Command(0xeb);    //(26) SET LCD BIAS RATIO   1/12BIAS

    uc1698_Write_Command(0xf8);    //(34) SET WINDOW PROGRAM MODE

    uc1698_Write_Command(0xf4);    //(30) SET WINDOW PROGRAM STARTING COLUMN ADDRESS
    uc1698_Write_Command(0);       //starting column address 0
    uc1698_Write_Command(0xf5);    //(31) SET WINDOW PROGRAM STARTING ROW ADDRESS
    uc1698_Write_Command(32);      //starting row address
    uc1698_Write_Command(0xf6);    //(32) SET WINDOW PROGRAM ENDING COLUMN ADDRESS
    uc1698_Write_Command(79);      //ending column address  240
    uc1698_Write_Command(0xf7);    //(33) SET WINDOW PROGRAM ENDING ROW ADDRESS
    uc1698_Write_Command(159);     //ending row address  160

    uc1698_Write_Command(0xd5);    //(21) SET COLOR MODE ���ݸ�ʽΪ RRRR-GGGG-BBBB   RRRR-GGGG-BBBB
    uc1698_Write_Command(0xd1);    //(20) SET COLOR PATTERN

    uc1698_Write_Command(0xa4);    //(15) SET ALL PIXEL ON  0xa5:all pixel on  0xa4:normal display
    uc1698_Write_Command(0x26);    //(5) SET TEMPERATURE COMPENSATION

    uc1698_Write_Command(0x2b);    //(6) SET POWER CONTROL

    uc1698_Write_Command(0xc4);    //(18) SET LCD MAPPING CONTROL   MX=1,MY=1
    uc1698_Write_Command(0xa3);    //(14) SET LINE RATE

    uc1698_Write_Command(0xad);    //(17) SET DISPLAY ENABLE

    DelayMs(40);
    uc1698_Lattice(0, 0, 0, 0, 0, 0);       /* ���� */
    DelayMs(40);

    /* ������ʾӢ�ļӺ��� */
    while (1)
    {
        for (uint8_t y = 0; y < 128; y = y + 16)
        {
            uc1698_show_string(0, y, hanzi);
            for (uint8_t i = 0; i < 30; i = i + 2)
            {
                hanzi[i + 1] = hanzi[i + 1] + 15;
                if (hanzi[i + 1] < 0xa1)
                {
                    hanzi[i]++;
                    if (hanzi[i] > 0xf7)
                    {
                        hanzi[i] = 0xa1;
                    }
                    hanzi[i + 1] = hanzi[i + 1] + 0xa1;
                }
                else
                {
                    //hanzi[i]++;
                }
            }
        }
    }
}

void uc1698_show_string(uint8_t x, uint8_t y, uint8_t *src)
{
    uint16_t x_len;
    uint8_t uc1698u_str_buffer[128];        /* 240���㣬120�ֽ� */
    uint8_t x_count, y_count;
    uint8_t str_len = strlen(src), str_count;          /* ��ʾ�ַ������� */
    const unsigned char *pic;

    for (y_count = 0; y_count < 16; y_count++)
    {
        x_len = 0;
        /* ��16����ʾ16�� */
        for (str_count = 0; str_count < str_len; str_count++)
        {
            /* �ֲ��ַ�������ȡ��ģ����ָ�� */
            if (src[str_count] > 0xa0) /* gb2312��һ�������0xa1��ʼ */
            {
                /* gb2312�ַ� */
                pic = gb2312_font + ((src[str_count] - 0xa1) * 94 + (src[str_count + 1] - 0xa1)) * 32;
                if (src[str_count] >= 0xb0)
                {
                    pic = pic - (6 * 94 * 32);  /* ����ƫ�� */
                }

                /* ��ȡ����ģ����, x����λ16 */
                x_count = 16;
                /* gb2312Ϊ�����ֽ� */
                str_count++;
            }
            else if ((src[str_count] >= 0x20) && (src[str_count] < 0x80))
            {
                /* ascii�ַ��� x����λ8 */
                pic = ascii_font + (src[str_count] - 0x20) * 16;
                x_count = 8;
            }
            else
            {
                x_count = 0;
                continue;
            }

            for (uint8_t i = 0; i < x_count; i++)
            {
                if (pic[i * 2 + (uint8_t)(y_count / 8)] & (0x01 << (y_count % 8)))
                {
                    /* ���ص�Ϊ�棬��Ҫ���� */
                    if (x_len & 1)
                    {
                        /* ��8λ */
                        uc1698u_str_buffer[x_len / 2] |= 0x0f;
                    }
                    else
                    {
                        /* ��8λ */
                        uc1698u_str_buffer[x_len / 2] = 0xf0;
                    }
                }
                else
                {
                    /* ���ص�Ϊ�٣���� */
                    if (x_len & 1)
                    {
                        /* ��8λ */
                        uc1698u_str_buffer[x_len / 2] &= 0xf0;
                    }
                    else
                    {
                        /* ��8λ */
                        uc1698u_str_buffer[x_len / 2] = 0x00;
                    }
                }
                x_len++;

            }
        }

        x_len = (x_len + 1) & 0xfe; /* ��ַ���� */
        x_len = x_len / 2;

        /* �е�ַ�Զ���1 */

        uc1698_Write_Command((((y + y_count) & 0x0f) | 0x60));
        uc1698_Write_Command((((y + y_count) >> 4) | 0x70)); //������ʾ������ʼ��ַ
        uc1698_Write_Command((x & 0x0f));
        uc1698_Write_Command(((x >> 4) | 0x10)); //������ʾ������ʼ��ַ

        for (x_count = 0; x_count < x_len; x_count++)
        {
            uc1698_Write_Data(uc1698u_str_buffer[x_count]);
        }
        x_len = x_len * 2;
        if (x_len % 3)
        {
            uc1698_Write_Data(0x00);
        }

    }
}

/*****  դ�����ʾ���� ******/
void uc1698_Lattice(u8 Data1, u8 Data2, u8 Data3, u8 Data4, u8 Data5, u8 Data6)
{
    u8 i, j;

    uc1698_Write_Command(0x60);
    uc1698_Write_Command(0x70);    //������ʾ������ʼ��ַ      0
    uc1698_Write_Command(0x00);
    uc1698_Write_Command(0x10);    //������ʾ������ʼ��ַ    0

    for (i = 0; i < 128; i++)
    {
        if (i % 2)
            for (j = 0; j < 40; j++)
            {
                uc1698_Write_Data(Data1);
                uc1698_Write_Data(Data2);
                uc1698_Write_Data(Data3);
            }
        else
            for (j = 0; j < 40; j++)
            {
                uc1698_Write_Data(Data4);
                uc1698_Write_Data(Data5);
                uc1698_Write_Data(Data6);
            }
    }
}

/*****  դ�����ʾ���� ******/
void uc1698_show_qrcode(uint8_t x, uint8_t y, int side, uint8_t *src)
{
    uint8_t uc1698u_str_buffer[128];        /* 240���㣬120�ֽ� */
    u8 i, j, k;
    int a;

    for (i = 0; i < side; i++)
    {

        for (j = 0; j < side; j++)
        {
            a = j * side + i;
            if (src[a / 8] & (1 << (7 - a % 8)))
            {
                /* ���ص�Ϊ�棬��Ҫ���� */
                if (j & 1)
                {
                    /* ��8λ */
                    uc1698u_str_buffer[j / 2] |= 0x0f;
                }
                else
                {
                    /* ��8λ */
                    uc1698u_str_buffer[j / 2] = 0xf0;
                }
            }
            else
            {
                /* ���ص�Ϊ�٣���� */
                if (j & 1)
                {
                    /* ��8λ */
                    uc1698u_str_buffer[j / 2] &= 0xf0;
                }
                else
                {
                    /* ��8λ */
                    uc1698u_str_buffer[j / 2] = 0x00;
                }
            }
        }

        j = (j + 1) & 0xfe; /* ��ַ���� */
        j = j / 2;

        uc1698_Write_Command((((y + i) & 0x0f) | 0x60));
        uc1698_Write_Command((((y + i) >> 4) | 0x70)); //������ʾ������ʼ��ַ
        uc1698_Write_Command((x & 0x0f));
        uc1698_Write_Command(((x >> 4) | 0x10)); //������ʾ������ʼ��ַ

        for (k = 0; k < j; k++)
        {
            uc1698_Write_Data(uc1698u_str_buffer[k]);
        }

        j = j * 2;
        if (j % 3)
        {
            uc1698_Write_Data(0x00);
        }
    }
}
