#!/bin/awk
{
  saturate = 5  # in %
  grey = 192
  
  stand = $1
  hit = $2
  
  b = grey
  if (stand > hit) {
    first = stand
    second = hit
    r = grey + (255-grey)*(1-exp(-(stand-hit)/saturate))
    g = b
  } else {
    first = hit
    second = stand
    g = grey + (255-grey)*(1-exp(-(hit-stand)/saturate))
    r = b
  }
  
  printf("  <td align=\"right\" style=\"background-color: rgb(%d, %d, %d)\">%s <small>(%s)</small></td>\n", r, g, b, first, second)
}
