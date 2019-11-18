/***************************************************************************
�� �t�@�C�����Fread_write.c
�� ���e�F�ǂݍ��݁C��������, �������m�ۓ��̊֐��Q

Copyright @ ASPL all rights reserved.
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************************************************************************
�� �֐����Fshort* Read_Raw_File_Short( char *fname, int *dtSize )
�� ���e�FRAW�`���̉���(fname)����ʎq���r�b�g16bit�Œ��o
         �T���v������*dtSize�Ɋi�[
�� �����Fchar *fname�F���̓t�@�C����
       �Fint *dtSize�F���̓t�@�C���̃T���v�������i�[����ϐ��̃A�h���X
�� �߂�l�F���̓t�@�C���̕W�{�f�[�^�̐擪�A�h���X
***************************************************************************/
short* Read_Raw_File_Short( char *fname, int *dtSize ){

	short *data;

	FILE *fp;

	// �t�@�C���I�[�v��
	if( ( fp = fopen( fname, "rb" ) ) == NULL ){
		printf("Read_Raw_File_Short() : FILE [%s] ERROR\n", fname);
		exit( -1 );
	}

	// �W�{���̎擾
	fseek( fp, 0, SEEK_END );
	*dtSize = ftell( fp ) / sizeof( short );
	fseek( fp, 0, SEEK_SET );

	// �W�{�����̃������m��
	if( ( data = ( short* )malloc( sizeof( short ) * ( *dtSize ) ) ) == NULL ){
		printf("Read_Raw_File_Short() : MALLOC ERROR\n");
		exit( -1 );
	}

	// �W�{�f�[�^�̊i�[
	if( fread( data, sizeof( short ), *dtSize, fp ) < *dtSize ){
		printf("Read_Raw_File_Short() : DATA READ ERROR\n");
		exit( -1 );
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	return( data );
}

/***************************************************************************
�� �֐����Fvoid Write_Raw_File_Short( short *data, char *fname, int dtSize )
�� ���e�F*data����ʎq���r�b�g16bit�̕W�{�l��dtSize��
         RAW�`���̉���(fname)�Ɋi�[
�� �����Fshort *data�F�o�͂���W�{�f�[�^
       �Fchar *fname�F�o�̓t�@�C����
       �Fint dtSize�F�o�̓t�@�C���̃T���v����
�� �߂�l�F�Ȃ�
***************************************************************************/
void Write_Raw_File_Short( short *data, char *fname, int dtSize ){

	FILE *fp;

	// �t�@�C���I�[�v��
	if( ( fp = fopen( fname, "wb" ) ) == NULL ){
		printf("Write_Raw_File_Short() : FILE [%s] ERROR\n", fname);
		exit( -1 );
	}

	// �f�[�^��������
	if( fwrite( data, sizeof( short ), dtSize, fp ) < dtSize ){
		printf("Write_Raw_File_Short() : DATA WRITE ERROR\n");
		exit( -1 );
	}

	// �t�@�C���N���[�Y
	fclose( fp );
}

/***************************************************************************
�� �֐����Fdouble* Read_Raw_File_Double( char *fname, int *dtSize )
�� ���e�FRAW�`���̉���(fname)����ʎq���r�b�g64bit�Œ��o
         �T���v������*dtSize�Ɋi�[
�� �����Fchar *fname�F���̓t�@�C����
       �Fint *dtSize�F���̓t�@�C���̃T���v�������i�[����ϐ��̃A�h���X
�� �߂�l�F���̓t�@�C���̕W�{�f�[�^�̐擪�A�h���X
***************************************************************************/
double* Read_Raw_File_Double( char *fname, int *dtSize ){

	double *data;

	FILE *fp;

	// �t�@�C���I�[�v��
	if( ( fp = fopen( fname, "rb" ) ) == NULL ){
		printf("Read_Raw_File_Short() : FILE [%s] ERROR\n", fname);
		exit( -1 );
	}

	// �W�{���̎擾
	fseek( fp, 0, SEEK_END );
	*dtSize = ftell( fp ) / sizeof( double );
	fseek( fp, 0, SEEK_SET );

	// �W�{�����̃������m��
	if( ( data = ( double* )malloc( sizeof( double ) * ( *dtSize ) ) ) == NULL ){
		printf("Read_Raw_File_Short() : MALLOC ERROR\n");
		exit( -1 );
	}

	// �W�{�f�[�^�̊i�[
	if( fread( data, sizeof( double ), *dtSize, fp ) < *dtSize ){
		printf("Read_Raw_File_Short() : DATA READ ERROR\n");
		exit( -1 );
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	return( data );
}

/***************************************************************************
�� �֐����Fvoid Write_Raw_File_Double( double *data, char *fname, int dtSize )
�� ���e�F*data����ʎq���r�b�g64bit�̕W�{�l��dtSize��
         RAW�`���̉���(fname)�Ɋi�[
�� �����Fdouble *data�F�o�͂���W�{�f�[�^
       �Fchar *fname�F�o�̓t�@�C����
       �Fint dtSize�F�o�̓t�@�C���̃T���v����
�� �߂�l�F�Ȃ�
***************************************************************************/
void Write_Raw_File_Double( double *data, char *fname, int dtSize ){

	FILE *fp;

	// �t�@�C���I�[�v��
	if( ( fp = fopen( fname, "wb" ) ) == NULL ){
		printf("Write_Raw_File_Short() : FILE [%s] ERROR\n", fname);
		exit( -1 );
	}

	// �f�[�^��������
	if( fwrite( data, sizeof( double ), dtSize, fp ) < dtSize ){
		printf("Write_Raw_File_Short() : DATA WRITE ERROR\n");
		exit( -1 );
	}

	// �t�@�C���N���[�Y
	fclose( fp );
}

/***************************************************************************
�� �֐����Fdouble* Memory_Double( int dtSize )
�� ���e�Fdouble�^�̃�������dtSize�m�ۂ���
�� �����Fint dtSize�F���̓t�@�C���̃T���v����
�� �߂�l�F�m�ۂ����������̐擪�A�h���X
***************************************************************************/
double* Memory_Double( int dtSize ){

	double *data;

	// �������m��
	if( ( data = ( double * )malloc( sizeof( double ) * dtSize ) ) == NULL ){
		fprintf( stderr, "Memory_Double() : MALLOC ERROR\n");
		exit( -1 );
	}

	return( data );
}

/***************************************************************************
�� �֐����Fshort* Memory_Short( int dtSize )
�� ���e�Fshort�^�̃�������dtSize�m�ۂ���
�� �����Fint dtSize�F���̓t�@�C���̃T���v����
�� �߂�l�F�m�ۂ����������̐擪�A�h���X
***************************************************************************/
short* Memory_Short( int dtSize ){

	short *data;

	// �������m��
	if( ( data = ( short * )malloc( sizeof( short ) * dtSize ) ) == NULL ){
		fprintf( stderr, "Memory_Short() : MALLOC ERROR\n");
		exit( -1 );
	}

	return( data );
}


/***************************************************************************
�� �֐����Fvoid DFT(int N, double D[], double Xr[], double Xi[])
�� ���e�F���͐M��D[]���t�[���G�_��N�Ńt�[���G�ϊ��������ʂ�
         ����Xr[], ����Xi[]�Ɋi�[����
�� �����Fint N�F�t�[���G�_��
         double D[]�F���͐M��
         double Xr[]�F�t�[���G�ϊ����ʁi�����j
         double Xi[]�F�t�[���G�ϊ����ʁi�����j
�� �߂�l�F�Ȃ�
***************************************************************************/
void DFT(int N, double D[], double Xr[], double Xi[]){

  int k, n;              // ���[�v�J�E���^
  double er, ei;         // �����E����

  double w;              // �e���g��
	double pai=3.1415926;  // �~����

	// �t�[���G�ϊ�
  for( k = 0; k < N; k++ ){

    Xr[ k ] = Xi[ k ] = 0.0;

    for( n = 0; n < N; n++ ){

  		w = 2 * pai * k * n / N;
			er = D[ n ] * cos( w );
			ei = D[ n ] * sin( -w );

      Xr[ k ] += er / N;
      Xi[ k ] += ei / N;
    }
  }
}
