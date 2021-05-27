# essential-headers
Some headers I use myself a lot. A lot of this is work in progress and not intended for public usage(use it if you want to but on your own risk)  I only uploaded this to Github so I can use it wherever I want to.

#AdMath
  #compiler agruments:
  -lm

  (int) 	IsEven(number)
  (int)		NegativeToPositive(number)
  (int) 	power(number,PowerOf)
  (int)	 	min(a,b)
  (int) 	max(a,b)
  (float) p_theorum(a,b)
  (int)		IntRoot(number,RootOf)	//broken
  
  
#CrossPlatform
				 							delay(in milliseconds)
	(int / usa as bool)	WaitForInput
	(char) 							PressedKey
				 							KeyPressed()
				 							CrossSystem()

#PrintColor
  #parameters
  (short / use as bool) bold
  (short / use as bool) LessVisible
  (short / use as bool) cursive
  (short / use as bool) underline
  (short / use as bool) SwapBackground
  (short / use as bool) SameBackground
  (short / use as bool) crossed
  (short / use as bool) LineOver

  #functions
                        text_color(color)
                        background_color(color)
                        reset()

#SimpleScreen
  (int / use as short)ScreenSpace[x][y][(int)PartOfScreen(foreground + background + occupancy)];
                      release()
                      resize(NewX,NewY)
  (int / use as bool) ClearColor
  (int / use as bool) RemoveOldOutput
  //whether or not screen will be cleared at runtime;
                      DebugPrint()
  (char)              background_occupancy[101]
                      screen("action(write + print + fill)","PartOfScreen(foreground + background + FullPixel + occupancy)",x,y,color)
                      ScreenPrint()
                      ScreenClear()
  (int / use as bool) SizeChanged
  (int / use as bool) UpdateScreen
                      DebugSettings()
                      
