# ☔ Campus RainHub

<div align="right">

[English](README.md) | [中文](README.zh-CN.md)

</div>

> Campus Smart Rain Gear Sharing System | C++/Qt + MySQL

> **"No more being trapped in buildings on rainy days."**

## Project Background

Every student has experienced this: you leave home in the morning with clear skies, but when class ends, it suddenly starts pouring. You're stuck in the building—either wait for the rain to stop or make a run for it. Neither option is great.

That's why this project exists.

The idea is simple: place smart terminals around campus where students can borrow and return umbrellas 24/7, just like shared power banks.

## Project Structure

```
Rainhub/
├── sql/                    # Database scripts
│   ├── init_db.sql        # Initialize table structure
│   └── data_insert.sql    # Test data
├── src/
│   ├── admin_ui/          # Admin dashboard UI
│   ├── client_ui/         # Client UI
│   │   └── assets/        # UI styles and resources
│   ├── control/           # Business logic layer (Service)
│   │   ├── AuthService.cpp
│   │   ├── BorrowService.cpp
│   │   └── Admin_*.cpp    # Admin-related services
│   ├── dao/               # Data access layer
│   │   ├── UserDao.cpp
│   │   ├── GearDao.cpp
│   │   └── StationDao.cpp
│   ├── Model/             # Data models
│   │   ├── User.cpp
│   │   └── RainGear.cpp
│   └── utils/             # Utility classes
├── assets/                # Resource files (icons, map configs)
├── third_party/           # Third-party libraries (MySQL DLL)
└── CMakeLists.txt         # Build configuration
```

## Features

### Client Application

- **Borrow/Return Gear**: Use campus card to select station and slot for borrowing/returning rain gear
- **Real-time Map**: View inventory status of all stations with real-time updates
- **Account Management**: Support student/staff roles, balance top-up, view borrowing history

### Admin Dashboard

- **Station Monitoring**: View online status and inventory of all stations
- **Gear Management**: Add, delete gear, modify status (available/borrowed/faulty)
- **User Management**: View user list and manage user information
- **Order Statistics**: View recent borrowing records and analyze usage

## Tech Stack

- **C++ 17** - Main development language
- **Qt 6.9.3** - GUI framework with QSS styling
- **MySQL 8.0** - Database, connected via Qt SQL module
- **CMake** - Build system

### Design Patterns

- **Factory Pattern**: Create different types of rain gear (umbrella, raincoat, etc.)
- **DAO Pattern**: Separation of data access layer and business logic layer
- **Singleton Pattern**: Database connection management

## Quick Start

### Requirements

- Qt 6.x (MinGW or MSVC)
- MySQL 8.0
- CMake 3.16+

### Setup Steps

1. **Create Database**

   ```sql
   CREATE DATABASE rainhub_db;
   ```

2. **Initialize Database**

   - Run `sql/init_db.sql` to create table structure
   - Run `sql/data_insert.sql` to import test data

3. **Configure Database**

   Open `src/control/DatabaseManager.cpp` and modify database username and password:

   ```cpp
   db.setUserName("your_mysql_username");
   db.setPassword("your_mysql_password");
   ```

4. **Build and Run**

   ```powershell
   # Navigate to project directory
   cd C:\Users\hdcqW\Desktop\Rainhub
   
   # Enter build directory
   cd build
   
   # Configure project (if CMakeLists.txt was modified)
   cmake ..
   
   # Build
   E:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe
   
   # Run client
   cd bin
   .\RainHub.exe
   
   # Or run admin dashboard
   .\RainHub_Admin.exe
   ```

   > If `mingw32-make` is added to system PATH, you can use `mingw32-make` directly instead of the full path

## Development Notes

- Project uses layered architecture: UI Layer → Service Layer → DAO Layer → Database
- Admin and user login are completely separated; admin accounts cannot log in to client app
- UI styling uses QSS with deep blue gradient theme
- Map data uses JSON configuration; station coordinates and descriptions are read from config file, inventory data is fetched from database in real-time

## TODO

- Customer service feature in client app
- Push notifications (borrow/return reminders)
- Server development
- More statistical charts

------

If you find this project interesting, feel free to Star ⭐
