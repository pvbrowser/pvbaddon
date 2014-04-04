//
// Qt binding class for pv functions
// begin: 03-mar-2011
//
#include "qtpvfunc.h"

// pv functions
int PV::lock()
{ 
  return ::pvlock(p);
}

int PV::unlock()
{ 
  return ::pvunlock(p);
}

int PV::system(const QString &command)
{ 
  return ::pvsystem(command.toUtf8());
}
 
int PV::SendVersion()
{ 
  return ::pvSendVersion(p);
}
 
int PV::XYAllocate(int n)
{ 
  return ::pvXYAllocate(p, n);
}

int PV::SetXY(int i, float x, float y)
{ 
  return ::pvSetXY(p, i, x, y);
}

int PV::InitInternal()
{ 
  return ::pvInitInternal(p);
}

int PV::Init(int ac, char **av)
{ 
  return ::pvInit(ac, av, p);
}

int PV::Accept()
{ 
  return ::pvAccept(p);
}

int PV::CreateThread(int s)
{ 
  return ::pvCreateThread(p, s);
}

int PV::GetInitialMask()
{ 
  return ::pvGetInitialMask(p);
}

int PV::SetCleanup(int (*cleanup)(void *), void *app_data)
{ 
  return ::pvSetCleanup(p, cleanup, app_data);
}

int PV::PollEvent(char *event)
{ 
  return ::pvPollEvent(p, event);
}

int PV::Wait(const QString &pattern)
{ 
  return ::pvWait(p, pattern.toUtf8());
}

int PV::GlUpdate(int id)
{ 
  return ::pvGlUpdate(p, id);
}

int PV::Sleep(int milliseconds)
{ 
  return ::pvSleep(milliseconds);
}

int PV::Warning(const QString &text)
{ 
  return ::pvWarning(p,text.toUtf8());
}

int PV::MainFatal(const QString &text)
{ 
  return ::pvMainFatal(p,text.toUtf8());
}

int PV::ThreadFatal(const QString &text)
{ 
  return ::pvThreadFatal(p,text.toUtf8());
}

int PV::ScreenHint(int w, int h)
{ 
  return ::pvScreenHint(p, w, h);
}

int PV::SetMouseShape(int shape)
{ 
  return ::pvSetMouseShape(p, shape);
}

int PV::SetWhatsThis(int id, const QString &text)
{ 
  return ::pvSetWhatsThis(p, id, text.toUtf8());
}

int PV::WhatsThisPrintf(int id, const QString &format, ...)
{
  char buf[MAX_PRINTF_LENGTH];

  va_list ap;
  const char *cptr = format.toUtf8();
  va_start(ap,cptr);
#ifdef PVWIN32
  _vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
#ifdef __VMS
  vsprintf(buf, cptr, ap);
#endif
#ifdef PVUNIX
  vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
  va_end(ap);
  int ret = ::pvWhatsThisPrintf(p, id, buf);
  return ret;
}

int PV::ClientCommand(const QString &command, const QString &filename)
{ 
  return ::pvClientCommand(p,command.toUtf8(), filename.toUtf8());
}

int PV::StartDefinition(int num_objects)
{ 
  return ::pvStartDefinition(p, num_objects);
}

int PV::QLayoutVbox(int id, int parent)
{ 
  return ::pvQLayoutVbox(p, id, parent);
}

int PV::QLayoutHbox(int id, int parent)
{ 
  return ::pvQLayoutHbox(p, id, parent);
}

int PV::QLayoutGrid(int id, int parent)
{ 
  return ::pvQLayoutGrid(p, id, parent);
}

int PV::QWidget(int id, int parent)
{ 
  return ::pvQWidget(p, id, parent);
}

int PV::QLabel(int id, int parent)
{ 
  return ::pvQLabel(p, id, parent);
}

int PV::QComboBox(int id, int parent, int editable, int policy)
{ 
  return ::pvQComboBox(p, id, parent, editable, policy);
}

int PV::QLineEdit(int id, int parent)
{ 
  return ::pvQLineEdit(p, id, parent);
}

int PV::QPushButton(int id, int parent)
{ 
  return ::pvQPushButton(p, id, parent);
}

int PV::QLCDNumber(int id, int parent, int numDigits, int segmentStyle, int mode)
{ 
  return ::pvQLCDNumber(p, id, parent, numDigits, segmentStyle, mode);
}

int PV::QSlider(int id, int parent, int minValue, int maxValue, int pageStep, int value, int orientation)
{ 
  return ::pvQSlider(p, id, parent, minValue, maxValue, pageStep, value, orientation);
}

int PV::QButtonGroup(int id, int parent, int columns, int orientation, const QString &title)
{ 
  return ::pvQButtonGroup(p, id, parent, columns, orientation, title.toUtf8());
}

int PV::QRadioButton(int id, int parent)
{ 
  return ::pvQRadioButton(p, id, parent);
}

int PV::QCheckBox(int id, int parent)
{ 
  return ::pvQCheckBox(p, id, parent);
}

int PV::QFrame(int id, int parent, int shape, int shadow, int line_width, int margin)
{ 
  return ::pvQFrame(p, id, parent, shape, shadow, line_width, margin);
}

int PV::QDraw(int id, int parent)
{ 
  return ::pvQDraw(p, id, parent);
}

int PV::QImage(int id, int parent, const QString &imagename, int *w, int *h, int *depth)
{ 
  return ::pvQImage(p, id, parent, imagename.toUtf8(), w, h, depth);
}

int PV::QGL(int id, int parent)
{ 
  return ::pvQGL(p, id, parent);
}

int PV::QTabWidget(int id, int parent)
{ 
  return ::pvQTabWidget(p, id, parent);
}

int PV::QToolBox(int id, int parent)
{ 
  return ::pvQToolBox(p, id, parent);
}

int PV::QGroupBox(int id, int parent, int columns, int orientation, const QString &title)
{ 
  return ::pvQGroupBox(p, id, parent, columns, orientation, title.toUtf8());
}

int PV::QListBox(int id, int parent)
{ 
  return ::pvQListBox(p, id, parent);
}

int PV::QTable(int id, int parent, int rows, int columns)
{ 
  return ::pvQTable(p, id, parent, rows, columns);
}

int PV::QSpinBox(int id, int parent, int min, int max, int step)
{ 
  return ::pvQSpinBox(p, id, parent, min, max, step);
}

int PV::QDial(int id, int parent, int min, int max, int page_step, int value)
{ 
  return ::pvQDial(p, id, parent, min, max, page_step, value);
}

int PV::QProgressBar(int id, int parent, int total_steps, int orientation)
{ 
  return ::pvQProgressBar(p, id, parent, total_steps, orientation);
}

int PV::QMultiLineEdit(int id, int parent, int editable, int max_lines)
{ 
  return ::pvQMultiLineEdit(p, id, parent, editable, max_lines);
}

int PV::QTextBrowser(int id, int parent)
{ 
  return ::pvQTextBrowser(p, id, parent);
}

int PV::QListView(int id, int parent)
{ 
  return ::pvQListView(p, id, parent);
}

int PV::QIconView(int id, int parent)
{ 
  return ::pvQIconView(p, id, parent);
}

