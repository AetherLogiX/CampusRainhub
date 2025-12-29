# ☔ Campus RainHub

<div align="right">

[English](README.md) | [中文](README.zh-CN.md)

</div>

> 校园智能雨具共享系统 | C++/Qt + MySQL

> **"下雨天，再也不用被困在教学楼了。"**

## 项目背景

相信每个在校生都遇到过这种情况：早上出门时天气好好的，结果下课突然下暴雨，被困在教学楼回不去。要么等雨停，要么硬着头皮冲回去，反正都不太舒服。

所以就有了这个项目。

想法很简单：在校园里放一些智能终端，学生可以自助借还雨伞，24小时可用，就像共享充电宝那样。

## 项目结构

```
Rainhub/
├── sql/                    # 数据库脚本
│   ├── init_db.sql        # 初始化表结构
│   └── data_insert.sql    # 测试数据
├── src/
│   ├── admin_ui/          # 管理员后台界面
│   ├── client_ui/         # 用户端界面
│   │   └── assets/        # UI样式和资源
│   ├── control/           # 业务逻辑层（Service）
│   │   ├── AuthService.cpp
│   │   ├── BorrowService.cpp
│   │   └── Admin_*.cpp    # 管理员相关服务
│   ├── dao/               # 数据访问层
│   │   ├── UserDao.cpp
│   │   ├── GearDao.cpp
│   │   └── StationDao.cpp
│   ├── Model/             # 数据模型
│   │   ├── User.cpp
│   │   └── RainGear.cpp
│   └── utils/             # 工具类
├── assets/                # 资源文件（图标、地图配置）
├── third_party/           # 第三方库（MySQL DLL）
└── CMakeLists.txt         # 构建配置
```

## 主要功能

### 用户端

- **借还雨具**：通过刷卡（校园一卡通），选择站点和槽位，进行借/还雨具
- **实时地图**：查看各个站点的库存情况，数据实时更新
- **账户管理**：支持学生/教职工身份，余额充值，查看借还记录

### 管理端

- **站点监控**：查看所有站点的在线状态和库存情况
- **雨具管理**：添加、删除雨具，修改状态（可用/已借/故障）
- **用户管理**：查看用户列表，管理用户信息
- **订单统计**：查看最近的借还记录，分析使用情况

## 技术栈

- **C++ 17** - 主要开发语言
- **Qt 6.9.3** - GUI框架，用 QSS 做了样式美化
- **MySQL 8.0** - 数据库，用 Qt 的 SQL 模块连接
- **CMake** - 构建系统

### 设计模式

- **工厂模式**：创建不同类型的雨具（雨伞、雨衣等）
- **DAO 模式**：数据访问层和业务逻辑层分离
- **单例模式**：数据库连接管理

## RUN_GUIDE

### 环境要求

- Qt 6.x (MinGW 或 MSVC)
- MySQL 8.0
- CMake 3.16+

### 配置步骤

1. **创建数据库**

   ```sql
   CREATE DATABASE rainhub_db;
   ```

2. **初始化数据库**

   - 运行 `sql/init_db.sql` 创建表结构
   - 运行 `sql/data_insert.sql` 导入测试数据

3. **修改数据库配置**

   打开 `src/control/DatabaseManager.cpp`，修改数据库用户名和密码：

   ```cpp
   db.setUserName("你的MySQL用户名");
   db.setPassword("你的MySQL密码");
   ```

4. **编译运行**

   ```powershell
   # 进入项目目录
   cd C:\Users\hdcqW\Desktop\Rainhub
   
   # 进入build目录
   cd build
   
   # 配置项目（如果修改了CMakeLists.txt）
   cmake ..
   
   # 编译
   E:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe
   
   # 运行客户端
   cd bin
   .\RainHub.exe
   
   # 或运行管理端
   .\RainHub_Admin.exe
   ```

   > 如果 `mingw32-make` 已添加到系统 PATH，可以直接用 `mingw32-make` 代替完整路径

## 开发笔记

- 项目采用分层架构：UI层 → Service层 → DAO层 → 数据库
- 管理员和用户登录完全分离，管理员账号无法在用户端登录
- UI样式使用 QSS 实现，支持深蓝渐变主题
- 地图数据使用 JSON 配置，站点坐标和描述信息从配置文件读取，库存数据从数据库实时获取

## 待完善的功能

-  用户端客服功能
-  消息推送（借还提醒）
-  服务器开发
-  更多统计图表

------

如果觉得这个项目有意思，欢迎 Star ⭐

