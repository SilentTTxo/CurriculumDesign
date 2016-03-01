yearDo();
function yearDo(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = document.getElementById("year").value;
	document.getElementById("year").value="";
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			var tb = document.getElementById('yeardata');
			$("#yeardata tr:not(:eq(0))").remove();
			data = xmlhttp.responseText;
			data = eval(data);
			b = document.getElementById("yeardata");
			for(i=0;i<data.length;i++){
				newrow = '<tr><td>'+data[i][0]+'</td><td>'+data[i][1]+'</td><td><button class="btn btn-danger" onClick="yeardel('+data[i][0]+');return false;">删除</button></td></tr>'
				$("#yeardata tr:last").after(newrow);
			}
		}
	}
	xmlhttp.open("GET","data.php?cmd=yearadd&year="+data,true);
	xmlhttp.send();
}
function yeardel(ID){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			yearDo();
		}
	}
	xmlhttp.open("GET","data.php?cmd=yeardel&ID="+ID,true);
	xmlhttp.send();
}
//==================================college===============================================
function collegeSerch(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=collegeSerch&college="+document.getElementById("collegename").value+"&year="+document.getElementById("serch_year").value;
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			var tb = document.getElementById('collegedata');
			$("#collegedata tr:not(:eq(0))").remove();
			data = xmlhttp.responseText;
			data = eval(data);
			for(i=0;i<data.length;i++){
				newrow = '<tr><td>'+data[i][0]+'</td><td>'+data[i][1]+'</td><td>'+data[i][2]+'</td><td>'+data[i][3]+'</td><td><button class="btn btn-danger" onClick="collegedel('+data[i][0]+');return false;">删除</button></td></tr>'
				$("#collegedata tr:last").after(newrow);
			}
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function collegeAdd(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=collegeAdd&college="+document.getElementById("collegename").value+"&year="+document.getElementById("serch_year").value;
	document.getElementById("collegename").value="";
	document.getElementById("serch_year").value="";
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			if(xmlhttp.responseText!=""){
				alert(xmlhttp.responseText);
			}
			collegeSerch();
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function collegedel(ID){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById("collegename").value="";
			document.getElementById("serch_year").value="";
			collegeSerch();
		}
	}
	xmlhttp.open("GET","data.php?cmd=collegeDel&ID="+ID,true);
	xmlhttp.send();
}
//==================================major===============================================
function majorSerch(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=majorSerch&majorname="+document.getElementById("majorname").value+"&collegeID="+document.getElementById("collegeID").value;
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			var tb = document.getElementById('majordata');
			$("#majordata tr:not(:eq(0))").remove();
			data = xmlhttp.responseText;
			data = eval(data);
			for(i=0;i<data.length;i++){
				newrow = '<tr><td>'+data[i][0]+'</td><td>'+data[i][1]+'</td><td>'+data[i][2]+'</td><td>'+data[i][3]+'</td><td><button class="btn btn-danger" onClick="majordel('+data[i][0]+');return false;">删除</button></td></tr>'
				$("#majordata tr:last").after(newrow);
			}
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function majorAdd(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=majorAdd&majorname="+document.getElementById("majorname").value+"&collegeID="+document.getElementById("collegeID").value;
	document.getElementById("majorname").value="";
	document.getElementById("collegeID").value="";
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			if(xmlhttp.responseText!=""){
				alert(xmlhttp.responseText);
			}
			majorSerch();
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function majordel(ID){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById("majorname").value="";
			document.getElementById("collegeID").value="";
			majorSerch();
		}
	}
	xmlhttp.open("GET","data.php?cmd=majorDel&ID="+ID,true);
	xmlhttp.send();
}
//==================================class===============================================
function classSerch(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=classSerch&majorID="+document.getElementById("majorID").value;
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			var tb = document.getElementById('classdata');
			$("#classdata tr:not(:eq(0))").remove();
			data = xmlhttp.responseText;
			data = eval(data);
			for(i=0;i<data.length;i++){
				newrow = '<tr><td>'+data[i][0]+'</td><td>'+data[i][1]+'</td><td>'+data[i][2]+'</td><td><button class="btn btn-danger" onClick="classdel('+data[i][0]+');return false;">删除</button></td></tr>'
				$("#classdata tr:last").after(newrow);
			}
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function classAdd(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=classAdd&majorID="+document.getElementById("majorID").value;
	document.getElementById("majorID").value="";
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			if(xmlhttp.responseText!=""){
				alert(xmlhttp.responseText);
			}
			classSerch();
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function classdel(ID){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById("majorID").value="";
			classSerch();
		}
	}
	xmlhttp.open("GET","data.php?cmd=classDel&ID="+ID,true);
	xmlhttp.send();
}
//============================Student===============================
function StudentSerch(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=StudentSerch&StudentID="+document.getElementById("StudentID").value;
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			var tb = document.getElementById('studentdata');
			$("#studentdata tr:not(:eq(0))").remove();
			data = xmlhttp.responseText;
			data = eval(data);
			for(i=0;i<data.length;i++){
				time = data[i][3].split(" ");
				newrow = '<tr><td>'+data[i][0]+'</td><td>'+data[i][2]+'</td><td>'+data[i][1]+'</td><td>'+time[0]+'</td><td>'+data[i][4]+'</td><td>'+data[i][6]+'</td><td>'+data[i][5]+'</td></tr>'
				$("#studentdata tr:last").after(newrow);
			}
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function StudentAdd(){
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	data = "cmd=StudentAdd&name="+document.getElementById("S_StudentName").value+"&class="+document.getElementById("S_class").value+"&birth="+document.getElementById("S_birth").value+"&sex="+document.getElementById("S_sex").value+"&high="+document.getElementById("S_high").value+"&address="+document.getElementById("S_address").value;
	document.getElementById("majorID").value="";
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			if(xmlhttp.responseText!=""){
				alert(xmlhttp.responseText);
			}
			StudentSerch();
		}
	}
	xmlhttp.open("GET","data.php?"+data,true);
	xmlhttp.send();
}
function Studentdel(){
	ID = document.getElementById("StudentID").value;
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById("StudentID").value="";
			StudentSerch();
		}
	}
	xmlhttp.open("GET","data.php?cmd=StudentDel&ID="+ID,true);
	xmlhttp.send();
}
//canvas
function Find(){
	setTimeout(showHigh,200);
	setTimeout(showGirl,100);
}
function showHigh(){
	var HighData = {
		labels : [],
		datasets : [
		{
			label: "My Second dataset",
			fillColor : "rgba(151,187,205,0.2)",
			strokeColor : "rgba(151,187,205,1)",
			pointColor : "rgba(151,187,205,1)",
			pointStrokeColor : "#fff",
			pointHighlightFill : "#fff",
			pointHighlightStroke : "rgba(151,187,205,1)",
			data : []
		}
		]
	}
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			data = xmlhttp.responseText;
			data = eval(data);
			for(i=0;i<data.length;i++){
				HighData['labels'][i]=data[i][0]
				HighData['datasets'][0]['data'][i]=data[i][1];
			}
			var ctx = document.getElementById("High").getContext("2d");
			window.myLine = new Chart(ctx).Line(HighData, {
				responsive: true
			});
		}
	}
	xmlhttp.open("GET","data.php?cmd=getClassID",true);
	xmlhttp.send();
}
function showGirl(){
	var GirlData = {
		labels : [],
		datasets : [
		{
			fillColor : "rgba(220,220,220,0.5)",
			strokeColor : "rgba(220,220,220,0.8)",
			highlightFill: "rgba(220,220,220,0.75)",
			highlightStroke: "rgba(220,220,220,1)",
			data : []
		},
		{
			fillColor : "rgba(151,187,205,0.5)",
			strokeColor : "rgba(151,187,205,0.8)",
			highlightFill : "rgba(151,187,205,0.75)",
			highlightStroke : "rgba(151,187,205,1)",
			data : []
		}
		]

	}
	if (window.XMLHttpRequest){// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			data = xmlhttp.responseText;
			data = eval(data);
			y=0;
			for(i=0;i<data.length;i++){
				if(i>=1){
					if(data[i][0]!=data[i-1][0]) GirlData['labels'][y++]=data[i][0];
				}
				else GirlData['labels'][y++]=data[i][0];
				if(data[i][1]=="男") GirlData['datasets'][0]['data'][y-1]=data[i][2];
				else GirlData['datasets'][1]['data'][y-1]=data[i][2];
			}
			for(i=0;i<GirlData['labels'].length;i++){
				if(GirlData['datasets'][0]['data'][i]==null){
					GirlData['datasets'][0]['data'][i]=0;
				}
				if(GirlData['datasets'][1]['data'][i]==null){
					GirlData['datasets'][1]['data'][i]=0;
				}
			}
			var ctx = document.getElementById("Girl").getContext("2d");
			window.myBar = new Chart(ctx).Bar(GirlData, {
				responsive : true
			});
		}
	}
	xmlhttp.open("GET","data.php?cmd=getClassSex",true);
	xmlhttp.send();
}