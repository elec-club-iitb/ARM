// input normalised sample
float getFreqComp(float* sample, int size,float freq);
void getDFT(float* sample,float* bin,int size);
void getDFT(float* sample  ,float* bin,int size)
{
		for( int k=0;k<size;k++)
		{
			bin[k] = getFreqComp(sample,size,6.28*k/size);
		}
		float max=-5;
		for(int k=0;k<size;k++)
		{
			if(bin[k]>max)max=bin[k];
		}
		for(int k=0;k<size;k++)
		{
			bin[k]/=max;
		}
}

float getFreqComp(float* sample, int size,float freq)
{
	float real=0,img=0;
	for(int i=0;i<size;i++)
	{
		real+= sample[i]*cos(freq*i);
		img+=  sample[i]*sin(freq*i);
	}
	return sqrt(real*real+img*img);
}

