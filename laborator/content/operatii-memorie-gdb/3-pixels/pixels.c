#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "pixel.h"
#define GET_PIXEL(a,i,j) (*(*(a+i)+j))

/*
	TODO a
	Functia primeste ca parametru o imagine si intoarce imaginea rasturnata.
	Prin imagine rasturnata se intelege inversarea liniilor matricei pix_array
	din structura lui Picture, astfel: Linia 1 devine linia n, linia 2 devine
	linia n - 1, etc.
*/
// void swap(){
// pic->GET_PIXEL(pix_array,i,j).R = 0.3 * pic->GET_PIXEL(pix_array,i,j).R;
// 	pic->GET_PIXEL(pix_array,i,j).G = 0.59 * pic->GET_PIXEL(pix_array,i,j).G;
// 	pic->GET_PIXEL(pix_array,i,j).B = 0.11 * pic->GET_PIXEL(pix_array,i,j).B;
// // }

void reversePic(Picture *pic){

	for(int i=0;i<pic->height/2;i++){
		for (int j=0;j<pic->width;j++){
			unsigned char aux;
	aux=pic->pix_array[pic->height-i-1][j].R;
	pic->pix_array[pic->height-i-1][j].R=pic->pix_array[i][j].R;
	pic->pix_array[i][j].R =aux;

	aux=pic->pix_array[pic->height-i-1][j].G;
	pic->pix_array[pic->height-i-1][j].G=pic->pix_array[i][j].G;
	pic->pix_array[i][j].G =aux;

	aux=pic->pix_array[pic->height-i-1][j].B;
	pic->pix_array[pic->height-i-1][j].B=pic->pix_array[i][j].B;
	pic->pix_array[i][j].B =aux;

		}
	}


}

void colorToGray(Picture *pic){

	for(int i=0;i<pic->height;i++){
		for (int j=0;j<pic->width;j++){
	pic->pix_array[i][j].R = 0.3 * pic->pix_array[i][j].R;
	pic->pix_array[i][j].G = 0.59 * pic->pix_array[i][j].G;
	pic->pix_array[i][j].B = 0.11 * pic->pix_array[i][j].B;
		}
	}


}


int main() {
	int height, width;
	scanf("%d%d", &height, &width);
	Pixel **pix_array = generatePixelArray(height, width);
	Picture *pic = generatePicture(height, width, pix_array);
	printf("poza inainte: \n");
	printPicture(pic);
	printf("poza dupa: \n");
	reversePic(pic);
	printPicture(pic);

	freePicture(&pic);
	freePixelArray(&pix_array, height, width);

	return 0;
}
