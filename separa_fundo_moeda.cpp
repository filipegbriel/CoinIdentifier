//Testes para separação da cor de fundo e a cor das moedas
//Solucao encontrada: Alterar o espaço de cores de RGB para HSV, pois neste sistema é possível diferenciar
//melhor as cores de fundo das cores das moedas.

//#include <cekeikon.h>
#include <opencv2/opencv.hpp>
#include <iostream>

#define PROPORCAO 1.333 //Proporcao 4/3
#define ALTURA 538

using namespace cv;
using namespace std;

Mat localiza_moedas(Mat input, Mat templ){

}

int main(){
	Mat moeda;
	Mat moeda_rz;
	
	moeda = imread("./moeda/moeda4.jpg",CV_LOAD_IMAGE_COLOR); //Lendo imagem
	
	resize(moeda, moeda_rz, Size(ALTURA*PROPORCAO,ALTURA),1,1,INTER_LINEAR ); //Mudando tamanho da imagem 
	imwrite("./moeda/moeda_rz.jpg", moeda_rz); 		 //Salvando imagem
	
	Mat moeda_blur;
	GaussianBlur(moeda_rz, moeda_blur, 3, 1);
	
	Mat moeda_blur_hsv;
	cvtColor(moeda_blur, moeda_blur_hsv, CV_BGR2HSV, 0); //Convertendo para CSV

	Mat moeda_bin(Size(ALTURA*PROPORCAO,ALTURA),CV_8U);
	
	int lim_inf = 80;	//Limites de limiarização para a componente H
	int lim_sup = 170;	
	
	
	for(int l = 0; l < moeda_blur_hsv.rows; l++){
		for(int c = 0; c < moeda_blur_hsv.cols; c++){
			if(moeda_blur_hsv.at<Vec3b>(l,c)[0]*2 <= lim_sup && moeda_blur_hsv.at<Vec3b>(l,c)[0]*2 >= lim_inf){
				moeda_bin.at<uchar>(l,c) = 255;
			} else {
				moeda_bin.at<uchar>(l,c) = 0;
			}
		}
	}
	namedWindow( "Display window2", WINDOW_AUTOSIZE );// Create a window for display.
	imshow("Display window", moeda_bin); //Mostra resultado 
	waitKey(0);
	
	imwrite("./moeda/moeda_bin.jpg", moeda_bin); //Salva resultado
	return 0;
}