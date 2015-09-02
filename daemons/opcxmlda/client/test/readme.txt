Test with 
./opcxmlda_client http://opcxml.demo-this.com/XmlDaSampleServer/Service.asmx Browse

########################################
nb5lehrig:/home/lehrig/temp/tcpdump # tcpdump -A -i enp9s0 -t -q -s 0 "host 88.146.100.88"
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on enp9s0, link-type EN10MB (Ethernet), capture size 262144 bytes
IP nb5lehrig.36748 > host-100-88.pldata.cz.http: tcp 0
E..<..@.@.......X.dX...P.I........r..H.........
.)..........
IP host-100-88.pldata.cz.http > nb5lehrig.36748: tcp 0
E..<R.@.u.3.X.dX.....P....E+.I.... .c..............
        I...)..
IP nb5lehrig.36748 > host-100-88.pldata.cz.http: tcp 0
E..4..@.@.......X.dX...P.I....E,.....@.....
.).\    I..
IP nb5lehrig.36748 > host-100-88.pldata.cz.http: tcp 47
E..c..@.@.......X.dX...P.I....E,.....o.....
.).\    I..POST /XmlDaSampleServer/Service.asmx HTTP/1.1

IP host-100-88.pldata.cz.http > nb5lehrig.36748: tcp 0
E..4R.@.u.3.X.dX.....P....E,.J.............
        I...).\
IP nb5lehrig.36748 > host-100-88.pldata.cz.http: tcp 509
E..1..@.@.......X.dX...P.J....E,.....=.....
.).h    I..Host: opcxml.demo-this.com
Date: Mon, 31 Aug 2015 07:21:43 GMT
Content-Length: 364
Content-Type: text/xml
Connection: Close
SoapAction: 

<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"> <SOAP-ENV:Header/> <SOAP-ENV:Body>  <m:Browse xmlns:m="urn:examples">  </m:Browse> </SOAP-ENV:Body></SOAP-ENV:Envelope>
IP host-100-88.pldata.cz.http > nb5lehrig.36748: tcp 0
E..4R.@.u.3.X.dX.....P....E,.J.............
        I...).h
IP nb5lehrig.36748 > host-100-88.pldata.cz.http: tcp 0
E..4..@.@.......X.dX...P.J....E,.....@.....
.*
v       I..
IP host-100-88.pldata.cz.http > nb5lehrig.36748: tcp 0
E..4R.@.u.3.X.dX.....P....E,.J.............
        I...*
v
IP host-100-88.pldata.cz.http > nb5lehrig.36748: tcp 662
E...R.@.u.1<X.dX.....P....E,.J......R......
        I...*
vHTTP/1.1 500 Internal Server Error
Cache-Control: private
Content-Type: text/xml; charset=utf-8
Server: Microsoft-IIS/7.5
X-AspNet-Version: 2.0.50727
X-Powered-By: ASP.NET
Date: Mon, 31 Aug 2015 05:17:39 GMT
Connection: close
Content-Length: 405