int PV::QVtkTclWidget(int id, int parent)
{ 
  return ::pvQVtkTclWidget(p, id, parent);
}

int PV::QwtPlotWidget(int id, int parent, int nCurves, int nMarker)
{ 
  return ::pvQwtPlotWidget(p, id, parent, nCurves, nMarker);
}

int PV::QwtScale(int id, int parent, int pos)
{ 
  return ::pvQwtScale(p, id, parent, pos);
}

int PV::QwtThermo(int id, int parent)
{ 
  return ::pvQwtThermo(p, id, parent);
}

int PV::QwtKnob(int id, int parent)
{ 
  return ::pvQwtKnob(p, id, parent);
}

int PV::QwtCounter(int id, int parent)
{ 
  return ::pvQwtCounter(p, id, parent);
}

int PV::QwtWheel(int id, int parent)
{ 
  return ::pvQwtWheel(p, id, parent);
}

int PV::QwtSlider(int id, int parent)
{ 
  return ::pvQwtSlider(p, id, parent);
}

int PV::QwtDial(int id, int parent)
{ 
  return ::pvQwtDial(p, id, parent);
}

int PV::QwtCompass(int id, int parent)
{ 
  return ::pvQwtCompass(p, id, parent);
}

int PV::QwtAnalogClock(int id, int parent)
{ 
  return ::pvQwtAnalogClock(p, id, parent);
}

int PV::QDateEdit(int id, int parent)
{ 
  return ::pvQDateEdit(p, id, parent);
}

int PV::QTimeEdit(int id, int parent)
{ 
  return ::pvQTimeEdit(p, id, parent);
}

int PV::QDateTimeEdit(int id, int parent)
{ 
  return ::pvQDateTimeEdit(p, id, parent);
}

int PV::EndDefinition()
{ 
  return ::pvEndDefinition(p);
}

int PV::AddWidgetOrLayout(int id, int item, int row, int col)
{ 
  return ::pvAddWidgetOrLayout(p, id, item, row, col);
}

int PV::AddStretch(int id, int param)
{ 
  return ::pvAddStretch(p, id, param);
}

int PV::TabOrder(int id1, int id2)
{ 
  return ::pvTabOrder(p, id1, id2);
}

int PV::DeleteWidget(int id)
{ 
  return ::pvDeleteWidget(p, id);
}

int PV::SetCaption(const QString &text)
{ 
  return ::pvSetCaption(p,text.toUtf8());
}

int PV::PlaySound(const QString &filename)
{ 
  return ::pvPlaySound(p,filename.toUtf8());
}

int PV::Beep()
{ 
  return ::pvBeep(p);
}

int PV::StatusMessage(int r, int g, int b, const QString &format, ...)
{ 
  char buf[MAX_PRINTF_LENGTH];

  va_list ap;
  const char *cptr = format.toUtf8();
  va_start(ap,cptr);
#ifdef PVWIN32
  _vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
#ifdef __VMS
  vsprintf(buf, cptr, ap);
#endif
#ifdef PVUNIX
  vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
  va_end(ap);
  int ret = ::pvStatusMessage(p, r, g, b, buf);
  return ret;
}

int PV::ToolTip(int id, const QString &text)
{ 
  return ::pvToolTip(p, id, text.toUtf8());
}

int PV::SetText(int id, const QString &text)
{ 
  return ::pvSetText(p, id, text.toUtf8());
}

int PV::Printf(int id, const QString &format, ...)
{ 
  char buf[MAX_PRINTF_LENGTH];

  va_list ap;
  const char *cptr = format.toUtf8();
  va_start(ap,cptr);
#ifdef PVWIN32
  _vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
#ifdef __VMS
  vsprintf(buf, cptr, ap);
#endif
#ifdef PVUNIX
  vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
  va_end(ap);
  int ret = ::pvSetText(p, id, buf);
  return ret;
}

int PV::SetValue(int id, int value)
{ 
  return ::pvSetValue(p, id, value);
}

int PV::Clear(int id)
{ 
  return ::pvClear(p, id);
}

int PV::ChangeItem(int id, int index, const QString &bmp_file, const QString &text, int download_icon)
{ 
  return ::pvChangeItem(p, id, index, bmp_file.toUtf8(), text.toUtf8(), download_icon);
}

int PV::InsertItem(int id, int index, const QString &bmp_file, const QString &text, int download_icon)
{ 
  return ::pvInsertItem(p, id, index, bmp_file.toUtf8(), text.toUtf8(), download_icon);
}

int PV::RemoveItem(int id, int index)
{ 
  return ::pvRemoveItem(p, id, index);
}

int PV::RemoveItemByName(int id, const QString &name)
{ 
  return ::pvRemoveItemByName(p, id, name.toUtf8());
}

int PV::AddColumn(int id, const QString &text, int size)
{ 
  return ::pvAddColumn(p, id, text.toUtf8(), size);
}

int PV::SetTableText(int id, int x, int y, const QString &text)
{ 
  return ::pvSetTableText(p, id, x, y, text.toUtf8());
}

int PV::SetTableButton(int id, int x, int y, const QString &text)
{ 
  return ::pvSetTableButton(p, id, x, y, text.toUtf8());
}

int PV::SetTableCheckBox(int id, int x, int y, int state, const QString &text)
{ 
  return ::pvSetTableCheckBox(p, id, x, y, state, text.toUtf8());
}

int PV::SetTableComboBox(int id, int x, int y, int editable, const QString &textlist)
{ 
  return ::pvSetTableComboBox(p, id, x, y, editable, textlist.toUtf8());
}

int PV::SetTableLabel(int id, int x, int y, const QString &text)
{ 
  return ::pvSetTableLabel(p, id, x, y, text.toUtf8());
}

int PV::TablePrintf(int id, int x, int y, const QString &format, ...)
{ 
  char buf[MAX_PRINTF_LENGTH];

  va_list ap;
  const char *cptr = format.toUtf8();
  va_start(ap,cptr);
#ifdef PVWIN32
  _vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
#ifdef __VMS
  vsprintf(buf, cptr, ap);
#endif
#ifdef PVUNIX
  vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
  va_end(ap);
  int ret = ::pvSetTableText(p, id, x, y, buf);
  return ret;
}

int PV::SetTableTextAlignment(int id, int x, int y, int alignment)
{ 
  return ::pvSetTableTextAlignment(p, id, x, y, alignment);
}

int PV::Mysqldump(int id, const QString &command)
{ 
  return ::pvMysqldump(p, id, command.toUtf8());
}

int PV::CSVdump(int id, const QString &filename, char delimitor)
{ 
  return ::pvCSVdump(p, id, filename.toUtf8(), delimitor);
}

int PV::CSVcreate(const QString &command, const QString &filename)
{ 
  return ::pvCSVcreate(p, command.toUtf8(), filename.toUtf8());
}

int PV::CSV(int id, const QString &command, char delimitor)
{ 
  return ::pvCSV(p, id, command.toUtf8(), delimitor);
}

int PV::SetListViewText(int id, const QString &path, int column, const QString &text)
{ 
  return ::pvSetListViewText(p, id, path.toUtf8(), column, text.toUtf8());
}

