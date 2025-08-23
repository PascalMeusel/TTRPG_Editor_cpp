#include "DataBaseManager.hpp"
#include <iostream>
#include "Rulesets/DND/DND5e.hpp"

std::shared_ptr<DatabaseManager>DatabaseManager::instance = nullptr;

std::shared_ptr<IRuleSet> createRuleSetFromName(const std::string &name)
{
    if (name == "Dungeons & Dragons 5th Edition")
    {
        return std::make_shared<DND5e>();
    }
    std::cerr << "Warnung: Unbekanntes Regelsystem '" << name << "'" << std::endl;
    return nullptr;
}

DatabaseManager::DatabaseManager(const std::string &dbPath)
{
    try
    {
        m_db = std::make_unique<SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // SQL-Befehl zum Erstellen der Tabelle
        const std::string createTableSQL = R"(
            CREATE TABLE IF NOT EXISTS campaigns (
                id            INTEGER PRIMARY KEY,
                name          TEXT NOT NULL UNIQUE,
                ruleset_name  TEXT NOT NULL,
                last_modified DATETIME DEFAULT CURRENT_TIMESTAMP
            );
        )";
        m_db->exec(createTableSQL);
    }
    catch (const std::exception &e)
    {
        std::cerr << "DatabaseManager Fehler: " << e.what() << std::endl;
        throw; // Fehler weiterwerfen
    }
}

std::shared_ptr<DatabaseManager> DatabaseManager::getInstance()
{
    if(instance == nullptr)
        instance = std::shared_ptr<DatabaseManager>(new DatabaseManager("TTRPG.db"));

    return instance;
}

void DatabaseManager::saveCampaign(const Campaign &campaign)
{
    try
    {
        SQLite::Statement query(*m_db, "INSERT OR REPLACE INTO campaigns (name, ruleset_name) VALUES (?, ?);");

        query.bind(1, campaign.name);
        query.bind(2, campaign.ruleSet->getName());

        query.exec();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fehler beim Speichern der Kampagne '" << campaign.name << "': " << e.what() << std::endl;
    }
}

std::vector<Campaign> DatabaseManager::loadAllCampaigns()
{
    std::vector<Campaign> campaigns;
    try
    {
        SQLite::Statement query(*m_db, "SELECT id, name, ruleset_name FROM campaigns;");

        while (query.executeStep())
        {
            Campaign campaign;
            campaign.id = query.getColumn(0).getInt64();
            campaign.name = query.getColumn(1).getString();
            std::string rulesetName = query.getColumn(2).getString();
            campaign.ruleSet = createRuleSetFromName(rulesetName);

            if (campaign.ruleSet)
                campaigns.push_back(std::move(campaign));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fehler beim Laden der Kampagnen: " << e.what() << std::endl;
    }
    return campaigns;
}

Campaign &DatabaseManager::loadCampaign(std::string campaignName)
{
    auto campaigns = loadAllCampaigns();
    for(auto campaign : campaigns)
    {
        if(campaign.name == campaignName)
        {
            currentCampaign = campaign;
            return currentCampaign;
        }
    }
    throw std::runtime_error("Campaign not found!");
}
