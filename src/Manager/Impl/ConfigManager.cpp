#include <fstream>
#include <format>
#include "nlohmann/json.hpp"
#include "ConfigManager.h"
#include "Animation/AnimTransCondition.h"
#include "Animation/AnimTransConditionFactory.h"
#include "Utility/Logger.h"

static nlohmann::json LoadJsonFile(const std::string& filePath)
{
    nlohmann::json json;
    std::ifstream configJsonFile(filePath);
    if (!configJsonFile.is_open())
    {
        Logger::LogError(std::string("File open failed: ") + filePath);
        return json;
    }

    configJsonFile >> json;
    configJsonFile.close();

    return json;
}

ConfigManager::ConfigManager()
{
    LoadGlobalSetting();
    LoadSpineSetting();
    LoadAnimationSetting();
    LoadPlayerSetting();
    LoadMonsterSetting();
    LoadSceneSetting();
    LoadMap();
}

auto ConfigManager::LoadGlobalSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/GlobalSetting.json");
    _globalSetting.globalGravity = json["globalGravity"];
    _globalSetting.levelMapPath = json["levelMapPath"];
    _globalSetting.levelWallTexPath = json["levelWallTexPath"];

    _globalSetting.cameraRectWorldCoordinateSize.x = json["cameraRectWorldCoordinateSize"]["x"];
    _globalSetting.cameraRectWorldCoordinateSize.y = json["cameraRectWorldCoordinateSize"]["y"];

    _globalSetting.wallPhysicsFixture.density = json["wallPhysics"]["density"];
    _globalSetting.wallPhysicsFixture.friction = json["wallPhysics"]["friction"];
    _globalSetting.wallPhysicsFixture.restitution = json["wallPhysics"]["restitution"];

    _globalSetting.entityPhysicsFixture.density = json["entityPhysics"]["density"];
    _globalSetting.entityPhysicsFixture.friction = json["entityPhysics"]["friction"];
    _globalSetting.entityPhysicsFixture.restitution = json["entityPhysics"]["restitution"];
}

auto ConfigManager::LoadSpineSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/SpineSetting.json");
    for (auto& spineDataNode : json)
    {
        SpineData spineData;
        spineData.name = spineDataNode["name"];
        spineData.jsonPath = spineDataNode["jsonPath"];
        spineData.atlasPath = spineDataNode["atlasPath"];
        spineData.loadScale = spineDataNode["loadScale"];

        for (auto blendPairNode: spineDataNode["animationBlend"])
        {
            AnimationBlendPair blendPair;
            blendPair.from = blendPairNode["from"];
            blendPair.to = blendPairNode["to"];
            blendPair.mixTime = blendPairNode["mixTime"];
            spineData.animationData.push_back(std::move(blendPair));
        }

        _spineSetting.allSpineData[spineData.name] = std::move(spineData);
    }
}

