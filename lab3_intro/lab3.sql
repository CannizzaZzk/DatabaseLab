--创建表FLIGHTS，航班信息
create table FLIGHTS (
FID char(20) PRIMARY KEY, 
FSTART char(30),     --出发地
FEND char(30),       --目的地 
FTIME char(30),      --起飞时间
FLOCATION char(5),   --登机口
);

--创建表SEAT，座位
create table SEAT(
SRAW int,    
SCOLUMN char(2),
SVALID int,
UID int,
FID char(20),
TID int, 
FOREIGN KEY(UID) REFERENCES USERS(UID),
FOREIGN KEY(TID,FID) REFERENCES TICKETS(TID,FID),
PRIMARY KEY (SRAW,SCOLUMN,FID)
);

--创建表USERS，用户信息
CREATE TABLE USERS(
UID int PRIMARY KEY,				 
UNAME char(20),         --用户名
UPASS char(20),         --密码 
);

--创建表TICKETS,票务信息
CREATE TABLE TICKETS(
TID int, 
FID char(20),
UID int,
TPRICE int,
TSTATE int,
FOREIGN KEY(FID) REFERENCES FLIGHTS(FID),
FOREIGN KEY(UID) REFERENCES USERS(UID),
PRIMARY KEY (TID,FID)
);


--创建表ANOUNCEMENT取票通知
CREATE TABLE ANOUNCEMENT(
    TID int,
    FID char(20),
    UID int,
    ATIME char(30), --通知时间，起飞前24小时
    TSTATE int,      --付款状态
    FOREIGN KEY(UID) REFERENCES USERS(UID),
    FOREIGN KEY(TID,FID) REFERENCES TICKETS(TID,FID),
    PRIMARY KEY (UID,TID,FID)
)

--创建表BILL
CREATE TABLE BILL(
    TID int,
    FID char(20),
    UID int,
    TSTATE int,      --付款状态
    FOREIGN KEY(UID) REFERENCES USERS(UID),
    FOREIGN KEY(TID,FID) REFERENCES TICKETS(TID,FID),
    PRIMARY KEY (UID,TID,FID)
)