.global _W2XS, _RFXS
_W2XS: #write to x space
 mov.w [w1], w10
 mov.w w0, [w10++]
 mov.w w10, [w1]
 return
 
_RFXS: #read from x space
 mov.w w0, w1
 mov.w [w1], w10
 mov.w [w10++], w0
 mov.w w10, [w1]
 return
.end