int PV::ListViewPrintf(int id, const QString &path, int column, const QString &format, ...)
{ 
  char buf[MAX_PRINTF_LENGTH];

  va_list ap;
  const char *cptr = format.toUtf8();
  va_start(ap,cptr);
#ifdef PVWIN32
  _vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
#ifdef __VMS
  vsprintf(buf, cptr, ap);
#endif
#ifdef PVUNIX
  vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
  va_end(ap);
  int ret = ::pvSetListViewText(p, id, path.toUtf8(), column, buf);
  return ret;
}

int PV::ListViewSetSelected(int id, const QString &path, int column, int selected)
{ 
  return ::pvListViewSetSelected(p, id, path.toUtf8(), column, selected);
}

int PV::ListBoxSetSelected(int id, int index, int selected)
{ 
  return ::pvListBoxSetSelected(p, id, index, selected);
}

int PV::SetColumnWidth(int id, int column, int width)
{ 
  return ::pvSetColumnWidth(p, id, column, width);
}

int PV::SetRowHeight(int id, int row, int height)
{ 
  return ::pvSetRowHeight(p, id, row, height);
}

int PV::SetWordWrap(int id, int wrap)
{ 
  return ::pvSetWordWrap(p, id, wrap);
}

int PV::SetPixmap(int id, const QString &bmp_file, int download_icon)
{ 
  return ::pvSetPixmap(p, id, bmp_file.toUtf8(), download_icon);
}

int PV::SetTablePixmap(int id, int x, int y, const QString &bmp_file, int download_icon)
{ 
  return ::pvSetTablePixmap(p, id, x, y, bmp_file.toUtf8(), download_icon);
}

int PV::SetSource(int id, const QString &html_file)
{ 
  return ::pvSetSource(p, id, html_file.toUtf8());
}

int PV::SetImage(int id, const QString &filename)
{ 
  return ::pvSetImage(p, id, filename.toUtf8());
}

int PV::SetBackgroundColor(int id, int r, int g, int b)
{ 
  return ::pvSetBackgroundColor(p, id, r, g, b);
}

int PV::SetPaletteBackgroundColor(int id, int r, int g, int b)
{ 
  return ::pvSetPaletteBackgroundColor(p, id, r, g, b);
}

int PV::SetPaletteForegroundColor(int id, int r, int g, int b)
{ 
  return ::pvSetPaletteForegroundColor(p, id, r, g, b);
}

int PV::SetFontColor(int id, int r, int g, int b)
{ 
  return ::pvSetFontColor(p, id, r, g, b);
}

int PV::SetFont(int id, const QString &family, int pointsize, int bold, int italic , int underline, int strikeout)
{ 
  return ::pvSetFont(p, id, family.toUtf8(), pointsize, bold, italic , underline, strikeout);
}

int PV::DisplayNum(int id, int num)
{ 
  return ::pvDisplayNum(p, id, num);
}

int PV::DisplayFloat(int id, float val)
{ 
  return ::pvDisplayFloat(p, id, val);
}

int PV::DisplayStr(int id, const QString &str)
{ 
  return ::pvDisplayStr(p, id, str.toUtf8());
}

int PV::AddTab(int id, int id_child, const QString &str)
{ 
  return ::pvAddTab(p, id, id_child, str.toUtf8());
}

int PV::SetListViewPixmap(int id, const QString &path, const QString &bmp_file, int column, int download_icon)
{ 
  return ::pvSetListViewPixmap(p, id, path.toUtf8(), bmp_file.toUtf8(), column, download_icon);
}

int PV::RemoveListViewItem(int id, const QString &path)
{ 
  return ::pvRemoveListViewItem(p, id, path.toUtf8());
}

int PV::RemoveIconViewItem(int id, const QString &text)
{ 
  return ::pvRemoveIconViewItem(p, id, text.toUtf8());
}

int PV::SetIconViewItem(int id, const QString &bmp_file, const QString &text, int download_icon)
{ 
  return ::pvSetIconViewItem(p, id, bmp_file.toUtf8(), text.toUtf8(), download_icon);
}

int PV::SetDateOrder(int id, int order)
{ 
  return ::pvSetDateOrder(p, id, order);
}

int PV::SetDate(int id, int year, int month, int day)
{ 
  return ::pvSetDate(p, id, year, month, day);
}

int PV::SetMinDate(int id, int year, int month, int day)
{ 
  return ::pvSetMinDate(p, id, year, month, day);
}

int PV::SetMaxDate(int id, int year, int month, int day)
{ 
  return ::pvSetMaxDate(p, id, year, month, day);
}

int PV::SetTime(int id, int hour, int minute, int second, int msec)
{ 
  return ::pvSetTime(p, id, hour, minute, second, msec);
}

int PV::SetMinTime(int id, int hour, int minute, int second, int msec)
{ 
  return ::pvSetMinTime(p, id, hour, minute, second, msec);
}

int PV::SetMaxTime(int id, int hour, int minute, int second, int msec)
{ 
  return ::pvSetMaxTime(p, id, hour, minute, second, msec);
}

int PV::EnsureCellVisible(int id, int row, int col)
{ 
  return ::pvEnsureCellVisible(p, id, row, col);
}

int PV::MoveCursor(int id, int cursor)
{ 
  return ::pvMoveCursor(p, id, cursor);
}

int PV::ScrollToAnchor(int id, const QString &anchor)
{ 
  return ::pvScrollToAnchor(p, id, anchor.toUtf8());
}

int PV::SetZoomFactor(int id, float factor)
{ 
  return ::pvSetZoomFactor(p, id, factor);
}

int PV::Text(int id)
{ 
  return ::pvText(p, id);
}

int PV::RequestGeometry(int id)
{ 
  return ::pvRequestGeometry(p, id);
}

int PV::RequestParentWidgetId(int id)
{ 
  return ::pvRequestParentWidgetId(p, id);
}

int PV::Selection(int id)
{ 
  return ::pvSelection(p, id);
}

int PV::RequestSvgBoundsOnElement(int id, const QString &objectname)
{ 
  return ::pvRequestSvgBoundsOnElement(p, id, objectname.toUtf8());
}

int PV::RequestSvgMatrixForElement(int id, const QString &objectname)
{ 
  return ::pvRequestSvgMatrixForElement(p, id, objectname.toUtf8());
}

int PV::MoveContent(int id, int pos)
{ 
  return ::pvMoveContent(p, id, pos);
}

int PV::SetGeometry(int id, int x, int y, int w, int h)
{ 
  return ::pvSetGeometry(p, id, x, y, w, h);
}

int PV::SetMinSize(int id, int w, int h)
{ 
  return ::pvSetMinSize(p, id, w, h);
}

int PV::SetMaxSize(int id, int w, int h)
{ 
  return ::pvSetMaxSize(p, id, w, h);
}

int PV::SetAlignment(int id, int alignment)
{ 
  return ::pvSetAlignment(p, id, alignment);
}

int PV::SetChecked(int id, int state)
{ 
  return ::pvSetChecked(p, id, state);
}

int PV::Move(int id, int x, int y)
{ 
  return ::pvMove(p, id, x, y);
}

