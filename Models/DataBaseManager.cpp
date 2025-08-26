#include "DataBaseManager.hpp"
#include <iostream>
#include <sstream>
#include "Rulesets/DND/DND5e.hpp"

std::shared_ptr<DatabaseManager> DatabaseManager::instance = nullptr;

std::shared_ptr<IRuleSet> createRuleSetFromName(const std::string &name)
{
    if (name == "Dungeons & Dragons 5th Edition")
    {
        return std::make_shared<DND5e>();
    }
    std::cerr << "Warnung: Unbekanntes Regelsystem '" << name << "'" << std::endl;
    return nullptr;
}

// Helper function to serialize the attributes map to a string
std::string DatabaseManager::serializeAttributes(const std::map<std::string, int>& attributes)
{
    std::stringstream ss;
    for (const auto& pair : attributes)
    {
        ss << pair.first << ":" << pair.second << ";";
    }
    return ss.str();
}

// Helper function to deserialize the attributes string back to a map
std::map<std::string, int> DatabaseManager::deserializeAttributes(const std::string& serializedAttributes)
{
    std::map<std::string, int> attributes;
    std::stringstream ss(serializedAttributes);
    std::string item;
    while (std::getline(ss, item, ';'))
    {
        size_t delimiterPos = item.find(':');
        if (delimiterPos != std::string::npos)
        {
            std::string key = item.substr(0, delimiterPos);
            int value = std::stoi(item.substr(delimiterPos + 1));
            attributes[key] = value;
        }
    }
    return attributes;
}


DatabaseManager::DatabaseManager(const std::string &dbPath)
{
    try
    {
        m_db = std::make_unique<SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // SQL command to create the campaigns table
        const std::string createCampaignsTableSQL = R"(
            CREATE TABLE IF NOT EXISTS campaigns (
                id            INTEGER PRIMARY KEY,
                name          TEXT NOT NULL UNIQUE,
                ruleset_name  TEXT NOT NULL,
                last_modified DATETIME DEFAULT CURRENT_TIMESTAMP
            );
        )";
        m_db->exec(createCampaignsTableSQL);

        // SQL command to create the characters table with a foreign key to campaigns
        const std::string createCharactersTableSQL = R"(
            CREATE TABLE IF NOT EXISTS characters (
                id          INTEGER PRIMARY KEY,
                campaign_id INTEGER NOT NULL,
                name        TEXT NOT NULL,
                level       INTEGER NOT NULL,
                class       TEXT,
                race        TEXT,
                attributes  TEXT,
                FOREIGN KEY(campaign_id) REFERENCES campaigns(id) ON DELETE CASCADE
            );
        )";
        m_db->exec(createCharactersTableSQL);
    }
    catch (const std::exception &e)
    {
        std::cerr << "DatabaseManager Fehler: " << e.what() << std::endl;
        throw; // re-throw exception
    }
}

std::shared_ptr<DatabaseManager> DatabaseManager::getInstance()
{
    if (instance == nullptr)
        instance = std::shared_ptr<DatabaseManager>(new DatabaseManager("TTRPG.db"));

    return instance;
}

void DatabaseManager::saveCampaign(const Campaign &campaign)
{
    try
    {
        // Insert or replace the campaign itself
        SQLite::Statement query_campaign(*m_db, "INSERT OR REPLACE INTO campaigns (name, ruleset_name) VALUES (?, ?);");
        query_campaign.bind(1, campaign.name);
        query_campaign.bind(2, campaign.ruleSet->getName());
        query_campaign.exec();

        // Get the ID of the campaign we just saved
        int64_t campaignId = m_db->getLastInsertRowid();

        // Delete existing characters for this campaign to prevent duplicates on re-save
        SQLite::Statement query_delete_chars(*m_db, "DELETE FROM characters WHERE campaign_id = ?;");
        query_delete_chars.bind(1, campaignId);
        query_delete_chars.exec();

        // Insert each character into the characters table
        SQLite::Statement query_insert_char(*m_db, "INSERT INTO characters (campaign_id, name, level, class, race, attributes) VALUES (?, ?, ?, ?, ?, ?);");
        for (const auto &character : campaign.characters)
        {
            query_insert_char.bind(1, campaignId);
            query_insert_char.bind(2, character.name);
            query_insert_char.bind(3, character.level);
            query_insert_char.bind(4, character.selectedClass);
            query_insert_char.bind(5, character.selectedRace);
            query_insert_char.bind(6, serializeAttributes(character.attributes));

            query_insert_char.exec();
            query_insert_char.reset(); // Reset for the next iteration
        }
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
        SQLite::Statement query_campaigns(*m_db, "SELECT id, name, ruleset_name FROM campaigns;");

        while (query_campaigns.executeStep())
        {
            Campaign campaign;
            campaign.id = query_campaigns.getColumn(0).getInt64();
            campaign.name = query_campaigns.getColumn(1).getString();
            std::string rulesetName = query_campaigns.getColumn(2).getString();
            campaign.ruleSet = createRuleSetFromName(rulesetName);

            if (campaign.ruleSet)
            {
                // Now load the characters for this campaign
                SQLite::Statement query_chars(*m_db, "SELECT name, level, class, race, attributes FROM characters WHERE campaign_id = ?;");
                query_chars.bind(1, static_cast<int64_t>(campaign.id));

                while (query_chars.executeStep())
                {
                    CharacterModel character;

                    character.name = query_chars.getColumn(0).getString();
                    character.level = query_chars.getColumn(1).getInt();
                    character.selectedClass = query_chars.getColumn(2).getString();
                    character.selectedRace = query_chars.getColumn(3).getString();
                    
                    std::string serialized_attributes = query_chars.getColumn(4).getString();
                    character.attributes = deserializeAttributes(serialized_attributes);

                    campaign.characters.push_back(character);
                }

                campaigns.push_back(std::move(campaign));
            }
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
    for (auto &campaign : campaigns)
    {
        if (campaign.name == campaignName)
        {
            currentCampaign = std::move(campaign);
            return currentCampaign;
        }
    }
    throw std::runtime_error("Campaign not found!");
}