auto ConfigManager::LoadAnimationSetting() -> void
{
    // prepare some functions, to make logic looks clear
    auto CreateCondition = [&](const nlohmann::json& conditionNode) -> uptr<AnimTransCondition>
    {
        const std::string& conditionType = conditionNode["type"];
        if (conditionType == "checkValue")
        {
            const std::string& operation = conditionNode["operation"];
            const std::string& source = conditionNode["source"];
            float target = conditionNode["target"];
            return AnimTransCheckerFactory::CreateValueChecker(operation, source, target);
        }
        else if (conditionType == "checkProgress")
        {
            float ratio = conditionNode["value"];
            return AnimTransCheckerFactory::CreateProgressChecker(ratio);
        }
        else if (conditionType == "checkTrigger")
        {
            const std::string& triggerName = conditionNode["triggerName"];
            return AnimTransCheckerFactory::CreateTriggerChecker(triggerName);
        }
        else if (conditionType == "checkState")
        {
            const std::string& state = conditionNode["state"];
            float value = conditionNode["value"];
            return AnimTransCheckerFactory::CreateStateChecker(state, value);
        }
        else 
        {
            Logger::LogError(std::format("[AnimationSetting] No checker named: {}", conditionType));
            return nullptr;
        }   
    };

    auto CreateTransition = [&](const nlohmann::json& transitionNode) -> std::pair<std::string, std::vector<uptr<AnimTransCondition>>>
    {
        std::string targetAnimName = transitionNode["anim"];
        std::vector<uptr<AnimTransCondition>> allConditions;
        for (auto& conditionNode: transitionNode["condition"])
            allConditions.push_back(CreateCondition(conditionNode));

        return { targetAnimName, std::move(allConditions) };
    };

    auto CreateAnimatorConfig = [&](const nlohmann::json& animatorNode) -> AnimatorConfig
    {
        AnimatorConfig animatorConfig;
        for (auto& animNode: animatorNode)
        {
            AnimationConfig animationConfig;
            animationConfig.animName = animNode["anim"];
            animationConfig.spineName = animNode["spineAnimName"];
            animationConfig.isLoop = animNode["loop"];

            for (auto& transitionNode: animNode["transition"])
            {
                auto [targetAnimName, conditionVec] = CreateTransition(transitionNode);
                animationConfig.transitions[targetAnimName] = std::move(conditionVec);
            }

            animatorConfig.animationConfigMap[animationConfig.animName] = std::move(animationConfig);
        }

        return animatorConfig;
    };

    nlohmann::json json = LoadJsonFile("./config/AnimationSetting.json");
    for (auto& singleAnimConfig: json)
    {
        const std::string& animatorName = singleAnimConfig["name"];
        AnimatorConfig animatorConfig = CreateAnimatorConfig(singleAnimConfig["animator"]);

        _animationSetting.animatorConfigMap[animatorName] = std::move(animatorConfig);
    }
}

auto ConfigManager::LoadLevelSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/LevelSetting.json");
}

auto ConfigManager::LoadPlayerSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/PlayerSetting.json");
    _playerSetting.spineName = json["spineName"];
    _playerSetting.animatorName = json["animatorName"];
    _playerSetting.initMaxHp = json["initMaxHp"];
    _playerSetting.initMaxMp = json["initMaxMp"];
}

auto ConfigManager::LoadMonsterSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/MonsterSetting.json");

    // all monster detail
    for (auto monsterConfigJson: json["allConfig"])
    {
        MonsterConfig config;
        config.monsterName = monsterConfigJson["name"];
        _monsterSetting.monsterConfig[config.monsterName] = config;
    }

    // monster mark
    for (auto monsterMapMarkJson: json["monsterMapMark"])
    {
        std::string mark = monsterMapMarkJson["mark"];
        std::string monster = monsterMapMarkJson["monster"];
        _monsterSetting.monsterMapMark[mark[0]] = monster;
    }
}

auto ConfigManager::LoadSceneSetting() -> void
{
    nlohmann::json json = LoadJsonFile("./config/SceneSetting.json");
}

auto ConfigManager::LoadMap() -> void
{
    std::ifstream txtFile(_globalSetting.levelMapPath);
    if (!txtFile.is_open())
    {
        Logger::LogError(std::string("File open failed: ") + _globalSetting.levelMapPath);
        return;
    }

    _mapData.clear();

    // read txt line by line
    while (true)
    {
        std::string lineContent;
        if (!std::getline(txtFile, lineContent))
            break;

        _mapData.push_back(std::move(lineContent));
    }

    txtFile.close();
}

auto ConfigManager::GetGlobalSetting() const -> const GlobalSetting&
{
    return _globalSetting;
}

auto ConfigManager::GetSpineSetting() const -> const SpineSetting&
{
    return _spineSetting;
}

auto ConfigManager::GetAnimationSetting() const -> const AnimationSetting&
{
    return _animationSetting;
}

auto ConfigManager::GetLevelSetting() const -> const LevelSetting&
{
    return _levelSetting;
}

auto ConfigManager::GetPlayerSetting() const -> const PlayerSetting&
{
    return _playerSetting;
}

auto ConfigManager::GetMonsterSetting() const -> const MonsterSetting&
{
    return _monsterSetting;
}

auto ConfigManager::GetSceneSetting() const -> const SceneSetting&
{
    return _sceneSetting;
}

auto ConfigManager::GetMapData() const -> const std::vector<std::string>&
{
    return _mapData;
}