int PV::Resize(int id, int w, int h)
{ 
  return ::pvResize(p, id, w, h);
}

int PV::Hide(int id)
{ 
  return ::pvHide(p, id);
}

int PV::Show(int id)
{ 
  return ::pvShow(p, id);
}

int PV::SetParent(int id, int id_parent)
{ 
  return ::pvSetParent(p, id, id_parent);
}

int PV::SetMultiSelection(int id, int mode)
{ 
  return ::pvSetMultiSelection(p, id, mode);
}

int PV::SetEchoMode(int id, int mode)
{ 
  return ::pvSetEchoMode(p, id, mode);
}

int PV::SetEditable(int id, int editable)
{ 
  return ::pvSetEditable(p, id, editable);
}

int PV::SetEnabled(int id, int enabled)
{ 
  return ::pvSetEnabled(p, id, enabled);
}

int PV::TableSetEnabled(int id, int x, int y, int enabled)
{ 
  return ::pvTableSetEnabled(p, id, x, y, enabled);
}

int PV::TableSetHeaderResizeEnabled(int id, int horizontal ,int enabled, int section)
{ 
  return ::pvTableSetHeaderResizeEnabled(p, id, horizontal , enabled, section);
}

int PV::SetSorting(int id, int column, int mode)
{ 
  return ::pvSetSorting(p, id, column, mode);
}

int PV::SetTabPosition(int id, int pos)
{ 
  return ::pvSetTabPosition(p, id, pos);
}

int PV::SetNumRows(int id, int num)
{ 
  return ::pvSetNumRows(p, id, num);
}

int PV::SetNumCols(int id, int num)
{ 
  return ::pvSetNumCols(p, id, num);
}

int PV::InsertRows(int id, int row, int count)
{ 
  return ::pvInsertRows(p, id, row, count);
}

int PV::InsertColumns(int id, int col, int count)
{ 
  return ::pvInsertColumns(p, id, col, count);
}

int PV::RemoveRow(int id, int row)
{ 
  return ::pvRemoveRow(p, id, row);
}

int PV::RemoveColumn(int id, int col)
{ 
  return ::pvRemoveColumn(p, id, col);
}

int PV::SetCurrentItem(int id, int index)
{ 
  return ::pvSetCurrentItem(p, id, index);
}

int PV::SetTimeEditDisplay(int id, int hour, int minute, int second, int ampm)
{ 
  return ::pvSetTimeEditDisplay(p, id, hour, minute, second, ampm);
}

int PV::ListViewEnsureVisible(int id, const QString &path)
{ 
  return ::pvListViewEnsureVisible(p, id, path.toUtf8());
}

int PV::ListViewSetOpen(int id, const QString &path, int open)
{ 
  return ::pvListViewSetOpen(p, id, path.toUtf8(), open);
}

int PV::ListViewSetHidden(int id, int column, int hidden)
{ 
  return ::pvListViewSetHidden(p, id, column, hidden);
}

int PV::ListViewSetStandardPopupMenu(int id, int standard_menu)
{ 
  return ::pvListViewSetStandardPopupMenu(p, id, standard_menu);
}

int PV::SetStyle(int id, int shape, int shadow, int line_width, int margin)
{ 
  return ::pvSetStyle(p, id, shape, shadow, line_width, margin);
}

int PV::SetMovie(int id, int background, const QString &filename)
{ 
  return ::pvSetMovie(p, id, background, filename.toUtf8());
}

int PV::MovieControl(int id, int step)
{ 
  return ::pvMovieControl(p, id, step);
}

int PV::MovieSpeed(int id, int speed)
{ 
  return ::pvMovieSpeed(p, id, speed);
}

int PV::VtkTcl(int id, const QString &tcl_command)
{ 
  return ::pvVtkTcl(p, id, tcl_command.toUtf8());
}

int PV::VtkTclPrintf(int id, const QString &format, ...)
{ 
  char buf[MAX_PRINTF_LENGTH];

  va_list ap;
  const char *cptr = format.toUtf8();
  va_start(ap, cptr);
#ifdef PVWIN32
  _vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
#ifdef __VMS
  vsprintf(buf, cptr, ap);
#endif
#ifdef PVUNIX
  vsnprintf(buf, MAX_PRINTF_LENGTH - 1, cptr, ap);
#endif
  va_end(ap);
  int ret = ::pvVtkTcl(p, id, buf);
  return ret;
}

int PV::VtkTclScript(int id, const QString &filename)
{ 
  return ::pvVtkTclScript(p, id, filename.toUtf8());
}

int PV::Hyperlink(const QString &link)
{ 
  return ::pvHyperlink(p,link.toUtf8());
}

int PV::SendUserEvent(int id, const QString &text)
{ 
  return ::pvSendUserEvent(p, id, text.toUtf8());
}

int PV::WriteFile(const QString &filename, int width, int height)
{ 
  return ::pvWriteFile(p, filename.toUtf8(), width, height);
}

int PV::CloseFile()
{ 
  return ::pvCloseFile(p);
}

int PV::GetText(const QString &command, QString *text)
{ 
  char txt[MAX_EVENT_LENGTH + 1];
  int ret = pvGetText(command.toUtf8(), txt);
  *text = txt;
  return ret;
}

int PV::ParseEvent(const QString &event, int *id, QString *text)
{ 
  char txt[MAX_EVENT_LENGTH + 1];
  int ret =  pvParseEvent(event.toUtf8(), id, txt);
  *text = txt;
  return ret;
}

int PV::CopyToClipboard(int id)
{ 
  return ::pvCopyToClipboard(p, id);
}

int PV::Print(int id)
{ 
  return ::pvPrint(p, id);
}

int PV::Save(int id)
{ 
  return ::pvSave(p, id);
}

int PV::Save(int id, const QString &filename)
{ 
  return ::pvSave(p, id, filename.toUtf8());
}

int PV::SaveAsBmp(int id, const QString &filename)
{ 
  return ::pvSaveAsBmp(p, id, filename.toUtf8());
}

int PV::SendFile(const QString &filename)
{ 
  return ::pvSendFile(p,filename.toUtf8());
}

int PV::DownloadFileAs(const QString &filename, const QString &newname)
{ 
  return ::pvDownloadFileAs(p, filename.toUtf8(), newname.toUtf8());
}

int PV::DownloadFile(const QString &filename)
{ 
  return ::pvDownloadFile(p,filename.toUtf8());
}

int PV::ClearMessageQueue()
{ 
  return ::pvClearMessageQueue(p);
}

int PV::tcpsend(const QString &buf, int len)
{ 
  return ::pvtcpsend(p, buf.toUtf8(), len);
}

int PV::tcpsend_binary(const QString &buf, int len)
{ 
  return ::pvtcpsend_binary(p, buf.toUtf8(), len);
}

int PV::tcpreceive(char *buf, int maxlen)
{ 
  return ::pvtcpreceive(p, buf, maxlen);
}

int PV::tcpreceive_binary(char *buf, int maxlen)
{ 
  return ::pvtcpreceive_binary(p, buf, maxlen);
}

int PV::GlBegin(int id)
{ 
  return ::pvGlBegin(p, id);
}

