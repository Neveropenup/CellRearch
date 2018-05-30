/*
 * AgcAjustment.c
 *
 *  Created on: 2018-5-30
 *      Author: silentlover
 *
 *  Description:
 *
 */
#include <DefineType.h>
#include <stdlib.h>
#include <AgcAjustment.h>

void AgcAjustment(int *antennaBuffer_p,
		          Uint16 bufferLength)
{
  Uint16 loopIndex;
  complexStructure *pAntennaBuffer;
  Uint32 accumulateAbs = 0;
  int16 AgcFactor = 0;

  pAntennaBuffer = (complexStructure *)antennaBuffer_p;

  for (loopIndex = 0; loopIndex < bufferLength; loopIndex++)
  {
	accumulateAbs += abs(pAntennaBuffer->RealPart);
	accumulateAbs += abs(pAntennaBuffer->ImagPart);

	pAntennaBuffer++;
  }

  while (accumulateAbs > SUPERIOR_LIMIT)
  {
	AgcFactor--;
	accumulateAbs = accumulateAbs >> 1;
  }

  while (accumulateAbs < LOWER_LIMIT)
  {
	AgcFactor++;
	accumulateAbs = accumulateAbs << 1;
  }

  if (0 == AgcFactor)
  {
    return;
  }
  else if (AgcFactor > 0)
  {
	pAntennaBuffer = (complexStructure *)antennaBuffer_p;

    for (loopIndex = 0; loopIndex < bufferLength; loopIndex++)
    {
      pAntennaBuffer->RealPart = pAntennaBuffer->RealPart << AgcFactor;
	  pAntennaBuffer->ImagPart = pAntennaBuffer->ImagPart << AgcFactor;

	  pAntennaBuffer++;
	}
  }
  else
  {
	AgcFactor = abs(AgcFactor);
	pAntennaBuffer = (complexStructure *)antennaBuffer_p;

    for (loopIndex = 0; loopIndex < bufferLength; loopIndex++)
    {
      pAntennaBuffer->RealPart = pAntennaBuffer->RealPart >> AgcFactor;
	  pAntennaBuffer->ImagPart = pAntennaBuffer->ImagPart >> AgcFactor;

	  pAntennaBuffer++;
	}
  }
}

