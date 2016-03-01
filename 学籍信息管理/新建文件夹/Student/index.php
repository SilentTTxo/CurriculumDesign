<?php
session_start();
if(!isset($_SESSION['login'])){
	header("location: login.html");
	exit();
}
?>
<head>
	<meta charset="utf-8">
	<link rel="stylesheet" href="//cdn.bootcss.com/bootstrap/3.3.5/css/bootstrap.min.css">
	<link rel="stylesheet" href="css/st.css">
</head>
<body style = "background-color:#333333">
	<h1 align="center" class = "login">学生管理信息系统</h1>
	<div class="container well">
		<ul class="nav nav-pills nav-stacked col-md-2">
			<li role="presentation" class="active"><a href="#level" aria-controls="level" role="tab" data-toggle="tab" onClick="yearDo();">年级管理</a></li>
			<li role="presentation"><a href="#college" aria-controls="college" role="tab" data-toggle="tab" onClick="collegeSerch();">学院管理</a></li>
			<li role="presentation"><a href="#major" aria-controls="major" role="tab" data-toggle="tab" onClick="majorSerch();">专业管理</a></li>
			<li role="presentation"><a href="#class" aria-controls="class" role="tab" data-toggle="tab" onClick="classSerch();">班级管理</a></li>
			<li role="presentation"><a href="#student" aria-controls="student" role="tab" data-toggle="tab" onClick="StudentSerch();">学生管理</a></li>
			<li role="presentation"><a href="#find" aria-controls="find" role="tab" data-toggle="tab" onClick="Find();">数据发现</a></li>
		</ul>
		<div class="col-md-10 well">
			<div class="tab-content" id = "tab">
				<div role="tabpanel" class="tab-pane active" id="level">
					<form class="form-inline col-md-offset-3">
						<div class="form-group">
							<label for="year">入学年份</label>
							<input type="text" class="form-control" id="year" placeholder="年份">
						</div>
						<button class="btn btn-default" onClick="yearDo();return false;">添加</button>
					</form>
					<table class="table table-hover" id = "yeardata">
						<th>ID</th>
						<th>年份</th>
						<th>删除</th>
					</table>
				</div>
				<div role="tabpanel" class="tab-pane" id="college">
					<form class="form-inline">
						<div class="form-group">
							<label for="college">学院名</label>
							<input type="text" class="form-control" id="collegename" placeholder="学院名">
						</div>
						<div class="form-group" style=" padding-left: 30;">
							<label for="serch_year">年份</label>
							<input type="text" class="form-control" id="serch_year" placeholder="年份">
							<button type="submit" class="btn btn-primary" onClick="collegeSerch();return false;">查询</button>
						</div>
						<button type="submit" class="btn btn-default" onClick="collegeAdd();return false;">添加</button>
					</form>
					<table class="table table-hover" id = "collegedata">
						<th>ID</th>
						<th>学院名</th>
						<th>所属年级ID</th>
						<th>入学年份</th>
						<th>删除</th>
					</table>
				</div>
				<div role="tabpanel" class="tab-pane" id="major">
					<form class="form-inline">
						<div class="form-group">
							<label for="majorname">专业名</label>
							<input type="text" class="form-control in" id="majorname" placeholder="专业名">
						</div>
						<div class="form-group" style=" padding-left: 30;">
							<label for="collegeID">学院ID</label>
							<input type="text" class="form-control" id="collegeID" placeholder="学院ID">
							<button type="submit" class="btn btn-primary" onClick="majorSerch();return false;">查询</button>
						</div>
						<button type="submit" class="btn btn-default" onClick="majorAdd();return false;">添加</button>
					</form>
					<table class="table table-hover" id = "majordata">
						<th>ID</th>
						<th>专业名</th>
						<th>所属学院ID</th>
						<th>学院名</th>
						<th>删除</th>
					</table>
				</div>
				<div role="tabpanel" class="tab-pane" id="class">
					<form class="form-inline">
						<div class="form-group">
							<button type="submit" class="btn btn-default" onClick="classAdd();return false;">添加班级</button>
						</div>
						<div class="form-group col-md-offset-4" style=" padding-left: 30;">
							<label for="majorID">专业ID</label>
							<input type="text" class="form-control" id="majorID" placeholder="专业ID">
							<button type="submit" class="btn btn-primary"  onClick="classSerch();return false;">查询</button>
						</div>
						
					</form>
					<table class="table table-hover" id = "classdata">
						<th>ID</th>
						<th>所属专业ID</th>
						<th>专业名</th>
						<th>删除</th>
					</table>
				</div>
				<div role="tabpanel" class="tab-pane" id="student">
					<form class="form-inline">
						<div class="form-group">
							<button type="submit" class="btn btn-default"  data-toggle="modal" data-target="#addStudent" onClick="return false;">添加学生</button>
						</div>
						<div class="form-group col-md-offset-4" style=" padding-left: 30;">
							<label for="StudentID">学号</label>
							<input type="text" class="form-control" id="StudentID" placeholder="学号">
							<button type="submit" class="btn btn-primary" onClick="StudentSerch();return false;">查询</button>
							<button type="submit" class="btn btn-danger" onClick="Studentdel();return false;">删除</button>
						</div>
					</form>
					<table class="table table-hover" id = "studentdata">
						<th>学号</th>
						<th>姓名</th>
						<th>班级</th>
						<th>生日</th>
						<th>性别</th>
						<th>身高</th>
						<th>地址</th>
					</table>
				</div>
				<!-- dataFind -->
				<div role="tabpanel" class="tab-pane" id="find">
					<div class="col-md-6">
						<div>
							<h3>平均班级身高</h3>
						</div>
						<div>
						<canvas id="High"  height="450" width="600"></canvas>
						</div>
					</div>
					<div class="col-md-6">
						<div>
							<h3>各班男女比例</h3>
						</div>
						<div>
						<canvas id="Girl"  height="450" width="600"></canvas>
						</div>
					</div>
				</div>
				<!-- admin -->
			</div>
		</div>
	</div>
	<!-- Modal -->
	<div class="modal fade" id="addStudent" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
		<div class="modal-dialog  modal-sm" role="document">
			<div class="modal-content">
				<div class="modal-header">
					<button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
					<h4 class="modal-title" id="myModalLabel">添加学生</h4>
				</div>
				<div class="modal-body">
					<form class="form-horizontal">
						<div class="form-group">
							<label for="S_StudentName" class="col-md-4 control-label">名字</label>
							<div class="col-md-8">
								<input type="text" class="form-control" id="S_StudentName" placeholder="名字">
							</div>
						</div>
						<div class="form-group">
							<label for="S_class" class="col-md-4 control-label">班级ID</label>
							<div class="col-md-8">
								<input type="text" class="form-control" id="S_class" placeholder="班级ID">
							</div>
						</div>
						<div class="form-group">
							<label for="S_birth" class="col-md-4 control-label">生日</label>
							<div class="col-md-8">
								<input type="text" class="form-control" id="S_birth" placeholder="XXXX-XX-XX">
							</div>
						</div>
						<div class="form-group">
							<label for="S_sex" class="col-md-4 control-label">性别</label>
							<div class="col-md-8">
								<input type="text" class="form-control" id="S_sex" placeholder="性别">
							</div>
						</div>
						<div class="form-group">
							<label for="S_high" class="col-md-4 control-label">身高</label>
							<div class="col-md-8">
								<input type="text" class="form-control" id="S_high" placeholder="身高">
							</div>
						</div>
						<div class="form-group">
							<label for="S_address" class="col-md-4 control-label">地址</label>
							<div class="col-md-8">
								<input type="text" class="form-control" id="S_address" placeholder="地址">
							</div>
						</div>
					</form>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default" data-dismiss="modal">返回</button>
					<button type="button" class="btn btn-primary" onClick="StudentAdd();return false;">提交</button>
				</div>
			</div>
		</div>
	</div>
	<script src="//cdn.bootcss.com/jquery/1.11.3/jquery.min.js"></script>
	<script src="//cdn.bootcss.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
	<script src="js/Chart.js"></script>
	<script src="js/st.js"></script>
</body>