int PV::SendOpenGL(const QString &filename, GLuint *listarray, int max_array, glFont *proportional, glFont *fixed)
{ 
  return ::pvSendOpenGL(p, filename.toUtf8(), listarray, max_array, proportional, fixed);
}

int PV::GlEnd()
{ 
  return ::pvGlEnd(p);
}

int PV::FileDialog(int id_return, int type)
{
  return ::pvFileDialog(p, id_return, type);
}

int PV::PopupMenu(int id_return, const QString &text)
{
  return ::pvPopupMenu(p, id_return, text.toUtf8());
}

int PV::MessageBox(int id_return, int type, const QString &text, int button0, int button1, int button2)
{
  return ::pvMessageBox(p, id_return, type, text.toUtf8(), button0, button1, button2);
}

int PV::InputDialog(int id_return, const QString &text, const QString &default_text)
{
  return ::pvInputDialog(p, id_return, text.toUtf8(), default_text.toUtf8());
}

int PV::RunModalDialog(int width, int height, int (*showMask)(PARAM *p), void *userData,int (*readData)(void *d), int (*showData)(PARAM *p, void *d), void *d)
{
  return ::pvRunModalDialog(p, width, height, showMask, userData, readData, showData, d);
}

int PV::RunModalDialogScript(int width, int height)
{ 
  return ::pvRunModalDialogScript(p, width, height); 
}

int PV::TerminateModalDialog()
{ 
  return ::pvTerminateModalDialog(p);
}

int PV::UpdateBaseWindow()
{ 
  return ::pvUpdateBaseWindow(p);
}

int PV::UpdateBaseWindowOnOff(int onoff)
{ 
  return ::pvUpdateBaseWindowOnOff(p, onoff);
}

int PV::AddDockWidget(const QString &title, int dock_id, int root_id, int allow_close, int floating, int allow_left, int allow_right, int allow_top, int allow_bottom)
{ 
  return ::pvAddDockWidget(p, title.toUtf8(), dock_id, root_id, allow_close, floating, allow_left, allow_right, allow_top, allow_bottom);
}

int PV::DeleteDockWidget(int dock_id, int delete_widget)
{ 
  return ::pvDeleteDockWidget(p, dock_id, delete_widget);
}

int PV::SetZoomX(int id, float zoom)
{ 
  return ::pvSetZoomX(p, id, zoom);
}

int PV::SetZoomY(int id, float zoom)
{ 
  return ::pvSetZoomY(p, id, zoom);
}

int PV::SetSelector(int id, int state)
{ 
  return ::pvSetSelector(p, id, state);
}

// g functions
int PV::glencode_set_param()
{ 
  return ::glencode_set_param(p);
}

int PV::getIntegers(const QString &text, IntegerArray *ia)
{ 
  return ::getIntegers(text.toUtf8(), ia);
}

int PV::getFloats(const QString &text, FloatArray *fa)
{ 
  return ::getFloats(text.toUtf8(), fa);
}

int PV::gWriteFile(const QString &file)
{ 
  return ::gWriteFile(file.toUtf8());
}

int PV::gCloseFile()
{ 
  return ::gCloseFile();
}

int PV::gBeginDraw(int id)
{ 
  return ::gBeginDraw(p, id);
}

int PV::gBox(int x, int y, int w, int h)
{ 
  return ::gBox(p, x, y, w, h);
}

int PV::gRect(int x, int y, int w, int h)
{ 
  return ::gRect(p, x, y, w, h);
}

int PV::gEndDraw()
{ 
  return ::gEndDraw(p);
}

int PV::gLineTo(int x, int y)
{ 
  return ::gLineTo(p, x, y);
}

int PV::gBufferedLine()
{ 
  return ::gBufferedLine(p);
}

int PV::gLine(float *x, float *y, int n)
{ 
  return ::gLine(p, x, y, n);
}

int PV::gMoveTo(int x, int y)
{ 
  return ::gMoveTo(p, x, y);
}

int PV::gRightYAxis( float start, float delta, float end, int draw)
{ 
  return ::gRightYAxis(p, start, delta, end, draw);
}

int PV::gSetColor(int r, int g, int b)
{ 
  return ::gSetColor(p, r, g, b);
}

int PV::gSetWidth(int w)
{ 
  return ::gSetWidth(p, w);
}

int PV::gSetStyle(int style)
{ 
  return ::gSetStyle(p, style);
}

int PV::gDrawArc(int x, int y, int w, int h, int start_angle, int angle_length)
{ 
  return ::gDrawArc(p, x, y, w, h, start_angle, angle_length);
}

int PV::gDrawPie(int x, int y, int w, int h, int start_angle, int angle_length)
{ 
  return ::gDrawPie(p, x, y, w, h, start_angle, angle_length);
}

int PV::gDrawPolygon(int *x, int *y, int n)
{ 
  return ::gDrawPolygon(p, x, y, n);
}

int PV::gSetFont(const QString &family, int size, int weight, int italic)
{ 
  return ::gSetFont(p,family.toUtf8(), size, weight, italic);
}

int PV::gSetLinestyle(int style)
{ 
  return ::gSetLinestyle(p, style);
}

int PV::gText(int x, int y, const QString &text, int alignment)
{ 
  return ::gText(p, x, y, text.toUtf8(), alignment);
}

int PV::gTextInAxis( float x, float y, const QString &text, int alignment)
{ 
  return ::gTextInAxis(p, x, y, text.toUtf8(), alignment);
}

int PV::gSetFloatFormat(const QString &text)
{ 
  return ::gSetFloatFormat(p, text.toUtf8());
}

int PV::gXAxis( float start, float delta, float end, int draw)
{ 
  return ::gXAxis(p, start, delta, end, draw);
}

int PV::gYAxis( float start, float delta, float end, int draw)
{ 
  return ::gYAxis(p, start, delta, end, draw);
}

int PV::gXGrid()
{ 
  return ::gXGrid(p);
}

int PV::gYGrid()
{ 
  return ::gYGrid(p);
}

int PV::gBoxWithText(int x, int y, int w, int h, int fontsize, const QString &xlabel, const QString &ylabel, const QString &rylabel)
{ 
  return ::gBoxWithText(p, x, y, w, h, fontsize, xlabel.toUtf8(), ylabel.toUtf8(), rylabel.toUtf8());
}

int PV::gComment(const QString &comment)
{ 
  return ::gComment(p, comment.toUtf8());
}

int PV::gPlaySVG(const QString &filename)
{ 
  return ::gPlaySVG(p, filename.toUtf8());
}

int PV::gSocketPlaySVG(const QString &svgstring)
{ 
  return ::gSocketPlaySVG(p, svgstring.toUtf8());
}

int PV::gTranslate( float x, float y)
{ 
  return ::gTranslate(p, x, y);
}

int PV::gRotate( float angle)
{ 
  return ::gRotate(p, angle);
}

int PV::gScale( float sx, float sy)
{ 
  return ::gScale(p, sx, sy);
}

int PV::getSvgBoundsOnElement(const QString &text, float *x, float *y, float *width, float *height)
{ 
  return ::getSvgBoundsOnElement(text.toUtf8(), x, y, width, height);
}

