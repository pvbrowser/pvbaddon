Within the subdirectories you find templates for using libcairo
https://www.cairographics.org/
within a pvserver.

libcairo can produce SVG output.
This output will be send from the pvserver to the pvbrowser client.
The pvbrowser client will render the received SVG using QSvgRenderer on a QDrawWidget. 

The static library within subdirectory
### libpvcairo ###  
implements support functions / classes that make this possible.
It makes use of pvslib and rllib, which are part of the core pvbrowser framework.

The subdirectory
### pvbasic ###
shows a very basic drawing that show howto do the example from: 
https://en.wikipedia.org/wiki/Cairo_(graphics)

The subdirectory
### pvscariodesigner ###
shows a suggestion howto implement widgets.
The parameters of the widgets are stored within a CSV table.
Each row of the table corresponds to 1 widget.
Each widget has the corrdinates xywh (x,y,width,height).
Within mask1_slots.h a basic graphical designer is implemented.
If you switch to mask2_slots.h the deployed mask is shown.
A hitTest function is available and you may click on the widgets.

