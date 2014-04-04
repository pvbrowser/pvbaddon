Alarm system for pvbrowser

This template shows howto implement alarms. We use a WebKit widget with HTML.
In main.cpp we define a Alarm class and refer to it from the masks as extern.

Now we can set alarms, acknowledge and reset them.
See the cyclic_actions thread within main.cpp and slotTextEvent() in mask1_slots.cpp .

In mask1_slots.h we use updateWidgetHTML() in slotNullEvent() on a WebKit widget.
By clicking the link with the alarm our pvserver gets a text event indicating an acknowledge.

The implementation supports any number of clients.

The alarms are defined within a CSV file.
The CSV file must use TAB as separator and " for surrounding the fields.
You may use open office or excel.

You may optionally send the alarms to pcontrol event log server also.
In that case the Alarm instance must be created with useEventLog=1 .

The files alarm.h and alarm.cpp are added to the project file.
alarm.h is included within pvapp.h .