int PV::getSvgMatrixForElement(const QString &text, float *m11, float *m12, float *m21, float *m22, float *det, float *dx,  float *dy)
{ 
  return ::getSvgMatrixForElement(text.toUtf8(), m11, m12, m21, m22, det, dx, dy);
}

int PV::getGeometry(const QString &text, int *x, int *y, int *width, int *height)
{ 
  return ::getGeometry(text.toUtf8(), x, y, width, height);
}

int PV::getParentWidgetId(const QString &text, int *parent)
{ 
  return ::getParentWidgetId(text.toUtf8(), parent);
}

// qwt functions
int PV::qwtScaleSetTitle(int id, const QString &text)
{ 
  return ::qwtScaleSetTitle(p, id, text.toUtf8());
}

int PV::qwtScaleSetTitleColor(int id, int r, int g, int b)
{ 
  return ::qwtScaleSetTitleColor(p, id, r, g, b);
}

int PV::qwtScaleSetTitleFont(int id, const QString &family, int pointsize, int bold, int italic, int underline, int strikeout)
{ 
  return ::qwtScaleSetTitleFont(p, id, family.toUtf8(), pointsize, bold, italic, underline, strikeout);
}

int PV::qwtScaleSetTitleAlignment(int id, int flags)
{ 
  return ::qwtScaleSetTitleAlignment(p, id, flags);
}

int PV::qwtScaleSetBorderDist(int id, int start, int end)
{ 
  return ::qwtScaleSetBorderDist(p, id, start, end);
}

int PV::qwtScaleSetBaselineDist(int id, int bd)
{ 
  return ::qwtScaleSetBaselineDist(p, id, bd);
}

int PV::qwtScaleSetScaleDiv(int id, float lBound, float hBound, int maxMaj, int maxMin, int log, float step, int ascend)
{ 
  return ::qwtScaleSetScaleDiv(p, id, lBound, hBound, maxMaj, maxMin, log, step, ascend);
}

int PV::qwtScaleSetLabelFormat(int id, int f, int prec, int fieldWidth)
{ 
  return ::qwtScaleSetLabelFormat(p, id, f, prec, fieldWidth);
}

int PV::qwtScaleSetLabelAlignment(int id, int align)
{ 
  return ::qwtScaleSetLabelAlignment(p, id, align);
}

int PV::qwtScaleSetLabelRotation(int id, float rotation)
{ 
  return ::qwtScaleSetLabelRotation(p, id, rotation);
}

int PV::qwtScaleSetPosition(int id, int position)
{ 
  return ::qwtScaleSetPosition(p, id, position);
}

int PV::qwtThermoSetScale(int id, float min, float max, float step, int logarithmic)
{ 
  return ::qwtThermoSetScale(p, id, min, max, step, logarithmic);
}

int PV::qwtThermoSetOrientation(int id, int orientation, int position)
{ 
  return ::qwtThermoSetOrientation(p, id, orientation, position);
}

int PV::qwtThermoSetBorderWidth(int id, int width)
{ 
  return ::qwtThermoSetBorderWidth(p, id, width);
}

int PV::qwtThermoSetFillColor(int id, int r, int g, int b)
{ 
  return ::qwtThermoSetFillColor(p, id, r, g, b);
}

int PV::qwtThermoSetAlarmColor(int id, int r, int g, int b)
{ 
  return ::qwtThermoSetAlarmColor(p, id, r, g, b);
}

int PV::qwtThermoSetAlarmLevel(int id, float level)
{ 
  return ::qwtThermoSetAlarmLevel(p, id, level);
}

int PV::qwtThermoSetAlarmEnabled(int id, int tf)
{ 
  return ::qwtThermoSetAlarmEnabled(p, id, tf);
}

int PV::qwtThermoSetPipeWidth(int id, int width)
{ 
  return ::qwtThermoSetPipeWidth(p, id, width);
}

int PV::qwtThermoSetRange(int id, float vmin, float vmax, float step)
{ 
  return ::qwtThermoSetRange(p, id, vmin, vmax, step);
}

int PV::qwtThermoSetMargin(int id, int margin)
{ 
  return ::qwtThermoSetMargin(p, id, margin);
}

int PV::qwtThermoSetValue(int id, float value)
{ 
  return ::qwtThermoSetValue(p, id, value);
}

int PV::qwtKnobSetScale(int id, float min, float max, float step, int logarithmic)
{ 
  return ::qwtKnobSetScale(p, id, min, max, step, logarithmic);
}

int PV::qwtKnobSetMass(int id, float mass)
{ 
  return ::qwtKnobSetMass(p, id, mass);
}

int PV::qwtKnobSetOrientation(int id, int orientation)
{ 
  return ::qwtKnobSetOrientation(p, id, orientation);
}

int PV::qwtKnobSetReadOnly(int id, int rdonly)
{ 
  return ::qwtKnobSetReadOnly(p, id, rdonly);
}

int PV::qwtKnobSetKnobWidth(int id, int width)
{ 
  return ::qwtKnobSetKnobWidth(p, id, width);
}

int PV::qwtKnobSetTotalAngle(int id, float angle)
{ 
  return ::qwtKnobSetTotalAngle(p, id, angle);
}

int PV::qwtKnobSetBorderWidth(int id, int width)
{ 
  return ::qwtKnobSetBorderWidth(p, id, width);
}

int PV::qwtKnobSetSymbol(int id, int symbol)
{ 
  return ::qwtKnobSetSymbol(p, id, symbol);
}

int PV::qwtKnobSetValue(int id, float value)
{ 
  return ::qwtKnobSetValue(p, id, value);
}

int PV::qwtCounterSetStep(int id, float step)
{ 
  return ::qwtCounterSetStep(p, id, step);
}

int PV::qwtCounterSetMinValue(int id, float value)
{ 
  return ::qwtCounterSetMinValue(p, id, value);
}

int PV::qwtCounterSetMaxValue(int id, float value)
{ 
  return ::qwtCounterSetMaxValue(p, id, value);
}

int PV::qwtCounterSetStepButton1(int id, int n)
{ 
  return ::qwtCounterSetStepButton1(p, id, n);
}

int PV::qwtCounterSetStepButton2(int id, int n)
{ 
  return ::qwtCounterSetStepButton2(p, id, n);
}

int PV::qwtCounterSetStepButton3(int id, int n)
{ 
  return ::qwtCounterSetStepButton3(p, id, n);
}

int PV::qwtCounterSetNumButtons(int id, int n)
{ 
  return ::qwtCounterSetNumButtons(p, id, n);
}

int PV::qwtCounterSetIncSteps(int id, int button, int n)
{ 
  return ::qwtCounterSetIncSteps(p, id, button, n);
}

int PV::qwtCounterSetValue(int id, float value)
{ 
  return ::qwtCounterSetValue(p, id, value);
}

int PV::qwtWheelSetMass(int id, float mass)
{ 
  return ::qwtWheelSetMass(p, id, mass);
}

int PV::qwtWheelSetOrientation(int id, int orientation)
{ 
  return ::qwtWheelSetOrientation(p, id, orientation);
}

int PV::qwtWheelSetReadOnly(int id, int rdonly)
{ 
  return ::qwtWheelSetReadOnly(p, id, rdonly);
}

