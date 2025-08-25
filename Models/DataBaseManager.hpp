// DataBaseManager.hpp
#pragma once
#include <memory>
#include <vector>
#include "SQLiteCpp/SQLiteCpp.h"
#include "Models/Campaign/Campaign.hpp"

class DatabaseManager
{
private:
    std::unique_ptr<SQLite::Database> m_db;
    static std::shared_ptr<DatabaseManager> instance;
    Campaign currentCampaign;

    DatabaseManager(const std::string &dbPath);

    // Helper functions for serializing the attributes map
    std::string serializeAttributes(const std::map<std::string, int>& attributes);
    std::map<std::string, int> deserializeAttributes(const std::string& serializedAttributes);


public:
    DatabaseManager(const DatabaseManager &) = delete;
    void operator=(const DatabaseManager &) = delete;

    static std::shared_ptr<DatabaseManager> getInstance();

    void saveCampaign(const Campaign &campaign);
    std::vector<Campaign> loadAllCampaigns();
    Campaign &loadCampaign(std::string campaignName);
    Campaign &getActiveCampaign() {return currentCampaign;}
};