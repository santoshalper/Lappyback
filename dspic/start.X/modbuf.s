.global _InpB, _W2OB , _R2OB
_InpB:
 mov.w [w1], w10
 mov.w w0, [w10++]
 mov.w w10, [w1]
 return

_W2OB:
 mov.w [w1], w11
 mov.w w0, [w11++]
 mov.w w11, [w1]
 return
 
_R2OB:
 mov.w w0, w1
 mov.w [w1], w10
 mov.w [w10++], w0
 mov.w w10, [w1]
 return
.end
 
  

