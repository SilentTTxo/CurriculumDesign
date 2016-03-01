<?php
/*
$data = "mysql:host=".SAE_MYSQL_HOST_M.";port=".SAE_MYSQL_PORT.";dbname=".SAE_MYSQL_DB;
$db = new PDO($data,SAE_MYSQL_USER,SAE_MYSQL_PASS);
*/
$dsn = "mysql:host=localhost;dbname=STUDENTINFO";
$db = new PDO($dsn, 'root', '');
if(isset($_POST["username"])){
	$rs = $db->query("SELECT * FROM LOGIN");
	$rs = $rs->fetchAll();
	foreach ($rs as $value) {
		if($value[1] == $_POST['username'] && $value[2] == $_POST['password']){
			session_start();
			$_SESSION['login']=true;
			header("location: index.php");
			exit();
		}
	}
	echo "帐号或密码错误";
	exit();
}
if($_GET['cmd']=="yearadd"){
	if($_GET['year']!=""){
		$count = $db->query("INSERT INTO LEVEL VALUES (NULL,{$_GET['year']})");
	}
	$count = $db->query("SELECT * FROM LEVEL");
	echo json_encode($count->fetchAll());
}
if($_GET['cmd']=="yeardel"){
	$count = $db->query("DELETE FROM LEVEL WHERE ID = {$_GET['ID']}");
	echo "删除成功！";
}
if($_GET['cmd']=="collegeSerch"){
	$count = $db->query("SELECT COLLEGE.ID,COLLEGE.NAME,LEVEL.ID AS LEVELID,LEVEL.YEAR FROM COLLEGE JOIN LEVEL ON COLLEGE._LEVEL = LEVEL.ID WHERE LEVEL.YEAR LIKE '%{$_GET['year']}%' AND COLLEGE.NAME LIKE '%{$_GET['college']}%'");
	echo json_encode($count->fetchAll());
}
if($_GET['cmd']=="collegeAdd"){
	$count = $db->query("SELECT * FROM LEVEL WHERE YEAR = '{$_GET['year']}'");
	$row = $count->fetch();
	if(!isset($row[0])){
		echo "年份错误！";
		exit();
	}
	$count = $db->query("INSERT INTO COLLEGE VALUES (NULL,{$row[0]},'{$_GET['college']}')");
}
if($_GET['cmd']=="collegeDel"){
	$count = $db->query("DELETE FROM COLLEGE WHERE ID = {$_GET['ID']}");
	echo "删除成功！";
}
if($_GET['cmd']=="majorSerch"){
	$count = $db->query("SELECT MAJOR.ID,MAJOR.NAME,COLLEGE.ID AS COLLEGEID,COLLEGE.NAME AS COLLEGENAME FROM MAJOR JOIN COLLEGE ON MAJOR._COLLEGE = COLLEGE.ID WHERE MAJOR.NAME LIKE '%{$_GET['majorname']}%' AND COLLEGE.ID LIKE '%{$_GET['collegeID']}%'");
	echo json_encode($count->fetchAll());
}
if($_GET['cmd']=="majorAdd"){
	$count = $db->query("INSERT INTO MAJOR VALUES (NULL,{$_GET['collegeID']},'{$_GET['majorname']}')");
}
if($_GET['cmd']=="majorDel"){
	$count = $db->query("DELETE FROM MAJOR WHERE ID = {$_GET['ID']}");
	echo "删除成功！";
}
if($_GET['cmd']=="classSerch"){
	if($_GET['majorID']!="") $count = $db->query("SELECT CLASS.ID,MAJOR.ID AS MAJORID,MAJOR.NAME FROM CLASS JOIN MAJOR ON CLASS._MAJOR = MAJOR.ID WHERE MAJOR.ID = {$_GET['majorID']}");
	else $count = $db->query("SELECT CLASS.ID,MAJOR.ID AS MAJORID,MAJOR.NAME FROM CLASS JOIN MAJOR ON CLASS._MAJOR = MAJOR.ID");
	echo json_encode($count->fetchAll());
}
if($_GET['cmd']=="classAdd"){
	$count = $db->query("INSERT INTO CLASS VALUES (NULL,{$_GET['majorID']},0)");
}
if($_GET['cmd']=="classDel"){
	$count = $db->query("DELETE FROM CLASS WHERE ID = {$_GET['ID']}");
	echo "删除成功！";
}
if($_GET['cmd']=="StudentSerch"){
	if($_GET['StudentID']!="") $count = $db->query("SELECT * FROM STUDENT WHERE ID = {$_GET['StudentID']}");
	else $count = $db->query("SELECT * FROM STUDENT");
	echo json_encode($count->fetchAll());
}
if($_GET['cmd']=="StudentAdd"){
	$count = $db->query("SELECT _MAJOR,NUM,ID FROM CLASS WHERE ID = {$_GET['class']}");
	$row = $count->fetch();$mj=$row[0];$no=$row[1]+1;$class=$row[2];$no = str_pad($row[1]+1,2,"0",STR_PAD_LEFT);
	$count = $db->query("UPDATE CLASS SET NUM={$no} WHERE ID = {$_GET['class']}");
	$count = $db->query("SELECT _COLLEGE FROM MAJOR WHERE ID = {$mj}");
	$row = $count->fetch();$cg=$row[0];
	$count = $db->query("SELECT _LEVEL FROM COLLEGE WHERE ID = {$cg}");
	$row = $count->fetch();$lv=$row[0];
	$sum = "{$lv}{$cg}{$mj}{$class}{$no}";
	$count = $db->query("INSERT INTO STUDENT VALUES ({$sum},{$_GET['class']},'{$_GET['name']}','{$_GET['birth']}','{$_GET['sex']}','{$_GET['address']}','{$_GET['high']}')");
	echo "ok";
}
if($_GET['cmd']=="StudentDel"){
	$count = $db->query("DELETE FROM STUDENT WHERE ID = {$_GET['ID']}");
	echo "删除成功！";
}
if($_GET['cmd']=="getClassID"){
	$count = $db->query("SELECT _CLASS,AVG(HIGH) FROM STUDENT GROUP BY _CLASS");
	echo json_encode($count->fetchAll());
}
if($_GET['cmd']=="getClassSex"){
	$count = $db->query("SELECT _CLASS,SEX,COUNT(*) FROM STUDENT GROUP BY _CLASS,SEX ");
	echo json_encode($count->fetchAll());
}
?>