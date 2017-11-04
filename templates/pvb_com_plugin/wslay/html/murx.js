  var command = "";
  var params;
  var payload;

  function onMessage(evt)
  {
    var ret;
    if(command == "")
    {
      params = parse(evt.data);
      command = params[0];
    }
    else
    {
      payload = evt.data;
    }
    ret = perhapsExecute(command) 
    if(ret == 1) command = ""; //if command has been executed then reset command
  }
