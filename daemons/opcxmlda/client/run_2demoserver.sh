#!/bin/bash
./opcxmlda_client http://opcxml.demo-this.com/XmlDaSampleServer/Service.asmx GetStatus -debug 
#./opcxmlda_client http://opcxml.demo-this.com/XmlDaSampleServer/Service.asmx Browse > murx2.itemlist 
./opcxmlda_client http://opcxml.demo-this.com/XmlDaSampleServer/Service.asmx Run -itemlist=murx.itemlist -debug 

