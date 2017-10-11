.global _W2XS, _RFXS, _CLYS
_W2XS: //right to x space
 mov.w [w1], w10
 mov.w w0, [w10++]
 mov.w w10, [w1]
 return
 
_RFXS: //read from x space
 mov.w w0, w1
 mov.w [w1], w10
 mov.w [w10++], w0
 mov.w w10, [w1]
 return

_CLYS: //clear y space	
 mov.w [w0], w11
 clr   [w11++]
 mov.w w11, [w0]
 return
.end
