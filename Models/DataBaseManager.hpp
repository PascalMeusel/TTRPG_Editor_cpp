#pragma once

#include "Campaign/Campaign.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>
#include <memory>

class DatabaseManager
{
public:
    static std::shared_ptr<DatabaseManager> getInstance();

    void saveCampaign(const Campaign &campaign);

    std::vector<Campaign> loadAllCampaigns();

    Campaign &loadCampaign(std::string campaignName);

    Campaign getActiveCampaign() {return currentCampaign;}
private:
    std::unique_ptr<SQLite::Database> m_db;
    static std::shared_ptr<DatabaseManager> instance;

    Campaign currentCampaign;
    explicit DatabaseManager(const std::string &dbPath);
};