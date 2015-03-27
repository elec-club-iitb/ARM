/*******************************************************************************************
  Font name: Tahoma
  Font width: varialbe (proportional font)
  Font height: 8
  Encode: Unicode

  Data length: 8 bits
  Data format: Little Endian, Column based, Row preferred, Unpacked

  Create time: 11:57 10-15-2009  by BitFontCreator Pro (e-mail: support@iseatech.com)
 *******************************************************************************************/

/*******************************************************************************************
  Data table provides the bitmap data of each character.

  To get the starting data offset of character 'A', you can use the following expression:

     const unsigned char index = index_table['A'];
     const unsigned int offset = offset_table[index];
     const unsigned char *pData = data_table[offset];

 *******************************************************************************************/
const unsigned char data_table[] = {

/* character 0x0020 (' '): (width=3, offset=0) */
0x00, 0x00, 0x00, 

/* character 0x0021 ('!'): (width=3, offset=3) */
0xBE, 0xBE, 0x00, 

/* character 0x0022 ('"'): (width=4, offset=6) */
0x07, 0x00, 0x07, 0x00, 

/* character 0x0023 ('#'): (width=7, offset=10) */
0x28, 0xFE, 0x28, 0x28, 0xFE, 0x28, 0x00, 

/* character 0x0024 ('$'): (width=7, offset=17) */
0x4C, 0x9E, 0xF2, 0x9F, 0xF2, 0x64, 0x00, 

/* character 0x0025 ('%'): (width=12, offset=24) */
0x0C, 0x1E, 0x12, 0x5E, 0x2C, 0x10, 0x68, 0xF4, 
0x90, 0xF0, 0x60, 0x00, 

/* character 0x0026 ('&'): (width=8, offset=36) */
0x6C, 0xFE, 0x92, 0xBE, 0x6C, 0xE0, 0x98, 0x00, 

/* character 0x0027 ('''): (width=2, offset=44) */
0x07, 0x00, 

/* character 0x0028 ('('): (width=5, offset=46) */
0xFC, 0xFE, 0x03, 0x01, 0x00, 

/* character 0x0029 (')'): (width=5, offset=51) */
0x01, 0x03, 0xFE, 0xFC, 0x00, 

/* character 0x002A ('*'): (width=6, offset=56) */
0x05, 0x02, 0x0F, 0x02, 0x05, 0x00, 

/* character 0x002B ('+'): (width=7, offset=62) */
0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, 

/* character 0x002C (','): (width=3, offset=69) */
0xC0, 0x00, 0x00, 

/* character 0x002D ('-'): (width=4, offset=72) */
0x10, 0x10, 0x10, 0x00, 

/* character 0x002E ('.'): (width=3, offset=76) */
0xC0, 0xC0, 0x00, 

/* character 0x002F ('/'): (width=5, offset=79) */
0x80, 0x60, 0x1C, 0x03, 0x00, 

/* character 0x0030 ('0'): (width=7, offset=84) */
0x7C, 0xFE, 0x82, 0x82, 0xFE, 0x7C, 0x00, 

/* character 0x0031 ('1'): (width=7, offset=91) */
0x00, 0x84, 0xFE, 0xFE, 0x80, 0x00, 0x00, 

/* character 0x0032 ('2'): (width=7, offset=98) */
0x8C, 0xC2, 0xE2, 0xB2, 0x9E, 0x8C, 0x00, 

/* character 0x0033 ('3'): (width=7, offset=105) */
0x44, 0x82, 0x92, 0x92, 0xFE, 0x6C, 0x00, 

/* character 0x0034 ('4'): (width=7, offset=112) */
0x30, 0x28, 0x24, 0xFE, 0xFE, 0x20, 0x00, 

/* character 0x0035 ('5'): (width=7, offset=119) */
0x4E, 0x8E, 0x8A, 0x8A, 0xFA, 0x72, 0x00, 

/* character 0x0036 ('6'): (width=7, offset=126) */
0x7C, 0xFE, 0x92, 0x92, 0xF2, 0x60, 0x00, 

/* character 0x0037 ('7'): (width=7, offset=133) */
0x02, 0x02, 0xE2, 0xFA, 0x1E, 0x06, 0x00, 

/* character 0x0038 ('8'): (width=7, offset=140) */
0x6C, 0xFE, 0x92, 0x92, 0xFE, 0x6C, 0x00, 

/* character 0x0039 ('9'): (width=7, offset=147) */
0x0C, 0x9E, 0x92, 0xD2, 0x7E, 0x3C, 0x00, 

/* character 0x003A (':'): (width=3, offset=154) */
0xD8, 0xD8, 0x00, 

/* character 0x003B (';'): (width=3, offset=157) */
0xD8, 0x18, 0x00, 

/* character 0x003C ('<'): (width=7, offset=160) */
0x30, 0x30, 0x48, 0x48, 0x84, 0x84, 0x00, 

/* character 0x003D ('='): (width=7, offset=167) */
0x00, 0x28, 0x28, 0x28, 0x28, 0x28, 0x00, 

/* character 0x003E ('>'): (width=7, offset=174) */
0x84, 0x84, 0x48, 0x48, 0x30, 0x30, 0x00, 

/* character 0x003F ('?'): (width=6, offset=181) */
0x04, 0xA2, 0xB2, 0x1E, 0x0C, 0x00, 

/* character 0x0040 ('@'): (width=10, offset=187) */
0x78, 0x84, 0x32, 0x7A, 0x4A, 0x3A, 0x7A, 0x44, 
0x38, 0x00, 

/* character 0x0041 ('A'): (width=8, offset=197) */
0x00, 0xE0, 0xF8, 0x3E, 0x26, 0x3E, 0xF8, 0xE0, 

/* character 0x0042 ('B'): (width=7, offset=205) */
0xFE, 0xFE, 0x92, 0x92, 0xFE, 0x6C, 0x00, 

/* character 0x0043 ('C'): (width=7, offset=212) */
0x7C, 0xFE, 0x82, 0x82, 0x82, 0x44, 0x00, 

/* character 0x0044 ('D'): (width=7, offset=219) */
0xFE, 0xFE, 0x82, 0x82, 0xFE, 0x7C, 0x00, 

/* character 0x0045 ('E'): (width=6, offset=226) */
0xFE, 0xFE, 0x92, 0x92, 0x82, 0x00, 

/* character 0x0046 ('F'): (width=6, offset=232) */
0xFE, 0xFE, 0x12, 0x12, 0x02, 0x00, 

/* character 0x0047 ('G'): (width=7, offset=238) */
0x7C, 0xFE, 0x82, 0x92, 0xF2, 0xF4, 0x00, 

/* character 0x0048 ('H'): (width=8, offset=245) */
0xFE, 0xFE, 0x10, 0x10, 0x10, 0xFE, 0xFE, 0x00, 

/* character 0x0049 ('I'): (width=5, offset=253) */
0x82, 0xFE, 0xFE, 0x82, 0x00, 

/* character 0x004A ('J'): (width=5, offset=258) */
0x80, 0x82, 0xFE, 0x7E, 0x00, 

/* character 0x004B ('K'): (width=7, offset=263) */
0xFE, 0xFE, 0x38, 0x6C, 0xC6, 0x82, 0x00, 

/* character 0x004C ('L'): (width=6, offset=270) */
0xFE, 0xFE, 0x80, 0x80, 0x80, 0x00, 

/* character 0x004D ('M'): (width=9, offset=276) */
0xFE, 0x0E, 0x1C, 0x38, 0x18, 0x0C, 0xFE, 0xFE, 
0x00, 

/* character 0x004E ('N'): (width=7, offset=285) */
0xFE, 0x0E, 0x1C, 0x38, 0x70, 0xFE, 0x00, 

/* character 0x004F ('O'): (width=8, offset=292) */
0x7C, 0xFE, 0x82, 0x82, 0x82, 0xFE, 0x7C, 0x00, 

/* character 0x0050 ('P'): (width=7, offset=300) */
0xFE, 0xFE, 0x22, 0x22, 0x3E, 0x1C, 0x00, 

/* character 0x0051 ('Q'): (width=8, offset=307) */
0x7C, 0xFE, 0x82, 0x82, 0x82, 0xFE, 0x7C, 0x00, 

/* character 0x0052 ('R'): (width=7, offset=315) */
0xFE, 0xFE, 0x32, 0x72, 0xDE, 0x8C, 0x00, 

/* character 0x0053 ('S'): (width=6, offset=322) */
0x4C, 0x9E, 0xBA, 0xF2, 0x64, 0x00, 

/* character 0x0054 ('T'): (width=7, offset=328) */
0x02, 0x02, 0xFE, 0xFE, 0x02, 0x02, 0x00, 

/* character 0x0055 ('U'): (width=7, offset=335) */
0x7E, 0xFE, 0x80, 0x80, 0xFE, 0x7E, 0x00, 

/* character 0x0056 ('V'): (width=7, offset=342) */
0x0E, 0x3E, 0xF0, 0xF0, 0x3E, 0x0E, 0x00, 

/* character 0x0057 ('W'): (width=9, offset=349) */
0x00, 0x3E, 0xFE, 0xC0, 0x3E, 0x3E, 0xC0, 0xFE, 
0x3E, 

/* character 0x0058 ('X'): (width=7, offset=358) */
0x00, 0xC6, 0xEE, 0x38, 0x38, 0xEE, 0xC6, 

/* character 0x0059 ('Y'): (width=7, offset=365) */
0x00, 0x06, 0x1E, 0xF8, 0xF8, 0x1E, 0x06, 

/* character 0x005A ('Z'): (width=6, offset=372) */
0xE2, 0xF2, 0xBA, 0x9E, 0x8E, 0x00, 

/* character 0x005B ('['): (width=5, offset=378) */
0xFF, 0xFF, 0x01, 0x01, 0x00, 

/* character 0x005C ('\'): (width=5, offset=383) */
0x03, 0x0C, 0x70, 0x80, 0x00, 

/* character 0x005D (']'): (width=5, offset=388) */
0x01, 0x01, 0xFF, 0xFF, 0x00, 

/* character 0x005E ('^'): (width=7, offset=393) */
0x08, 0x04, 0x02, 0x02, 0x04, 0x08, 0x00, 

/* character 0x005F ('_'): (width=6, offset=400) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

/* character 0x0060 ('`'): (width=5, offset=406) */
0x00, 0x01, 0x02, 0x00, 0x00, 

/* character 0x0061 ('a'): (width=6, offset=411) */
0x40, 0xE8, 0xA8, 0xF8, 0xF0, 0x00, 

/* character 0x0062 ('b'): (width=6, offset=417) */
0xFF, 0xFF, 0x88, 0xF8, 0x70, 0x00, 

/* character 0x0063 ('c'): (width=5, offset=423) */
0x70, 0xF8, 0x88, 0x88, 0x00, 

/* character 0x0064 ('d'): (width=6, offset=428) */
0x70, 0xF8, 0x88, 0xFF, 0xFF, 0x00, 

/* character 0x0065 ('e'): (width=6, offset=434) */
0x70, 0xF8, 0xA8, 0xB8, 0xB0, 0x00, 

/* character 0x0066 ('f'): (width=4, offset=440) */
0xFE, 0xFF, 0x09, 0x01, 

/* character 0x0067 ('g'): (width=6, offset=444) */
0x70, 0xF8, 0x88, 0xF8, 0xF8, 0x00, 

/* character 0x0068 ('h'): (width=6, offset=450) */
0xFF, 0xFF, 0x08, 0xF8, 0xF0, 0x00, 

/* character 0x0069 ('i'): (width=3, offset=456) */
0xFA, 0xFA, 0x00, 

/* character 0x006A ('j'): (width=4, offset=459) */
0x08, 0xFA, 0xFA, 0x00, 

/* character 0x006B ('k'): (width=6, offset=463) */
0xFF, 0xFF, 0x70, 0xD8, 0x88, 0x00, 

/* character 0x006C ('l'): (width=3, offset=469) */
0xFF, 0xFF, 0x00, 

/* character 0x006D ('m'): (width=9, offset=472) */
0xF8, 0xF8, 0x08, 0xF8, 0xF0, 0x08, 0xF8, 0xF0, 
0x00, 

/* character 0x006E ('n'): (width=6, offset=481) */
0xF8, 0xF8, 0x08, 0xF8, 0xF0, 0x00, 

/* character 0x006F ('o'): (width=6, offset=487) */
0x70, 0xF8, 0x88, 0xF8, 0x70, 0x00, 

/* character 0x0070 ('p'): (width=6, offset=493) */
0xF8, 0xF8, 0x88, 0xF8, 0x70, 0x00, 

/* character 0x0071 ('q'): (width=6, offset=499) */
0x70, 0xF8, 0x88, 0xF8, 0xF8, 0x00, 

/* character 0x0072 ('r'): (width=5, offset=505) */
0xF8, 0xF8, 0x10, 0x18, 0x00, 

/* character 0x0073 ('s'): (width=5, offset=510) */
0x90, 0xB8, 0xE8, 0x48, 0x00, 

/* character 0x0074 ('t'): (width=4, offset=515) */
0x7C, 0xFC, 0x88, 0x00, 

/* character 0x0075 ('u'): (width=6, offset=519) */
0x78, 0xF8, 0x80, 0xF8, 0xF8, 0x00, 

/* character 0x0076 ('v'): (width=6, offset=525) */
0x00, 0x18, 0x78, 0xE0, 0x78, 0x18, 

/* character 0x0077 ('w'): (width=8, offset=531) */
0x38, 0xF8, 0xC0, 0x30, 0xC0, 0xF8, 0x38, 0x00, 

/* character 0x0078 ('x'): (width=6, offset=539) */
0x00, 0xD8, 0xF8, 0x20, 0xF8, 0xD8, 

/* character 0x0079 ('y'): (width=6, offset=545) */
0x00, 0x38, 0x78, 0xC0, 0xF8, 0x38, 

/* character 0x007A ('z'): (width=5, offset=551) */
0xC8, 0xE8, 0xB8, 0x98, 0x00, 

/* character 0x007B ('{'): (width=7, offset=556) */
0x10, 0x10, 0xFE, 0xEF, 0x01, 0x01, 0x00, 

/* character 0x007C ('|'): (width=5, offset=563) */
0x00, 0xFF, 0xFF, 0x00, 0x00, 

/* character 0x007D ('}'): (width=7, offset=568) */
0x01, 0x01, 0xEF, 0xFE, 0x10, 0x10, 0x00, 

/* character 0x007E ('~'): (width=7, offset=575) */
0x60, 0x10, 0x30, 0x60, 0x40, 0x30, 0x00, 

/* character 0x007F (''): (width=6, offset=582) */
0xFC, 0xFC, 0x84, 0xFC, 0xFC, 0x00, 

};

