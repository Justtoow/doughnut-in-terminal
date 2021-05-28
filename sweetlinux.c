#include"stdio.h"
#include"math.h"
#include"string.h"
#include"stdlib.h"

const float phi_spacing =0.01;
const float theta_spacing=0.1;
const int screen_width=100;
const int screen_height=40;


// radius
const float R1=1;
//center of circle
const float R2 =2;
//distance  from object to screen
const float D2 =5;
//distance from eye to screen
const float D1 =20;


void sweet(float A,float B){
	float zbuffer[screen_width*screen_height];
	char output[screen_width*screen_height];
	memset(output,' ',screen_width*screen_height);
	memset(zbuffer,0,screen_width*screen_height*4);
	float theta ;
	float phi;
	for(theta =0;theta<2*M_PI;theta+=theta_spacing){
		for( phi=0;phi<2*M_PI;phi+=phi_spacing){
			float sinA=sin(A);
			float sinB=sin(B);
			float cosA=cos(A);
			float cosB=cos(B);
			float sinphi=sin(phi);
			float sintheta=sin(theta);
			float cosphi=cos(phi);
			float costheta=cos(theta);
			
			
			float circlex= costheta*R1+R2;
			float circley=R1*sintheta;
			//use matrix to calculate x,y,z
			float x= circlex*(cosB*cosphi+sinA*sinB*sinphi)-circley*cosA*sinB;
			float y=circlex*(sinB*cosphi-sinA*cosB*sinphi)+circley*cosA*cosB;
			float z= D2 +cosA*circlex*sinphi+circley*sinA;
			float ratez =1/z;
			
			int xp=screen_width/2+2*D1*ratez*x;
			int yp=screen_height/2 -D1*ratez*y;
			int i= xp+screen_width*yp;
			float L =cosphi*costheta*sinB-cosA*costheta*sinphi-sinA*sintheta
			+cosB*(cosA*sintheta-costheta*sinA*sinphi);
			int lum_index =L*8;
			if(screen_height>yp&&yp>0&&xp>0&&screen_width>xp){
				zbuffer[i]=ratez;
				output[i]=
				    ".,-~:;=!*#$@"[lum_index>0?lum_index :0];
			}
		}
	}
	printf("\x1b[H");//refresh
	int k;
	for( k=0;k<screen_width*screen_height+1;k++){
		putchar(k%screen_width ?output[k]:10);
	}
}

int main(){
    float A=0;
    float B=0;
    float i,j,zbuffer[screen_width*screen_height];
    printf("\x1b[2J");
    int back=0;
    for(;;){
    	sweet(A,B);
    	A+=0.04;
    	B+=0.02;
    	usleep(20000);
	}
	return 0;
} 