<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema"><soap:Body><soap:Fault><faultcode>soap:Client</faultcode><faultstring>Server did not recognize the value of HTTP Header SOAPAction: .</faultstring><detail /></soap:Fault></soap:Body></soap:Envelope>
IP nb5lehrig.36748 > host-100-88.pldata.cz.http: tcp 0
E..(..@.@.......X.dX...P.J......P.......

########################################
Test with 
lehrig@nb5lehrig:~/Downloads/pyopc/PyOPC-0.1/samples/clients> python simple.py 
address='http://opcxml.demo-this.com/XmlDaSampleServer/Service.asmx'
########################################
IP nb5lehrig.37205 > host-100-88.pldata.cz.http: tcp 0
E..<a.@.@.Y.....X.dX.U.P.Ne.......r..H.........
............
IP host-100-88.pldata.cz.http > nb5lehrig.37205: tcp 0
E..<S.@.u.2.X.dX.....P.U'....Ne... ..g.............
	S......
IP nb5lehrig.37205 > host-100-88.pldata.cz.http: tcp 0
E..4a.@.@.Y.....X.dX.U.P.Ne.'........@.....
....	S..
IP nb5lehrig.37205 > host-100-88.pldata.cz.http: tcp 238
E.."a.@.@.X.....X.dX.U.P.Ne.'..............
....	S..POST /XmlDaSampleServer/Service.asmx HTTP/1.1
Host: opcxml.demo-this.com
Accept-Encoding: identity
Content-Length: 507
Content-Type: text/xml; charset="utf-8"
SOAPAction: "http://opcfoundation.org/webservices/XMLDA/1.0/GetStatus"


IP host-100-88.pldata.cz.http > nb5lehrig.37205: tcp 0
E..4S.@.u.2.X.dX.....P.U'....Nf.....]......
	S......
IP nb5lehrig.37205 > host-100-88.pldata.cz.http: tcp 507
E../a.@.@.W.....X.dX.U.P.Nf.'........;.....
....	S..<SOAP-ENV:Envelope xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ZSI="http://www.zolera.com/schemas/ZSI/" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"><SOAP-ENV:Header></SOAP-ENV:Header><SOAP-ENV:Body xmlns:ns1="http://opcfoundation.org/webservices/XMLDA/1.0/"><ns1:GetStatus ClientRequestHandle="ZSI_dDEr3P7EPK_GetStatus"></ns1:GetStatus></SOAP-ENV:Body></SOAP-ENV:Envelope>
IP host-100-88.pldata.cz.http > nb5lehrig.37205: tcp 1149
E...S.@.u..MX.dX.....P.U'....Nh............
	S......HTTP/1.1 200 OK
Cache-Control: private, max-age=0
Content-Type: text/xml; charset=utf-8
Server: Microsoft-IIS/7.5
X-AspNet-Version: 2.0.50727
X-Powered-By: ASP.NET
Date: Mon, 31 Aug 2015 07:09:02 GMT
Content-Length: 919

<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema"><soap:Body><GetStatusResponse xmlns="http://opcfoundation.org/webservices/XMLDA/1.0/"><GetStatusResult RcvTime="2015-08-31T09:09:02.37925+02:00" ReplyTime="2015-08-31T09:09:02.37925+02:00" ClientRequestHandle="ZSI_dDEr3P7EPK_GetStatus" RevisedLocaleID="en" ServerState="running" /><Status StartTime="2015-08-31T09:07:12.598+02:00" ProductVersion="2.0.1.0"><StatusInfo>running</StatusInfo><VendorInfo>OPC .NET API Sample Data Access Server</VendorInfo><SupportedLocaleIDs>en</SupportedLocaleIDs><SupportedLocaleIDs>fr</SupportedLocaleIDs><SupportedLocaleIDs>de</SupportedLocaleIDs><SupportedInterfaceVersions>XML_DA_Version_1_0</SupportedInterfaceVersions></Status></GetStatusResponse></soap:Body></soap:Envelope>
IP nb5lehrig.37205 > host-100-88.pldata.cz.http: tcp 0
E..4a.@.@.Y.....X.dX.U.P.Nh.'..U.....@.....
...C	S..
IP nb5lehrig.37205 > host-100-88.pldata.cz.http: tcp 0
E..4a.@.@.Y.....X.dX.U.P.Nh.'..U.....@.....
...K	S..
IP nb5lehrig.37206 > host-100-88.pldata.cz.http: tcp 0
E..<.0@.@..q....X.dX.V.P.[.{......r..H.........
...K........
IP host-100-88.pldata.cz.http > nb5lehrig.37205: tcp 0
E..4S.@.u.2.X.dX.....P.U'..U.Nh.....U......
	S.....K
IP nb5lehrig.37205 > host-100-88.pldata.cz.http: tcp 0
E..4a.@.@.Y.....X.dX.U.P.Nh.'..V.....@.....
....	S..
IP host-100-88.pldata.cz.http > nb5lehrig.37206: tcp 0
E..<S.@.u.2.X.dX.....P.V.e...[.|.. .p3.............
	S.....K
IP nb5lehrig.37206 > host-100-88.pldata.cz.http: tcp 0
E..4.1@.@..x....X.dX.V.P.[.|.e.......@.....
....	S..
IP nb5lehrig.37206 > host-100-88.pldata.cz.http: tcp 235
E....2@.@.......X.dX.V.P.[.|.e.......+.....
....	S..POST /XmlDaSampleServer/Service.asmx HTTP/1.1
Host: opcxml.demo-this.com
Accept-Encoding: identity
Content-Length: 521
Content-Type: text/xml; charset="utf-8"
SOAPAction: "http://opcfoundation.org/webservices/XMLDA/1.0/Browse"


IP host-100-88.pldata.cz.http > nb5lehrig.37206: tcp 0
E..4S.@.u.2.X.dX.....P.V.e...[.g.....~.....
	S.1....
IP nb5lehrig.37206 > host-100-88.pldata.cz.http: tcp 521
E..=.3@.@..m....X.dX.V.P.[.g.e.......I.....
....	S.1<SOAP-ENV:Envelope xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ZSI="http://www.zolera.com/schemas/ZSI/" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"><SOAP-ENV:Header></SOAP-ENV:Header><SOAP-ENV:Body xmlns:ns1="http://opcfoundation.org/webservices/XMLDA/1.0/"><ns1:Browse ClientRequestHandle="ZSI_dDEr3P7EPK_Browse" ReturnErrorText="true"></ns1:Browse></SOAP-ENV:Body></SOAP-ENV:Envelope>
IP host-100-88.pldata.cz.http > nb5lehrig.37206: tcp 1118
E...S.@.u..hX.dX.....P.V.e...[.p....h......
	S.9....HTTP/1.1 200 OK
Cache-Control: private, max-age=0
Content-Type: text/xml; charset=utf-8
Server: Microsoft-IIS/7.5
X-AspNet-Version: 2.0.50727
X-Powered-By: ASP.NET
Date: Mon, 31 Aug 2015 07:09:02 GMT
Content-Length: 888

<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema"><soap:Body><BrowseResponse xmlns="http://opcfoundation.org/webservices/XMLDA/1.0/"><BrowseResult RcvTime="2015-08-31T09:09:02.832375+02:00" ReplyTime="2015-08-31T09:09:02.832375+02:00" ClientRequestHandle="ZSI_dDEr3P7EPK_Browse" RevisedLocaleID="en" ServerState="running" /><Elements Name="Static" ItemPath="" ItemName="Static" IsItem="false" HasChildren="true" /><Elements Name="Dynamic" ItemPath="" ItemName="Dynamic" IsItem="false" HasChildren="true" /><Elements Name="DA20" ItemPath="DA20" ItemName="DA20" IsItem="false" HasChildren="true" /><Elements Name="DA30" ItemPath="DA30" ItemName="DA30" IsItem="false" HasChildren="true" /></BrowseResponse></soap:Body></soap:Envelope>
IP nb5lehrig.37206 > host-100-88.pldata.cz.http: tcp 0
E..4.4@.@..u....X.dX.V.P.[.p.e.	.....@.....
...		S.9
IP nb5lehrig.37206 > host-100-88.pldata.cz.http: tcp 0
E..4.5@.@..t....X.dX.V.P.[.p.e.	.....@.....
....	S.9
IP nb5lehrig.37207 > host-100-88.pldata.cz.http: tcp 0
E..<z.@.@.@.....X.dX.W.Ps#r.......r..H.........
............
IP host-100-88.pldata.cz.http > nb5lehrig.37206: tcp 0
E..4S.@.u.2.X.dX.....P.V.e.	.[.q...........
	S.B....
IP nb5lehrig.37206 > host-100-88.pldata.cz.http: tcp 0
E..4.6@.@..s....X.dX.V.P.[.q.e.
.....@.....
...W	S.B
IP host-100-88.pldata.cz.http > nb5lehrig.37207: tcp 0
E..<S.@.u.2.X.dX.....P.W....s#r... .,..............
	S.C....
IP nb5lehrig.37207 > host-100-88.pldata.cz.http: tcp 0
E..4z.@.@.@.....X.dX.W.Ps#r..........@.....
...^	S.C
IP nb5lehrig.37207 > host-100-88.pldata.cz.http: tcp 233
E...z.@.@.?.....X.dX.W.Ps#r..........).....
..._	S.CPOST /XmlDaSampleServer/Service.asmx HTTP/1.1
Host: opcxml.demo-this.com
Accept-Encoding: identity
Content-Length: 736
Content-Type: text/xml; charset="utf-8"
SOAPAction: "http://opcfoundation.org/webservices/XMLDA/1.0/Read"


IP host-100-88.pldata.cz.http > nb5lehrig.37207: tcp 0
E..4S.@.u.2.X.dX.....P.W....s#s.....x......
	S.^..._
IP nb5lehrig.37207 > host-100-88.pldata.cz.http: tcp 736
E...z.@.@.=.....X.dX.W.Ps#s.......... .....
..	t	S.^<SOAP-ENV:Envelope xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ZSI="http://www.zolera.com/schemas/ZSI/" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"><SOAP-ENV:Header></SOAP-ENV:Header><SOAP-ENV:Body xmlns:ns1="http://opcfoundation.org/webservices/XMLDA/1.0/"><ns1:Read><ns1:Options ClientRequestHandle="ZSI_dDEr3P7EPK_Read" LocaleID="en-us" ReturnErrorText="true" ReturnItemName="true" ReturnItemPath="true"></ns1:Options><ns1:ItemList><ns1:Items ClientItemHandle="ZSI_dDEr3P7EPK_ReadItem_0" ItemName="simple_item" MaxAge="500"></ns1:Items></ns1:ItemList></ns1:Read></SOAP-ENV:Body></SOAP-ENV:Envelope>
IP host-100-88.pldata.cz.http > nb5lehrig.37207: tcp 991
E...S.@.u...X.dX.....P.W....s#v............
	S.g..	tHTTP/1.1 200 OK
Cache-Control: private, max-age=0
Content-Type: text/xml; charset=utf-8
Server: Microsoft-IIS/7.5
X-AspNet-Version: 2.0.50727
X-Powered-By: ASP.NET
Date: Mon, 31 Aug 2015 07:09:02 GMT
Content-Length: 761

<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema"><soap:Body><ReadResponse xmlns="http://opcfoundation.org/webservices/XMLDA/1.0/"><ReadResult RcvTime="2015-08-31T09:09:03.2855+02:00" ReplyTime="2015-08-31T09:09:03.2855+02:00" ClientRequestHandle="ZSI_dDEr3P7EPK_Read" RevisedLocaleID="en" ServerState="running" /><RItemList><Items ItemName="simple_item" ClientItemHandle="ZSI_dDEr3P7EPK_ReadItem_0" ResultID="E_UNKNOWNITEMPATH" /></RItemList><Errors ID="E_UNKNOWNITEMPATH"><Text>The item path is no longer available in the server address space.</Text></Errors></ReadResponse></soap:Body></soap:Envelope>
IP nb5lehrig.37207 > host-100-88.pldata.cz.http: tcp 0
E..4z.@.@.@.....X.dX.W.Ps#v..........@.....
..	.	S.g
IP nb5lehrig.37207 > host-100-88.pldata.cz.http: tcp 0
E..4z.@.@.@.....X.dX.W.Ps#v..........@.....
..	.	S.g
IP host-100-88.pldata.cz.http > nb5lehrig.37207: tcp 0
E..4S.@.u.2.X.dX.....P.W....s#v.....px.....
	S.q..	.
IP nb5lehrig.37207 > host-100-88.pldata.cz.http: tcp 0
E..4z.@.@.@.....X.dX.W.Ps#v..........@.....
..
2	S.q


