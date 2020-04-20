#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "utils/cheader.h"

typedef enum color {BLUE, GREEN, RED} Color;

_global_ void gray_cu(unsigned char *src, unsigned char *dest, int width, int heigth, int step, int channels) {
	int ren, col;
	float r, g, b, avg;

	ren = blockIdx.x;
	col = threadIdx.x;
	r = 0; g = 0; b = 0;

	r = (float) src[(ren * step) + (col * channels) + RED];
	g = (float) src[(ren * step) + (col * channels) + GREEN];
	b = (float) src[(ren * step) + (col * channels) + BLUE];

  avg = (r + g + b)/3.0;

	dest[(ren * step) + (col * channels) + RED] =  (unsigned char) (avg);
	dest[(ren * step) + (col * channels) + GREEN] = (unsigned char) (avg);
	dest[(ren * step) + (col * channels) + BLUE] = (unsigned char) (avg);
}


void gray_seq(unsigned char *src, unsigned char *dest, int width, int height, int step, int channels){
	float r, g, b, avg;

	r = 0; g = 0; b = 0;

  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      r = (float) src[(i * step) + (j * channels) + RED];
      g = (float) src[(i * step) + (j * channels) + GREEN];
      b = (float) src[(i * step) + (j * channels) + BLUE];

      avg = (r + g + b)/3.0;

      dest[(i * step) + (j * channels) + RED] =  (unsigned char) (avg);
      dest[(i * step) + (j * channels) + GREEN] = (unsigned char) (avg);
      dest[(i * step) + (j * channels) + BLUE] = (unsigned char) (avg);
    }
  }
}

int main(int argc, char* argv[]) {
	int i, step, size;
	double acum_seq, acum_cu;
	unsigned char *dev_src, *dev_dest, *seq_dest;

	if (argc != 2) {
		printf("usage: %s source_file\n", argv[0]);
		return -1;
	}

	IplImage *src = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	IplImage *dest = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 3);

	if (!src) {
		printf("Could not load image file: %s\n", argv[1]);
		return -1;
	}

	size = src->width * src->height * src->nChannels * sizeof(uchar);
	step = src->widthStep / sizeof(uchar);

	cudaMalloc((void**) &dev_src, size);
	cudaMalloc((void**) &dev_dest, size);


  seq_dest = new unsigned char[size];

	cudaMemcpy(dev_src, src->imageData, size, cudaMemcpyHostToDevice);

  cvShowImage("Lenna (ORIGINAL)", src);

  acum_seq = 0;
  for(i = 0; i < N; i++){
    start_timer();
    gray_seq((uchar*)src->imageData, seq_dest, src->width, src->height, step, src->nChannels);
    acum_seq += stop_timer();
  }

  memcpy(dest->imageData, seq_dest, size);
  cvShowImage("Lenna (GRAY_SEQUENTIAL)", dest);

  printf("avg sequential time = %.5lf ms\n", (acum_seq / N));
	acum_cu = 0;
	for (i = 0; i < N; i++) {
		start_timer();
		gray_cu<<<src->height, src->width>>>(dev_src, dev_dest, src->width, src->height, step, src->nChannels);
		acum_cu += stop_timer();
	}

	cudaMemcpy(dest->imageData, dev_dest, size, cudaMemcpyDeviceToHost);
  cvShowImage("Lenna (GRAY_CUDA)", dest);

  printf("avg CUDA time = %.5lf ms\n", (acum_cu / N));

	printf("Speedup: %.5lf \n",(acum_seq/acum_cu));

	cudaFree(dev_dest);
	cudaFree(dev_src);
  free(seq_dest);


  cvWaitKey(0);
  cvDestroyWindow("Lenna (ORIGINAL)");
  cvDestroyWindow("Lenna (GRAY_SEQUENTIAL)");
  cvDestroyWindow("Lenna (GRAY_CUDA)");

	return 0;
}
