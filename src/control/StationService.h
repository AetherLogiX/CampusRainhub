#pragma once

#include<vector>
#include<memory>
#include"../dao/StationDao.h"
#include"../model/Stationlocal.h"

class StationService {
public:
    //获取所有站点信息
    std::vector<std::unique_ptr<Stationlocal>> getAllStations();
    //获取单个站点详情
    std::unique_ptr<Stationlocal> getStationDetail(Station stationId);
private:
    StationDao stationDao;
};