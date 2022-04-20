#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<Windows.h>

/* データ型のtypdef宣言 */
typedef unsigned char				t_u08;
typedef unsigned short			t_u16;
typedef unsigned int				t_u32;
typedef unsigned long long     t_u64;
typedef signed char				t_s08;
typedef signed short				t_s16;
typedef signed int					t_s32;
typedef signed long long			t_s64;

/* define宣言 */
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
//PNGのバイナリ構造
PNG_Header			 8byte
	-0x89 ASCII文字で表現できない値。テキストファイルとして間違えてロードされてしまう可能性を減らす
	-0x50 フォーマット名(P)
	-0x4E フォーマット名(N)
	-0x47 フォーマット名(G)
	-0x0D 改行文字"として解釈されてしまい、システムによって勝手に「\r」や「\n」に置き換えられたりしないかを検出するために利用される
	-0x0A 改行文字"として解釈されてしまい、システムによって勝手に「\r」や「\n」に置き換えられたりしないかを検出するために利用される
	-0x1A Control-z文字。ファイルの中身をテキストとして読み出し表示させようとしたDOSコマンドを停止させる
	-0x0A改行文字"として解釈されてしまい、システムによって勝手に「\r」や「\n」に置き換えられたりしないかを検出するために利用される
IHDR_chunk			25byte
	-lenght;								// チャンクの長さ(常に13)
	-chunk_type;						// チャンクのタイプ(16進数で常に 49 48 44 52)
	-width;								// 画像の幅
	-hight;								// 画像の高さ
	-bit_depth;							// ビット深度(有効な値は 1, 2, 4, 8, 16 、カラータイプにより使用できないものも出てくるs)
	-color_type;						// カラータイプ(1 - パレット使用 2 - カラー 4 - αチャンネル(有効な値は 0, 2, 3, 4, 6 ))
	-compression_type;				// 圧縮方法
	-filter_type;							// フィルター手法
	-interlace_type;					// インターレース手法
	-cyclic_redundancy_check;	// 巡回冗長検査（じゅんかいじょうちょうけんさ)というらしい...

IDAT_chunk			Nbyte
	-画像の実データ

IEND_chunk			12byte
	-終端データ
------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------
 note
 インターレース手法とは

 画像を表示する際に用いる手法である。
 ノンインターレースは、画像を徐々に表示していき、最初から綺麗に表示する。
 表示される体感速度は遅いが、データ容量は小さく出来る。

 インターレースはいきなり全ての画像を表示して徐々に綺麗になって行く手法。
 表示される体感速度は早く感じるが、データの容量が大きくなってします。
------------------------------------------------------------------------------------------------------------*/

/* pngの構造体 */
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
	
	// 長さを揃えるために1バイト放り込むべきか？
}pngInfo;

/* プロトタイプ宣言 */
void read_bmp(const char argv);

/* pngファイルの読み込み */

int main( int argc, char *argv[] ) 
{
	FILE* fp = NULL;
	pngInfo *pi= NULL;


	return 0;
}



/* bmpファイルの読み込み */
void read_bmp(const char argv)
{
	// BMPデータの読み込み。
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