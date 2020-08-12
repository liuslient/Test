

```c
mysql -u root -p

new _password

create database try default charset=utf8;

use try;

create table userinfo(nickname varchar(20),password varchar(20));

create table relationinfo(name1 varchar(20),name2 varchar(20),status int);

create table recordinfo(name1 varchar(20),name2 varchar(20),message varchar(100));

create table off_recordinfo(name1 varchar(20),name2 varchar(20),message varchar(100));

insert into userinfo values("111","111");

insert into userinfo values("222","222");

insert into relationinfo values("111","222",1);

insert into recordinfo values("111","222","不错");

insert into off_recordinfo values("111","222","很好");

exit 
```

