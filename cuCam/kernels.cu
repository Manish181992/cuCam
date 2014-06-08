#include <SDL.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>


struct pix24{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

__global__ void oldtimes(pix24 *pixels){

	pix24 *pixel = &pixels[blockIdx.x * blockDim.x + threadIdx.x];
	float intensity = .299f * pixel->r + .587f * pixel->g + .114f * pixel->b;
	
	pixel->r = intensity;
	pixel->g = intensity;
	pixel->b = intensity;
}

SDL_Surface *manSurf(SDL_Surface *surf, int manType){

	struct pix24 *d_pixels = NULL;
	int noOfPixels = surf->w * surf->h;

	const dim3 gridDims(surf->h,1,1);
	const dim3 blockDims(surf->w,1,1);
	
	cudaMalloc((void **)&d_pixels, noOfPixels * (3));
	cudaMemcpy(d_pixels, surf->pixels, noOfPixels * 3, cudaMemcpyHostToDevice);

	switch(manType){
		case 1:
			oldtimes<<<gridDims, blockDims>>>(d_pixels);
			break;
	};

	cudaMemcpy(surf->pixels, d_pixels, noOfPixels * 3, cudaMemcpyDeviceToHost);
	cudaFree(d_pixels);
	return surf;
}