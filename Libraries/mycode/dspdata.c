#include "headfile.h"
#include "dspdata.h"
/*
arm_cfft_q15
*/
void dsp_fft_image(uint8* souce_image,uint8* tar_image)
{
  int i;
  q15_t souce_fft[ROW*COL],tar_fft[ROW*COL];
  arm_rfft_instance_q15 fft_init_struct;
  uint32_t fftLenReal,ifftFlagR,bitReverseFlag;
  arm_status fft_sta = ARM_MATH_SUCCESS;

  /*
  fft_init_struct.fftLenReal = ROW*COL;
  fft_init_struct.ifftFlagR = 0;
  fft_init_struct.bitReverseFlagR  = 0;
  */
  fftLenReal = ROW*COL;
  ifftFlagR = 0;
  bitReverseFlag = 0;
  fft_sta = arm_rfft_init_q15(&fft_init_struct,fftLenReal,ifftFlagR,bitReverseFlag);
  if(fft_sta == ARM_MATH_SUCCESS)
  {
    for(i=0;i< ROW*COL;i++)
    {
     souce_fft[i] = (q15_t)souce_image[i];
    }
  
    arm_rfft_q15(&fft_init_struct,souce_fft,tar_fft);
    
    for(i=0;i< ROW*COL;i++)
    {
     tar_image[i] = (uint8)tar_fft[i];
    }
  }
  
}