/*******************************************************************************************
  Offset table provides the starting offset of each character in the data table.

  To get the starting offset of character 'A', you can use the following expression:

     const unsigned char index = index_table['A'];
     const unsigned int offset = offset_table[index]

 *******************************************************************************************/
const unsigned int offset_table[] = {
/*		offset    char    hexcode */
/*		======    ====    ======= */
  		     0, /*          0020    */
  		     3, /*   !      0021    */
  		     6, /*   "      0022    */
  		    10, /*   #      0023    */
  		    17, /*   $      0024    */
  		    24, /*   %      0025    */
  		    36, /*   &      0026    */
  		    44, /*   '      0027    */
  		    46, /*   (      0028    */
  		    51, /*   )      0029    */
  		    56, /*   *      002A    */
  		    62, /*   +      002B    */
  		    69, /*   ,      002C    */
  		    72, /*   -      002D    */
  		    76, /*   .      002E    */
  		    79, /*   /      002F    */
  		    84, /*   0      0030    */
  		    91, /*   1      0031    */
  		    98, /*   2      0032    */
  		   105, /*   3      0033    */
  		   112, /*   4      0034    */
  		   119, /*   5      0035    */
  		   126, /*   6      0036    */
  		   133, /*   7      0037    */
  		   140, /*   8      0038    */
  		   147, /*   9      0039    */
  		   154, /*   :      003A    */
  		   157, /*   ;      003B    */
  		   160, /*   <      003C    */
  		   167, /*   =      003D    */
  		   174, /*   >      003E    */
  		   181, /*   ?      003F    */
  		   187, /*   @      0040    */
  		   197, /*   A      0041    */
  		   205, /*   B      0042    */
  		   212, /*   C      0043    */
  		   219, /*   D      0044    */
  		   226, /*   E      0045    */
  		   232, /*   F      0046    */
  		   238, /*   G      0047    */
  		   245, /*   H      0048    */
  		   253, /*   I      0049    */
  		   258, /*   J      004A    */
  		   263, /*   K      004B    */
  		   270, /*   L      004C    */
  		   276, /*   M      004D    */
  		   285, /*   N      004E    */
  		   292, /*   O      004F    */
  		   300, /*   P      0050    */
  		   307, /*   Q      0051    */
  		   315, /*   R      0052    */
  		   322, /*   S      0053    */
  		   328, /*   T      0054    */
  		   335, /*   U      0055    */
  		   342, /*   V      0056    */
  		   349, /*   W      0057    */
  		   358, /*   X      0058    */
  		   365, /*   Y      0059    */
  		   372, /*   Z      005A    */
  		   378, /*   [      005B    */
  		   383, /*   \      005C    */
  		   388, /*   ]      005D    */
  		   393, /*   ^      005E    */
  		   400, /*   _      005F    */
  		   406, /*   `      0060    */
  		   411, /*   a      0061    */
  		   417, /*   b      0062    */
  		   423, /*   c      0063    */
  		   428, /*   d      0064    */
  		   434, /*   e      0065    */
  		   440, /*   f      0066    */
  		   444, /*   g      0067    */
  		   450, /*   h      0068    */
  		   456, /*   i      0069    */
  		   459, /*   j      006A    */
  		   463, /*   k      006B    */
  		   469, /*   l      006C    */
  		   472, /*   m      006D    */
  		   481, /*   n      006E    */
  		   487, /*   o      006F    */
  		   493, /*   p      0070    */
  		   499, /*   q      0071    */
  		   505, /*   r      0072    */
  		   510, /*   s      0073    */
  		   515, /*   t      0074    */
  		   519, /*   u      0075    */
  		   525, /*   v      0076    */
  		   531, /*   w      0077    */
  		   539, /*   x      0078    */
  		   545, /*   y      0079    */
  		   551, /*   z      007A    */
  		   556, /*   {      007B    */
  		   563, /*   |      007C    */
  		   568, /*   }      007D    */
  		   575, /*   ~      007E    */
  		   582, /*         007F    */
};

