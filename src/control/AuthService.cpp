#include"AuthService.h"
#include"../utils/ConnectionPool.h
#include<QDebug>

AuthService::AuthService():userDao(std::make_unique<UserDao>()){

}

AuthService::LoginStatus AuthService::checkLogin(const QString& id, const QString& name) const{
    QSqlDatabase db=ConnectionPool::getThreadLocalConnection();
    if(!db.isOpen()){
        return LoginStatus::DatabaseError; //数据库连接失败
    }
    auto user=userDao.selectById(db,id);
    if(!user){
        return LoginStatus::UserNotFound; //学号不存在
    }else if(user->getName()!=name){
        return LoginStatus::NameMismatch; //姓名不匹配
    }else if(user->getPassword().isEmpty()){
        return LoginStatus::SuccessFiratTime; //首次login in，UI跳转设置新密码
    }
    return LoginStatus::SuccessNormal; //非首次login in，UI跳转输密码
}