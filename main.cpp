#include <iostream>
#include<stdio.h>
#include <random>
#include <time.h>
#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>

using namespace std;
class AES
{
    int Rcon[10] =
    {
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
    };

    static int whichRcon;
    public:
    void rewritting(int tableOfState[4][4], int table[4][4])
    {
        for(int i = 0; i < 4; ++i)
            for(int j =0; j < 4; ++j)
                tableOfState[j][i] = table[j][i];
    }

    void showTable(int table[4][4])
    {
        cout<<endl;
        for(int i=0; i<4; ++i)
        {
            for(int j =0; j<4; ++j)
            {
                cout<<hex<< table[j][i]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void shiftRows(int tableOfState[4][4])
    {
        int pom0 = tableOfState[0][1];
        int pom1 = tableOfState[1][1];
        int pom2 = tableOfState[2][1];
        int pom3 = tableOfState[3][1];
        tableOfState[0][1] = pom1;
        tableOfState[1][1] = pom2;
        tableOfState[2][1] = pom3;
        tableOfState[3][1] = pom0;
        //1 row swift by 1
        pom0 = tableOfState[0][2];
        pom1 = tableOfState[1][2];
        pom2 = tableOfState[2][2];
        pom3 = tableOfState[3][2];
        tableOfState[0][2] = pom2;
        tableOfState[1][2] = pom3;
        tableOfState[2][2] = pom0;
        tableOfState[3][2] = pom1;
        //2 row swift by 2
        pom0 = tableOfState[0][3];
        pom1 = tableOfState[1][3];
        pom2 = tableOfState[2][3];
        pom3 = tableOfState[3][3];
        tableOfState[0][3] = pom3;
        tableOfState[1][3] = pom0;
        tableOfState[2][3] = pom1;
        tableOfState[3][3] = pom2;
        //3 row  swift by 3
    }

    int getSBoxValue(const int &number)
    {
        int sbox[256] =
        {
            //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
            0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  //F
        };
        return sbox[number];
    }
    void firstRow(int tableOfState[4][4], int wynik[4][4], const int& i)
    {
        tableOfState[i][0]<<=1;
        if(tableOfState[i][0]>255)
        {
            tableOfState[i][0] -= 256;
            tableOfState[i][0]^=27;
        }
        int prev = tableOfState[i][1];
        tableOfState[i][1]<<=1;
        if(tableOfState[i][1]>255)
        {
            tableOfState[i][1] -= 256;
            tableOfState[i][1]^=27;
        }
        tableOfState[i][1]^=prev;
        wynik[i][0] = tableOfState[i][0]^tableOfState[i][1]^tableOfState[i][2]^tableOfState[i][3];
    }

    void secondRow(int tableOfState[4][4], int wynik[4][4], const int& i)
    {
        tableOfState[i][1]<<=1;
        if(tableOfState[i][1]>255)
        {
            tableOfState[i][1] -= 256;
            tableOfState[i][1]^=27;
        }
        int prev = tableOfState[i][2];
        tableOfState[i][2]<<=1;
        if(tableOfState[i][2]>255)
        {
            tableOfState[i][2] -= 256;
            tableOfState[i][2]^=27;
        }
        tableOfState[i][2]^=prev;
        wynik[i][1] = tableOfState[i][0]^tableOfState[i][1]^tableOfState[i][2]^tableOfState[i][3];
    }
    void thirdRow(int tableOfState[4][4], int wynik[4][4], const int& i)
    {
        tableOfState[i][2]<<=1;
        if(tableOfState[i][2]>255)
        {
            tableOfState[i][2] -= 256;
            tableOfState[i][2]^=27;
        }
        int prev = tableOfState[i][3];
        tableOfState[i][3]<<=1;
        if(tableOfState[i][3]>255)
        {
            tableOfState[i][3] -= 256;
            tableOfState[i][3]^=27;
        }
        tableOfState[i][3]^=prev;
        wynik[i][2] = tableOfState[i][0]^tableOfState[i][1]^tableOfState[i][2]^tableOfState[i][3];
    }
    void fourthRow(int tableOfState[4][4], int wynik[4][4], const int& i)
    {
        tableOfState[i][3]<<=1;
        if(tableOfState[i][3]>255)
        {
            tableOfState[i][3] -= 256;
            tableOfState[i][3]^=27;
        }
        int prev = tableOfState[i][0];
        tableOfState[i][0]<<=1;
        if(tableOfState[i][0]>255)
        {

            tableOfState[i][0] -= 256;
            tableOfState[i][0]^=27;
        }
        tableOfState[i][0]^=prev;
        wynik[i][3] = tableOfState[i][0]^tableOfState[i][1]^tableOfState[i][2]^tableOfState[i][3];
    }
    void mixColumns(int tableOfState[4][4])
    {
        int wynik[4][4];
        int tablica[4][4];
        int tablica2[4][4];
        int tablica3[4][4];
        int tablica4[4][4];
        rewritting(tablica, tableOfState);
        rewritting(tablica2, tableOfState);
        rewritting(tablica3, tableOfState);
        rewritting(tablica4, tableOfState);
        for(int i=0; i<4; i++)
        {
            firstRow(tablica, wynik, i);                       // | 02 03 01 01 |
            secondRow(tablica2, wynik, i);                     // | 01 02 03 01 |
            thirdRow(tablica3, wynik, i);                      // | 01 01 02 03 |
            fourthRow(tablica4, wynik, i);                     // | 03 01 01 02 |
        }
        rewritting(tableOfState, wynik);
    }

    void addRoundKey(int tableOfState[4][4], int key[4][4])
    {
        for(int i=0; i<4; ++i)
            for(int j=0; j<4; ++j)
                tableOfState[j][i] ^= key[j][i];
    }
    void RotWord(int columnLast[4])
    {
        int pom1 = columnLast[0];
        columnLast[0] = columnLast[1];
        columnLast[1] = columnLast[2];
        columnLast[2]=columnLast[3];
        columnLast[3]=pom1;
    }

    void makeFirstColumn(int columnFirst[4], int columnLast[4], int Column[4])
    {
        RotWord(columnLast);
        for(int j =0; j<4; ++j)
        {
            columnLast[j] = getSBoxValue(columnLast[j]);
            if(j==0)
                Column[j] = columnFirst[j]^columnLast[j]^Rcon[whichRcon];
            else
                Column[j] = columnFirst[j]^columnLast[j];
        }
        whichRcon++;
    }

    void makeOtherColumn(int columnFirst[4], int columnLast[4], int Column[4])
    {
        for(int j =0; j<4; ++j)
            Column[j] = columnFirst[j]^columnLast[j];
    }

    void addColumnTonewKeyTable(int Column[4], int newKeyTable[4][4], const int& x)
    {
        for(int j=0; j<4; ++j)
        {
            for(int k=0; k<4; ++k)
            {
                if(k==x)
                    newKeyTable[k][j]=Column[j];
            }
        }
    }

    void makeVector(int ColumnFirst[4], int KeyTable[4][4], const int& x)
    {
        for(int j=0; j<4; ++j)
            for(int k=0; k<4; ++k)
            {
                if(k==x)
                    ColumnFirst[j]= KeyTable[k][j];
            }
    }

    void makeVector2(int ColumnLast[4], int KeyTable[4][4], const int& x)
    {
        for(int j=0; j<4; ++j)
            for(int k=0; k<4; ++k)
            {
                if(k==x)
                    ColumnLast[j]= KeyTable[k][j];
            }
    }

    void subBytes(int tableOfState[4][4])
    {
        for(int i=0; i<4; ++i)
            for(int j =0; j<4; ++j)
                tableOfState[j][i] = getSBoxValue(tableOfState[j][i]);
    }

    void keySchedule(int keyTable[4][4])
    {
        int newKeyTable[4][4];
        int Column[4];
        int columnLast[] = {keyTable[3][0],keyTable[3][1],keyTable[3][2],keyTable[3][3]};
        int columnFirst[] = {keyTable[0][0],keyTable[0][1],keyTable[0][2],keyTable[0][3]};
        for(int i = 0; i < 4; ++i)
        {
            if(i == 0)
            {
                makeFirstColumn(columnFirst, columnLast, Column);
                addColumnTonewKeyTable(Column, newKeyTable,i);
            }
            else
            {
                makeOtherColumn(columnFirst, columnLast, Column);
                addColumnTonewKeyTable(Column, newKeyTable,i);
            }
            if(i<3)
            {
                makeVector(columnFirst,keyTable,i + 1);
                makeVector2(columnLast,newKeyTable,i);
            }
        }
        rewritting(keyTable, newKeyTable);
    }

    void encrypt(int tableOfState[4][4], int key[4][4])
    {
        addRoundKey(tableOfState,key);
        keySchedule(key);
        for(int k =0 ; k<9; ++k)
        {
            subBytes(tableOfState);
            shiftRows(tableOfState);
            mixColumns(tableOfState);
            addRoundKey(tableOfState,key);
            keySchedule(key);
        }
        subBytes(tableOfState);
        shiftRows(tableOfState);
        addRoundKey(tableOfState,key);
    }

};

int AES:: whichRcon = 0;

inline int randNumber()
{
        return rand()%255;
}

int main()
{
    AES aes;
    int tableOfState[4][4];
    int key[4][4];
    srand(time(NULL));
        for(int i=0; i<4; ++i)
        {
            for(int j=0; j<4; ++j)
            {
                tableOfState[j][i] = randNumber();
                key[j][i] = randNumber();
            }
        }
    //test values
    //int tableOfState[4][4]= {{0x32,0x43,0xf6,0xa8},{0x88,0x5a,0x30,0x8d},{0x31,0x31,0x98,0xa2},{0xe0,0x37,0x07,0x34}};
    // int key[4][4]= {{0x2b,0x7e,0x15,0x16},{0x28,0xae,0xd2,0xa6},{0xab,0xf7,0x15,0x88},{0x9,0xcf,0x4f,0x3c}};
    aes.showTable(tableOfState);
    aes.showTable(key);
    aes.encrypt(tableOfState,key);
    aes.showTable(tableOfState);
    aes.showTable(key);

    return 0;
}