/*******************************************************************************************
  Index table is used to find the mapping index of a character.

  If you can find a simple mathematical expression for index mapping, you can use that.
  If you do not have such a mathematical expression, this index table is just for you.

  To get the index of character 'A', you can use the following expression:

     const unsigned char index = index_table['A'];

 *******************************************************************************************/
const unsigned char index_table[] = {
/*		index   hexcode   decimal  char */
/*		=====   =======   =======  ==== */
  		  0, /*   00          0     .   */
  		  0, /*   01          1     .   */
  		  0, /*   02          2     .   */
  		  0, /*   03          3     .   */
  		  0, /*   04          4     .   */
  		  0, /*   05          5     .   */
  		  0, /*   06          6     .   */
  		  0, /*   07          7     .   */
  		  0, /*   08          8     .   */
  		  0, /*   09          9     .   */
  		  0, /*   0A         10     .   */
  		  0, /*   0B         11     .   */
  		  0, /*   0C         12     .   */
  		  0, /*   0D         13     .   */
  		  0, /*   0E         14     .   */
  		  0, /*   0F         15     .   */
  		  0, /*   10         16     .   */
  		  0, /*   11         17     .   */
  		  0, /*   12         18     .   */
  		  0, /*   13         19     .   */
  		  0, /*   14         20     .   */
  		  0, /*   15         21     .   */
  		  0, /*   16         22     .   */
  		  0, /*   17         23     .   */
  		  0, /*   18         24     .   */
  		  0, /*   19         25     .   */
  		  0, /*   1A         26     .   */
  		  0, /*   1B         27     .   */
  		  0, /*   1C         28     .   */
  		  0, /*   1D         29     .   */
  		  0, /*   1E         30     .   */
  		  0, /*   1F         31     .   */
  		  0, /*   20         32         */
  		  1, /*   21         33     !   */
  		  2, /*   22         34     "   */
  		  3, /*   23         35     #   */
  		  4, /*   24         36     $   */
  		  5, /*   25         37     %   */
  		  6, /*   26         38     &   */
  		  7, /*   27         39     '   */
  		  8, /*   28         40     (   */
  		  9, /*   29         41     )   */
  		 10, /*   2A         42     *   */
  		 11, /*   2B         43     +   */
  		 12, /*   2C         44     ,   */
  		 13, /*   2D         45     -   */
  		 14, /*   2E         46     .   */
  		 15, /*   2F         47     /   */
  		 16, /*   30         48     0   */
  		 17, /*   31         49     1   */
  		 18, /*   32         50     2   */
  		 19, /*   33         51     3   */
  		 20, /*   34         52     4   */
  		 21, /*   35         53     5   */
  		 22, /*   36         54     6   */
  		 23, /*   37         55     7   */
  		 24, /*   38         56     8   */
  		 25, /*   39         57     9   */
  		 26, /*   3A         58     :   */
  		 27, /*   3B         59     ;   */
  		 28, /*   3C         60     <   */
  		 29, /*   3D         61     =   */
  		 30, /*   3E         62     >   */
  		 31, /*   3F         63     ?   */
  		 32, /*   40         64     @   */
  		 33, /*   41         65     A   */
  		 34, /*   42         66     B   */
  		 35, /*   43         67     C   */
  		 36, /*   44         68     D   */
  		 37, /*   45         69     E   */
  		 38, /*   46         70     F   */
  		 39, /*   47         71     G   */
  		 40, /*   48         72     H   */
  		 41, /*   49         73     I   */
  		 42, /*   4A         74     J   */
  		 43, /*   4B         75     K   */
  		 44, /*   4C         76     L   */
  		 45, /*   4D         77     M   */
  		 46, /*   4E         78     N   */
  		 47, /*   4F         79     O   */
  		 48, /*   50         80     P   */
  		 49, /*   51         81     Q   */
  		 50, /*   52         82     R   */
  		 51, /*   53         83     S   */
  		 52, /*   54         84     T   */
  		 53, /*   55         85     U   */
  		 54, /*   56         86     V   */
  		 55, /*   57         87     W   */
  		 56, /*   58         88     X   */
  		 57, /*   59         89     Y   */
  		 58, /*   5A         90     Z   */
  		 59, /*   5B         91     [   */
  		 60, /*   5C         92     \   */
  		 61, /*   5D         93     ]   */
  		 62, /*   5E         94     ^   */
  		 63, /*   5F         95     _   */
  		 64, /*   60         96     `   */
  		 65, /*   61         97     a   */
  		 66, /*   62         98     b   */
  		 67, /*   63         99     c   */
  		 68, /*   64        100     d   */
  		 69, /*   65        101     e   */
  		 70, /*   66        102     f   */
  		 71, /*   67        103     g   */
  		 72, /*   68        104     h   */
  		 73, /*   69        105     i   */
  		 74, /*   6A        106     j   */
  		 75, /*   6B        107     k   */
  		 76, /*   6C        108     l   */
  		 77, /*   6D        109     m   */
  		 78, /*   6E        110     n   */
  		 79, /*   6F        111     o   */
  		 80, /*   70        112     p   */
  		 81, /*   71        113     q   */
  		 82, /*   72        114     r   */
  		 83, /*   73        115     s   */
  		 84, /*   74        116     t   */
  		 85, /*   75        117     u   */
  		 86, /*   76        118     v   */
  		 87, /*   77        119     w   */
  		 88, /*   78        120     x   */
  		 89, /*   79        121     y   */
  		 90, /*   7A        122     z   */
  		 91, /*   7B        123     {   */
  		 92, /*   7C        124     |   */
  		 93, /*   7D        125     }   */
  		 94, /*   7E        126     ~   */
  		 95, /*   7F        127        */
  		  0, /*   80        128   ? */
  		  0, /*   81        129   Å */
  		  0, /*   82        130   ? */
  		  0, /*   83        131   ? */
  		  0, /*   84        132   ? */
  		  0, /*   85        133   ? */
  		  0, /*   86        134   ? */
  		  0, /*   87        135   ? */
  		  0, /*   88        136   ? */
  		  0, /*   89        137   ? */
  		  0, /*   8A        138   ? */
  		  0, /*   8B        139   ? */
  		  0, /*   8C        140   ? */
  		  0, /*   8D        141   ç */
  		  0, /*   8E        142   ? */
  		  0, /*   8F        143   è */
  		  0, /*   90        144   ê */
  		  0, /*   91        145   ? */
  		  0, /*   92        146   ? */
  		  0, /*   93        147   ? */
  		  0, /*   94        148   ? */
  		  0, /*   95        149   ? */
  		  0, /*   96        150   ? */
  		  0, /*   97        151   ? */
  		  0, /*   98        152   ? */
  		  0, /*   99        153   ? */
  		  0, /*   9A        154   ? */
  		  0, /*   9B        155   ? */
  		  0, /*   9C        156   ? */
  		  0, /*   9D        157   ù */
  		  0, /*   9E        158   ? */
  		  0, /*   9F        159   ? */
  		  0, /*   A0        160   † */
  		  0, /*   A1        161   ° */
  		  0, /*   A2        162   ¢ */
  		  0, /*   A3        163   £ */
  		  0, /*   A4        164   § */
  		  0, /*   A5        165   • */
  		  0, /*   A6        166   ¶ */
  		  0, /*   A7        167   ß */
  		  0, /*   A8        168   ® */
  		  0, /*   A9        169   © */
  		  0, /*   AA        170   ™ */
  		  0, /*   AB        171   ´ */
  		  0, /*   AC        172   ¨ */
  		  0, /*   AD        173   ≠ */
  		  0, /*   AE        174   Æ */
  		  0, /*   AF        175   Ø */
  		  0, /*   B0        176   ∞ */
  		  0, /*   B1        177   ± */
  		  0, /*   B2        178   ≤ */
  		  0, /*   B3        179   ≥ */
  		  0, /*   B4        180   ¥ */
  		  0, /*   B5        181   µ */
  		  0, /*   B6        182   ∂ */
  		  0, /*   B7        183   ∑ */
  		  0, /*   B8        184   ∏ */
  		  0, /*   B9        185   π */
  		  0, /*   BA        186   ∫ */
  		  0, /*   BB        187   ª */
  		  0, /*   BC        188   º */
  		  0, /*   BD        189   Ω */
  		  0, /*   BE        190   æ */
  		  0, /*   BF        191   ø */
  		  0, /*   C0        192   ¿ */
  		  0, /*   C1        193   ¡ */
  		  0, /*   C2        194   ¬ */
  		  0, /*   C3        195   √ */
  		  0, /*   C4        196   ƒ */
  		  0, /*   C5        197   ≈ */
  		  0, /*   C6        198   ∆ */
  		  0, /*   C7        199   « */
  		  0, /*   C8        200   » */
  		  0, /*   C9        201   … */
  		  0, /*   CA        202     */
  		  0, /*   CB        203   À */
  		  0, /*   CC        204   Ã */
  		  0, /*   CD        205   Õ */
  		  0, /*   CE        206   Œ */
  		  0, /*   CF        207   œ */
  		  0, /*   D0        208   – */
  		  0, /*   D1        209   — */
  		  0, /*   D2        210   “ */
  		  0, /*   D3        211   ” */
  		  0, /*   D4        212   ‘ */
  		  0, /*   D5        213   ’ */
  		  0, /*   D6        214   ÷ */
  		  0, /*   D7        215   ◊ */
  		  0, /*   D8        216   ÿ */
  		  0, /*   D9        217   Ÿ */
  		  0, /*   DA        218   ⁄ */
  		  0, /*   DB        219   € */
  		  0, /*   DC        220   ‹ */
  		  0, /*   DD        221   › */
  		  0, /*   DE        222   ﬁ */
  		  0, /*   DF        223   ﬂ */
  		  0, /*   E0        224   ‡ */
  		  0, /*   E1        225   · */
  		  0, /*   E2        226   ‚ */
  		  0, /*   E3        227   „ */
  		  0, /*   E4        228   ‰ */
  		  0, /*   E5        229   Â */
  		  0, /*   E6        230   Ê */
  		  0, /*   E7        231   Á */
  		  0, /*   E8        232   Ë */
  		  0, /*   E9        233   È */
  		  0, /*   EA        234   Í */
  		  0, /*   EB        235   Î */
  		  0, /*   EC        236   Ï */
  		  0, /*   ED        237   Ì */
  		  0, /*   EE        238   Ó */
  		  0, /*   EF        239   Ô */
  		  0, /*   F0        240    */
  		  0, /*   F1        241   Ò */
  		  0, /*   F2        242   Ú */
  		  0, /*   F3        243   Û */
  		  0, /*   F4        244   Ù */
  		  0, /*   F5        245   ı */
  		  0, /*   F6        246   ˆ */
  		  0, /*   F7        247   ˜ */
  		  0, /*   F8        248   ¯ */
  		  0, /*   F9        249   ˘ */
  		  0, /*   FA        250   ˙ */
  		  0, /*   FB        251   ˚ */
  		  0, /*   FC        252   ¸ */
  		  0, /*   FD        253   ˝ */
  		  0, /*   FE        254   ˛ */
  		  0, /*   FF        255   ˇ */
};