int PV::qwtWheelSetTotalAngle(int id, float angle)
{ 
  return ::qwtWheelSetTotalAngle(p, id, angle);
}

int PV::qwtWheelSetTickCnt(int id, int cnt)
{ 
  return ::qwtWheelSetTickCnt(p, id, cnt);
}

int PV::qwtWheelSetViewAngle(int id, float angle)
{ 
  return ::qwtWheelSetViewAngle(p, id, angle);
}

int PV::qwtWheelSetInternalBorder(int id, int width)
{ 
  return ::qwtWheelSetInternalBorder(p, id, width);
}

int PV::qwtWheelSetWheelWidth(int id, int width)
{ 
  return ::qwtWheelSetWheelWidth(p, id, width);
}

int PV::qwtWheelSetValue(int id, float value)
{ 
  return ::qwtWheelSetValue(p, id, value);
}

int PV::qwtSliderSetScale(int id, float min, float max, float step, int logarithmic)
{ 
  return ::qwtSliderSetScale(p, id, min, max, step, logarithmic);
}

int PV::qwtSliderSetMass(int id, float mass)
{ 
  return ::qwtSliderSetMass(p, id, mass);
}

int PV::qwtSliderSetOrientation(int id, int orientation)
{ 
  return ::qwtSliderSetOrientation(p, id, orientation);
}

int PV::qwtSliderSetReadOnly(int id, int rdonly)
{ 
  return ::qwtSliderSetReadOnly(p, id, rdonly);
}

int PV::qwtSliderSetBgStyle(int id, int style)
{ 
  return ::qwtSliderSetBgStyle(p, id, style);
}

int PV::qwtSliderSetScalePos(int id, int pos)
{ 
  return ::qwtSliderSetScalePos(p, id, pos);
}

int PV::qwtSliderSetThumbLength(int id, int length)
{ 
  return ::qwtSliderSetThumbLength(p, id, length);
}

int PV::qwtSliderSetThumbWidth(int id, int width)
{ 
  return ::qwtSliderSetThumbWidth(p, id, width);
}

int PV::qwtSliderSetBorderWidth(int id, int width)
{ 
  return ::qwtSliderSetBorderWidth(p, id, width);
}

int PV::qwtSliderSetMargins(int id, int x, int y)
{ 
  return ::qwtSliderSetMargins(p, id, x, y);
}

int PV::qwtSliderSetValue(int id, float value)
{ 
  return ::qwtSliderSetValue(p, id, value);
}

int PV::qwtCompassSetSimpleCompassRose(int id, int numThorns, int numThornLevels, float width)
{ 
  return ::qwtCompassSetSimpleCompassRose(p, id, numThorns, numThornLevels, width);
}

int PV::qwtCompassSetRange(int id, float vmin, float vmax, float step)
{ 
  return ::qwtCompassSetRange(p, id, vmin, vmax, step);
}

int PV::qwtCompassSetMass(int id, float mass)
{ 
  return ::qwtCompassSetMass(p, id, mass);
}

int PV::qwtCompassSetReadOnly(int id, int rdonly)
{ 
  return ::qwtCompassSetReadOnly(p, id, rdonly);
}

int PV::qwtCompassSetFrameShadow(int id, int shadow)
{ 
  return ::qwtCompassSetFrameShadow(p, id, shadow);
}

int PV::qwtCompassShowBackground(int id, int show)
{ 
  return ::qwtCompassShowBackground(p, id, show);
}

int PV::qwtCompassSetLineWidth(int id, int width)
{ 
  return ::qwtCompassSetLineWidth(p, id, width);
}

int PV::qwtCompassSetMode(int id, int mode)
{ 
  return ::qwtCompassSetMode(p, id, mode);
}

int PV::qwtCompassSetWrapping(int id, int wrap)
{ 
  return ::qwtCompassSetWrapping(p, id, wrap);
}

int PV::qwtCompassSetScale(int id, int maxMajIntv, int maxMinIntv, float step)
{ 
  return ::qwtCompassSetScale(p, id, maxMajIntv, maxMinIntv, step);
}

int PV::qwtCompassSetScaleArc(int id, float min, float max)
{ 
  return ::qwtCompassSetScaleArc(p, id, min, max);
}

int PV::qwtCompassSetOrigin(int id, float o)
{ 
  return ::qwtCompassSetOrigin(p, id, o);
}

int PV::qwtCompassSetNeedle(int id, int which, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3)
{ 
  return ::qwtCompassSetNeedle(p, id, which, r1, g1, b1, r2, g2, b2, r3, g3, b3);
}

int PV::qwtCompassSetValue(int id, float value)
{ 
  return ::qwtCompassSetValue(p, id, value);
}

int PV::qwtDialSetRange(int id, float vmin, float vmax, float step)
{ 
  return ::qwtDialSetRange(p, id, vmin, vmax, step);
}

int PV::qwtDialSetMass(int id, float mass)
{ 
  return ::qwtDialSetMass(p, id, mass);
}

int PV::qwtDialSetReadOnly(int id, int rdonly)
{ 
  return ::qwtDialSetReadOnly(p, id, rdonly);
}

int PV::qwtDialSetFrameShadow(int id, int shadow)
{ 
  return ::qwtDialSetFrameShadow(p, id, shadow);
}

int PV::qwtDialShowBackground(int id, int show)
{ 
  return ::qwtDialShowBackground(p, id, show);
}

int PV::qwtDialSetLineWidth(int id, int width)
{ 
  return ::qwtDialSetLineWidth(p, id, width);
}

int PV::qwtDialSetMode(int id, int mode)
{ 
  return ::qwtDialSetMode(p, id, mode);
}

int PV::qwtDialSetWrapping(int id, int wrap)
{ 
  return ::qwtDialSetWrapping(p, id, wrap);
}

int PV::qwtDialSetScale(int id, int maxMajIntv, int maxMinIntv, float step)
{ 
  return ::qwtDialSetScale(p, id, maxMajIntv, maxMinIntv, step);
}

int PV::qwtDialSetScaleArc(int id, float min, float max)
{ 
  return ::qwtDialSetScaleArc(p, id, min, max);
}

int PV::qwtDialSetOrigin(int id, float o)
{ 
  return ::qwtDialSetOrigin(p, id, o);
}

int PV::qwtDialSetNeedle(int id, int which, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3)
{ 
  return ::qwtDialSetNeedle(p, id, which, r1, g1, b1, r2, g2, b2, r3, g3, b3);
}

int PV::qwtDialSetValue(int id, float value)
{ 
  return ::qwtDialSetValue(p, id, value);
}

int PV::qwtAnalogClockSetTime(int id, int hour, int minute, int second)
{ 
  return ::qwtAnalogClockSetTime(p, id, hour, minute, second);
}

int PV::qwtAnalogClockSetMass(int id, float mass)
{ 
  return ::qwtAnalogClockSetMass(p, id, mass);
}

int PV::qwtAnalogClockSetReadOnly(int id, int rdonly)
{ 
  return ::qwtAnalogClockSetReadOnly(p, id, rdonly);
}

int PV::qwtAnalogClockSetFrameShadow(int id, int shadow)
{ 
  return ::qwtAnalogClockSetFrameShadow(p, id, shadow);
}

