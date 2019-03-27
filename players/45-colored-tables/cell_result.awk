#!/bin/awk
{
  saturate = 25  # in %
  grey = 128
  
  result = $1
  error = $2
  
  if (result > 0) {
    g = grey + (255-grey)*(1-exp(-result/saturate))
#     g = grey + (255-grey)*result/100
    r = grey
    b = grey + (255-grey)*(exp(-result/saturate))
  } else {    
    r = grey + (255-grey)*(1-exp(+result/saturate))
#     r = grey - (255-grey)*result/100
    g = grey
    b = grey + (255-grey)*(exp(result/saturate))
  }
  
  printf("  <td align=\"right\" style=\"background-color: rgb(%d, %d, %d)\">%s <small>&plusmn; %s</small></td>\n", r, g, b, result, error)
}