/*******************************************************************************************
  Width table provides the width of each character. It's useful for proportional font only.
  For monospaced font, the width of each character is the same.

  To get the width of character 'A', you can use the following expression:

     const unsigned char index = index_table['A'];
     const unsigned char width = width_table[index];

 *******************************************************************************************/
const unsigned char width_table[] = {
/*		width    char    hexcode */
/*		=====    ====    ======= */
  		  3, /*          0020    */
  		  3, /*   !      0021    */
  		  4, /*   "      0022    */
  		  7, /*   #      0023    */
  		  7, /*   $      0024    */
  		 12, /*   %      0025    */
  		  8, /*   &      0026    */
  		  2, /*   '      0027    */
  		  5, /*   (      0028    */
  		  5, /*   )      0029    */
  		  6, /*   *      002A    */
  		  7, /*   +      002B    */
  		  3, /*   ,      002C    */
  		  4, /*   -      002D    */
  		  3, /*   .      002E    */
  		  5, /*   /      002F    */
  		  7, /*   0      0030    */
  		  7, /*   1      0031    */
  		  7, /*   2      0032    */
  		  7, /*   3      0033    */
  		  7, /*   4      0034    */
  		  7, /*   5      0035    */
  		  7, /*   6      0036    */
  		  7, /*   7      0037    */
  		  7, /*   8      0038    */
  		  7, /*   9      0039    */
  		  3, /*   :      003A    */
  		  3, /*   ;      003B    */
  		  7, /*   <      003C    */
  		  7, /*   =      003D    */
  		  7, /*   >      003E    */
  		  6, /*   ?      003F    */
  		 10, /*   @      0040    */
  		  8, /*   A      0041    */
  		  7, /*   B      0042    */
  		  7, /*   C      0043    */
  		  7, /*   D      0044    */
  		  6, /*   E      0045    */
  		  6, /*   F      0046    */
  		  7, /*   G      0047    */
  		  8, /*   H      0048    */
  		  5, /*   I      0049    */
  		  5, /*   J      004A    */
  		  7, /*   K      004B    */
  		  6, /*   L      004C    */
  		  9, /*   M      004D    */
  		  7, /*   N      004E    */
  		  8, /*   O      004F    */
  		  7, /*   P      0050    */
  		  8, /*   Q      0051    */
  		  7, /*   R      0052    */
  		  6, /*   S      0053    */
  		  7, /*   T      0054    */
  		  7, /*   U      0055    */
  		  7, /*   V      0056    */
  		  9, /*   W      0057    */
  		  7, /*   X      0058    */
  		  7, /*   Y      0059    */
  		  6, /*   Z      005A    */
  		  5, /*   [      005B    */
  		  5, /*   \      005C    */
  		  5, /*   ]      005D    */
  		  7, /*   ^      005E    */
  		  6, /*   _      005F    */
  		  5, /*   `      0060    */
  		  6, /*   a      0061    */
  		  6, /*   b      0062    */
  		  5, /*   c      0063    */
  		  6, /*   d      0064    */
  		  6, /*   e      0065    */
  		  4, /*   f      0066    */
  		  6, /*   g      0067    */
  		  6, /*   h      0068    */
  		  3, /*   i      0069    */
  		  4, /*   j      006A    */
  		  6, /*   k      006B    */
  		  3, /*   l      006C    */
  		  9, /*   m      006D    */
  		  6, /*   n      006E    */
  		  6, /*   o      006F    */
  		  6, /*   p      0070    */
  		  6, /*   q      0071    */
  		  5, /*   r      0072    */
  		  5, /*   s      0073    */
  		  4, /*   t      0074    */
  		  6, /*   u      0075    */
  		  6, /*   v      0076    */
  		  8, /*   w      0077    */
  		  6, /*   x      0078    */
  		  6, /*   y      0079    */
  		  5, /*   z      007A    */
  		  7, /*   {      007B    */
  		  5, /*   |      007C    */
  		  7, /*   }      007D    */
  		  7, /*   ~      007E    */
  		  6, /*         007F    */
};

unsigned char get_width_of_char(unsigned char charecter)
{
  unsigned char index = 0;
	unsigned char width = 0;

	index = index_table[charecter];
	width = width_table[index];

	return width;
}

unsigned char get_data_from_data_table(unsigned char charecter, unsigned char col)
{
	unsigned char index = index_table[charecter];
	unsigned int offset = offset_table[index];
	unsigned char data = data_table[offset + col];

	return data;
}


