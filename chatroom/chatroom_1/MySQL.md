```c
create database chat_room default charset=utf8;

use chat_room;

create table user(nickname varchar(20),password varchar(20));

create table relation(user varchar(20),oth_user varchar(20),status int);

create table messages(user varchar(20),oth_user varchar(20),message varchar(100));

create table off_messages(user varchar(20),oth_user varchar(20),message varchar(100));

insert into user values("111","111");

insert into user values("222","222");

insert into relation values("111","222",1);

insert into messages values("111","222","不错");

insert into off_messages values("111","222","很好");
```

