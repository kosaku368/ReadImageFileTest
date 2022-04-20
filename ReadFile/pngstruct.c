#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<Windows.h>

/* �f�[�^�^��typdef�錾 */
typedef unsigned char				t_u08;
typedef unsigned short			t_u16;
typedef unsigned int				t_u32;
typedef unsigned long long     t_u64;
typedef signed char				t_s08;
typedef signed short				t_s16;
typedef signed int					t_s32;
typedef signed long long			t_s64;

/* define�錾 */
#define PNG_HEADER_BYTE							( 8 )
#define PNG_CHUNK_LENGHT_BYTE				( 4 )
#define PNG_CHUNK_TYPE_BYTE					( 4 )
#define PNG_WIDTH_BYTE								( 4 )
#define PNG_HIGHT_BYTE								( 4 )
#define PNG_BIT_DEPTH_BYTE						( 1 )
#define PNG_COLOR_TYPE_BYTE					( 1 )
#define PNG_COMPRESSION_TYPE_BYTE		( 1 )
#define PNG_FILTER_TYPE_BYTE					( 1 )
#define PNG_INTERLACE_TYPE_BYTE				( 1 )
#define PNG_CYCLIC_REDUNDANCY_CHACK	( 4 )
#define PNG_END_CHUNK								(12)
/*------------------------------------------------------------------------------------------------------------
//PNG�̃o�C�i���\��
PNG_Header			 8byte
	-0x89 ASCII�����ŕ\���ł��Ȃ��l�B�e�L�X�g�t�@�C���Ƃ��ĊԈႦ�ă��[�h����Ă��܂��\�������炷
	-0x50 �t�H�[�}�b�g��(P)
	-0x4E �t�H�[�}�b�g��(N)
	-0x47 �t�H�[�}�b�g��(G)
	-0x0D ���s����"�Ƃ��ĉ��߂���Ă��܂��A�V�X�e���ɂ���ď���Ɂu\r�v��u\n�v�ɒu��������ꂽ�肵�Ȃ��������o���邽�߂ɗ��p�����
	-0x0A ���s����"�Ƃ��ĉ��߂���Ă��܂��A�V�X�e���ɂ���ď���Ɂu\r�v��u\n�v�ɒu��������ꂽ�肵�Ȃ��������o���邽�߂ɗ��p�����
	-0x1A Control-z�����B�t�@�C���̒��g���e�L�X�g�Ƃ��ēǂݏo���\�������悤�Ƃ���DOS�R�}���h���~������
	-0x0A���s����"�Ƃ��ĉ��߂���Ă��܂��A�V�X�e���ɂ���ď���Ɂu\r�v��u\n�v�ɒu��������ꂽ�肵�Ȃ��������o���邽�߂ɗ��p�����
IHDR_chunk			25byte
	-lenght;								// �`�����N�̒���(���13)
	-chunk_type;						// �`�����N�̃^�C�v(16�i���ŏ�� 49 48 44 52)
	-width;								// �摜�̕�
	-hight;								// �摜�̍���
	-bit_depth;							// �r�b�g�[�x(�L���Ȓl�� 1, 2, 4, 8, 16 �A�J���[�^�C�v�ɂ��g�p�ł��Ȃ����̂��o�Ă���s)
	-color_type;						// �J���[�^�C�v(1 - �p���b�g�g�p 2 - �J���[ 4 - ���`�����l��(�L���Ȓl�� 0, 2, 3, 4, 6 ))
	-compression_type;				// ���k���@
	-filter_type;							// �t�B���^�[��@
	-interlace_type;					// �C���^�[���[�X��@
	-cyclic_redundancy_check;	// ����璷�����i����񂩂����傤���傤����)�Ƃ����炵��...

IDAT_chunk			Nbyte
	-�摜�̎��f�[�^

IEND_chunk			12byte
	-�I�[�f�[�^
------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------
 note
 �C���^�[���[�X��@�Ƃ�

 �摜��\������ۂɗp�����@�ł���B
 �m���C���^�[���[�X�́A�摜�����X�ɕ\�����Ă����A�ŏ������Y��ɕ\������B
 �\�������̊����x�͒x�����A�f�[�^�e�ʂ͏������o����B

 �C���^�[���[�X�͂����Ȃ�S�Ẳ摜��\�����ď��X���Y��ɂȂ��čs����@�B
 �\�������̊����x�͑��������邪�A�f�[�^�̗e�ʂ��傫���Ȃ��Ă��܂��B
------------------------------------------------------------------------------------------------------------*/

/* png�̍\���� */
typedef struct 
{
	t_u64 header;									//  8

	t_u32 lenght;										// 4
	t_u32 chunk_type;								// 8
	t_u32 width;										// 12
	t_u32 hight;										// 16
	t_u08 bit_depth;								// 17
	t_u08 color_type;								// 18
	t_u08 compression_type;					// 19
	t_u08 filter_type;								// 20
	t_u08 interlace_type;							// 21
	t_u32 cyclic_redundancy_check;			// 25
	
	// �����𑵂��邽�߂�1�o�C�g���荞�ނׂ����H
}pngInfo;

/* �v���g�^�C�v�錾 */
void read_bmp(const char argv);

/* png�t�@�C���̓ǂݍ��� */

int main( int argc, char *argv[] ) 
{
	FILE* fp = NULL;
	pngInfo *pi= NULL;


	return 0;
}



/* bmp�t�@�C���̓ǂݍ��� */
void read_bmp(const char argv)
{
	// BMP�f�[�^�̓ǂݍ��݁B
	struct stat s_stat;
	void* buffer = NULL;
	char* read_file_name;
	int file_size = 0;

	read_file_name = argv;
	if (stat(read_file_name, &s_stat) != -1)
	{
		file_size = s_stat.st_size;
	}

	FILE* read_file = NULL;
	BITMAPFILEHEADER* hb = NULL;
	BITMAPINFOHEADER* ib = NULL;

	fopen_s(&read_file, read_file_name, "rb");
	buffer = malloc(file_size);
	if (read_file != NULL)
	{
		if (buffer != NULL) {
			fread(buffer, file_size, 1, read_file);

			hb = (BITMAPFILEHEADER*)buffer;
			ib = (BITMAPINFOHEADER*)((t_u64)buffer + sizeof(BITMAPFILEHEADER));

			printf("FILE\n");
			printf(" bfType           -> %d\n", hb->bfType);
			printf(" bfSize	            -> %d\n", hb->bfSize);
			printf(" bfReserved1   -> %d\n", hb->bfReserved1);
			printf(" bfReserved2   -> %d\n", hb->bfReserved2);
			printf(" bfOffBits         -> %d\n\n", hb->bfOffBits);

			printf("INFO\n");
			printf(" biSize	                    -> %d\n", ib->biSize);
			printf(" biWidth                  -> %d\n", ib->biWidth);
			printf(" biHeight	                -> %d\n", ib->biHeight);
			printf(" biPlanes	                -> %d\n", ib->biPlanes);
			printf(" biBitCount              -> %d\n", ib->biBitCount);
			printf(" biCompression        -> %d\n", ib->biCompression);
			printf(" biSizeImage           -> %d\n", ib->biSizeImage);
			printf(" biXPelsPerMeter      -> %d\n", ib->biXPelsPerMeter);
			printf(" biYPelsPerMeter      -> %d\n", ib->biYPelsPerMeter);
			printf(" biClrUsed               -> %d\n", ib->biClrUsed);
			printf(" biClrImportant        -> %d\n", ib->biClrImportant);

			fclose(read_file);
			free(buffer);
		}
	}
}