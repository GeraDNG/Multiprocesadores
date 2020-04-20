#include <iostream>
#include <opencv/highgui.h>
#include "cppheader.h"

using namespace std;

const int BLUR_WINDOW = 15;

enum color {BLUE, GREEN, RED};

class BlurProcess {
private:
	IplImage *src, *dest;h

	void blur_pixel(int ren, int col) {
		int side_pixels, i, j, cells;
		int tmp_ren, tmp_col, step;
		float r, g, b;

		side_pixels = (BLUR_WINDOW - 1) / 2;
		cells = (BLUR_WINDOW * BLUR_WINDOW);
		step = src->widthStep / sizeof(uchar);
		r = 0; g = 0; b = 0;
		for (i = -side_pixels; i <= side_pixels; i++) {
			for (j = -side_pixels; j <= side_pixels; j++) {
				tmp_ren = MIN( MAX(ren + i, 0), src->height - 1 );
				tmp_col = MIN( MAX(col + j, 0), src->width - 1);

				r += (float) src->imageData[(tmp_ren * step) + (tmp_col * src->nChannels) + RED];
				g += (float) src->imageData[(tmp_ren * step) + (tmp_col * src->nChannels) + GREEN];
				b += (float) src->imageData[(tmp_ren * step) + (tmp_col * src->nChannels) + BLUE];
			}
		}

		dest->imageData[(ren * step) + (col * dest->nChannels) + RED] =  (unsigned char) (r / cells);
		dest->imageData[(ren * step) + (col * dest->nChannels) + GREEN] = (unsigned char) (g / cells);
		dest->imageData[(ren * step) + (col * dest->nChannels) + BLUE] = (unsigned char) (b / cells);
	}

public:

	BlurProcess(IplImage *source, IplImage *destination)
		:src(source), dest(destination) {}

	void doMagic() {
		int index, size, step;
		int ren, col;

		size = src->width * src->height;
		step = src->widthStep / sizeof(uchar);
		for (index = 0; index < size; index++) {
			ren = index / src->width;
			col = index % src->width;
			blur_pixel(ren, col);
		}
	}
};

int main(int argc, char* argv[]) {
	Timer t;
	double acum;

	IplImage *src = cvLoadImage("lenaColor.ppm", CV_LOAD_IMAGE_COLOR);
	IplImage *dest = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);

	BlurProcess bp(src, dest);
	acum = 0;
	for (int i = 0; i < N; i++) {
		t.start();
		bp.doMagic();
		acum += t.stop();
	}
	cout << "avg time = " << (acum /N) << endl;

	cvShowImage("Lenna (Original)", src);
	cvShowImage("Lenna (Blur)", dest);
	cvWaitKey(0);
	cvDestroyWindow("Lenna (Original)");
	cvDestroyWindow("Lenna (Blur)");

	return 0;
}
