t <html>
t <head>
t  <title>Parking IT2R1</title>
t    <style>
t  h2 {
t    color: black;
t    font-family: calibri;
t    font-size: 300%;
t
t }
t td { 
t background-color: transparent;
t    color: white;
t }
t th { 
t background-color: transparent;
t    color: white;
t }
t tr { 
t    background-color: transparent;
t }
t a {
t    color: white;
t    font-family: calibri;
t    font-size: 200%;
t }
t p {
t    color: white;
t    font-family: calibri;
t }
t
t #footer {
t   position: absolute;
t  botom: 0;
t }
t
t
t </style> 
t </head>
t
t <body bgcolor="#34495E" leftmargin="0" topmargin="10" marginwidth=
t "0" marginheight="0">
t  <div align="center" style="width: 833; height: 470">
t    	<table style="border: 0px solid #40E0D0" height="384"
t    	cellspacing="20" cellpadding="0" width="815">
t      		<tbody>
t        		<tr bgcolor="#EEEEEE">
t          			<td style="border-bottom: 20px solid #40E0D0" valign=
t          			"bottom" nowrap height="70" margin="50" width="567">
t            		<h2 align="center"><font face="calibri" color=
t            		"#FFFFFF">IT2R1 Parking</font></h2>
t          			</td>
t
t        			<td style="border-bottom: 20px solid #40E0D0" valign=
t          			"center" nowrap height="73" width="160"><a href=
t          			"http://www.iut-cachan.u-psud.fr/fr/index.html"><img border="0" src="IT2R.png"
t          			align="left" width="151" height="47"></a></td>
t
t 					<td style="border-bottom: 0px solid #40E0D0" align=center vAlign=center noWrap width="70"> 
t   				<a href="index.htm"><img border="0" src="home.png" width="31" height="29"></a>
t  					</td>
t        		</tr>
t
t        		<tr>
t          			<td colspan="5" height="358" width="805" bgcolor="#E6E6FA">
t            			<div align="center">
t              				<center>
t                			<table width="90%" border="0">
t                  			<tbody>
t                    			<tr>
t                     				<td width="95%">		
t 										<p align="center"><img border="0" height="180" width="800"
t                         				src="parking.jpg"></a></p>
t
t 										<form action=adc.cgi method=post name=cgi>
t 										<input type=hidden value="adc" name=pg>
t 											<table border=0 width=99%><font size="4">
t 												<tr bgcolor=#FFFFFF>
t  													<th width=40%>Commande</th>
t  													<th width=60%>Valeur</th></tr>
# Cette partie contient les informations CGI qu'il va falloir traiter
t 												<tr>
t 													<td align="center">  Autonomie batterie : </td>
c b <td align="center"> %d %%</td></tr>
t 												<tr>
t 													<td align="center">  Places libres : </td>
c a <td align="center"><img src="%c.png"><img src="%c.png"></td></tr>					
t 												</font></table>
# Définition du bouton Rafraichir
t 										<p align=center>
t 											<input type=submit name=set value="Rafraîchir" id="sbm">
t 										</p>
t 										</form>
t       							</td>
t      							</tr>
t 							</tbody>
t 							</table>
t     						</center>
t    					</div>
t   				</td>
t  				</tr>
t 				</tbody></table>
t 	</div>
t 	 <footer>
t  <p align="left">&copy; IT2R1 IUT de Cachan by Julien BEHAR & Wassim El AZHARI</p>
t </footer> 
t </body>
t </html>
. End of script.