int PV::qwtAnalogClockShowBackground(int id, int show)
{ 
  return ::qwtAnalogClockShowBackground(p, id, show);
}

int PV::qwtAnalogClockSetLineWidth(int id, int width)
{ 
  return ::qwtAnalogClockSetLineWidth(p, id, width);
}

int PV::qwtAnalogClockSetMode(int id, int mode)
{ 
  return ::qwtAnalogClockSetMode(p, id, mode);
}

int PV::qwtAnalogClockSetWrapping(int id, int wrap)
{ 
  return ::qwtAnalogClockSetWrapping(p, id, wrap);
}

int PV::qwtAnalogClockSetScale(int id, int maxMajIntv, int maxMinIntv, float step)
{ 
  return ::qwtAnalogClockSetScale(p, id, maxMajIntv, maxMinIntv, step);
}

int PV::qwtAnalogClockSetScaleArc(int id, float min, float max)
{ 
  return ::qwtAnalogClockSetScaleArc(p, id, min, max);
}

int PV::qwtAnalogClockSetOrigin(int id, float o)
{ 
  return ::qwtAnalogClockSetOrigin(p, id, o);
}

int PV::qwtAnalogClockSetNeedle(int id, int which, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3)
{ 
  return ::qwtAnalogClockSetNeedle(p, id, which, r1, g1, b1, r2, g2, b2, r3, g3, b3);
}

int PV::qwtAnalogClockSetValue(int id, float value)
{ 
  return ::qwtAnalogClockSetValue(p, id, value);
}

// qpw functions
int PV::qpwSetCurveData(int id, int c, int count, double *x, double *y)
{ 
  return ::qpwSetCurveData(p, id, c, count, x, y);
}

int PV::qpwSetBufferedCurveData(int id, int c)
{ 
  return ::qpwSetBufferedCurveData(p, id, c);
}

int PV::qpwReplot(int id)
{ 
  return ::qpwReplot(p, id);
}

int PV::qpwSetTitle(int id, const QString &text)
{ 
  return ::qpwSetTitle(p, id, text.toUtf8());
}

int PV::qpwSetCanvasBackground(int id, int r, int g, int b)
{ 
  return ::qpwSetCanvasBackground(p, id, r, g, b);
}

int PV::qpwEnableOutline(int id, int val)
{ 
  return ::qpwEnableOutline(p, id, val);
}

int PV::qpwSetOutlinePen(int id, int r, int g, int b)
{ 
  return ::qpwSetOutlinePen(p, id, r, g, b);
}

int PV::qpwSetAutoLegend(int id, int val)
{ 
  return ::qpwSetAutoLegend(p, id, val);
}

int PV::qpwEnableLegend(int id, int val)
{ 
  return ::qpwEnableLegend(p, id, val);
}

int PV::qpwSetLegendPos(int id, int pos)
{ 
  return ::qpwSetLegendPos(p, id, pos);
}

int PV::qpwSetLegendFrameStyle(int id, int style)
{ 
  return ::qpwSetLegendFrameStyle(p, id, style);
}

int PV::qpwEnableGridXMin(int id)
{ 
  return ::qpwEnableGridXMin(p, id);
}

int PV::qpwSetGridMajPen(int id, int r, int g, int b, int style)
{ 
  return ::qpwSetGridMajPen(p, id, r, g, b, style);
}

int PV::qpwSetGridMinPen(int id, int r, int g, int b, int style)
{ 
  return ::qpwSetGridMinPen(p, id, r, g, b, style);
}

int PV::qpwEnableAxis(int id, int pos)
{ 
  return ::qpwEnableAxis(p, id, pos);
}

int PV::qpwSetAxisTitle(int id, int pos, const QString &text)
{ 
  return ::qpwSetAxisTitle(p, id, pos, text.toUtf8());
}

int PV::qpwSetAxisOptions(int id, int pos, int val)
{ 
  return ::qpwSetAxisOptions(p, id, pos, val);
}

int PV::qpwSetAxisMaxMajor(int id, int pos, int val)
{ 
  return ::qpwSetAxisMaxMajor(p, id, pos, val);
}

int PV::qpwSetAxisMaxMinor(int id, int pos, int val)
{ 
  return ::qpwSetAxisMaxMinor(p, id, pos, val);
}

int PV::qpwInsertCurve(int id, int index, const QString &text)
{ 
  return ::qpwInsertCurve(p, id, index, text.toUtf8());
}

int PV::qpwRemoveCurve(int id, int index)
{ 
  return ::qpwRemoveCurve(p, id, index);
}

int PV::qpwSetCurvePen(int id, int index, int r, int g, int b, int width, int style)
{ 
  return ::qpwSetCurvePen(p, id, index, r, g, b, width, style);
}

int PV::qpwSetCurveSymbol(int id, int index, int symbol, int r1, int g1, int b1, int r2, int g2, int b2, int w, int h)
{ 
  return ::qpwSetCurveSymbol(p, id, index, symbol, r1, g1, b1, r2, g2, b2, w, h);
}

int PV::qpwSetCurveYAxis(int id, int index, int pos)
{ 
  return ::qpwSetCurveYAxis(p, id, index, pos);
}

int PV::qpwInsertMarker(int id, int index)
{ 
  return ::qpwInsertMarker(p, id, index);
}

int PV::qpwSetMarkerLineStyle(int id, int index, int style)
{ 
  return ::qpwSetMarkerLineStyle(p, id, index, style);
}

int PV::qpwSetMarkerPos(int id, int index, float x, float y)
{ 
  return ::qpwSetMarkerPos(p, id, index, x, y);
}

int PV::qpwSetMarkerLabelAlign(int id, int index, int align)
{ 
  return ::qpwSetMarkerLabelAlign(p, id, index, align);
}

int PV::qpwSetMarkerPen(int id, int index, int r, int g, int b, int style)
{ 
  return ::qpwSetMarkerPen(p, id, index, r, g, b, style);
}

int PV::qpwSetMarkerLabel(int id, int number, const QString &text)
{ 
  return ::qpwSetMarkerLabel(p, id, number, text.toUtf8());
}

int PV::qpwSetMarkerFont(int id, int index, const QString &family, int size, int style)
{ 
  return ::qpwSetMarkerFont(p, id, index, family.toUtf8(), size, style);
}  

int PV::qpwSetMarkerSymbol(int id, int index, int symbol, int r1, int g1, int b1, int r2, int g2, int b2, int w, int h)
{ 
  return ::qpwSetMarkerSymbol(p, id, index, symbol, r1, g1, b1, r2, g2, b2, w, h);
}

int PV::qpwInsertLineMarker(int id, int index, const QString &text, int pos)
{ 
  return ::qpwInsertLineMarker(p, id, index, text.toUtf8(), pos);
}

int PV::qpwSetAxisScaleDraw(int id, int pos, const QString &text )
{ 
  return ::qpwSetAxisScaleDraw(p, id, pos, text.toUtf8());
}

int PV::qpwSetAxisScale(int id, int pos, float min, float max, float step)
{ 
  return ::qpwSetAxisScale(p, id, pos, min, max, step);
}

