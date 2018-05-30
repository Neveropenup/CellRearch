/*
 * ComplexConv.c
 *
 *  Created on: 2018-5-30
 *      Author: silentlover
 *
 *  Description:
 *  perform a convolution operation.
 */

#include <DefineType.h>
#include <ComplexConv.h>


void ComplexConv(int *convOutput_p,
		         int *complex_p,
		         int *conjComplex_p,
		         Uint16 correlationglength,
		         Uint16 convolutionlength)
{
  Uint16 convLoop;
  Uint16 correLoop;
  Uint16 convLength;
  Uint16 correLength;
  int32 realPart;
  int32 imagPart;
  complexStructure *pComplex;
  complexStructure *pConjComplex;
  complexStructure *pConvOutput;

  /* parameter initial */
  convLength = convolutionlength;
  correLength = correlationglength;

  for (convLoop = 0; convLoop < convLength; convLoop++)
  {
	pComplex = (complexStructure *)&complex_p[convLoop];
	pConjComplex = (complexStructure *)conjComplex_p;
	pConvOutput = (complexStructure *)convOutput_p;

	for (correLoop = 0; correLoop < correLength; correLoop++)
	{
	  realPart = pComplex->RealPart * pConjComplex->RealPart + pComplex->ImagPart * pConjComplex->ImagPart;
	  imagPart = pComplex->ImagPart * pConjComplex->RealPart - pComplex->RealPart * pConjComplex->ImagPart;

	  pConvOutput->RealPart = realPart >> 15;
	  pConvOutput->ImagPart = realPart >> 15;

	  pComplex++;
	  pConjComplex++;
	  pConvOutput;
	}
  }
}

