#include "ZigBeeHomeAutomation.h"

// Zigbee2mqtt deduplicates commands based on the transaction id.
// We generate this transaction ID using the field below. Every time
// we send out a command, we bump this value by one.
static uint8_t nextTransactionSequenceNumber = 0;

AttributeUInt8* GenBasicCluster::getZclVersion() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::ZclVersion);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getAppVersion() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::AppVersion);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getStackVersion() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::StackVersion);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getHwVersion() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::HwVersion);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBasicCluster::getManufacturerName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBasicAttribute::ManufacturerName);
    if (result == nullptr) {
        result = new AttributeString(4);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBasicCluster::getModelId() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBasicAttribute::ModelId);
    if (result == nullptr) {
        result = new AttributeString(5);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBasicCluster::getDateCode() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBasicAttribute::DateCode);
    if (result == nullptr) {
        result = new AttributeString(6);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getPowerSource() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::PowerSource);
    if (result == nullptr) {
        result = new AttributeUInt8(7, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getAppProfileVersion() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::AppProfileVersion);
    if (result == nullptr) {
        result = new AttributeUInt8(8, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBasicCluster::getSwBuildId() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBasicAttribute::SwBuildId);
    if (result == nullptr) {
        result = new AttributeString(16384);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBasicCluster::getLocationDesc() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBasicAttribute::LocationDesc);
    if (result == nullptr) {
        result = new AttributeString(16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getPhysicalEnv() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::PhysicalEnv);
    if (result == nullptr) {
        result = new AttributeUInt8(17, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getDeviceEnabled() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::DeviceEnabled);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getAlarmMask() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::AlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt8(19, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBasicCluster::getDisableLocalConfig() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBasicAttribute::DisableLocalConfig);
    if (result == nullptr) {
        result = new AttributeUInt8(20, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

void GenBasicCluster::sendResetFactDefaultCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenBasicCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onResetFactDefaultCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt16* GenPowerCfgCluster::getMainsVoltage() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPowerCfgAttribute::MainsVoltage);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getMainsFrequency() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::MainsFrequency);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getMainsAlarmMask() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::MainsAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt8(16, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenPowerCfgCluster::getMainsVoltMinThres() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPowerCfgAttribute::MainsVoltMinThres);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenPowerCfgCluster::getMainsVoltMaxThres() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPowerCfgAttribute::MainsVoltMaxThres);
    if (result == nullptr) {
        result = new AttributeUInt16(18, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenPowerCfgCluster::getMainsVoltageDwellTripPoint() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPowerCfgAttribute::MainsVoltageDwellTripPoint);
    if (result == nullptr) {
        result = new AttributeUInt16(19, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryVoltage() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryVoltage);
    if (result == nullptr) {
        result = new AttributeUInt8(32, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryPercentageRemaining() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryPercentageRemaining);
    if (result == nullptr) {
        result = new AttributeUInt8(33, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenPowerCfgCluster::getBatteryManufacturer() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryManufacturer);
    if (result == nullptr) {
        result = new AttributeString(48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatterySize() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatterySize);
    if (result == nullptr) {
        result = new AttributeUInt8(49, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenPowerCfgCluster::getBatteryAHrRating() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryAHrRating);
    if (result == nullptr) {
        result = new AttributeUInt16(50, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryQuantity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryQuantity);
    if (result == nullptr) {
        result = new AttributeUInt8(51, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryRatedVoltage() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryRatedVoltage);
    if (result == nullptr) {
        result = new AttributeUInt8(52, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryAlarmMask() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt8(53, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryVoltMinThres() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryVoltMinThres);
    if (result == nullptr) {
        result = new AttributeUInt8(54, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryVoltThres1() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryVoltThres1);
    if (result == nullptr) {
        result = new AttributeUInt8(55, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryVoltThres2() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryVoltThres2);
    if (result == nullptr) {
        result = new AttributeUInt8(56, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryVoltThres3() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryVoltThres3);
    if (result == nullptr) {
        result = new AttributeUInt8(57, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryPercentMinThres() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryPercentMinThres);
    if (result == nullptr) {
        result = new AttributeUInt8(58, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryPercentThres1() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryPercentThres1);
    if (result == nullptr) {
        result = new AttributeUInt8(59, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryPercentThres2() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryPercentThres2);
    if (result == nullptr) {
        result = new AttributeUInt8(60, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenPowerCfgCluster::getBatteryPercentThres3() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryPercentThres3);
    if (result == nullptr) {
        result = new AttributeUInt8(61, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenPowerCfgCluster::getBatteryAlarmState() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenPowerCfgAttribute::BatteryAlarmState);
    if (result == nullptr) {
        result = new AttributeUInt32(62, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenDeviceTempCfgCluster::getCurrentTemperature() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::CurrentTemperature);
    if (result == nullptr) {
        result = new AttributeInt16(0, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenDeviceTempCfgCluster::getMinTempExperienced() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::MinTempExperienced);
    if (result == nullptr) {
        result = new AttributeInt16(1, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenDeviceTempCfgCluster::getMaxTempExperienced() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::MaxTempExperienced);
    if (result == nullptr) {
        result = new AttributeInt16(2, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenDeviceTempCfgCluster::getOverTempTotalDwell() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::OverTempTotalDwell);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenDeviceTempCfgCluster::getDevTempAlarmMask() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::DevTempAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt8(16, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenDeviceTempCfgCluster::getLowTempThres() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::LowTempThres);
    if (result == nullptr) {
        result = new AttributeInt16(17, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenDeviceTempCfgCluster::getHighTempThres() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::HighTempThres);
    if (result == nullptr) {
        result = new AttributeInt16(18, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* GenDeviceTempCfgCluster::getLowTempDwellTripPoint() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::LowTempDwellTripPoint);
    if (result == nullptr) {
        result = new AttributeUInt24(19, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* GenDeviceTempCfgCluster::getHighTempDwellTripPoint() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)GenDeviceTempCfgAttribute::HighTempDwellTripPoint);
    if (result == nullptr) {
        result = new AttributeUInt24(20, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenIdentifyCluster::getIdentifyTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenIdentifyAttribute::IdentifyTime);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void GenIdentifyCluster::sendIdentifyCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t identifytime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt16Le(identifytime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenIdentifyCluster::sendIdentifyQueryCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenIdentifyCluster::sendEzmodeInvokeCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t action) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt8(action);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenIdentifyCluster::sendUpdateCommissionStateCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t action, uint8_t commstatemask) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);

    buffer.writeUInt8(action);
    buffer.writeUInt8(commstatemask);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenIdentifyCluster::sendTriggerEffectCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t effectid, uint8_t effectvariant) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        64
    ).write(buffer);

    buffer.writeUInt8(effectid);
    buffer.writeUInt8(effectvariant);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenIdentifyCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto identifytime = request.readUInt16Le();
            auto status_ = onIdentifyCommand(identifytime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onIdentifyQueryCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto action = request.readUInt8();
            auto status_ = onEzmodeInvokeCommand(action);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto action = request.readUInt8();
            auto commstatemask = request.readUInt8();
            auto status_ = onUpdateCommissionStateCommand(action, commstatemask);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 64: {
            auto effectid = request.readUInt8();
            auto effectvariant = request.readUInt8();
            auto status_ = onTriggerEffectCommand(effectid, effectvariant);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* GenGroupsCluster::getNameSupport() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenGroupsAttribute::NameSupport);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

void GenGroupsCluster::sendViewCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t groupid) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeUInt16Le(groupid);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenGroupsCluster::sendRemoveAllCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenGroupsCluster::sendAddIfIdentifyingCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t groupid, String groupname) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        5
    ).write(buffer);

    buffer.writeUInt16Le(groupid);
    buffer.writeString(groupname);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenGroupsCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto groupid = request.readUInt16Le();
            auto groupname = request.readString();
            AddCommandResponse response_;
            auto status_ = onAddCommand(groupid, groupname, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
                response.writeUInt16Le(response_.getGroupid());
            }
            return;
        }
        case 1: {
            auto groupid = request.readUInt16Le();
            auto status_ = onViewCommand(groupid);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto groupid = request.readUInt16Le();
            RemoveCommandResponse response_;
            auto status_ = onRemoveCommand(groupid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
                response.writeUInt16Le(response_.getGroupid());
            }
            return;
        }
        case 4: {
            auto status_ = onRemoveAllCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 5: {
            auto groupid = request.readUInt16Le();
            auto groupname = request.readString();
            auto status_ = onAddIfIdentifyingCommand(groupid, groupname);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* GenScenesCluster::getCount() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenScenesAttribute::Count);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenScenesCluster::getCurrentScene() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenScenesAttribute::CurrentScene);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenScenesCluster::getCurrentGroup() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenScenesAttribute::CurrentGroup);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenScenesCluster::getSceneValid() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenScenesAttribute::SceneValid);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenScenesCluster::getNameSupport() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenScenesAttribute::NameSupport);
    if (result == nullptr) {
        result = new AttributeUInt8(4, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt64* GenScenesCluster::getLastCfgBy() {
    auto result = (AttributeUInt64*)getAttributeById((uint16_t)GenScenesAttribute::LastCfgBy);
    if (result == nullptr) {
        result = new AttributeUInt64(5, DataType::EUI64);
        addAttribute(result);
    }
    return result;
}

void GenScenesCluster::sendRecallCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t groupid, uint8_t sceneid) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        5
    ).write(buffer);

    buffer.writeUInt16Le(groupid);
    buffer.writeUInt8(sceneid);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenScenesCluster::sendTradfriArrowSingleCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t value, uint16_t value2) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        7
    ).write(buffer);

    buffer.writeUInt16Le(value);
    buffer.writeUInt16Le(value2);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenScenesCluster::sendTradfriArrowHoldCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t value) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        8
    ).write(buffer);

    buffer.writeUInt16Le(value);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenScenesCluster::sendTradfriArrowReleaseCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t value) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        9
    ).write(buffer);

    buffer.writeUInt16Le(value);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenScenesCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 2: {
            auto groupid = request.readUInt16Le();
            auto sceneid = request.readUInt8();
            RemoveCommandResponse response_;
            auto status_ = onRemoveCommand(groupid, sceneid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
                response.writeUInt16Le(response_.getGroupid());
                response.writeUInt8(response_.getSceneid());
            }
            return;
        }
        case 3: {
            auto groupid = request.readUInt16Le();
            RemoveAllCommandResponse response_;
            auto status_ = onRemoveAllCommand(groupid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
                response.writeUInt16Le(response_.getGroupid());
            }
            return;
        }
        case 4: {
            auto groupid = request.readUInt16Le();
            auto sceneid = request.readUInt8();
            StoreCommandResponse response_;
            auto status_ = onStoreCommand(groupid, sceneid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
                response.writeUInt16Le(response_.getGroupid());
                response.writeUInt8(response_.getSceneid());
            }
            return;
        }
        case 5: {
            auto groupid = request.readUInt16Le();
            auto sceneid = request.readUInt8();
            auto status_ = onRecallCommand(groupid, sceneid);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 66: {
            auto mode = request.readUInt8();
            auto groupidfrom = request.readUInt16Le();
            auto sceneidfrom = request.readUInt8();
            auto groupidto = request.readUInt16Le();
            auto sceneidto = request.readUInt8();
            CopyCommandResponse response_;
            auto status_ = onCopyCommand(mode, groupidfrom, sceneidfrom, groupidto, sceneidto, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
                response.writeUInt16Le(response_.getGroupidfrom());
                response.writeUInt8(response_.getSceneidfrom());
            }
            return;
        }
        case 7: {
            auto value = request.readUInt16Le();
            auto value2 = request.readUInt16Le();
            auto status_ = onTradfriArrowSingleCommand(value, value2);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 8: {
            auto value = request.readUInt16Le();
            auto status_ = onTradfriArrowHoldCommand(value);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 9: {
            auto value = request.readUInt16Le();
            auto status_ = onTradfriArrowReleaseCommand(value);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* GenOnOffCluster::getOnOff() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenOnOffAttribute::OnOff);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenOnOffCluster::getGlobalSceneCtrl() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenOnOffAttribute::GlobalSceneCtrl);
    if (result == nullptr) {
        result = new AttributeUInt8(16384, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenOnOffCluster::getOnTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenOnOffAttribute::OnTime);
    if (result == nullptr) {
        result = new AttributeUInt16(16385, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenOnOffCluster::getOffWaitTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenOnOffAttribute::OffWaitTime);
    if (result == nullptr) {
        result = new AttributeUInt16(16386, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenOnOffCluster::getStartUpOnOff() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenOnOffAttribute::StartUpOnOff);
    if (result == nullptr) {
        result = new AttributeUInt8(16387, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenOnOffCluster::getMoesStartUpOnOff() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenOnOffAttribute::MoesStartUpOnOff);
    if (result == nullptr) {
        result = new AttributeUInt8(32770, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

void GenOnOffCluster::sendOffCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenOnOffCluster::sendOnCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenOnOffCluster::sendToggleCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenOnOffCluster::sendOffWithEffectCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t effectid, uint8_t effectvariant) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        64
    ).write(buffer);

    buffer.writeUInt8(effectid);
    buffer.writeUInt8(effectvariant);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenOnOffCluster::sendOnWithRecallGlobalSceneCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        65
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenOnOffCluster::sendOnWithTimedOffCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t ctrlbits, uint16_t ontime, uint16_t offwaittime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        66
    ).write(buffer);

    buffer.writeUInt8(ctrlbits);
    buffer.writeUInt16Le(ontime);
    buffer.writeUInt16Le(offwaittime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenOnOffCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onOffCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onOnCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto status_ = onToggleCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 64: {
            auto effectid = request.readUInt8();
            auto effectvariant = request.readUInt8();
            auto status_ = onOffWithEffectCommand(effectid, effectvariant);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 65: {
            auto status_ = onOnWithRecallGlobalSceneCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 66: {
            auto ctrlbits = request.readUInt8();
            auto ontime = request.readUInt16Le();
            auto offwaittime = request.readUInt16Le();
            auto status_ = onOnWithTimedOffCommand(ctrlbits, ontime, offwaittime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* GenOnOffSwitchCfgCluster::getSwitchType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenOnOffSwitchCfgAttribute::SwitchType);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenOnOffSwitchCfgCluster::getSwitchActions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenOnOffSwitchCfgAttribute::SwitchActions);
    if (result == nullptr) {
        result = new AttributeUInt8(16, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenLevelCtrlCluster::getCurrentLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenLevelCtrlAttribute::CurrentLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenLevelCtrlCluster::getRemainingTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenLevelCtrlAttribute::RemainingTime);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenLevelCtrlCluster::getMinLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenLevelCtrlAttribute::MinLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenLevelCtrlCluster::getMaxLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenLevelCtrlAttribute::MaxLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenLevelCtrlCluster::getOptions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenLevelCtrlAttribute::Options);
    if (result == nullptr) {
        result = new AttributeUInt8(15, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenLevelCtrlCluster::getOnOffTransitionTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenLevelCtrlAttribute::OnOffTransitionTime);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenLevelCtrlCluster::getOnLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenLevelCtrlAttribute::OnLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(17, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenLevelCtrlCluster::getOnTransitionTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenLevelCtrlAttribute::OnTransitionTime);
    if (result == nullptr) {
        result = new AttributeUInt16(18, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenLevelCtrlCluster::getOffTransitionTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenLevelCtrlAttribute::OffTransitionTime);
    if (result == nullptr) {
        result = new AttributeUInt16(19, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenLevelCtrlCluster::getDefaultMoveRate() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenLevelCtrlAttribute::DefaultMoveRate);
    if (result == nullptr) {
        result = new AttributeUInt16(20, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenLevelCtrlCluster::getStartUpCurrentLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenLevelCtrlAttribute::StartUpCurrentLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(16384, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

void GenLevelCtrlCluster::sendMoveToLevelCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t level, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(level);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendMoveCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t movemode, uint8_t rate) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeUInt8(movemode);
    buffer.writeUInt8(rate);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendStepCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t stepmode, uint8_t stepsize, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt8(stepmode);
    buffer.writeUInt8(stepsize);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendStopCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendMoveToLevelWithOnOffCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t level, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);

    buffer.writeUInt8(level);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendMoveWithOnOffCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t movemode, uint8_t rate) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        5
    ).write(buffer);

    buffer.writeUInt8(movemode);
    buffer.writeUInt8(rate);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendStepWithOnOffCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t stepmode, uint8_t stepsize, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        6
    ).write(buffer);

    buffer.writeUInt8(stepmode);
    buffer.writeUInt8(stepsize);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendStopWithOnOffCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        7
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::sendMoveToLevelTuyaCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t level, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        240
    ).write(buffer);

    buffer.writeUInt16Le(level);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenLevelCtrlCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto level = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToLevelCommand(level, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto movemode = request.readUInt8();
            auto rate = request.readUInt8();
            auto status_ = onMoveCommand(movemode, rate);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto stepmode = request.readUInt8();
            auto stepsize = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onStepCommand(stepmode, stepsize, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto status_ = onStopCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto level = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToLevelWithOnOffCommand(level, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 5: {
            auto movemode = request.readUInt8();
            auto rate = request.readUInt8();
            auto status_ = onMoveWithOnOffCommand(movemode, rate);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 6: {
            auto stepmode = request.readUInt8();
            auto stepsize = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onStepWithOnOffCommand(stepmode, stepsize, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 7: {
            auto status_ = onStopWithOnOffCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 240: {
            auto level = request.readUInt16Le();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToLevelTuyaCommand(level, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt16* GenAlarmsCluster::getAlarmCount() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenAlarmsAttribute::AlarmCount);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void GenAlarmsCluster::sendResetCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t alarmcode, uint16_t clusterid) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(alarmcode);
    buffer.writeUInt16Le(clusterid);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenAlarmsCluster::sendResetAllCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenAlarmsCluster::sendGetAlarmCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenAlarmsCluster::sendResetLogCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenAlarmsCluster::sendPublishEventLogCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenAlarmsCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto alarmcode = request.readUInt8();
            auto clusterid = request.readUInt16Le();
            auto status_ = onResetCommand(alarmcode, clusterid);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onResetAllCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto status_ = onGetAlarmCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto status_ = onResetLogCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto status_ = onPublishEventLogCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt32* GenTimeCluster::getTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenTimeAttribute::Time);
    if (result == nullptr) {
        result = new AttributeUInt32(0, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenTimeCluster::getTimeStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenTimeAttribute::TimeStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeInt32* GenTimeCluster::getTimeZone() {
    auto result = (AttributeInt32*)getAttributeById((uint16_t)GenTimeAttribute::TimeZone);
    if (result == nullptr) {
        result = new AttributeInt32(2, DataType::Int32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenTimeCluster::getDstStart() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenTimeAttribute::DstStart);
    if (result == nullptr) {
        result = new AttributeUInt32(3, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenTimeCluster::getDstEnd() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenTimeAttribute::DstEnd);
    if (result == nullptr) {
        result = new AttributeUInt32(4, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeInt32* GenTimeCluster::getDstShift() {
    auto result = (AttributeInt32*)getAttributeById((uint16_t)GenTimeAttribute::DstShift);
    if (result == nullptr) {
        result = new AttributeInt32(5, DataType::Int32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenTimeCluster::getStandardTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenTimeAttribute::StandardTime);
    if (result == nullptr) {
        result = new AttributeUInt32(6, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenTimeCluster::getLocalTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenTimeAttribute::LocalTime);
    if (result == nullptr) {
        result = new AttributeUInt32(7, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenTimeCluster::getLastSetTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenTimeAttribute::LastSetTime);
    if (result == nullptr) {
        result = new AttributeUInt32(8, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenTimeCluster::getValidUntilTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenTimeAttribute::ValidUntilTime);
    if (result == nullptr) {
        result = new AttributeUInt32(9, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenRssiLocationCluster::getType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenRssiLocationAttribute::Type);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Data8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenRssiLocationCluster::getMethod() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenRssiLocationAttribute::Method);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenRssiLocationCluster::getAge() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::Age);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenRssiLocationCluster::getQualityMeasure() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenRssiLocationAttribute::QualityMeasure);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenRssiLocationCluster::getNumOfDevices() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenRssiLocationAttribute::NumOfDevices);
    if (result == nullptr) {
        result = new AttributeUInt8(4, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenRssiLocationCluster::getCoordinate1() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::Coordinate1);
    if (result == nullptr) {
        result = new AttributeInt16(16, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenRssiLocationCluster::getCoordinate2() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::Coordinate2);
    if (result == nullptr) {
        result = new AttributeInt16(17, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenRssiLocationCluster::getCoordinate3() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::Coordinate3);
    if (result == nullptr) {
        result = new AttributeInt16(18, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* GenRssiLocationCluster::getPower() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::Power);
    if (result == nullptr) {
        result = new AttributeInt16(19, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenRssiLocationCluster::getPathLossExponent() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::PathLossExponent);
    if (result == nullptr) {
        result = new AttributeUInt16(20, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenRssiLocationCluster::getReportingPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::ReportingPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(21, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenRssiLocationCluster::getCalcPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::CalcPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(22, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenRssiLocationCluster::getNumRSSIMeasurements() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenRssiLocationAttribute::NumRSSIMeasurements);
    if (result == nullptr) {
        result = new AttributeUInt16(23, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void GenRssiLocationCluster::sendSetAbsoluteCommand(DeviceManager& deviceManager, uint8_t endpointId, int16_t coord1, int16_t coord2, int16_t coord3, int16_t power, uint16_t pathlossexponent) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeInt16Le(coord1);
    buffer.writeInt16Le(coord2);
    buffer.writeInt16Le(coord3);
    buffer.writeInt16Le(power);
    buffer.writeUInt16Le(pathlossexponent);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenRssiLocationCluster::sendSetDevCfgCommand(DeviceManager& deviceManager, uint8_t endpointId, int16_t power, uint16_t pathlossexponent, uint16_t calperiod, uint8_t numrssimeasurements, uint16_t reportingperiod) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeInt16Le(power);
    buffer.writeUInt16Le(pathlossexponent);
    buffer.writeUInt16Le(calperiod);
    buffer.writeUInt8(numrssimeasurements);
    buffer.writeUInt16Le(reportingperiod);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenRssiLocationCluster::sendGetDevCfgCommand(DeviceManager& deviceManager, uint8_t endpointId, uint64_t targetaddr) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt64Le(targetaddr);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenRssiLocationCluster::sendGetDataCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t getdatainfo, uint8_t numrsp, uint64_t targetaddr) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);

    buffer.writeUInt8(getdatainfo);
    buffer.writeUInt8(numrsp);
    buffer.writeUInt64Le(targetaddr);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenRssiLocationCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto coord1 = request.readInt16Le();
            auto coord2 = request.readInt16Le();
            auto coord3 = request.readInt16Le();
            auto power = request.readInt16Le();
            auto pathlossexponent = request.readUInt16Le();
            auto status_ = onSetAbsoluteCommand(coord1, coord2, coord3, power, pathlossexponent);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto power = request.readInt16Le();
            auto pathlossexponent = request.readUInt16Le();
            auto calperiod = request.readUInt16Le();
            auto numrssimeasurements = request.readUInt8();
            auto reportingperiod = request.readUInt16Le();
            auto status_ = onSetDevCfgCommand(power, pathlossexponent, calperiod, numrssimeasurements, reportingperiod);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto targetaddr = request.readUInt64Le();
            auto status_ = onGetDevCfgCommand(targetaddr);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto getdatainfo = request.readUInt8();
            auto numrsp = request.readUInt8();
            auto targetaddr = request.readUInt64Le();
            auto status_ = onGetDataCommand(getdatainfo, numrsp, targetaddr);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeString* GenAnalogInputCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenAnalogInputAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogInputCluster::getMaxPresentValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogInputAttribute::MaxPresentValue);
    if (result == nullptr) {
        result = new AttributeSingle(65, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogInputCluster::getMinPresentValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogInputAttribute::MinPresentValue);
    if (result == nullptr) {
        result = new AttributeSingle(69, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogInputCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogInputAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogInputCluster::getPresentValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogInputAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeSingle(85, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogInputCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogInputAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogInputCluster::getResolution() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogInputAttribute::Resolution);
    if (result == nullptr) {
        result = new AttributeSingle(106, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogInputCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogInputAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenAnalogInputCluster::getEngineeringUnits() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenAnalogInputAttribute::EngineeringUnits);
    if (result == nullptr) {
        result = new AttributeUInt16(117, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenAnalogInputCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenAnalogInputAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenAnalogOutputCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenAnalogOutputAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogOutputCluster::getMaxPresentValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogOutputAttribute::MaxPresentValue);
    if (result == nullptr) {
        result = new AttributeSingle(65, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogOutputCluster::getMinPresentValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogOutputAttribute::MinPresentValue);
    if (result == nullptr) {
        result = new AttributeSingle(69, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogOutputCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogOutputAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogOutputCluster::getPresentValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogOutputAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeSingle(85, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogOutputCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogOutputAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogOutputCluster::getRelinquishDefault() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogOutputAttribute::RelinquishDefault);
    if (result == nullptr) {
        result = new AttributeSingle(104, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogOutputCluster::getResolution() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogOutputAttribute::Resolution);
    if (result == nullptr) {
        result = new AttributeSingle(106, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogOutputCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogOutputAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenAnalogOutputCluster::getEngineeringUnits() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenAnalogOutputAttribute::EngineeringUnits);
    if (result == nullptr) {
        result = new AttributeUInt16(117, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenAnalogOutputCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenAnalogOutputAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenAnalogValueCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenAnalogValueAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogValueCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogValueAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogValueCluster::getPresentValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogValueAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeSingle(85, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogValueCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogValueAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* GenAnalogValueCluster::getRelinquishDefault() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)GenAnalogValueAttribute::RelinquishDefault);
    if (result == nullptr) {
        result = new AttributeSingle(104, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenAnalogValueCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenAnalogValueAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenAnalogValueCluster::getEngineeringUnits() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenAnalogValueAttribute::EngineeringUnits);
    if (result == nullptr) {
        result = new AttributeUInt16(117, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenAnalogValueCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenAnalogValueAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryInputCluster::getActiveText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryInputAttribute::ActiveText);
    if (result == nullptr) {
        result = new AttributeString(4);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryInputCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryInputAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryInputCluster::getInactiveText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryInputAttribute::InactiveText);
    if (result == nullptr) {
        result = new AttributeString(46);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryInputCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryInputAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryInputCluster::getPolarity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryInputAttribute::Polarity);
    if (result == nullptr) {
        result = new AttributeUInt8(84, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryInputCluster::getPresentValue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryInputAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeUInt8(85, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryInputCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryInputAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryInputCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryInputAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenBinaryInputCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenBinaryInputAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryOutputCluster::getActiveText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryOutputAttribute::ActiveText);
    if (result == nullptr) {
        result = new AttributeString(4);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryOutputCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryOutputAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryOutputCluster::getInactiveText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryOutputAttribute::InactiveText);
    if (result == nullptr) {
        result = new AttributeString(46);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenBinaryOutputCluster::getMinimumOffTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenBinaryOutputAttribute::MinimumOffTime);
    if (result == nullptr) {
        result = new AttributeUInt32(66, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenBinaryOutputCluster::getMinimumOnTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenBinaryOutputAttribute::MinimumOnTime);
    if (result == nullptr) {
        result = new AttributeUInt32(67, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryOutputCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryOutputAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryOutputCluster::getPolarity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryOutputAttribute::Polarity);
    if (result == nullptr) {
        result = new AttributeUInt8(84, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryOutputCluster::getPresentValue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryOutputAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeUInt8(85, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryOutputCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryOutputAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryOutputCluster::getRelinquishDefault() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryOutputAttribute::RelinquishDefault);
    if (result == nullptr) {
        result = new AttributeUInt8(104, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryOutputCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryOutputAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenBinaryOutputCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenBinaryOutputAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryValueCluster::getActiveText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryValueAttribute::ActiveText);
    if (result == nullptr) {
        result = new AttributeString(4);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryValueCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryValueAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenBinaryValueCluster::getInactiveText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenBinaryValueAttribute::InactiveText);
    if (result == nullptr) {
        result = new AttributeString(46);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenBinaryValueCluster::getMinimumOffTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenBinaryValueAttribute::MinimumOffTime);
    if (result == nullptr) {
        result = new AttributeUInt32(66, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenBinaryValueCluster::getMinimumOnTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenBinaryValueAttribute::MinimumOnTime);
    if (result == nullptr) {
        result = new AttributeUInt32(67, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryValueCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryValueAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryValueCluster::getPresentValue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryValueAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeUInt8(85, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryValueCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryValueAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryValueCluster::getRelinquishDefault() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryValueAttribute::RelinquishDefault);
    if (result == nullptr) {
        result = new AttributeUInt8(104, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenBinaryValueCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenBinaryValueAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenBinaryValueCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenBinaryValueAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenMultistateInputCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenMultistateInputAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateInputCluster::getNumberOfStates() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateInputAttribute::NumberOfStates);
    if (result == nullptr) {
        result = new AttributeUInt16(74, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateInputCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateInputAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateInputCluster::getPresentValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateInputAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeUInt16(85, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateInputCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateInputAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateInputCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateInputAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenMultistateInputCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenMultistateInputAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenMultistateOutputCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenMultistateOutputAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateOutputCluster::getNumberOfStates() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateOutputAttribute::NumberOfStates);
    if (result == nullptr) {
        result = new AttributeUInt16(74, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateOutputCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateOutputAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateOutputCluster::getPresentValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateOutputAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeUInt16(85, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateOutputCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateOutputAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateOutputCluster::getRelinquishDefault() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateOutputAttribute::RelinquishDefault);
    if (result == nullptr) {
        result = new AttributeUInt16(104, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateOutputCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateOutputAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenMultistateOutputCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenMultistateOutputAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeString* GenMultistateValueCluster::getDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)GenMultistateValueAttribute::Description);
    if (result == nullptr) {
        result = new AttributeString(28);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateValueCluster::getNumberOfStates() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateValueAttribute::NumberOfStates);
    if (result == nullptr) {
        result = new AttributeUInt16(74, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateValueCluster::getOutOfService() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateValueAttribute::OutOfService);
    if (result == nullptr) {
        result = new AttributeUInt8(81, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateValueCluster::getPresentValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateValueAttribute::PresentValue);
    if (result == nullptr) {
        result = new AttributeUInt16(85, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateValueCluster::getReliability() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateValueAttribute::Reliability);
    if (result == nullptr) {
        result = new AttributeUInt8(103, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenMultistateValueCluster::getRelinquishDefault() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenMultistateValueAttribute::RelinquishDefault);
    if (result == nullptr) {
        result = new AttributeUInt16(104, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenMultistateValueCluster::getStatusFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenMultistateValueAttribute::StatusFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(111, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenMultistateValueCluster::getApplicationType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenMultistateValueAttribute::ApplicationType);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenCommissioningCluster::getShortress() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenCommissioningAttribute::Shortress);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt64* GenCommissioningCluster::getExtendedPANId() {
    auto result = (AttributeUInt64*)getAttributeById((uint16_t)GenCommissioningAttribute::ExtendedPANId);
    if (result == nullptr) {
        result = new AttributeUInt64(1, DataType::EUI64);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenCommissioningCluster::getPanId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenCommissioningAttribute::PanId);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenCommissioningCluster::getChannelmask() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenCommissioningAttribute::Channelmask);
    if (result == nullptr) {
        result = new AttributeUInt32(3, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getProtocolVersion() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::ProtocolVersion);
    if (result == nullptr) {
        result = new AttributeUInt8(4, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getStackProfile() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::StackProfile);
    if (result == nullptr) {
        result = new AttributeUInt8(5, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getStartupControl() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::StartupControl);
    if (result == nullptr) {
        result = new AttributeUInt8(6, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt64* GenCommissioningCluster::getTrustCenterress() {
    auto result = (AttributeUInt64*)getAttributeById((uint16_t)GenCommissioningAttribute::TrustCenterress);
    if (result == nullptr) {
        result = new AttributeUInt64(16, DataType::EUI64);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getUseInsecureJoin() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::UseInsecureJoin);
    if (result == nullptr) {
        result = new AttributeUInt8(19, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getNetworkKeySeqNum() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::NetworkKeySeqNum);
    if (result == nullptr) {
        result = new AttributeUInt8(21, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getNetworkKeyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::NetworkKeyType);
    if (result == nullptr) {
        result = new AttributeUInt8(22, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenCommissioningCluster::getNetworkManagerress() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenCommissioningAttribute::NetworkManagerress);
    if (result == nullptr) {
        result = new AttributeUInt16(23, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getScanAttempts() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::ScanAttempts);
    if (result == nullptr) {
        result = new AttributeUInt8(32, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenCommissioningCluster::getTimeBetweenScans() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenCommissioningAttribute::TimeBetweenScans);
    if (result == nullptr) {
        result = new AttributeUInt16(33, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenCommissioningCluster::getRejoinInterval() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenCommissioningAttribute::RejoinInterval);
    if (result == nullptr) {
        result = new AttributeUInt16(34, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenCommissioningCluster::getMaxRejoinInterval() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenCommissioningAttribute::MaxRejoinInterval);
    if (result == nullptr) {
        result = new AttributeUInt16(35, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenCommissioningCluster::getIndirectPollRate() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenCommissioningAttribute::IndirectPollRate);
    if (result == nullptr) {
        result = new AttributeUInt16(48, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getParentRetryThreshold() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::ParentRetryThreshold);
    if (result == nullptr) {
        result = new AttributeUInt8(49, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getConcentratorFlag() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::ConcentratorFlag);
    if (result == nullptr) {
        result = new AttributeUInt8(64, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getConcentratorRus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::ConcentratorRus);
    if (result == nullptr) {
        result = new AttributeUInt8(65, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenCommissioningCluster::getConcentratorDiscoveryTime() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenCommissioningAttribute::ConcentratorDiscoveryTime);
    if (result == nullptr) {
        result = new AttributeUInt8(66, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

void GenCommissioningCluster::sendRestartDeviceCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t options, uint8_t delay, uint8_t jitter) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(options);
    buffer.writeUInt8(delay);
    buffer.writeUInt8(jitter);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenCommissioningCluster::sendSaveStartupParamsCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t options, uint8_t index) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeUInt8(options);
    buffer.writeUInt8(index);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenCommissioningCluster::sendRestoreStartupParamsCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t options, uint8_t index) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt8(options);
    buffer.writeUInt8(index);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenCommissioningCluster::sendResetStartupParamsCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t options, uint8_t index) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);

    buffer.writeUInt8(options);
    buffer.writeUInt8(index);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenCommissioningCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto options = request.readUInt8();
            auto delay = request.readUInt8();
            auto jitter = request.readUInt8();
            auto status_ = onRestartDeviceCommand(options, delay, jitter);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto options = request.readUInt8();
            auto index = request.readUInt8();
            auto status_ = onSaveStartupParamsCommand(options, index);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto options = request.readUInt8();
            auto index = request.readUInt8();
            auto status_ = onRestoreStartupParamsCommand(options, index);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto options = request.readUInt8();
            auto index = request.readUInt8();
            auto status_ = onResetStartupParamsCommand(options, index);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt64* GenOtaCluster::getUpgradeServerId() {
    auto result = (AttributeUInt64*)getAttributeById((uint16_t)GenOtaAttribute::UpgradeServerId);
    if (result == nullptr) {
        result = new AttributeUInt64(0, DataType::EUI64);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenOtaCluster::getFileOffset() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenOtaAttribute::FileOffset);
    if (result == nullptr) {
        result = new AttributeUInt32(1, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenOtaCluster::getCurrentFileVersion() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenOtaAttribute::CurrentFileVersion);
    if (result == nullptr) {
        result = new AttributeUInt32(2, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenOtaCluster::getCurrentZigbeeStackVersion() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenOtaAttribute::CurrentZigbeeStackVersion);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenOtaCluster::getDownloadedFileVersion() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenOtaAttribute::DownloadedFileVersion);
    if (result == nullptr) {
        result = new AttributeUInt32(4, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenOtaCluster::getDownloadedZigbeeStackVersion() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenOtaAttribute::DownloadedZigbeeStackVersion);
    if (result == nullptr) {
        result = new AttributeUInt16(5, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* GenOtaCluster::getImageUpgradeStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)GenOtaAttribute::ImageUpgradeStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(6, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenOtaCluster::getManufacturerId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenOtaAttribute::ManufacturerId);
    if (result == nullptr) {
        result = new AttributeUInt16(7, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenOtaCluster::getImageTypeId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenOtaAttribute::ImageTypeId);
    if (result == nullptr) {
        result = new AttributeUInt16(8, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenOtaCluster::getMinimumBlockReqDelay() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenOtaAttribute::MinimumBlockReqDelay);
    if (result == nullptr) {
        result = new AttributeUInt16(9, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenOtaCluster::getImageStamp() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenOtaAttribute::ImageStamp);
    if (result == nullptr) {
        result = new AttributeUInt32(10, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

void GenOtaCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 1: {
            auto fieldControl = request.readUInt8();
            auto manufacturerCode = request.readUInt16Le();
            auto imageType = request.readUInt16Le();
            auto fileVersion = request.readUInt32Le();
            QueryNextImageRequestCommandResponse response_;
            auto status_ = onQueryNextImageRequestCommand(fieldControl, manufacturerCode, imageType, fileVersion, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
                response.writeUInt16Le(response_.getManufacturerCode());
                response.writeUInt16Le(response_.getImageType());
                response.writeUInt32Le(response_.getFileVersion());
                response.writeUInt32Le(response_.getImageSize());
            }
            return;
        }
        case 6: {
            auto status = request.readUInt8();
            auto manufacturerCode = request.readUInt16Le();
            auto imageType = request.readUInt16Le();
            auto fileVersion = request.readUInt32Le();
            UpgradeEndRequestCommandResponse response_;
            auto status_ = onUpgradeEndRequestCommand(status, manufacturerCode, imageType, fileVersion, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt16Le(response_.getManufacturerCode());
                response.writeUInt16Le(response_.getImageType());
                response.writeUInt32Le(response_.getFileVersion());
                response.writeUInt32Le(response_.getCurrentTime());
                response.writeUInt32Le(response_.getUpgradeTime());
            }
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt32* GenPollCtrlCluster::getCheckinInterval() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenPollCtrlAttribute::CheckinInterval);
    if (result == nullptr) {
        result = new AttributeUInt32(0, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenPollCtrlCluster::getLongPollInterval() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenPollCtrlAttribute::LongPollInterval);
    if (result == nullptr) {
        result = new AttributeUInt32(1, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenPollCtrlCluster::getShortPollInterval() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPollCtrlAttribute::ShortPollInterval);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenPollCtrlCluster::getFastPollTimeout() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPollCtrlAttribute::FastPollTimeout);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenPollCtrlCluster::getCheckinIntervalMin() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenPollCtrlAttribute::CheckinIntervalMin);
    if (result == nullptr) {
        result = new AttributeUInt32(4, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* GenPollCtrlCluster::getLongPollIntervalMin() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)GenPollCtrlAttribute::LongPollIntervalMin);
    if (result == nullptr) {
        result = new AttributeUInt32(5, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* GenPollCtrlCluster::getFastPollTimeoutMax() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)GenPollCtrlAttribute::FastPollTimeoutMax);
    if (result == nullptr) {
        result = new AttributeUInt16(6, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void GenPollCtrlCluster::sendCheckinRspCommand(DeviceManager& deviceManager, uint8_t endpointId, bool startFastPolling, uint16_t fastPollTimeout) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(startFastPolling);
    buffer.writeUInt16Le(fastPollTimeout);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenPollCtrlCluster::sendFastPollStopCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenPollCtrlCluster::sendSetLongPollIntervalCommand(DeviceManager& deviceManager, uint8_t endpointId, uint32_t newLongPollInterval) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt32Le(newLongPollInterval);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenPollCtrlCluster::sendSetShortPollIntervalCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t newShortPollInterval) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);

    buffer.writeUInt16Le(newShortPollInterval);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void GenPollCtrlCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto startFastPolling = request.readUInt8();
            auto fastPollTimeout = request.readUInt16Le();
            auto status_ = onCheckinRspCommand(startFastPolling, fastPollTimeout);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onFastPollStopCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto newLongPollInterval = request.readUInt32Le();
            auto status_ = onSetLongPollIntervalCommand(newLongPollInterval);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto newShortPollInterval = request.readUInt16Le();
            auto status_ = onSetShortPollIntervalCommand(newShortPollInterval);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt16* MobileDeviceCfgCluster::getKeepAliveTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MobileDeviceCfgAttribute::KeepAliveTime);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MobileDeviceCfgCluster::getRejoinTimeout() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MobileDeviceCfgAttribute::RejoinTimeout);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* NeighborCleaningCluster::getNeighborCleaningTimeout() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)NeighborCleaningAttribute::NeighborCleaningTimeout);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* NearestGatewayCluster::getNearestGateway() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)NearestGatewayAttribute::NearestGateway);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* NearestGatewayCluster::getNewMobileNode() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)NearestGatewayAttribute::NewMobileNode);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresShadeCfgCluster::getPhysicalClosedLimit() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresShadeCfgAttribute::PhysicalClosedLimit);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresShadeCfgCluster::getMotorStepSize() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresShadeCfgAttribute::MotorStepSize);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresShadeCfgCluster::getStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresShadeCfgAttribute::Status);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresShadeCfgCluster::getLosedLimit() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresShadeCfgAttribute::LosedLimit);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresShadeCfgCluster::getMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresShadeCfgAttribute::Mode);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getLockState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::LockState);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getLockType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::LockType);
    if (result == nullptr) {
        result = new AttributeUInt16(38, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getActuatorEnabled() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::ActuatorEnabled);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getDoorState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::DoorState);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* ClosuresDoorLockCluster::getDoorOpenEvents() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::DoorOpenEvents);
    if (result == nullptr) {
        result = new AttributeUInt32(4, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* ClosuresDoorLockCluster::getDoorClosedEvents() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::DoorClosedEvents);
    if (result == nullptr) {
        result = new AttributeUInt32(5, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getOpenPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::OpenPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(6, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getNumOfLockRecordsSupported() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::NumOfLockRecordsSupported);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getNumOfTotalUsersSupported() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::NumOfTotalUsersSupported);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getNumOfPinUsersSupported() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::NumOfPinUsersSupported);
    if (result == nullptr) {
        result = new AttributeUInt16(18, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getNumOfRfidUsersSupported() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::NumOfRfidUsersSupported);
    if (result == nullptr) {
        result = new AttributeUInt16(19, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getNumOfWeekDaySchedulesSupportedPerUser() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::NumOfWeekDaySchedulesSupportedPerUser);
    if (result == nullptr) {
        result = new AttributeUInt8(20, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getNumOfYearDaySchedulesSupportedPerUser() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::NumOfYearDaySchedulesSupportedPerUser);
    if (result == nullptr) {
        result = new AttributeUInt8(21, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getNumOfHolidayScheduledsSupported() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::NumOfHolidayScheduledsSupported);
    if (result == nullptr) {
        result = new AttributeUInt8(22, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getMaxPinLen() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::MaxPinLen);
    if (result == nullptr) {
        result = new AttributeUInt8(23, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getMinPinLen() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::MinPinLen);
    if (result == nullptr) {
        result = new AttributeUInt8(24, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getMaxRfidLen() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::MaxRfidLen);
    if (result == nullptr) {
        result = new AttributeUInt8(25, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getMinRfidLen() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::MinRfidLen);
    if (result == nullptr) {
        result = new AttributeUInt8(26, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getEnableLogging() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::EnableLogging);
    if (result == nullptr) {
        result = new AttributeUInt8(32, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeString* ClosuresDoorLockCluster::getLanguage() {
    auto result = (AttributeString*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::Language);
    if (result == nullptr) {
        result = new AttributeString(33);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getLedSettings() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::LedSettings);
    if (result == nullptr) {
        result = new AttributeUInt8(34, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* ClosuresDoorLockCluster::getAutoRelockTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::AutoRelockTime);
    if (result == nullptr) {
        result = new AttributeUInt32(35, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getSoundVolume() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::SoundVolume);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* ClosuresDoorLockCluster::getOperatingMode() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::OperatingMode);
    if (result == nullptr) {
        result = new AttributeUInt32(37, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getDefaultConfigurationRegister() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::DefaultConfigurationRegister);
    if (result == nullptr) {
        result = new AttributeUInt16(39, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getEnableLocalProgramming() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::EnableLocalProgramming);
    if (result == nullptr) {
        result = new AttributeUInt8(40, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getEnableOneTouchLocking() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::EnableOneTouchLocking);
    if (result == nullptr) {
        result = new AttributeUInt8(41, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getEnableInsideStatusLed() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::EnableInsideStatusLed);
    if (result == nullptr) {
        result = new AttributeUInt8(42, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getEnablePrivacyModeButton() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::EnablePrivacyModeButton);
    if (result == nullptr) {
        result = new AttributeUInt8(43, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getWrongCodeEntryLimit() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::WrongCodeEntryLimit);
    if (result == nullptr) {
        result = new AttributeUInt8(48, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getUserCodeTemporaryDisableTime() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::UserCodeTemporaryDisableTime);
    if (result == nullptr) {
        result = new AttributeUInt8(49, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getSendPinOta() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::SendPinOta);
    if (result == nullptr) {
        result = new AttributeUInt8(50, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getRequirePinForRfOperation() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::RequirePinForRfOperation);
    if (result == nullptr) {
        result = new AttributeUInt8(51, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresDoorLockCluster::getZigbeeSecurityLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::ZigbeeSecurityLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(52, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getAlarmMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::AlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt16(64, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getKeypadOperationEventMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::KeypadOperationEventMask);
    if (result == nullptr) {
        result = new AttributeUInt16(65, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getRfOperationEventMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::RfOperationEventMask);
    if (result == nullptr) {
        result = new AttributeUInt16(66, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getManualOperationEventMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::ManualOperationEventMask);
    if (result == nullptr) {
        result = new AttributeUInt16(67, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getRfidOperationEventMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::RfidOperationEventMask);
    if (result == nullptr) {
        result = new AttributeUInt16(68, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getKeypadProgrammingEventMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::KeypadProgrammingEventMask);
    if (result == nullptr) {
        result = new AttributeUInt16(69, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getRfProgrammingEventMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::RfProgrammingEventMask);
    if (result == nullptr) {
        result = new AttributeUInt16(70, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresDoorLockCluster::getRfidProgrammingEventMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresDoorLockAttribute::RfidProgrammingEventMask);
    if (result == nullptr) {
        result = new AttributeUInt16(71, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

void ClosuresDoorLockCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto pincodevalue = request.readString();
            LockDoorCommandResponse response_;
            auto status_ = onLockDoorCommand(pincodevalue, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 1: {
            auto pincodevalue = request.readString();
            UnlockDoorCommandResponse response_;
            auto status_ = onUnlockDoorCommand(pincodevalue, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 2: {
            auto pincodevalue = request.readString();
            ToggleDoorCommandResponse response_;
            auto status_ = onToggleDoorCommand(pincodevalue, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 3: {
            auto timeout = request.readUInt16Le();
            auto pincodevalue = request.readString();
            UnlockWithTimeoutCommandResponse response_;
            auto status_ = onUnlockWithTimeoutCommand(timeout, pincodevalue, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 4: {
            auto logindex = request.readUInt16Le();
            GetLogRecordCommandResponse response_;
            auto status_ = onGetLogRecordCommand(logindex, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt16Le(response_.getLogentryid());
                response.writeUInt32Le(response_.getTimestamp());
                response.writeUInt8(response_.getEventtype());
                response.writeUInt8(response_.getSource());
                response.writeUInt8(response_.getEventidalarmcode());
                response.writeUInt16Le(response_.getUserid());
                response.writeString(response_.getPincodevalue());
            }
            return;
        }
        case 5: {
            auto userid = request.readUInt16Le();
            auto userstatus = request.readUInt8();
            auto usertype = request.readUInt8();
            auto pincodevalue = request.readString();
            SetPinCodeCommandResponse response_;
            auto status_ = onSetPinCodeCommand(userid, userstatus, usertype, pincodevalue, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 6: {
            auto userid = request.readUInt16Le();
            GetPinCodeCommandResponse response_;
            auto status_ = onGetPinCodeCommand(userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt16Le(response_.getUserid());
                response.writeUInt8(response_.getUserstatus());
                response.writeUInt8(response_.getUsertype());
                response.writeString(response_.getPincodevalue());
            }
            return;
        }
        case 7: {
            auto userid = request.readUInt16Le();
            ClearPinCodeCommandResponse response_;
            auto status_ = onClearPinCodeCommand(userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 8: {
            ClearAllPinCodesCommandResponse response_;
            auto status_ = onClearAllPinCodesCommand(response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 9: {
            auto userid = request.readUInt16Le();
            auto userstatus = request.readUInt8();
            SetUserStatusCommandResponse response_;
            auto status_ = onSetUserStatusCommand(userid, userstatus, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 10: {
            auto userid = request.readUInt16Le();
            GetUserStatusCommandResponse response_;
            auto status_ = onGetUserStatusCommand(userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt16Le(response_.getUserid());
                response.writeUInt8(response_.getUserstatus());
            }
            return;
        }
        case 11: {
            auto scheduleid = request.readUInt8();
            auto userid = request.readUInt16Le();
            auto daysmask = request.readUInt8();
            auto starthour = request.readUInt8();
            auto startminute = request.readUInt8();
            auto endhour = request.readUInt8();
            auto endminute = request.readUInt8();
            SetWeekDayScheduleCommandResponse response_;
            auto status_ = onSetWeekDayScheduleCommand(scheduleid, userid, daysmask, starthour, startminute, endhour, endminute, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 12: {
            auto scheduleid = request.readUInt8();
            auto userid = request.readUInt16Le();
            GetWeekDayScheduleCommandResponse response_;
            auto status_ = onGetWeekDayScheduleCommand(scheduleid, userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getScheduleid());
                response.writeUInt16Le(response_.getUserid());
                response.writeUInt8(response_.getStatus());
                response.writeUInt8(response_.getDaysmask());
                response.writeUInt8(response_.getStarthour());
                response.writeUInt8(response_.getStartminute());
                response.writeUInt8(response_.getEndhour());
                response.writeUInt8(response_.getEndminute());
            }
            return;
        }
        case 13: {
            auto scheduleid = request.readUInt8();
            auto userid = request.readUInt16Le();
            ClearWeekDayScheduleCommandResponse response_;
            auto status_ = onClearWeekDayScheduleCommand(scheduleid, userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 14: {
            auto scheduleid = request.readUInt8();
            auto userid = request.readUInt16Le();
            auto zigbeelocalstarttime = request.readUInt32Le();
            auto zigbeelocalendtime = request.readUInt32Le();
            SetYearDayScheduleCommandResponse response_;
            auto status_ = onSetYearDayScheduleCommand(scheduleid, userid, zigbeelocalstarttime, zigbeelocalendtime, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 15: {
            auto scheduleid = request.readUInt8();
            auto userid = request.readUInt16Le();
            GetYearDayScheduleCommandResponse response_;
            auto status_ = onGetYearDayScheduleCommand(scheduleid, userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getScheduleid());
                response.writeUInt16Le(response_.getUserid());
                response.writeUInt8(response_.getStatus());
                response.writeUInt32Le(response_.getZigbeelocalstarttime());
                response.writeUInt32Le(response_.getZigbeelocalendtime());
            }
            return;
        }
        case 16: {
            auto scheduleid = request.readUInt8();
            auto userid = request.readUInt16Le();
            ClearYearDayScheduleCommandResponse response_;
            auto status_ = onClearYearDayScheduleCommand(scheduleid, userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 17: {
            auto holidayscheduleid = request.readUInt8();
            auto zigbeelocalstarttime = request.readUInt32Le();
            auto zigbeelocalendtime = request.readUInt32Le();
            auto opermodelduringholiday = request.readUInt8();
            SetHolidayScheduleCommandResponse response_;
            auto status_ = onSetHolidayScheduleCommand(holidayscheduleid, zigbeelocalstarttime, zigbeelocalendtime, opermodelduringholiday, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 18: {
            auto holidayscheduleid = request.readUInt8();
            GetHolidayScheduleCommandResponse response_;
            auto status_ = onGetHolidayScheduleCommand(holidayscheduleid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getHolidayscheduleid());
                response.writeUInt8(response_.getStatus());
                response.writeUInt32Le(response_.getZigbeelocalstarttime());
                response.writeUInt32Le(response_.getZigbeelocalendtime());
                response.writeUInt8(response_.getOpermodelduringholiday());
            }
            return;
        }
        case 19: {
            auto holidayscheduleid = request.readUInt8();
            ClearHolidayScheduleCommandResponse response_;
            auto status_ = onClearHolidayScheduleCommand(holidayscheduleid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 20: {
            auto userid = request.readUInt16Le();
            auto usertype = request.readUInt8();
            SetUserTypeCommandResponse response_;
            auto status_ = onSetUserTypeCommand(userid, usertype, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 21: {
            auto userid = request.readUInt16Le();
            GetUserTypeCommandResponse response_;
            auto status_ = onGetUserTypeCommand(userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt16Le(response_.getUserid());
                response.writeUInt8(response_.getUsertype());
            }
            return;
        }
        case 22: {
            auto userid = request.readUInt16Le();
            auto userstatus = request.readUInt8();
            auto usertype = request.readUInt8();
            auto pincodevalue = request.readString();
            SetRfidCodeCommandResponse response_;
            auto status_ = onSetRfidCodeCommand(userid, userstatus, usertype, pincodevalue, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 23: {
            auto userid = request.readUInt16Le();
            GetRfidCodeCommandResponse response_;
            auto status_ = onGetRfidCodeCommand(userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt16Le(response_.getUserid());
                response.writeUInt8(response_.getUserstatus());
                response.writeUInt8(response_.getUsertype());
                response.writeString(response_.getPincodevalue());
            }
            return;
        }
        case 24: {
            auto userid = request.readUInt16Le();
            ClearRfidCodeCommandResponse response_;
            auto status_ = onClearRfidCodeCommand(userid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        case 25: {
            ClearAllRfidCodesCommandResponse response_;
            auto status_ = onClearAllRfidCodesCommand(response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getStatus());
            }
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* ClosuresWindowCoveringCluster::getWindowCoveringType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::WindowCoveringType);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getPhysicalClosedLimitLiftCm() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::PhysicalClosedLimitLiftCm);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getPhysicalClosedLimitTiltDdegree() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::PhysicalClosedLimitTiltDdegree);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getCurrentPositionLiftCm() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::CurrentPositionLiftCm);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getCurrentPositionTiltDdegree() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::CurrentPositionTiltDdegree);
    if (result == nullptr) {
        result = new AttributeUInt16(4, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getNumOfActuationsLift() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::NumOfActuationsLift);
    if (result == nullptr) {
        result = new AttributeUInt16(5, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getNumOfActuationsTilt() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::NumOfActuationsTilt);
    if (result == nullptr) {
        result = new AttributeUInt16(6, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresWindowCoveringCluster::getConfigStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::ConfigStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(7, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresWindowCoveringCluster::getCurrentPositionLiftPercentage() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::CurrentPositionLiftPercentage);
    if (result == nullptr) {
        result = new AttributeUInt8(8, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresWindowCoveringCluster::getCurrentPositionTiltPercentage() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::CurrentPositionTiltPercentage);
    if (result == nullptr) {
        result = new AttributeUInt8(9, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresWindowCoveringCluster::getOperationalStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::OperationalStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(10, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getInstalledOpenLimitLiftCm() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::InstalledOpenLimitLiftCm);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getInstalledClosedLimitLiftCm() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::InstalledClosedLimitLiftCm);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getInstalledOpenLimitTiltDdegree() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::InstalledOpenLimitTiltDdegree);
    if (result == nullptr) {
        result = new AttributeUInt16(18, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getInstalledClosedLimitTiltDdegree() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::InstalledClosedLimitTiltDdegree);
    if (result == nullptr) {
        result = new AttributeUInt16(19, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getVelocityLift() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::VelocityLift);
    if (result == nullptr) {
        result = new AttributeUInt16(20, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getAccelerationTimeLift() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::AccelerationTimeLift);
    if (result == nullptr) {
        result = new AttributeUInt16(21, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getDecelerationTimeLift() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::DecelerationTimeLift);
    if (result == nullptr) {
        result = new AttributeUInt16(22, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* ClosuresWindowCoveringCluster::getWindowCoveringMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::WindowCoveringMode);
    if (result == nullptr) {
        result = new AttributeUInt8(23, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* ClosuresWindowCoveringCluster::getIntermediateSetpointsLift() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::IntermediateSetpointsLift);
    if (result == nullptr) {
        result = new AttributeOctstr(24);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* ClosuresWindowCoveringCluster::getIntermediateSetpointsTilt() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::IntermediateSetpointsTilt);
    if (result == nullptr) {
        result = new AttributeOctstr(25);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* ClosuresWindowCoveringCluster::getMoesCalibrationTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)ClosuresWindowCoveringAttribute::MoesCalibrationTime);
    if (result == nullptr) {
        result = new AttributeUInt16(61443, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void ClosuresWindowCoveringCluster::sendUpOpenCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::sendDownCloseCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::sendStopCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::sendGoToLiftValueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t liftvalue) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);

    buffer.writeUInt16Le(liftvalue);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::sendGoToLiftPercentageCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t percentageliftvalue) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        5
    ).write(buffer);

    buffer.writeUInt8(percentageliftvalue);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::sendGoToTiltValueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t tiltvalue) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        7
    ).write(buffer);

    buffer.writeUInt16Le(tiltvalue);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::sendGoToTiltPercentageCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t percentagetiltvalue) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        8
    ).write(buffer);

    buffer.writeUInt8(percentagetiltvalue);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::sendElkoStopOrStepLiftPercentageCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t direction, uint16_t stepvalue) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        128
    ).write(buffer);

    buffer.writeUInt16Le(direction);
    buffer.writeUInt16Le(stepvalue);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ClosuresWindowCoveringCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onUpOpenCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onDownCloseCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto status_ = onStopCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto liftvalue = request.readUInt16Le();
            auto status_ = onGoToLiftValueCommand(liftvalue);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 5: {
            auto percentageliftvalue = request.readUInt8();
            auto status_ = onGoToLiftPercentageCommand(percentageliftvalue);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 7: {
            auto tiltvalue = request.readUInt16Le();
            auto status_ = onGoToTiltValueCommand(tiltvalue);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 8: {
            auto percentagetiltvalue = request.readUInt8();
            auto status_ = onGoToTiltPercentageCommand(percentagetiltvalue);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 128: {
            auto direction = request.readUInt16Le();
            auto stepvalue = request.readUInt16Le();
            auto status_ = onElkoStopOrStepLiftPercentageCommand(direction, stepvalue);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* BarrierControlCluster::getMovingState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)BarrierControlAttribute::MovingState);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* BarrierControlCluster::getSafetyStatus() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)BarrierControlAttribute::SafetyStatus);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* BarrierControlCluster::getCapabilities() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)BarrierControlAttribute::Capabilities);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* BarrierControlCluster::getOpenEvents() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)BarrierControlAttribute::OpenEvents);
    if (result == nullptr) {
        result = new AttributeUInt16(4, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* BarrierControlCluster::getCloseEvents() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)BarrierControlAttribute::CloseEvents);
    if (result == nullptr) {
        result = new AttributeUInt16(5, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* BarrierControlCluster::getCommandOpenEvents() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)BarrierControlAttribute::CommandOpenEvents);
    if (result == nullptr) {
        result = new AttributeUInt16(6, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* BarrierControlCluster::getCommandCloseEvents() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)BarrierControlAttribute::CommandCloseEvents);
    if (result == nullptr) {
        result = new AttributeUInt16(7, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* BarrierControlCluster::getOpenPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)BarrierControlAttribute::OpenPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(8, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* BarrierControlCluster::getClosePeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)BarrierControlAttribute::ClosePeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(9, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* BarrierControlCluster::getBarrierPosition() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)BarrierControlAttribute::BarrierPosition);
    if (result == nullptr) {
        result = new AttributeUInt8(10, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

void BarrierControlCluster::sendGoToPercentCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t percentOpen) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(percentOpen);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void BarrierControlCluster::sendStopCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void BarrierControlCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto percentOpen = request.readUInt8();
            auto status_ = onGoToPercentCommand(percentOpen);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onStopCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeInt16* HvacPumpCfgCtrlCluster::getMaxPressure() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxPressure);
    if (result == nullptr) {
        result = new AttributeInt16(0, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getMaxSpeed() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxSpeed);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getMaxFlow() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxFlow);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacPumpCfgCtrlCluster::getMinConstPressure() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MinConstPressure);
    if (result == nullptr) {
        result = new AttributeInt16(3, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacPumpCfgCtrlCluster::getMaxConstPressure() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxConstPressure);
    if (result == nullptr) {
        result = new AttributeInt16(4, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacPumpCfgCtrlCluster::getMinCompPressure() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MinCompPressure);
    if (result == nullptr) {
        result = new AttributeInt16(5, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacPumpCfgCtrlCluster::getMaxCompPressure() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxCompPressure);
    if (result == nullptr) {
        result = new AttributeInt16(6, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getMinConstSpeed() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MinConstSpeed);
    if (result == nullptr) {
        result = new AttributeUInt16(7, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getMaxConstSpeed() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxConstSpeed);
    if (result == nullptr) {
        result = new AttributeUInt16(8, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getMinConstFlow() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MinConstFlow);
    if (result == nullptr) {
        result = new AttributeUInt16(9, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getMaxConstFlow() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxConstFlow);
    if (result == nullptr) {
        result = new AttributeUInt16(10, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacPumpCfgCtrlCluster::getMinConstTemp() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MinConstTemp);
    if (result == nullptr) {
        result = new AttributeInt16(11, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacPumpCfgCtrlCluster::getMaxConstTemp() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::MaxConstTemp);
    if (result == nullptr) {
        result = new AttributeInt16(12, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getPumpStatus() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::PumpStatus);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacPumpCfgCtrlCluster::getEffectiveOperationMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::EffectiveOperationMode);
    if (result == nullptr) {
        result = new AttributeUInt8(17, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacPumpCfgCtrlCluster::getEffectiveControlMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::EffectiveControlMode);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacPumpCfgCtrlCluster::getCapacity() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::Capacity);
    if (result == nullptr) {
        result = new AttributeInt16(19, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getSpeed() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::Speed);
    if (result == nullptr) {
        result = new AttributeUInt16(20, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* HvacPumpCfgCtrlCluster::getLifetimeRunningHours() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::LifetimeRunningHours);
    if (result == nullptr) {
        result = new AttributeUInt24(21, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* HvacPumpCfgCtrlCluster::getPower() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::Power);
    if (result == nullptr) {
        result = new AttributeUInt24(22, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HvacPumpCfgCtrlCluster::getLifetimeEnergyConsumed() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::LifetimeEnergyConsumed);
    if (result == nullptr) {
        result = new AttributeUInt32(23, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacPumpCfgCtrlCluster::getOperationMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::OperationMode);
    if (result == nullptr) {
        result = new AttributeUInt8(32, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacPumpCfgCtrlCluster::getControlMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::ControlMode);
    if (result == nullptr) {
        result = new AttributeUInt8(33, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacPumpCfgCtrlCluster::getAlarmMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacPumpCfgCtrlAttribute::AlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt16(34, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getLocalTemp() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::LocalTemp);
    if (result == nullptr) {
        result = new AttributeInt16(0, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getOutdoorTemp() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::OutdoorTemp);
    if (result == nullptr) {
        result = new AttributeInt16(1, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getOccupancy() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::Occupancy);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getAbsMinHeatSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::AbsMinHeatSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(3, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getAbsMaxHeatSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::AbsMaxHeatSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(4, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getAbsMinCoolSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::AbsMinCoolSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(5, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getAbsMaxCoolSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::AbsMaxCoolSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(6, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getPICoolingDemand() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::PICoolingDemand);
    if (result == nullptr) {
        result = new AttributeUInt8(7, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getPIHeatingDemand() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::PIHeatingDemand);
    if (result == nullptr) {
        result = new AttributeUInt8(8, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getSystemTypeConfig() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::SystemTypeConfig);
    if (result == nullptr) {
        result = new AttributeUInt8(9, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HvacThermostatCluster::getLocalTemperatureCalibration() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::LocalTemperatureCalibration);
    if (result == nullptr) {
        result = new AttributeInt8(16, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getOccupiedCoolingSetpoint() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::OccupiedCoolingSetpoint);
    if (result == nullptr) {
        result = new AttributeInt16(17, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getOccupiedHeatingSetpoint() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::OccupiedHeatingSetpoint);
    if (result == nullptr) {
        result = new AttributeInt16(18, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getUnoccupiedCoolingSetpoint() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::UnoccupiedCoolingSetpoint);
    if (result == nullptr) {
        result = new AttributeInt16(19, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getUnoccupiedHeatingSetpoint() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::UnoccupiedHeatingSetpoint);
    if (result == nullptr) {
        result = new AttributeInt16(20, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getMinHeatSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::MinHeatSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(21, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getMaxHeatSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::MaxHeatSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(22, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getMinCoolSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::MinCoolSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(23, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getMaxCoolSetpointLimit() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::MaxCoolSetpointLimit);
    if (result == nullptr) {
        result = new AttributeInt16(24, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HvacThermostatCluster::getMinSetpointDeadBand() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::MinSetpointDeadBand);
    if (result == nullptr) {
        result = new AttributeInt8(25, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getRemoteSensing() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::RemoteSensing);
    if (result == nullptr) {
        result = new AttributeUInt8(26, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getCtrlSeqeOfOper() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::CtrlSeqeOfOper);
    if (result == nullptr) {
        result = new AttributeUInt8(27, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getSystemMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::SystemMode);
    if (result == nullptr) {
        result = new AttributeUInt8(28, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getAlarmMask() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::AlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt8(29, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getRunningMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::RunningMode);
    if (result == nullptr) {
        result = new AttributeUInt8(30, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getStartOfWeek() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::StartOfWeek);
    if (result == nullptr) {
        result = new AttributeUInt8(32, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getNumberOfWeeklyTrans() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::NumberOfWeeklyTrans);
    if (result == nullptr) {
        result = new AttributeUInt8(33, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getNumberOfDailyTrans() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::NumberOfDailyTrans);
    if (result == nullptr) {
        result = new AttributeUInt8(34, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getTempSetpointHold() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::TempSetpointHold);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacThermostatCluster::getTempSetpointHoldDuration() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::TempSetpointHoldDuration);
    if (result == nullptr) {
        result = new AttributeUInt16(36, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getProgramingOperMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ProgramingOperMode);
    if (result == nullptr) {
        result = new AttributeUInt8(37, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacThermostatCluster::getRunningState() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::RunningState);
    if (result == nullptr) {
        result = new AttributeUInt16(41, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getSetpointChangeSource() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::SetpointChangeSource);
    if (result == nullptr) {
        result = new AttributeUInt8(48, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getSetpointChangeAmount() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::SetpointChangeAmount);
    if (result == nullptr) {
        result = new AttributeInt16(49, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HvacThermostatCluster::getSetpointChangeSourceTimeStamp() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HvacThermostatAttribute::SetpointChangeSourceTimeStamp);
    if (result == nullptr) {
        result = new AttributeUInt32(50, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getAcType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::AcType);
    if (result == nullptr) {
        result = new AttributeUInt8(64, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacThermostatCluster::getAcCapacity() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::AcCapacity);
    if (result == nullptr) {
        result = new AttributeUInt16(65, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getAcRefrigerantType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::AcRefrigerantType);
    if (result == nullptr) {
        result = new AttributeUInt8(66, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getAcConpressorType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::AcConpressorType);
    if (result == nullptr) {
        result = new AttributeUInt8(67, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HvacThermostatCluster::getAcErrorCode() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HvacThermostatAttribute::AcErrorCode);
    if (result == nullptr) {
        result = new AttributeUInt32(68, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getAcLouverPosition() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::AcLouverPosition);
    if (result == nullptr) {
        result = new AttributeUInt8(69, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getAcCollTemp() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::AcCollTemp);
    if (result == nullptr) {
        result = new AttributeInt16(70, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getAcCapacityFormat() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::AcCapacityFormat);
    if (result == nullptr) {
        result = new AttributeUInt8(71, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getStelproSystemMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::StelproSystemMode);
    if (result == nullptr) {
        result = new AttributeUInt8(16412, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacThermostatCluster::getElkoLoad() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoLoad);
    if (result == nullptr) {
        result = new AttributeUInt16(1025, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeString* HvacThermostatCluster::getElkoDisplayText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoDisplayText);
    if (result == nullptr) {
        result = new AttributeString(1026);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoSensor() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoSensor);
    if (result == nullptr) {
        result = new AttributeUInt8(1027, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoRegulatorTime() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoRegulatorTime);
    if (result == nullptr) {
        result = new AttributeUInt8(1028, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoRegulatorMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoRegulatorMode);
    if (result == nullptr) {
        result = new AttributeUInt8(1029, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoPowerStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoPowerStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(1030, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* HvacThermostatCluster::getElkoDateTime() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoDateTime);
    if (result == nullptr) {
        result = new AttributeOctstr(1031);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HvacThermostatCluster::getElkoMeanPower() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoMeanPower);
    if (result == nullptr) {
        result = new AttributeUInt16(1032, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HvacThermostatCluster::getElkoExternalTemp() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoExternalTemp);
    if (result == nullptr) {
        result = new AttributeInt16(1033, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoNightSwitching() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoNightSwitching);
    if (result == nullptr) {
        result = new AttributeUInt8(1041, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoFrostGuard() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoFrostGuard);
    if (result == nullptr) {
        result = new AttributeUInt8(1042, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoChildLock() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoChildLock);
    if (result == nullptr) {
        result = new AttributeUInt8(1043, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoMaxFloorTemp() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoMaxFloorTemp);
    if (result == nullptr) {
        result = new AttributeUInt8(1044, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoRelayState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoRelayState);
    if (result == nullptr) {
        result = new AttributeUInt8(1045, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* HvacThermostatCluster::getElkoVersion() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoVersion);
    if (result == nullptr) {
        result = new AttributeOctstr(1046);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HvacThermostatCluster::getElkoCalibration() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoCalibration);
    if (result == nullptr) {
        result = new AttributeInt8(1047, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoLastMessageId() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoLastMessageId);
    if (result == nullptr) {
        result = new AttributeUInt8(1048, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacThermostatCluster::getElkoLastMessageStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacThermostatAttribute::ElkoLastMessageStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(1049, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

void HvacThermostatCluster::sendSetpointRaiseLowerCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t mode, int8_t amount) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(mode);
    buffer.writeInt8(amount);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendGetWeeklyScheduleCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t daystoreturn, uint8_t modetoreturn) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt8(daystoreturn);
    buffer.writeUInt8(modetoreturn);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendClearWeeklyScheduleCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendGetRelayStatusLogCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendDanfossSetpointCommandCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t setpointType, int16_t setpoint) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        64
    ).write(buffer);

    buffer.writeUInt8(setpointType);
    buffer.writeInt16Le(setpoint);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendSchneiderWiserThermostatBoostCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t command, uint8_t enable, uint16_t temperature, uint16_t duration) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        128
    ).write(buffer);

    buffer.writeUInt8(command);
    buffer.writeUInt8(enable);
    buffer.writeUInt16Le(temperature);
    buffer.writeUInt16Le(duration);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendWiserSmartSetSetpointCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t operatingmode, uint8_t zonemode, int16_t setpoint, uint8_t reserved) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        224
    ).write(buffer);

    buffer.writeUInt8(operatingmode);
    buffer.writeUInt8(zonemode);
    buffer.writeInt16Le(setpoint);
    buffer.writeUInt8(reserved);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendWiserSmartSetFipModeCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t zonemode, uint8_t fipmode, uint8_t reserved) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        225
    ).write(buffer);

    buffer.writeUInt8(zonemode);
    buffer.writeUInt8(fipmode);
    buffer.writeUInt8(reserved);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendWiserSmartCalibrateValveCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        226
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendPlugwiseCalibrateValveCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        160
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::sendBoschCalibrateValveCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        65
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HvacThermostatCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto mode = request.readUInt8();
            auto amount = request.readInt8();
            auto status_ = onSetpointRaiseLowerCommand(mode, amount);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto daystoreturn = request.readUInt8();
            auto modetoreturn = request.readUInt8();
            auto status_ = onGetWeeklyScheduleCommand(daystoreturn, modetoreturn);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto status_ = onClearWeeklyScheduleCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto status_ = onGetRelayStatusLogCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 64: {
            auto setpointType = request.readUInt8();
            auto setpoint = request.readInt16Le();
            auto status_ = onDanfossSetpointCommandCommand(setpointType, setpoint);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 128: {
            auto command = request.readUInt8();
            auto enable = request.readUInt8();
            auto temperature = request.readUInt16Le();
            auto duration = request.readUInt16Le();
            auto status_ = onSchneiderWiserThermostatBoostCommand(command, enable, temperature, duration);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 224: {
            auto operatingmode = request.readUInt8();
            auto zonemode = request.readUInt8();
            auto setpoint = request.readInt16Le();
            auto reserved = request.readUInt8();
            auto status_ = onWiserSmartSetSetpointCommand(operatingmode, zonemode, setpoint, reserved);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 225: {
            auto zonemode = request.readUInt8();
            auto fipmode = request.readUInt8();
            auto reserved = request.readUInt8();
            auto status_ = onWiserSmartSetFipModeCommand(zonemode, fipmode, reserved);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 226: {
            auto status_ = onWiserSmartCalibrateValveCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 160: {
            auto status_ = onPlugwiseCalibrateValveCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 65: {
            auto status_ = onBoschCalibrateValveCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* HvacFanCtrlCluster::getFanMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacFanCtrlAttribute::FanMode);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacFanCtrlCluster::getFanModeSequence() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacFanCtrlAttribute::FanModeSequence);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getRelativeHumidity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::RelativeHumidity);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getDehumidCooling() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::DehumidCooling);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getRhDehumidSetpoint() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::RhDehumidSetpoint);
    if (result == nullptr) {
        result = new AttributeUInt8(16, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getRelativeHumidityMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::RelativeHumidityMode);
    if (result == nullptr) {
        result = new AttributeUInt8(17, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getDehumidLockout() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::DehumidLockout);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getDehumidHysteresis() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::DehumidHysteresis);
    if (result == nullptr) {
        result = new AttributeUInt8(19, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getDehumidMaxCool() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::DehumidMaxCool);
    if (result == nullptr) {
        result = new AttributeUInt8(20, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacDehumidificationCtrlCluster::getRelativeHumidDisplay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacDehumidificationCtrlAttribute::RelativeHumidDisplay);
    if (result == nullptr) {
        result = new AttributeUInt8(21, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacUserInterfaceCfgCluster::getTempDisplayMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacUserInterfaceCfgAttribute::TempDisplayMode);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacUserInterfaceCfgCluster::getKeypadLockout() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacUserInterfaceCfgAttribute::KeypadLockout);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HvacUserInterfaceCfgCluster::getProgrammingVisibility() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HvacUserInterfaceCfgAttribute::ProgrammingVisibility);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getCurrentHue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::CurrentHue);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getCurrentSaturation() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::CurrentSaturation);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getRemainingTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::RemainingTime);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getCurrentX() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::CurrentX);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getCurrentY() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::CurrentY);
    if (result == nullptr) {
        result = new AttributeUInt16(4, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getDriftCompensation() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::DriftCompensation);
    if (result == nullptr) {
        result = new AttributeUInt8(5, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeString* LightingColorCtrlCluster::getCompensationText() {
    auto result = (AttributeString*)getAttributeById((uint16_t)LightingColorCtrlAttribute::CompensationText);
    if (result == nullptr) {
        result = new AttributeString(6);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorTemperature() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorTemperature);
    if (result == nullptr) {
        result = new AttributeUInt16(7, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getColorMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorMode);
    if (result == nullptr) {
        result = new AttributeUInt8(8, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getOptions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Options);
    if (result == nullptr) {
        result = new AttributeUInt8(15, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getNumPrimaries() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::NumPrimaries);
    if (result == nullptr) {
        result = new AttributeUInt8(16, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary1X() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary1X);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary1Y() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary1Y);
    if (result == nullptr) {
        result = new AttributeUInt16(18, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getPrimary1Intensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary1Intensity);
    if (result == nullptr) {
        result = new AttributeUInt8(19, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary2X() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary2X);
    if (result == nullptr) {
        result = new AttributeUInt16(21, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary2Y() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary2Y);
    if (result == nullptr) {
        result = new AttributeUInt16(22, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getPrimary2Intensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary2Intensity);
    if (result == nullptr) {
        result = new AttributeUInt8(23, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary3X() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary3X);
    if (result == nullptr) {
        result = new AttributeUInt16(25, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary3Y() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary3Y);
    if (result == nullptr) {
        result = new AttributeUInt16(26, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getPrimary3Intensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary3Intensity);
    if (result == nullptr) {
        result = new AttributeUInt8(27, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary4X() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary4X);
    if (result == nullptr) {
        result = new AttributeUInt16(32, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary4Y() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary4Y);
    if (result == nullptr) {
        result = new AttributeUInt16(33, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getPrimary4Intensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary4Intensity);
    if (result == nullptr) {
        result = new AttributeUInt8(34, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary5X() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary5X);
    if (result == nullptr) {
        result = new AttributeUInt16(36, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary5Y() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary5Y);
    if (result == nullptr) {
        result = new AttributeUInt16(37, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getPrimary5Intensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary5Intensity);
    if (result == nullptr) {
        result = new AttributeUInt8(38, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary6X() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary6X);
    if (result == nullptr) {
        result = new AttributeUInt16(40, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getPrimary6Y() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary6Y);
    if (result == nullptr) {
        result = new AttributeUInt16(41, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getPrimary6Intensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::Primary6Intensity);
    if (result == nullptr) {
        result = new AttributeUInt8(42, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getWhitePointX() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::WhitePointX);
    if (result == nullptr) {
        result = new AttributeUInt16(48, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getWhitePointY() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::WhitePointY);
    if (result == nullptr) {
        result = new AttributeUInt16(49, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorPointRX() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointRX);
    if (result == nullptr) {
        result = new AttributeUInt16(50, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorPointRY() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointRY);
    if (result == nullptr) {
        result = new AttributeUInt16(51, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getColorPointRIntensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointRIntensity);
    if (result == nullptr) {
        result = new AttributeUInt8(52, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorPointGX() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointGX);
    if (result == nullptr) {
        result = new AttributeUInt16(54, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorPointGY() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointGY);
    if (result == nullptr) {
        result = new AttributeUInt16(55, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getColorPointGIntensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointGIntensity);
    if (result == nullptr) {
        result = new AttributeUInt8(56, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorPointBX() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointBX);
    if (result == nullptr) {
        result = new AttributeUInt16(58, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorPointBY() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointBY);
    if (result == nullptr) {
        result = new AttributeUInt16(59, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getColorPointBIntensity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorPointBIntensity);
    if (result == nullptr) {
        result = new AttributeUInt8(60, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getEnhancedCurrentHue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::EnhancedCurrentHue);
    if (result == nullptr) {
        result = new AttributeUInt16(16384, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getEnhancedColorMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::EnhancedColorMode);
    if (result == nullptr) {
        result = new AttributeUInt8(16385, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getColorLoopActive() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorLoopActive);
    if (result == nullptr) {
        result = new AttributeUInt8(16386, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingColorCtrlCluster::getColorLoopDirection() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorLoopDirection);
    if (result == nullptr) {
        result = new AttributeUInt8(16387, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorLoopTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorLoopTime);
    if (result == nullptr) {
        result = new AttributeUInt16(16388, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorLoopStartEnhancedHue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorLoopStartEnhancedHue);
    if (result == nullptr) {
        result = new AttributeUInt16(16389, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorLoopStoredEnhancedHue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorLoopStoredEnhancedHue);
    if (result == nullptr) {
        result = new AttributeUInt16(16390, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorCapabilities() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorCapabilities);
    if (result == nullptr) {
        result = new AttributeUInt16(16394, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorTempPhysicalMin() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorTempPhysicalMin);
    if (result == nullptr) {
        result = new AttributeUInt16(16395, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getColorTempPhysicalMax() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::ColorTempPhysicalMax);
    if (result == nullptr) {
        result = new AttributeUInt16(16396, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getCoupleColorTempToLevelMin() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::CoupleColorTempToLevelMin);
    if (result == nullptr) {
        result = new AttributeUInt16(16397, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingColorCtrlCluster::getStartUpColorTemperature() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingColorCtrlAttribute::StartUpColorTemperature);
    if (result == nullptr) {
        result = new AttributeUInt16(16400, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void LightingColorCtrlCluster::sendMoveToHueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t hue, uint8_t direction, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(hue);
    buffer.writeUInt8(direction);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveHueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t movemode, uint8_t rate) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeUInt8(movemode);
    buffer.writeUInt8(rate);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendStepHueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t stepmode, uint8_t stepsize, uint8_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt8(stepmode);
    buffer.writeUInt8(stepsize);
    buffer.writeUInt8(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveToSaturationCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t saturation, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);

    buffer.writeUInt8(saturation);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveSaturationCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t movemode, uint8_t rate) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);

    buffer.writeUInt8(movemode);
    buffer.writeUInt8(rate);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendStepSaturationCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t stepmode, uint8_t stepsize, uint8_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        5
    ).write(buffer);

    buffer.writeUInt8(stepmode);
    buffer.writeUInt8(stepsize);
    buffer.writeUInt8(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveToHueAndSaturationCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t hue, uint8_t saturation, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        6
    ).write(buffer);

    buffer.writeUInt8(hue);
    buffer.writeUInt8(saturation);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveToColorCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t colorx, uint16_t colory, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        7
    ).write(buffer);

    buffer.writeUInt16Le(colorx);
    buffer.writeUInt16Le(colory);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveColorCommand(DeviceManager& deviceManager, uint8_t endpointId, int16_t ratex, int16_t ratey) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        8
    ).write(buffer);

    buffer.writeInt16Le(ratex);
    buffer.writeInt16Le(ratey);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendStepColorCommand(DeviceManager& deviceManager, uint8_t endpointId, int16_t stepx, int16_t stepy, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        9
    ).write(buffer);

    buffer.writeInt16Le(stepx);
    buffer.writeInt16Le(stepy);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveToColorTempCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t colortemp, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        10
    ).write(buffer);

    buffer.writeUInt16Le(colortemp);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendEnhancedMoveToHueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t enhancehue, uint8_t direction, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        64
    ).write(buffer);

    buffer.writeUInt16Le(enhancehue);
    buffer.writeUInt8(direction);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendEnhancedMoveHueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t movemode, uint16_t rate) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        65
    ).write(buffer);

    buffer.writeUInt8(movemode);
    buffer.writeUInt16Le(rate);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendEnhancedStepHueCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t stepmode, uint16_t stepsize, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        66
    ).write(buffer);

    buffer.writeUInt8(stepmode);
    buffer.writeUInt16Le(stepsize);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendEnhancedMoveToHueAndSaturationCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t enhancehue, uint8_t saturation, uint16_t transtime) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        67
    ).write(buffer);

    buffer.writeUInt16Le(enhancehue);
    buffer.writeUInt8(saturation);
    buffer.writeUInt16Le(transtime);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendColorLoopSetCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t updateflags, uint8_t action, uint8_t direction, uint16_t time, uint16_t starthue) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        68
    ).write(buffer);

    buffer.writeUInt8(updateflags);
    buffer.writeUInt8(action);
    buffer.writeUInt8(direction);
    buffer.writeUInt16Le(time);
    buffer.writeUInt16Le(starthue);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendStopMoveStepCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t bits, uint8_t bytee, uint8_t action, uint8_t direction, uint16_t time, uint16_t starthue) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        71
    ).write(buffer);

    buffer.writeUInt8(bits);
    buffer.writeUInt8(bytee);
    buffer.writeUInt8(action);
    buffer.writeUInt8(direction);
    buffer.writeUInt16Le(time);
    buffer.writeUInt16Le(starthue);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendMoveColorTempCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t movemode, uint16_t rate, uint16_t minimum, uint16_t maximum) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        75
    ).write(buffer);

    buffer.writeUInt8(movemode);
    buffer.writeUInt16Le(rate);
    buffer.writeUInt16Le(minimum);
    buffer.writeUInt16Le(maximum);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::sendStepColorTempCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t stepmode, uint16_t stepsize, uint16_t transtime, uint16_t minimum, uint16_t maximum) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        76
    ).write(buffer);

    buffer.writeUInt8(stepmode);
    buffer.writeUInt16Le(stepsize);
    buffer.writeUInt16Le(transtime);
    buffer.writeUInt16Le(minimum);
    buffer.writeUInt16Le(maximum);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void LightingColorCtrlCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto hue = request.readUInt8();
            auto direction = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToHueCommand(hue, direction, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto movemode = request.readUInt8();
            auto rate = request.readUInt8();
            auto status_ = onMoveHueCommand(movemode, rate);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto stepmode = request.readUInt8();
            auto stepsize = request.readUInt8();
            auto transtime = request.readUInt8();
            auto status_ = onStepHueCommand(stepmode, stepsize, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto saturation = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToSaturationCommand(saturation, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto movemode = request.readUInt8();
            auto rate = request.readUInt8();
            auto status_ = onMoveSaturationCommand(movemode, rate);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 5: {
            auto stepmode = request.readUInt8();
            auto stepsize = request.readUInt8();
            auto transtime = request.readUInt8();
            auto status_ = onStepSaturationCommand(stepmode, stepsize, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 6: {
            auto hue = request.readUInt8();
            auto saturation = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToHueAndSaturationCommand(hue, saturation, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 7: {
            auto colorx = request.readUInt16Le();
            auto colory = request.readUInt16Le();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToColorCommand(colorx, colory, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 8: {
            auto ratex = request.readInt16Le();
            auto ratey = request.readInt16Le();
            auto status_ = onMoveColorCommand(ratex, ratey);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 9: {
            auto stepx = request.readInt16Le();
            auto stepy = request.readInt16Le();
            auto transtime = request.readUInt16Le();
            auto status_ = onStepColorCommand(stepx, stepy, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 10: {
            auto colortemp = request.readUInt16Le();
            auto transtime = request.readUInt16Le();
            auto status_ = onMoveToColorTempCommand(colortemp, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 64: {
            auto enhancehue = request.readUInt16Le();
            auto direction = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onEnhancedMoveToHueCommand(enhancehue, direction, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 65: {
            auto movemode = request.readUInt8();
            auto rate = request.readUInt16Le();
            auto status_ = onEnhancedMoveHueCommand(movemode, rate);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 66: {
            auto stepmode = request.readUInt8();
            auto stepsize = request.readUInt16Le();
            auto transtime = request.readUInt16Le();
            auto status_ = onEnhancedStepHueCommand(stepmode, stepsize, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 67: {
            auto enhancehue = request.readUInt16Le();
            auto saturation = request.readUInt8();
            auto transtime = request.readUInt16Le();
            auto status_ = onEnhancedMoveToHueAndSaturationCommand(enhancehue, saturation, transtime);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 68: {
            auto updateflags = request.readUInt8();
            auto action = request.readUInt8();
            auto direction = request.readUInt8();
            auto time = request.readUInt16Le();
            auto starthue = request.readUInt16Le();
            auto status_ = onColorLoopSetCommand(updateflags, action, direction, time, starthue);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 71: {
            auto bits = request.readUInt8();
            auto bytee = request.readUInt8();
            auto action = request.readUInt8();
            auto direction = request.readUInt8();
            auto time = request.readUInt16Le();
            auto starthue = request.readUInt16Le();
            auto status_ = onStopMoveStepCommand(bits, bytee, action, direction, time, starthue);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 75: {
            auto movemode = request.readUInt8();
            auto rate = request.readUInt16Le();
            auto minimum = request.readUInt16Le();
            auto maximum = request.readUInt16Le();
            auto status_ = onMoveColorTempCommand(movemode, rate, minimum, maximum);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 76: {
            auto stepmode = request.readUInt8();
            auto stepsize = request.readUInt16Le();
            auto transtime = request.readUInt16Le();
            auto minimum = request.readUInt16Le();
            auto maximum = request.readUInt16Le();
            auto status_ = onStepColorTempCommand(stepmode, stepsize, transtime, minimum, maximum);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* LightingBallastCfgCluster::getPhysicalMinLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::PhysicalMinLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getPhysicalMaxLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::PhysicalMaxLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getBallastStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::BallastStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getMinLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::MinLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(16, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getMaxLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::MaxLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(17, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getPowerOnLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::PowerOnLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* LightingBallastCfgCluster::getPowerOnFadeTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)LightingBallastCfgAttribute::PowerOnFadeTime);
    if (result == nullptr) {
        result = new AttributeUInt16(19, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getIntrinsicBallastFactor() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::IntrinsicBallastFactor);
    if (result == nullptr) {
        result = new AttributeUInt8(20, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getBallastFactorAdjustment() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::BallastFactorAdjustment);
    if (result == nullptr) {
        result = new AttributeUInt8(21, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getLampQuantity() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::LampQuantity);
    if (result == nullptr) {
        result = new AttributeUInt8(32, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* LightingBallastCfgCluster::getLampType() {
    auto result = (AttributeString*)getAttributeById((uint16_t)LightingBallastCfgAttribute::LampType);
    if (result == nullptr) {
        result = new AttributeString(48);
        addAttribute(result);
    }
    return result;
}

AttributeString* LightingBallastCfgCluster::getLampManufacturer() {
    auto result = (AttributeString*)getAttributeById((uint16_t)LightingBallastCfgAttribute::LampManufacturer);
    if (result == nullptr) {
        result = new AttributeString(49);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* LightingBallastCfgCluster::getLampRatedHours() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)LightingBallastCfgAttribute::LampRatedHours);
    if (result == nullptr) {
        result = new AttributeUInt24(50, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* LightingBallastCfgCluster::getLampBurnHours() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)LightingBallastCfgAttribute::LampBurnHours);
    if (result == nullptr) {
        result = new AttributeUInt24(51, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* LightingBallastCfgCluster::getLampAlarmMode() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)LightingBallastCfgAttribute::LampAlarmMode);
    if (result == nullptr) {
        result = new AttributeUInt8(52, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* LightingBallastCfgCluster::getLampBurnHoursTripPoint() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)LightingBallastCfgAttribute::LampBurnHoursTripPoint);
    if (result == nullptr) {
        result = new AttributeUInt24(53, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsIlluminanceMeasurementCluster::getMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsIlluminanceMeasurementAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsIlluminanceMeasurementCluster::getMinMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsIlluminanceMeasurementAttribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsIlluminanceMeasurementCluster::getMaxMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsIlluminanceMeasurementAttribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsIlluminanceMeasurementCluster::getTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsIlluminanceMeasurementAttribute::Tolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* MsIlluminanceMeasurementCluster::getLightSensorType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)MsIlluminanceMeasurementAttribute::LightSensorType);
    if (result == nullptr) {
        result = new AttributeUInt8(4, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* MsIlluminanceLevelSensingCluster::getLevelStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)MsIlluminanceLevelSensingAttribute::LevelStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* MsIlluminanceLevelSensingCluster::getLightSensorType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)MsIlluminanceLevelSensingAttribute::LightSensorType);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsIlluminanceLevelSensingCluster::getIlluminanceTargetLevel() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsIlluminanceLevelSensingAttribute::IlluminanceTargetLevel);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsTemperatureMeasurementCluster::getMeasuredValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsTemperatureMeasurementAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeInt16(0, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsTemperatureMeasurementCluster::getMinMeasuredValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsTemperatureMeasurementAttribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeInt16(1, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsTemperatureMeasurementCluster::getMaxMeasuredValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsTemperatureMeasurementAttribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeInt16(2, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsTemperatureMeasurementCluster::getTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsTemperatureMeasurementAttribute::Tolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsPressureMeasurementCluster::getMeasuredValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeInt16(0, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsPressureMeasurementCluster::getMinMeasuredValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeInt16(1, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsPressureMeasurementCluster::getMaxMeasuredValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeInt16(2, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsPressureMeasurementCluster::getTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::Tolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsPressureMeasurementCluster::getScaledValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::ScaledValue);
    if (result == nullptr) {
        result = new AttributeInt16(16, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsPressureMeasurementCluster::getMinScaledValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::MinScaledValue);
    if (result == nullptr) {
        result = new AttributeInt16(17, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* MsPressureMeasurementCluster::getMaxScaledValue() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::MaxScaledValue);
    if (result == nullptr) {
        result = new AttributeInt16(18, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsPressureMeasurementCluster::getScaledTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::ScaledTolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(19, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* MsPressureMeasurementCluster::getScale() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)MsPressureMeasurementAttribute::Scale);
    if (result == nullptr) {
        result = new AttributeInt8(20, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsFlowMeasurementCluster::getMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsFlowMeasurementAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsFlowMeasurementCluster::getMinMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsFlowMeasurementAttribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsFlowMeasurementCluster::getMaxMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsFlowMeasurementAttribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsFlowMeasurementCluster::getTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsFlowMeasurementAttribute::Tolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsRelativeHumidityCluster::getMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsRelativeHumidityAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsRelativeHumidityCluster::getMinMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsRelativeHumidityAttribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsRelativeHumidityCluster::getMaxMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsRelativeHumidityAttribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsRelativeHumidityCluster::getTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsRelativeHumidityAttribute::Tolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* MsOccupancySensingCluster::getOccupancy() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)MsOccupancySensingAttribute::Occupancy);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* MsOccupancySensingCluster::getOccupancySensorType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)MsOccupancySensingAttribute::OccupancySensorType);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsOccupancySensingCluster::getPirOToUDelay() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsOccupancySensingAttribute::PirOToUDelay);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsOccupancySensingCluster::getPirUToODelay() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsOccupancySensingAttribute::PirUToODelay);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* MsOccupancySensingCluster::getPirUToOThreshold() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)MsOccupancySensingAttribute::PirUToOThreshold);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsOccupancySensingCluster::getUltrasonicOToUDelay() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsOccupancySensingAttribute::UltrasonicOToUDelay);
    if (result == nullptr) {
        result = new AttributeUInt16(32, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsOccupancySensingCluster::getUltrasonicUToODelay() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsOccupancySensingAttribute::UltrasonicUToODelay);
    if (result == nullptr) {
        result = new AttributeUInt16(33, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* MsOccupancySensingCluster::getUltrasonicUToOThreshold() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)MsOccupancySensingAttribute::UltrasonicUToOThreshold);
    if (result == nullptr) {
        result = new AttributeUInt8(34, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsSoilMoistureCluster::getMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsSoilMoistureAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsSoilMoistureCluster::getMinMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsSoilMoistureAttribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsSoilMoistureCluster::getMaxMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsSoilMoistureAttribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* MsSoilMoistureCluster::getTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)MsSoilMoistureAttribute::Tolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PHMeasurementCluster::getMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PHMeasurementAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PHMeasurementCluster::getMinMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PHMeasurementAttribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PHMeasurementCluster::getMaxMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PHMeasurementAttribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PHMeasurementCluster::getTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PHMeasurementAttribute::Tolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* MsCO2Cluster::getMeasuredValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)MsCO2Attribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeSingle(0, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* MsCO2Cluster::getMinMeasuredValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)MsCO2Attribute::MinMeasuredValue);
    if (result == nullptr) {
        result = new AttributeSingle(1, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* MsCO2Cluster::getMaxMeasuredValue() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)MsCO2Attribute::MaxMeasuredValue);
    if (result == nullptr) {
        result = new AttributeSingle(2, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* Pm25MeasurementCluster::getMeasuredValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)Pm25MeasurementAttribute::MeasuredValue);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* Pm25MeasurementCluster::getMeasuredMinValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)Pm25MeasurementAttribute::MeasuredMinValue);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* Pm25MeasurementCluster::getMeasuredMaxValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)Pm25MeasurementAttribute::MeasuredMaxValue);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* Pm25MeasurementCluster::getMeasuredTolerance() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)Pm25MeasurementAttribute::MeasuredTolerance);
    if (result == nullptr) {
        result = new AttributeUInt16(3, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SsIasZoneCluster::getZoneState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SsIasZoneAttribute::ZoneState);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SsIasZoneCluster::getZoneType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SsIasZoneAttribute::ZoneType);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SsIasZoneCluster::getZoneStatus() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SsIasZoneAttribute::ZoneStatus);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt64* SsIasZoneCluster::getIasCieAddr() {
    auto result = (AttributeUInt64*)getAttributeById((uint16_t)SsIasZoneAttribute::IasCieAddr);
    if (result == nullptr) {
        result = new AttributeUInt64(16, DataType::EUI64);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SsIasZoneCluster::getZoneId() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SsIasZoneAttribute::ZoneId);
    if (result == nullptr) {
        result = new AttributeUInt8(17, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SsIasZoneCluster::getNumZoneSensitivityLevelsSupported() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SsIasZoneAttribute::NumZoneSensitivityLevelsSupported);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SsIasZoneCluster::getCurrentZoneSensitivityLevel() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SsIasZoneAttribute::CurrentZoneSensitivityLevel);
    if (result == nullptr) {
        result = new AttributeUInt8(19, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

void SsIasZoneCluster::sendEnrollRspCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t enrollrspcode, uint8_t zoneid) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(enrollrspcode);
    buffer.writeUInt8(zoneid);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasZoneCluster::sendInitNormalOpModeCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasZoneCluster::sendInitTestModeCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasZoneCluster::sendBoschTestTamperCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t data) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        243
    ).write(buffer);

    buffer.writeUInt8(data);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasZoneCluster::sendBoschSmokeDetectorSirenCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t data) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        128
    ).write(buffer);

    buffer.writeUInt16Le(data);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasZoneCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto enrollrspcode = request.readUInt8();
            auto zoneid = request.readUInt8();
            auto status_ = onEnrollRspCommand(enrollrspcode, zoneid);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onInitNormalOpModeCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto status_ = onInitTestModeCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 243: {
            auto data = request.readUInt8();
            auto status_ = onBoschTestTamperCommand(data);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 128: {
            auto data = request.readUInt16Le();
            auto status_ = onBoschSmokeDetectorSirenCommand(data);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

void SsIasAceCluster::sendEmergencyCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasAceCluster::sendFireCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasAceCluster::sendPanicCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasAceCluster::sendGetBypassedZoneListCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        8
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasAceCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto armmode = request.readUInt8();
            auto code = request.readString();
            auto zoneid = request.readUInt8();
            ArmCommandResponse response_;
            auto status_ = onArmCommand(armmode, code, zoneid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getArmnotification());
            }
            return;
        }
        case 2: {
            auto status_ = onEmergencyCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto status_ = onFireCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto status_ = onPanicCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 5: {
            GetZoneIDMapCommandResponse response_;
            auto status_ = onGetZoneIDMapCommand(response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt16Le(response_.getZoneidmapsection0());
                response.writeUInt16Le(response_.getZoneidmapsection1());
                response.writeUInt16Le(response_.getZoneidmapsection2());
                response.writeUInt16Le(response_.getZoneidmapsection3());
                response.writeUInt16Le(response_.getZoneidmapsection4());
                response.writeUInt16Le(response_.getZoneidmapsection5());
                response.writeUInt16Le(response_.getZoneidmapsection6());
                response.writeUInt16Le(response_.getZoneidmapsection7());
                response.writeUInt16Le(response_.getZoneidmapsection8());
                response.writeUInt16Le(response_.getZoneidmapsection9());
                response.writeUInt16Le(response_.getZoneidmapsection10());
                response.writeUInt16Le(response_.getZoneidmapsection11());
                response.writeUInt16Le(response_.getZoneidmapsection12());
                response.writeUInt16Le(response_.getZoneidmapsection13());
                response.writeUInt16Le(response_.getZoneidmapsection14());
                response.writeUInt16Le(response_.getZoneidmapsection15());
            }
            return;
        }
        case 6: {
            auto zoneid = request.readUInt8();
            GetZoneInfoCommandResponse response_;
            auto status_ = onGetZoneInfoCommand(zoneid, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getZoneid());
                response.writeUInt16Le(response_.getZonetype());
                response.writeUInt64Le(response_.getIeeeaddr());
                response.writeString(response_.getZonelabel());
            }
            return;
        }
        case 7: {
            GetPanelStatusCommandResponse response_;
            auto status_ = onGetPanelStatusCommand(response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt8(response_.getPanelstatus());
                response.writeUInt8(response_.getSecondsremain());
                response.writeUInt8(response_.getAudiblenotif());
                response.writeUInt8(response_.getAlarmstatus());
            }
            return;
        }
        case 8: {
            auto status_ = onGetBypassedZoneListCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt16* SsIasWdCluster::getMaxDuration() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SsIasWdAttribute::MaxDuration);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void SsIasWdCluster::sendStartWarningCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t startwarninginfo, uint16_t warningduration, uint8_t strobedutycycle, uint8_t strobelevel) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(startwarninginfo);
    buffer.writeUInt16Le(warningduration);
    buffer.writeUInt8(strobedutycycle);
    buffer.writeUInt8(strobelevel);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasWdCluster::sendSquawkCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t squawkinfo) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeUInt8(squawkinfo);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void SsIasWdCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto startwarninginfo = request.readUInt8();
            auto warningduration = request.readUInt16Le();
            auto strobedutycycle = request.readUInt8();
            auto strobelevel = request.readUInt8();
            auto status_ = onStartWarningCommand(startwarninginfo, warningduration, strobedutycycle, strobelevel);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto squawkinfo = request.readUInt8();
            auto status_ = onSquawkCommand(squawkinfo);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt16* PiGenericTunnelCluster::getMaxIncomeTransSize() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiGenericTunnelAttribute::MaxIncomeTransSize);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiGenericTunnelCluster::getMaxOutgoTransSize() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiGenericTunnelAttribute::MaxOutgoTransSize);
    if (result == nullptr) {
        result = new AttributeUInt16(2, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* PiGenericTunnelCluster::getProtocolAddr() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)PiGenericTunnelAttribute::ProtocolAddr);
    if (result == nullptr) {
        result = new AttributeOctstr(3);
        addAttribute(result);
    }
    return result;
}

void PiGenericTunnelCluster::sendMatchProtocolAddrCommand(DeviceManager& deviceManager, uint8_t endpointId, String protocoladdr) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeString(protocoladdr);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void PiGenericTunnelCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto protocoladdr = request.readString();
            auto status_ = onMatchProtocolAddrCommand(protocoladdr);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

void PiBacnetProtocolTunnelCluster::sendTransferNpduCommand(DeviceManager& deviceManager, uint8_t endpointId, uint8_t npdu) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt8(npdu);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void PiBacnetProtocolTunnelCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto npdu = request.readUInt8();
            auto status_ = onTransferNpduCommand(npdu);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeSingle* PiAnalogInputRegCluster::getCovIncrement() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogInputRegAttribute::CovIncrement);
    if (result == nullptr) {
        result = new AttributeSingle(22, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogInputRegCluster::getDeviceType() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogInputRegAttribute::DeviceType);
    if (result == nullptr) {
        result = new AttributeString(31);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiAnalogInputRegCluster::getObjectId() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiAnalogInputRegAttribute::ObjectId);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogInputRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogInputRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiAnalogInputRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiAnalogInputRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogInputRegCluster::getUpdateInterval() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogInputRegAttribute::UpdateInterval);
    if (result == nullptr) {
        result = new AttributeUInt8(118, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogInputRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogInputRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogInputExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiAnalogInputExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogInputExtCluster::getDeadband() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::Deadband);
    if (result == nullptr) {
        result = new AttributeSingle(25, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogInputExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogInputExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogInputExtCluster::getHighLimit() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::HighLimit);
    if (result == nullptr) {
        result = new AttributeSingle(45, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogInputExtCluster::getLimitEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::LimitEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(52, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogInputExtCluster::getLowLimit() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::LowLimit);
    if (result == nullptr) {
        result = new AttributeSingle(59, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogInputExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogInputExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogInputExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

void PiAnalogInputExtCluster::sendTransferApduCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void PiAnalogInputExtCluster::sendConnectReqCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void PiAnalogInputExtCluster::sendDisconnectReqCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void PiAnalogInputExtCluster::sendConnectStatusNotiCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void PiAnalogInputExtCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onTransferApduCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onConnectReqCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto status_ = onDisconnectReqCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto status_ = onConnectStatusNotiCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeSingle* PiAnalogOutputRegCluster::getCovIncrement() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogOutputRegAttribute::CovIncrement);
    if (result == nullptr) {
        result = new AttributeSingle(22, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogOutputRegCluster::getDeviceType() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogOutputRegAttribute::DeviceType);
    if (result == nullptr) {
        result = new AttributeString(31);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiAnalogOutputRegCluster::getObjectId() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiAnalogOutputRegAttribute::ObjectId);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogOutputRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogOutputRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiAnalogOutputRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiAnalogOutputRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogOutputRegCluster::getUpdateInterval() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogOutputRegAttribute::UpdateInterval);
    if (result == nullptr) {
        result = new AttributeUInt8(118, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogOutputRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogOutputRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogOutputExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiAnalogOutputExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogOutputExtCluster::getDeadband() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::Deadband);
    if (result == nullptr) {
        result = new AttributeSingle(25, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogOutputExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogOutputExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogOutputExtCluster::getHighLimit() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::HighLimit);
    if (result == nullptr) {
        result = new AttributeSingle(45, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogOutputExtCluster::getLimitEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::LimitEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(52, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogOutputExtCluster::getLowLimit() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::LowLimit);
    if (result == nullptr) {
        result = new AttributeSingle(59, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogOutputExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogOutputExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogOutputExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogValueRegCluster::getCovIncrement() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogValueRegAttribute::CovIncrement);
    if (result == nullptr) {
        result = new AttributeSingle(22, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiAnalogValueRegCluster::getObjectId() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiAnalogValueRegAttribute::ObjectId);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogValueRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogValueRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiAnalogValueRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiAnalogValueRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiAnalogValueRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiAnalogValueRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogValueExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiAnalogValueExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogValueExtCluster::getDeadband() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::Deadband);
    if (result == nullptr) {
        result = new AttributeSingle(25, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogValueExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogValueExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogValueExtCluster::getHighLimit() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::HighLimit);
    if (result == nullptr) {
        result = new AttributeSingle(45, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogValueExtCluster::getLimitEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::LimitEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(52, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeSingle* PiAnalogValueExtCluster::getLowLimit() {
    auto result = (AttributeSingle*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::LowLimit);
    if (result == nullptr) {
        result = new AttributeSingle(59, DataType::Single);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogValueExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiAnalogValueExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiAnalogValueExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryInputRegCluster::getChangeOfStateCount() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::ChangeOfStateCount);
    if (result == nullptr) {
        result = new AttributeUInt32(15, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryInputRegCluster::getChangeOfStateTime() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::ChangeOfStateTime);
    if (result == nullptr) {
        result = new AttributeDateTime(16, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryInputRegCluster::getDeviceType() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::DeviceType);
    if (result == nullptr) {
        result = new AttributeString(31);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryInputRegCluster::getElapsedActiveTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::ElapsedActiveTime);
    if (result == nullptr) {
        result = new AttributeUInt32(33, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryInputRegCluster::getObjectIdentifier() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::ObjectIdentifier);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryInputRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiBinaryInputRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryInputRegCluster::getTimeOfATReset() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::TimeOfATReset);
    if (result == nullptr) {
        result = new AttributeDateTime(114, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryInputRegCluster::getTimeOfSCReset() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::TimeOfSCReset);
    if (result == nullptr) {
        result = new AttributeDateTime(115, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryInputRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryInputRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryInputExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryInputExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryInputExtCluster::getAlarmValue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryInputExtAttribute::AlarmValue);
    if (result == nullptr) {
        result = new AttributeUInt8(6, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiBinaryInputExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiBinaryInputExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryInputExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryInputExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryInputExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryInputExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryInputExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryInputExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryInputExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryInputExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryOutputRegCluster::getChangeOfStateCount() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::ChangeOfStateCount);
    if (result == nullptr) {
        result = new AttributeUInt32(15, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryOutputRegCluster::getChangeOfStateTime() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::ChangeOfStateTime);
    if (result == nullptr) {
        result = new AttributeDateTime(16, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryOutputRegCluster::getDeviceType() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::DeviceType);
    if (result == nullptr) {
        result = new AttributeString(31);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryOutputRegCluster::getElapsedActiveTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::ElapsedActiveTime);
    if (result == nullptr) {
        result = new AttributeUInt32(33, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryOutputRegCluster::getFeedBackValue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::FeedBackValue);
    if (result == nullptr) {
        result = new AttributeUInt8(40, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryOutputRegCluster::getObjectIdentifier() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::ObjectIdentifier);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryOutputRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiBinaryOutputRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryOutputRegCluster::getTimeOfATReset() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::TimeOfATReset);
    if (result == nullptr) {
        result = new AttributeDateTime(114, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryOutputRegCluster::getTimeOfSCReset() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::TimeOfSCReset);
    if (result == nullptr) {
        result = new AttributeDateTime(115, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryOutputRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryOutputRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryOutputExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryOutputExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiBinaryOutputExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiBinaryOutputExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryOutputExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryOutputExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryOutputExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryOutputExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryOutputExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryOutputExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryOutputExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryOutputExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryValueRegCluster::getChangeOfStateCount() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::ChangeOfStateCount);
    if (result == nullptr) {
        result = new AttributeUInt32(15, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryValueRegCluster::getChangeOfStateTime() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::ChangeOfStateTime);
    if (result == nullptr) {
        result = new AttributeDateTime(16, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryValueRegCluster::getElapsedActiveTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::ElapsedActiveTime);
    if (result == nullptr) {
        result = new AttributeUInt32(33, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiBinaryValueRegCluster::getObjectIdentifier() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::ObjectIdentifier);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryValueRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiBinaryValueRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryValueRegCluster::getTimeOfATReset() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::TimeOfATReset);
    if (result == nullptr) {
        result = new AttributeDateTime(114, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeDateTime* PiBinaryValueRegCluster::getTimeOfSCReset() {
    auto result = (AttributeDateTime*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::TimeOfSCReset);
    if (result == nullptr) {
        result = new AttributeDateTime(115, DataType::DateTime);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiBinaryValueRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiBinaryValueRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryValueExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryValueExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryValueExtCluster::getAlarmValue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryValueExtAttribute::AlarmValue);
    if (result == nullptr) {
        result = new AttributeUInt8(6, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiBinaryValueExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiBinaryValueExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryValueExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryValueExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryValueExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryValueExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryValueExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryValueExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiBinaryValueExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiBinaryValueExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateInputRegCluster::getDeviceType() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateInputRegAttribute::DeviceType);
    if (result == nullptr) {
        result = new AttributeString(31);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiMultistateInputRegCluster::getObjectId() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiMultistateInputRegAttribute::ObjectId);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateInputRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateInputRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateInputRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateInputRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateInputRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateInputRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateInputExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateInputExtCluster::getAlarmValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::AlarmValue);
    if (result == nullptr) {
        result = new AttributeUInt16(6, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateInputExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateInputExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateInputExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateInputExtCluster::getFaultValues() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::FaultValues);
    if (result == nullptr) {
        result = new AttributeUInt16(37, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateInputExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateInputExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateInputExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateOutputRegCluster::getDeviceType() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateOutputRegAttribute::DeviceType);
    if (result == nullptr) {
        result = new AttributeString(31);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateOutputRegCluster::getFeedBackValue() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateOutputRegAttribute::FeedBackValue);
    if (result == nullptr) {
        result = new AttributeUInt8(40, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiMultistateOutputRegCluster::getObjectId() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiMultistateOutputRegAttribute::ObjectId);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateOutputRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateOutputRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateOutputRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateOutputRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateOutputRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateOutputRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateOutputExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateOutputExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateOutputExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateOutputExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateOutputExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateOutputExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateOutputExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateOutputExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateOutputExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateOutputExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateOutputExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateOutputExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* PiMultistateValueRegCluster::getObjectId() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)PiMultistateValueRegAttribute::ObjectId);
    if (result == nullptr) {
        result = new AttributeUInt32(75, DataType::BacOID);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateValueRegCluster::getObjectName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateValueRegAttribute::ObjectName);
    if (result == nullptr) {
        result = new AttributeString(77);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateValueRegCluster::getObjectType() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateValueRegAttribute::ObjectType);
    if (result == nullptr) {
        result = new AttributeUInt16(79, DataType::Enum16);
        addAttribute(result);
    }
    return result;
}

AttributeString* PiMultistateValueRegCluster::getProfileName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)PiMultistateValueRegAttribute::ProfileName);
    if (result == nullptr) {
        result = new AttributeString(168);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateValueExtCluster::getAckedTransitions() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::AckedTransitions);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateValueExtCluster::getAlarmValue() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::AlarmValue);
    if (result == nullptr) {
        result = new AttributeUInt16(6, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateValueExtCluster::getNotificationClass() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::NotificationClass);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateValueExtCluster::getEventEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::EventEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(35, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateValueExtCluster::getEventState() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::EventState);
    if (result == nullptr) {
        result = new AttributeUInt8(36, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiMultistateValueExtCluster::getFaultValues() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::FaultValues);
    if (result == nullptr) {
        result = new AttributeUInt16(37, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateValueExtCluster::getNotifyType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::NotifyType);
    if (result == nullptr) {
        result = new AttributeUInt8(72, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* PiMultistateValueExtCluster::getTimeDelay() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiMultistateValueExtAttribute::TimeDelay);
    if (result == nullptr) {
        result = new AttributeUInt8(113, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt64* Pi11073ProtocolTunnelCluster::getManagerTarget() {
    auto result = (AttributeUInt64*)getAttributeById((uint16_t)Pi11073ProtocolTunnelAttribute::ManagerTarget);
    if (result == nullptr) {
        result = new AttributeUInt64(1, DataType::EUI64);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* Pi11073ProtocolTunnelCluster::getManagerEndpoint() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)Pi11073ProtocolTunnelAttribute::ManagerEndpoint);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* Pi11073ProtocolTunnelCluster::getConnected() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)Pi11073ProtocolTunnelAttribute::Connected);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* Pi11073ProtocolTunnelCluster::getPreemptible() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)Pi11073ProtocolTunnelAttribute::Preemptible);
    if (result == nullptr) {
        result = new AttributeUInt8(4, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* Pi11073ProtocolTunnelCluster::getIdleTimeout() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)Pi11073ProtocolTunnelAttribute::IdleTimeout);
    if (result == nullptr) {
        result = new AttributeUInt16(5, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void Pi11073ProtocolTunnelCluster::sendTransferApduCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void Pi11073ProtocolTunnelCluster::sendConnectReqCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void Pi11073ProtocolTunnelCluster::sendDisconnectReqCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void Pi11073ProtocolTunnelCluster::sendConnectStatusNotiCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void Pi11073ProtocolTunnelCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onTransferApduCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onConnectReqCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto status_ = onDisconnectReqCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto status_ = onConnectStatusNotiCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt8* PiIso7818ProtocolTunnelCluster::getStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)PiIso7818ProtocolTunnelAttribute::Status);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiRetailTunnelCluster::getManufacturerCode() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiRetailTunnelAttribute::ManufacturerCode);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* PiRetailTunnelCluster::getMsProfile() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)PiRetailTunnelAttribute::MsProfile);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentSummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentSummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(0, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentSummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentSummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(1, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentMaxDemandDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentMaxDemandDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(2, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentMaxDemandReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentMaxDemandReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(3, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getDftSumm() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::DftSumm);
    if (result == nullptr) {
        result = new AttributeUInt48(4, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getDailyFreezeTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::DailyFreezeTime);
    if (result == nullptr) {
        result = new AttributeUInt16(5, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* SeMeteringCluster::getPowerFactor() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)SeMeteringAttribute::PowerFactor);
    if (result == nullptr) {
        result = new AttributeInt8(6, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getReadingSnapshotTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::ReadingSnapshotTime);
    if (result == nullptr) {
        result = new AttributeUInt32(7, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getCurrentMaxDemandDeliverdTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentMaxDemandDeliverdTime);
    if (result == nullptr) {
        result = new AttributeUInt32(8, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getCurrentMaxDemandReceivedTime() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentMaxDemandReceivedTime);
    if (result == nullptr) {
        result = new AttributeUInt32(9, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getDefaultUpdatePeriod() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::DefaultUpdatePeriod);
    if (result == nullptr) {
        result = new AttributeUInt8(10, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getFastPollUpdatePeriod() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::FastPollUpdatePeriod);
    if (result == nullptr) {
        result = new AttributeUInt8(11, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentBlockPeriodConsumpDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentBlockPeriodConsumpDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(12, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getDailyConsumpTarget() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::DailyConsumpTarget);
    if (result == nullptr) {
        result = new AttributeUInt24(13, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getCurrentBlock() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentBlock);
    if (result == nullptr) {
        result = new AttributeUInt8(14, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getProfileIntervalPeriod() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::ProfileIntervalPeriod);
    if (result == nullptr) {
        result = new AttributeUInt8(15, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getIntervalReadReportingPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::IntervalReadReportingPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getPresetReadingTime() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::PresetReadingTime);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getVolumePerReport() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::VolumePerReport);
    if (result == nullptr) {
        result = new AttributeUInt16(18, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getFlowRestriction() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::FlowRestriction);
    if (result == nullptr) {
        result = new AttributeUInt8(19, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getSupplyStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::SupplyStatus);
    if (result == nullptr) {
        result = new AttributeUInt8(20, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentInEnergyCarrierSumm() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentInEnergyCarrierSumm);
    if (result == nullptr) {
        result = new AttributeUInt48(21, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentOutEnergyCarrierSumm() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentOutEnergyCarrierSumm);
    if (result == nullptr) {
        result = new AttributeUInt48(22, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getInletTempreature() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::InletTempreature);
    if (result == nullptr) {
        result = new AttributeInt24(23, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getOutletTempreature() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::OutletTempreature);
    if (result == nullptr) {
        result = new AttributeInt24(24, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getControlTempreature() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::ControlTempreature);
    if (result == nullptr) {
        result = new AttributeInt24(25, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurrentInEnergyCarrierDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentInEnergyCarrierDemand);
    if (result == nullptr) {
        result = new AttributeInt24(26, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurrentOutEnergyCarrierDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentOutEnergyCarrierDemand);
    if (result == nullptr) {
        result = new AttributeInt24(27, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentBlockPeriodConsumpReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentBlockPeriodConsumpReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(29, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentBlockReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentBlockReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(30, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getDFTSummationReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::DFTSummationReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(31, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getActiveRegisterTierDelivered() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::ActiveRegisterTierDelivered);
    if (result == nullptr) {
        result = new AttributeUInt8(32, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getActiveRegisterTierReceived() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::ActiveRegisterTierReceived);
    if (result == nullptr) {
        result = new AttributeUInt8(33, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier1SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier1SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(256, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier1SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier1SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(257, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier2SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier2SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(258, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier2SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier2SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(259, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier3SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier3SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(260, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier3SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier3SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(261, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier4SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier4SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(262, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier4SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier4SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(263, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier5SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier5SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(264, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier5SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier5SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(265, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier6SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier6SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(266, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier6SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier6SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(267, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier7SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier7SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(268, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier7SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier7SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(269, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier8SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier8SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(270, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier8SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier8SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(271, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier9SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier9SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(272, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier9SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier9SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(273, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier10SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier10SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(274, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier10SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier10SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(275, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier11SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier11SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(276, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier11SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier11SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(277, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier12SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier12SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(278, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier12SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier12SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(279, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier13SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier13SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(280, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier13SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier13SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(281, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier14SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier14SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(282, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier14SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier14SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(283, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier15SummDelivered() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier15SummDelivered);
    if (result == nullptr) {
        result = new AttributeUInt48(284, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentTier15SummReceived() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentTier15SummReceived);
    if (result == nullptr) {
        result = new AttributeUInt48(285, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getStatus() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::Status);
    if (result == nullptr) {
        result = new AttributeUInt8(512, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getRemainingBattLife() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::RemainingBattLife);
    if (result == nullptr) {
        result = new AttributeUInt8(513, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getHoursInOperation() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::HoursInOperation);
    if (result == nullptr) {
        result = new AttributeUInt24(514, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getHoursInFault() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::HoursInFault);
    if (result == nullptr) {
        result = new AttributeUInt24(515, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt64* SeMeteringCluster::getExtendedStatus() {
    auto result = (AttributeUInt64*)getAttributeById((uint16_t)SeMeteringAttribute::ExtendedStatus);
    if (result == nullptr) {
        result = new AttributeUInt64(516, DataType::Map64);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getUnitOfMeasure() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::UnitOfMeasure);
    if (result == nullptr) {
        result = new AttributeUInt8(768, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getMultiplier() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::Multiplier);
    if (result == nullptr) {
        result = new AttributeUInt24(769, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getDivisor() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::Divisor);
    if (result == nullptr) {
        result = new AttributeUInt24(770, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getSummaFormatting() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::SummaFormatting);
    if (result == nullptr) {
        result = new AttributeUInt8(771, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getDemandFormatting() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::DemandFormatting);
    if (result == nullptr) {
        result = new AttributeUInt8(772, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getHistoricalConsumpFormatting() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::HistoricalConsumpFormatting);
    if (result == nullptr) {
        result = new AttributeUInt8(773, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getMeteringDeviceType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::MeteringDeviceType);
    if (result == nullptr) {
        result = new AttributeUInt8(774, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* SeMeteringCluster::getSiteId() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)SeMeteringAttribute::SiteId);
    if (result == nullptr) {
        result = new AttributeOctstr(775);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* SeMeteringCluster::getMeterSerialNumber() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)SeMeteringAttribute::MeterSerialNumber);
    if (result == nullptr) {
        result = new AttributeOctstr(776);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getEnergyCarrierUnitOfMeas() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::EnergyCarrierUnitOfMeas);
    if (result == nullptr) {
        result = new AttributeUInt8(777, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getEnergyCarrierSummFormatting() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::EnergyCarrierSummFormatting);
    if (result == nullptr) {
        result = new AttributeUInt8(778, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getEnergyCarrierDemandFormatting() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::EnergyCarrierDemandFormatting);
    if (result == nullptr) {
        result = new AttributeUInt8(779, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getTemperatureUnitOfMeas() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::TemperatureUnitOfMeas);
    if (result == nullptr) {
        result = new AttributeUInt8(780, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getTemperatureFormatting() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::TemperatureFormatting);
    if (result == nullptr) {
        result = new AttributeUInt8(781, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* SeMeteringCluster::getModuleSerialNumber() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)SeMeteringAttribute::ModuleSerialNumber);
    if (result == nullptr) {
        result = new AttributeOctstr(782);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* SeMeteringCluster::getOperatingTariffLevel() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)SeMeteringAttribute::OperatingTariffLevel);
    if (result == nullptr) {
        result = new AttributeOctstr(783);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getInstantaneousDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::InstantaneousDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1024, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getCurrentdayConsumpDelivered() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentdayConsumpDelivered);
    if (result == nullptr) {
        result = new AttributeUInt24(1025, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getCurrentdayConsumpReceived() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentdayConsumpReceived);
    if (result == nullptr) {
        result = new AttributeUInt24(1026, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getPreviousdayConsumpDelivered() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::PreviousdayConsumpDelivered);
    if (result == nullptr) {
        result = new AttributeUInt24(1027, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getPreviousdayConsumpReceived() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::PreviousdayConsumpReceived);
    if (result == nullptr) {
        result = new AttributeUInt24(1028, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getCurPartProfileIntStartTimeDelivered() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::CurPartProfileIntStartTimeDelivered);
    if (result == nullptr) {
        result = new AttributeUInt32(1029, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getCurPartProfileIntStartTimeReceived() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::CurPartProfileIntStartTimeReceived);
    if (result == nullptr) {
        result = new AttributeUInt32(1030, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getCurPartProfileIntValueDelivered() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurPartProfileIntValueDelivered);
    if (result == nullptr) {
        result = new AttributeUInt24(1031, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getCurPartProfileIntValueReceived() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurPartProfileIntValueReceived);
    if (result == nullptr) {
        result = new AttributeUInt24(1032, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentDayMaxPressure() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentDayMaxPressure);
    if (result == nullptr) {
        result = new AttributeUInt48(1033, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getCurrentDayMinPressure() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentDayMinPressure);
    if (result == nullptr) {
        result = new AttributeUInt48(1034, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getPreviousDayMaxPressure() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::PreviousDayMaxPressure);
    if (result == nullptr) {
        result = new AttributeUInt48(1035, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getPreviousDayMinPressure() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::PreviousDayMinPressure);
    if (result == nullptr) {
        result = new AttributeUInt48(1036, DataType::UInt48);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurrentDayMaxDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentDayMaxDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1037, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getPreviousDayMaxDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::PreviousDayMaxDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1038, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurrentMonthMaxDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentMonthMaxDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1039, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurrentYearMaxDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentYearMaxDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1040, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurrentdayMaxEnergyCarrDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentdayMaxEnergyCarrDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1041, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getPreviousdayMaxEnergyCarrDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::PreviousdayMaxEnergyCarrDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1042, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurMonthMaxEnergyCarrDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurMonthMaxEnergyCarrDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1043, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurMonthMinEnergyCarrDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurMonthMinEnergyCarrDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1044, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurYearMaxEnergyCarrDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurYearMaxEnergyCarrDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1045, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* SeMeteringCluster::getCurYearMinEnergyCarrDemand() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurYearMinEnergyCarrDemand);
    if (result == nullptr) {
        result = new AttributeInt24(1046, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getMaxNumberOfPeriodsDelivered() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::MaxNumberOfPeriodsDelivered);
    if (result == nullptr) {
        result = new AttributeUInt8(1280, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getCurrentDemandDelivered() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::CurrentDemandDelivered);
    if (result == nullptr) {
        result = new AttributeUInt24(1536, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt24* SeMeteringCluster::getDemandLimit() {
    auto result = (AttributeUInt24*)getAttributeById((uint16_t)SeMeteringAttribute::DemandLimit);
    if (result == nullptr) {
        result = new AttributeUInt24(1537, DataType::UInt24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getDemandIntegrationPeriod() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::DemandIntegrationPeriod);
    if (result == nullptr) {
        result = new AttributeUInt8(1538, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* SeMeteringCluster::getNumberOfDemandSubintervals() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)SeMeteringAttribute::NumberOfDemandSubintervals);
    if (result == nullptr) {
        result = new AttributeUInt8(1539, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getDemandLimitArmDuration() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::DemandLimitArmDuration);
    if (result == nullptr) {
        result = new AttributeUInt16(1540, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getGenericAlarmMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::GenericAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt16(2048, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getElectricityAlarmMask() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::ElectricityAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt32(2049, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getGenFlowPressureAlarmMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::GenFlowPressureAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt16(2050, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getWaterSpecificAlarmMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::WaterSpecificAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt16(2051, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getHeatCoolSpecificAlarmMASK() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::HeatCoolSpecificAlarmMASK);
    if (result == nullptr) {
        result = new AttributeUInt16(2052, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getGasSpecificAlarmMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::GasSpecificAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt16(2053, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt48* SeMeteringCluster::getExtendedGenericAlarmMask() {
    auto result = (AttributeUInt48*)getAttributeById((uint16_t)SeMeteringAttribute::ExtendedGenericAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt48(2054, DataType::Map48);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* SeMeteringCluster::getManufactureAlarmMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)SeMeteringAttribute::ManufactureAlarmMask);
    if (result == nullptr) {
        result = new AttributeUInt16(2055, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getBillToDate() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::BillToDate);
    if (result == nullptr) {
        result = new AttributeUInt32(2560, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getBillToDateTimeStamp() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::BillToDateTimeStamp);
    if (result == nullptr) {
        result = new AttributeUInt32(2561, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getProjectedBill() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::ProjectedBill);
    if (result == nullptr) {
        result = new AttributeUInt32(2562, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getProjectedBillTimeStamp() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::ProjectedBillTimeStamp);
    if (result == nullptr) {
        result = new AttributeUInt32(2563, DataType::UTC);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getNotificationControlFlags() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::NotificationControlFlags);
    if (result == nullptr) {
        result = new AttributeUInt32(0, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getNotificationFlags() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::NotificationFlags);
    if (result == nullptr) {
        result = new AttributeUInt32(1, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getPriceNotificationFlags() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::PriceNotificationFlags);
    if (result == nullptr) {
        result = new AttributeUInt32(2, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getCalendarNotificationFlags() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::CalendarNotificationFlags);
    if (result == nullptr) {
        result = new AttributeUInt32(3, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getPrePayNotificationFlags() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::PrePayNotificationFlags);
    if (result == nullptr) {
        result = new AttributeUInt32(4, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* SeMeteringCluster::getDeviceManagementFlags() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)SeMeteringAttribute::DeviceManagementFlags);
    if (result == nullptr) {
        result = new AttributeUInt32(5, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

void SeMeteringCluster::sendGetProfileCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendReqMirrorCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendMirrorRemCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendReqFastPollModeCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendGetSnapshotCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendTakeSnapshotCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        5
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendMirrorReportAttrRspCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        6
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendOwonGetHistoryRecordCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        32
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::sendOwonStopSendingHistoricalRecordCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        33
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void SeMeteringCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onGetProfileCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onReqMirrorCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto status_ = onMirrorRemCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto status_ = onReqFastPollModeCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto status_ = onGetSnapshotCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 5: {
            auto status_ = onTakeSnapshotCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 6: {
            auto status_ = onMirrorReportAttrRspCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 32: {
            auto status_ = onOwonGetHistoryRecordCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 33: {
            auto status_ = onOwonStopSendingHistoricalRecordCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeString* TelecommunicationsInformationCluster::getNodeDescription() {
    auto result = (AttributeString*)getAttributeById((uint16_t)TelecommunicationsInformationAttribute::NodeDescription);
    if (result == nullptr) {
        result = new AttributeString(0);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsInformationCluster::getDeliveryEnable() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsInformationAttribute::DeliveryEnable);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* TelecommunicationsInformationCluster::getPushInformationTimer() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)TelecommunicationsInformationAttribute::PushInformationTimer);
    if (result == nullptr) {
        result = new AttributeUInt32(2, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsInformationCluster::getEnableSecureConfiguration() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsInformationAttribute::EnableSecureConfiguration);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* TelecommunicationsInformationCluster::getNumberOfContents() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)TelecommunicationsInformationAttribute::NumberOfContents);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* TelecommunicationsInformationCluster::getContentRootID() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)TelecommunicationsInformationAttribute::ContentRootID);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getCodecType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::CodecType);
    if (result == nullptr) {
        result = new AttributeUInt8(0, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getSamplingFrequency() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::SamplingFrequency);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getCodecrate() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::Codecrate);
    if (result == nullptr) {
        result = new AttributeUInt8(2, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getEstablishmentTimeout() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::EstablishmentTimeout);
    if (result == nullptr) {
        result = new AttributeUInt8(3, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getCodecTypeSub1() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::CodecTypeSub1);
    if (result == nullptr) {
        result = new AttributeUInt8(4, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getCodecTypeSub2() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::CodecTypeSub2);
    if (result == nullptr) {
        result = new AttributeUInt8(5, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getCodecTypeSub3() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::CodecTypeSub3);
    if (result == nullptr) {
        result = new AttributeUInt8(6, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getCompressionType() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::CompressionType);
    if (result == nullptr) {
        result = new AttributeUInt8(7, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getCompressionRate() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::CompressionRate);
    if (result == nullptr) {
        result = new AttributeUInt8(8, DataType::Enum8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getOptionFlags() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::OptionFlags);
    if (result == nullptr) {
        result = new AttributeUInt8(9, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsVoiceOverZigbeeCluster::getThreshold() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsVoiceOverZigbeeAttribute::Threshold);
    if (result == nullptr) {
        result = new AttributeUInt8(10, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* TelecommunicationsChattingCluster::getUID() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)TelecommunicationsChattingAttribute::UID);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeString* TelecommunicationsChattingCluster::getNickname() {
    auto result = (AttributeString*)getAttributeById((uint16_t)TelecommunicationsChattingAttribute::Nickname);
    if (result == nullptr) {
        result = new AttributeString(1);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* TelecommunicationsChattingCluster::getCID() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)TelecommunicationsChattingAttribute::CID);
    if (result == nullptr) {
        result = new AttributeUInt16(16, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeString* TelecommunicationsChattingCluster::getName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)TelecommunicationsChattingAttribute::Name);
    if (result == nullptr) {
        result = new AttributeString(17);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* TelecommunicationsChattingCluster::getEnableAddChat() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)TelecommunicationsChattingAttribute::EnableAddChat);
    if (result == nullptr) {
        result = new AttributeUInt8(18, DataType::Bool);
        addAttribute(result);
    }
    return result;
}

AttributeUInt56* HaApplianceIdentificationCluster::getBasicIdentification() {
    auto result = (AttributeUInt56*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::BasicIdentification);
    if (result == nullptr) {
        result = new AttributeUInt56(0, DataType::UInt56);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaApplianceIdentificationCluster::getCompanyName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::CompanyName);
    if (result == nullptr) {
        result = new AttributeString(16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaApplianceIdentificationCluster::getCompanyId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::CompanyId);
    if (result == nullptr) {
        result = new AttributeUInt16(17, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaApplianceIdentificationCluster::getBrandName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::BrandName);
    if (result == nullptr) {
        result = new AttributeString(18);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaApplianceIdentificationCluster::getBrandId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::BrandId);
    if (result == nullptr) {
        result = new AttributeUInt16(19, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* HaApplianceIdentificationCluster::getModel() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::Model);
    if (result == nullptr) {
        result = new AttributeOctstr(20);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* HaApplianceIdentificationCluster::getPartNumber() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::PartNumber);
    if (result == nullptr) {
        result = new AttributeOctstr(21);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* HaApplianceIdentificationCluster::getProductRevision() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::ProductRevision);
    if (result == nullptr) {
        result = new AttributeOctstr(22);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* HaApplianceIdentificationCluster::getSoftwareRevision() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::SoftwareRevision);
    if (result == nullptr) {
        result = new AttributeOctstr(23);
        addAttribute(result);
    }
    return result;
}

AttributeOctstr* HaApplianceIdentificationCluster::getProductTypeName() {
    auto result = (AttributeOctstr*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::ProductTypeName);
    if (result == nullptr) {
        result = new AttributeOctstr(24);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaApplianceIdentificationCluster::getProductTypeId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::ProductTypeId);
    if (result == nullptr) {
        result = new AttributeUInt16(25, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HaApplianceIdentificationCluster::getCecedSpecificationVersion() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HaApplianceIdentificationAttribute::CecedSpecificationVersion);
    if (result == nullptr) {
        result = new AttributeUInt8(26, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getCompanyName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::CompanyName);
    if (result == nullptr) {
        result = new AttributeString(0);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaMeterIdentificationCluster::getMeterTypeId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::MeterTypeId);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaMeterIdentificationCluster::getDataQualityId() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::DataQualityId);
    if (result == nullptr) {
        result = new AttributeUInt16(4, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getCustomerName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::CustomerName);
    if (result == nullptr) {
        result = new AttributeString(5);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getModel() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::Model);
    if (result == nullptr) {
        result = new AttributeString(6);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getPartNumber() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::PartNumber);
    if (result == nullptr) {
        result = new AttributeString(7);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getProductRevision() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::ProductRevision);
    if (result == nullptr) {
        result = new AttributeString(8);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getSoftwareRevision() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::SoftwareRevision);
    if (result == nullptr) {
        result = new AttributeString(10);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getUtilityName() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::UtilityName);
    if (result == nullptr) {
        result = new AttributeString(11);
        addAttribute(result);
    }
    return result;
}

AttributeString* HaMeterIdentificationCluster::getPod() {
    auto result = (AttributeString*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::Pod);
    if (result == nullptr) {
        result = new AttributeString(12);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* HaMeterIdentificationCluster::getAvailablePower() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::AvailablePower);
    if (result == nullptr) {
        result = new AttributeInt24(13, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

AttributeInt24* HaMeterIdentificationCluster::getPowerThreshold() {
    auto result = (AttributeInt24*)getAttributeById((uint16_t)HaMeterIdentificationAttribute::PowerThreshold);
    if (result == nullptr) {
        result = new AttributeInt24(14, DataType::Int24);
        addAttribute(result);
    }
    return result;
}

void HaApplianceEventsAlertsCluster::sendGetAlertsCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HaApplianceEventsAlertsCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onGetAlertsCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt32* HaApplianceStatisticsCluster::getLogMaxSize() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaApplianceStatisticsAttribute::LogMaxSize);
    if (result == nullptr) {
        result = new AttributeUInt32(0, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HaApplianceStatisticsCluster::getLogQueueMaxSize() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HaApplianceStatisticsAttribute::LogQueueMaxSize);
    if (result == nullptr) {
        result = new AttributeUInt8(1, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

void HaApplianceStatisticsCluster::sendLogCommand(DeviceManager& deviceManager, uint8_t endpointId, uint32_t logid) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt32Le(logid);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HaApplianceStatisticsCluster::sendLogQueueCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HaApplianceStatisticsCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto logid = request.readUInt32Le();
            auto status_ = onLogCommand(logid);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto status_ = onLogQueueCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt32* HaElectricalMeasurementCluster::getMeasurementType() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::MeasurementType);
    if (result == nullptr) {
        result = new AttributeUInt32(0, DataType::Map32);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcVoltage() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcVoltage);
    if (result == nullptr) {
        result = new AttributeInt16(256, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcVoltageMin() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcVoltageMin);
    if (result == nullptr) {
        result = new AttributeInt16(257, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcvoltagemax() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::Dcvoltagemax);
    if (result == nullptr) {
        result = new AttributeInt16(258, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(259, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcCurrentMin() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcCurrentMin);
    if (result == nullptr) {
        result = new AttributeInt16(260, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcCurrentMax() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcCurrentMax);
    if (result == nullptr) {
        result = new AttributeInt16(261, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcPower() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcPower);
    if (result == nullptr) {
        result = new AttributeInt16(262, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcPowerMin() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcPowerMin);
    if (result == nullptr) {
        result = new AttributeInt16(263, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcPowerMax() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcPowerMax);
    if (result == nullptr) {
        result = new AttributeInt16(264, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getDcVoltageMultiplier() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcVoltageMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt16(512, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getDcVoltageDivisor() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcVoltageDivisor);
    if (result == nullptr) {
        result = new AttributeUInt16(513, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getDcCurrentMultiplier() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcCurrentMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt16(514, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getDcCurrentDivisor() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcCurrentDivisor);
    if (result == nullptr) {
        result = new AttributeUInt16(515, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getDcPowerMultiplier() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcPowerMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt16(516, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getDcPowerDivisor() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcPowerDivisor);
    if (result == nullptr) {
        result = new AttributeUInt16(517, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcFrequency() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcFrequency);
    if (result == nullptr) {
        result = new AttributeUInt16(768, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcFrequencyMin() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcFrequencyMin);
    if (result == nullptr) {
        result = new AttributeUInt16(769, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcFrequencyMax() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcFrequencyMax);
    if (result == nullptr) {
        result = new AttributeUInt16(770, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getNeutralCurrent() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::NeutralCurrent);
    if (result == nullptr) {
        result = new AttributeUInt16(771, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt32* HaElectricalMeasurementCluster::getTotalActivePower() {
    auto result = (AttributeInt32*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::TotalActivePower);
    if (result == nullptr) {
        result = new AttributeInt32(772, DataType::Int32);
        addAttribute(result);
    }
    return result;
}

AttributeInt32* HaElectricalMeasurementCluster::getTotalReactivePower() {
    auto result = (AttributeInt32*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::TotalReactivePower);
    if (result == nullptr) {
        result = new AttributeInt32(773, DataType::Int32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HaElectricalMeasurementCluster::getTotalApparentPower() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::TotalApparentPower);
    if (result == nullptr) {
        result = new AttributeUInt32(774, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeas1stHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::Meas1stHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(775, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeas3rdHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::Meas3rdHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(776, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeas5thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::Meas5thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(777, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeas7thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::Meas7thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(778, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeas9thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::Meas9thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(779, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeas11thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::Meas11thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(780, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeasPhase1stHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::MeasPhase1stHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(781, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeasPhase3rdHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::MeasPhase3rdHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(782, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeasPhase5thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::MeasPhase5thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(783, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeasPhase7thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::MeasPhase7thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(784, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeasPhase9thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::MeasPhase9thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(785, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getMeasPhase11thHarmonicCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::MeasPhase11thHarmonicCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(786, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcFrequencyMultiplier() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcFrequencyMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt16(1024, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcFrequencyDivisor() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcFrequencyDivisor);
    if (result == nullptr) {
        result = new AttributeUInt16(1025, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HaElectricalMeasurementCluster::getPowerMultiplier() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::PowerMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt32(1026, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HaElectricalMeasurementCluster::getPowerDivisor() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::PowerDivisor);
    if (result == nullptr) {
        result = new AttributeUInt32(1027, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HaElectricalMeasurementCluster::getHarmonicCurrentMultiplier() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::HarmonicCurrentMultiplier);
    if (result == nullptr) {
        result = new AttributeInt8(1028, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HaElectricalMeasurementCluster::getPhaseHarmonicCurrentMultiplier() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::PhaseHarmonicCurrentMultiplier);
    if (result == nullptr) {
        result = new AttributeInt8(1029, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getInstantaneousVoltage() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::InstantaneousVoltage);
    if (result == nullptr) {
        result = new AttributeInt16(1280, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getInstantaneousLineCurrent() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::InstantaneousLineCurrent);
    if (result == nullptr) {
        result = new AttributeUInt16(1281, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getInstantaneousActiveCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::InstantaneousActiveCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(1282, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getInstantaneousReactiveCurrent() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::InstantaneousReactiveCurrent);
    if (result == nullptr) {
        result = new AttributeInt16(1283, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getInstantaneousPower() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::InstantaneousPower);
    if (result == nullptr) {
        result = new AttributeInt16(1284, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltage() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltage);
    if (result == nullptr) {
        result = new AttributeUInt16(1285, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageMin() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageMin);
    if (result == nullptr) {
        result = new AttributeUInt16(1286, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageMax() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageMax);
    if (result == nullptr) {
        result = new AttributeUInt16(1287, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrent() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrent);
    if (result == nullptr) {
        result = new AttributeUInt16(1288, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentMin() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentMin);
    if (result == nullptr) {
        result = new AttributeUInt16(1289, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentMax() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentMax);
    if (result == nullptr) {
        result = new AttributeUInt16(1290, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePower() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePower);
    if (result == nullptr) {
        result = new AttributeInt16(1291, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerMin() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerMin);
    if (result == nullptr) {
        result = new AttributeInt16(1292, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerMax() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerMax);
    if (result == nullptr) {
        result = new AttributeInt16(1293, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getReactivePower() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ReactivePower);
    if (result == nullptr) {
        result = new AttributeInt16(1294, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getApparentPower() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ApparentPower);
    if (result == nullptr) {
        result = new AttributeUInt16(1295, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HaElectricalMeasurementCluster::getPowerFactor() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::PowerFactor);
    if (result == nullptr) {
        result = new AttributeInt8(1296, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageRmsVoltageMeasPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsVoltageMeasPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(1297, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageRmsOverVoltageCounter() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsOverVoltageCounter);
    if (result == nullptr) {
        result = new AttributeUInt16(1298, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageRmsUnderVoltageCounter() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsUnderVoltageCounter);
    if (result == nullptr) {
        result = new AttributeUInt16(1299, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsExtremeOverVoltagePeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeOverVoltagePeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(1300, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsExtremeUnderVoltagePeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeUnderVoltagePeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(1301, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageSagPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSagPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(1302, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageSwellPeriod() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSwellPeriod);
    if (result == nullptr) {
        result = new AttributeUInt16(1303, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcVoltageMultiplier() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcVoltageMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt16(1536, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcVoltageDivisor() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcVoltageDivisor);
    if (result == nullptr) {
        result = new AttributeUInt16(1537, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcCurrentMultiplier() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcCurrentMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt16(1538, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcCurrentDivisor() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcCurrentDivisor);
    if (result == nullptr) {
        result = new AttributeUInt16(1539, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcPowerMultiplier() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcPowerMultiplier);
    if (result == nullptr) {
        result = new AttributeUInt16(1540, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcPowerDivisor() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcPowerDivisor);
    if (result == nullptr) {
        result = new AttributeUInt16(1541, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HaElectricalMeasurementCluster::getDcOverloadAlarmsMask() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcOverloadAlarmsMask);
    if (result == nullptr) {
        result = new AttributeUInt8(1792, DataType::Map8);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcVoltageOverload() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcVoltageOverload);
    if (result == nullptr) {
        result = new AttributeInt16(1793, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getDcCurrentOverload() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::DcCurrentOverload);
    if (result == nullptr) {
        result = new AttributeInt16(1794, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAcAlarmsMask() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcAlarmsMask);
    if (result == nullptr) {
        result = new AttributeUInt16(2048, DataType::Map16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getAcVoltageOverload() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcVoltageOverload);
    if (result == nullptr) {
        result = new AttributeInt16(2049, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getAcCurrentOverload() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcCurrentOverload);
    if (result == nullptr) {
        result = new AttributeInt16(2050, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getAcActivePowerOverload() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcActivePowerOverload);
    if (result == nullptr) {
        result = new AttributeInt16(2051, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getAcReactivePowerOverload() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AcReactivePowerOverload);
    if (result == nullptr) {
        result = new AttributeInt16(2052, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getAverageRmsOverVoltage() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsOverVoltage);
    if (result == nullptr) {
        result = new AttributeInt16(2053, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getAverageRmsUnderVoltage() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsUnderVoltage);
    if (result == nullptr) {
        result = new AttributeInt16(2054, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getRmsExtremeOverVoltage() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeOverVoltage);
    if (result == nullptr) {
        result = new AttributeInt16(2055, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getRmsExtremeUnderVoltage() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeUnderVoltage);
    if (result == nullptr) {
        result = new AttributeInt16(2056, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getRmsVoltageSag() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSag);
    if (result == nullptr) {
        result = new AttributeInt16(2057, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getRmsVoltageSwell() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSwell);
    if (result == nullptr) {
        result = new AttributeInt16(2058, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getLineCurrentPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::LineCurrentPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2305, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActiveCurrentPhB() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActiveCurrentPhB);
    if (result == nullptr) {
        result = new AttributeInt16(2306, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getReactiveCurrentPhB() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ReactiveCurrentPhB);
    if (result == nullptr) {
        result = new AttributeInt16(2307, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltagePhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltagePhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2309, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageMinPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageMinPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2310, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageMaxPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageMaxPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2311, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2312, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentMinPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentMinPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2313, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentMaxPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentMaxPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2314, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerPhB() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerPhB);
    if (result == nullptr) {
        result = new AttributeInt16(2315, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerMinPhB() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerMinPhB);
    if (result == nullptr) {
        result = new AttributeInt16(2316, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerMaxPhB() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerMaxPhB);
    if (result == nullptr) {
        result = new AttributeInt16(2317, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getReactivePowerPhB() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ReactivePowerPhB);
    if (result == nullptr) {
        result = new AttributeInt16(2318, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getApparentPowerPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ApparentPowerPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2319, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HaElectricalMeasurementCluster::getPowerFactorPhB() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::PowerFactorPhB);
    if (result == nullptr) {
        result = new AttributeInt8(2320, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageRmsVoltageMeasurePeriodPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsVoltageMeasurePeriodPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2321, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageRmsOverVoltageCounterPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsOverVoltageCounterPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2322, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageUnderVoltageCounterPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageUnderVoltageCounterPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2323, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsExtremeOverVoltagePeriodPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeOverVoltagePeriodPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2324, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsExtremeUnderVoltagePeriodPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeUnderVoltagePeriodPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2325, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageSagPeriodPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSagPeriodPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2326, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageSwellPeriodPhB() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSwellPeriodPhB);
    if (result == nullptr) {
        result = new AttributeUInt16(2327, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getLineCurrentPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::LineCurrentPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2561, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActiveCurrentPhC() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActiveCurrentPhC);
    if (result == nullptr) {
        result = new AttributeInt16(2562, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getReactiveCurrentPhC() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ReactiveCurrentPhC);
    if (result == nullptr) {
        result = new AttributeInt16(2563, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltagePhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltagePhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2565, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageMinPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageMinPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2566, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageMaxPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageMaxPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2567, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2568, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentMinPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentMinPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2569, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsCurrentMaxPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsCurrentMaxPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2570, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerPhC() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerPhC);
    if (result == nullptr) {
        result = new AttributeInt16(2571, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerMinPhC() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerMinPhC);
    if (result == nullptr) {
        result = new AttributeInt16(2572, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getActivePowerMaxPhC() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ActivePowerMaxPhC);
    if (result == nullptr) {
        result = new AttributeInt16(2573, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeInt16* HaElectricalMeasurementCluster::getReactivePowerPhC() {
    auto result = (AttributeInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ReactivePowerPhC);
    if (result == nullptr) {
        result = new AttributeInt16(2574, DataType::Int16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getApparentPowerPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::ApparentPowerPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2575, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HaElectricalMeasurementCluster::getPowerFactorPhC() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::PowerFactorPhC);
    if (result == nullptr) {
        result = new AttributeInt8(2576, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageRmsVoltageMeasPeriodPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsVoltageMeasPeriodPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2577, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageRmsOverVoltageCounterPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageRmsOverVoltageCounterPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2578, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getAverageUnderVoltageCounterPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::AverageUnderVoltageCounterPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2579, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsExtremeOverVoltagePeriodPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeOverVoltagePeriodPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2580, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsExtremeUnderVoltagePeriodPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsExtremeUnderVoltagePeriodPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2581, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageSagPeriodPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSagPeriodPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2582, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaElectricalMeasurementCluster::getRmsVoltageSwellPeriodPhC() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaElectricalMeasurementAttribute::RmsVoltageSwellPeriodPhC);
    if (result == nullptr) {
        result = new AttributeUInt16(2583, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

void HaElectricalMeasurementCluster::sendGetProfileInfoCommand(DeviceManager& deviceManager, uint8_t endpointId) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);


    deviceManager.sendMessage(this, endpointId, buffer);
}

void HaElectricalMeasurementCluster::sendGetMeasurementProfileCommand(DeviceManager& deviceManager, uint8_t endpointId, uint16_t attrId, uint32_t starttime, uint8_t numofuntervals) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeUInt16Le(attrId);
    buffer.writeUInt32Le(starttime);
    buffer.writeUInt8(numofuntervals);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void HaElectricalMeasurementCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto status_ = onGetProfileInfoCommand();
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto attrId = request.readUInt16Le();
            auto starttime = request.readUInt32Le();
            auto numofuntervals = request.readUInt8();
            auto status_ = onGetMeasurementProfileCommand(attrId, starttime, numofuntervals);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeUInt16* HaDiagnosticCluster::getNumberOfResets() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::NumberOfResets);
    if (result == nullptr) {
        result = new AttributeUInt16(0, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getPersistentMemoryWrites() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::PersistentMemoryWrites);
    if (result == nullptr) {
        result = new AttributeUInt16(1, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HaDiagnosticCluster::getMacRxBcast() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaDiagnosticAttribute::MacRxBcast);
    if (result == nullptr) {
        result = new AttributeUInt32(256, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HaDiagnosticCluster::getMacTxBcast() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaDiagnosticAttribute::MacTxBcast);
    if (result == nullptr) {
        result = new AttributeUInt32(257, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HaDiagnosticCluster::getMacRxUcast() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaDiagnosticAttribute::MacRxUcast);
    if (result == nullptr) {
        result = new AttributeUInt32(258, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt32* HaDiagnosticCluster::getMacTxUcast() {
    auto result = (AttributeUInt32*)getAttributeById((uint16_t)HaDiagnosticAttribute::MacTxUcast);
    if (result == nullptr) {
        result = new AttributeUInt32(259, DataType::UInt32);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getMacTxUcastRetry() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::MacTxUcastRetry);
    if (result == nullptr) {
        result = new AttributeUInt16(260, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getMacTxUcastFail() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::MacTxUcastFail);
    if (result == nullptr) {
        result = new AttributeUInt16(261, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getAPSRxBcast() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::APSRxBcast);
    if (result == nullptr) {
        result = new AttributeUInt16(262, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getAPSTxBcast() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::APSTxBcast);
    if (result == nullptr) {
        result = new AttributeUInt16(263, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getAPSRxUcast() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::APSRxUcast);
    if (result == nullptr) {
        result = new AttributeUInt16(264, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getAPSTxUcastSuccess() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::APSTxUcastSuccess);
    if (result == nullptr) {
        result = new AttributeUInt16(265, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getAPSTxUcastRetry() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::APSTxUcastRetry);
    if (result == nullptr) {
        result = new AttributeUInt16(266, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getAPSTxUcastFail() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::APSTxUcastFail);
    if (result == nullptr) {
        result = new AttributeUInt16(267, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getRouteDiscInitiated() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::RouteDiscInitiated);
    if (result == nullptr) {
        result = new AttributeUInt16(268, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getNeighborAdded() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::NeighborAdded);
    if (result == nullptr) {
        result = new AttributeUInt16(269, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getNeighborRemoved() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::NeighborRemoved);
    if (result == nullptr) {
        result = new AttributeUInt16(270, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getNeighborStale() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::NeighborStale);
    if (result == nullptr) {
        result = new AttributeUInt16(271, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getJoinIndication() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::JoinIndication);
    if (result == nullptr) {
        result = new AttributeUInt16(272, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getChildMoved() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::ChildMoved);
    if (result == nullptr) {
        result = new AttributeUInt16(273, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getNwkFcFailure() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::NwkFcFailure);
    if (result == nullptr) {
        result = new AttributeUInt16(274, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getApsFcFailure() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::ApsFcFailure);
    if (result == nullptr) {
        result = new AttributeUInt16(275, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getApsUnauthorizedKey() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::ApsUnauthorizedKey);
    if (result == nullptr) {
        result = new AttributeUInt16(276, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getNwkDecryptFailures() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::NwkDecryptFailures);
    if (result == nullptr) {
        result = new AttributeUInt16(277, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getApsDecryptFailures() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::ApsDecryptFailures);
    if (result == nullptr) {
        result = new AttributeUInt16(278, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getPacketBufferAllocateFailures() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::PacketBufferAllocateFailures);
    if (result == nullptr) {
        result = new AttributeUInt16(279, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getRelayedUcast() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::RelayedUcast);
    if (result == nullptr) {
        result = new AttributeUInt16(280, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getPhyToMacQueueLimitReached() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::PhyToMacQueueLimitReached);
    if (result == nullptr) {
        result = new AttributeUInt16(281, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getPacketValidateDropCount() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::PacketValidateDropCount);
    if (result == nullptr) {
        result = new AttributeUInt16(282, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt16* HaDiagnosticCluster::getAverageMacRetryPerApsMessageSent() {
    auto result = (AttributeUInt16*)getAttributeById((uint16_t)HaDiagnosticAttribute::AverageMacRetryPerApsMessageSent);
    if (result == nullptr) {
        result = new AttributeUInt16(283, DataType::UInt16);
        addAttribute(result);
    }
    return result;
}

AttributeUInt8* HaDiagnosticCluster::getLastMessageLqi() {
    auto result = (AttributeUInt8*)getAttributeById((uint16_t)HaDiagnosticAttribute::LastMessageLqi);
    if (result == nullptr) {
        result = new AttributeUInt8(284, DataType::UInt8);
        addAttribute(result);
    }
    return result;
}

AttributeInt8* HaDiagnosticCluster::getLastMessageRssi() {
    auto result = (AttributeInt8*)getAttributeById((uint16_t)HaDiagnosticAttribute::LastMessageRssi);
    if (result == nullptr) {
        result = new AttributeInt8(285, DataType::Int8);
        addAttribute(result);
    }
    return result;
}

void TouchlinkCluster::sendIdentifyRequestCommand(DeviceManager& deviceManager, uint8_t endpointId, uint32_t transactionID, uint16_t duration) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        6
    ).write(buffer);

    buffer.writeUInt32Le(transactionID);
    buffer.writeUInt16Le(duration);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void TouchlinkCluster::sendResetToFactoryNewCommand(DeviceManager& deviceManager, uint8_t endpointId, uint32_t transactionID) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        7
    ).write(buffer);

    buffer.writeUInt32Le(transactionID);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void TouchlinkCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto transactionID = request.readUInt32Le();
            auto zigbeeInformation = request.readUInt8();
            auto touchlinkInformation = request.readUInt8();
            ScanRequestCommandResponse response_;
            auto status_ = onScanRequestCommand(transactionID, zigbeeInformation, touchlinkInformation, response_);
            response.writeUInt8((uint8_t)status_);
            if (status_ == Status::Success) {
                response.writeUInt32Le(response_.getTransactionID());
                response.writeUInt8(response_.getRssiCorrection());
                response.writeUInt8(response_.getZigbeeInformation());
                response.writeUInt8(response_.getTouchlinkInformation());
                response.writeUInt16Le(response_.getKeyBitmask());
                response.writeUInt32Le(response_.getResponseID());
                response.writeUInt64Le(response_.getExtendedPanID());
                response.writeUInt8(response_.getNetworkUpdateID());
                response.writeUInt8(response_.getLogicalChannel());
                response.writeUInt16Le(response_.getPanID());
                response.writeUInt16Le(response_.getNetworkAddress());
                response.writeUInt8(response_.getNumberOfSubDevices());
                response.writeUInt8(response_.getTotalGroupIdentifiers());
            }
            return;
        }
        case 6: {
            auto transactionID = request.readUInt32Le();
            auto duration = request.readUInt16Le();
            auto status_ = onIdentifyRequestCommand(transactionID, duration);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 7: {
            auto transactionID = request.readUInt32Le();
            auto status_ = onResetToFactoryNewCommand(transactionID);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}

AttributeString* WiserDeviceInfoCluster::getDeviceInfo() {
    auto result = (AttributeString*)getAttributeById((uint16_t)WiserDeviceInfoAttribute::DeviceInfo);
    if (result == nullptr) {
        result = new AttributeString(32);
        addAttribute(result);
    }
    return result;
}

void ZosungIRTransmitCluster::sendZosungSendIRCode00Command(DeviceManager& deviceManager, uint8_t endpointId, uint16_t seq, uint32_t length, uint32_t unk1, uint16_t unk2, uint8_t unk3, uint8_t cmd, uint16_t unk4) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        0
    ).write(buffer);

    buffer.writeUInt16Le(seq);
    buffer.writeUInt32Le(length);
    buffer.writeUInt32Le(unk1);
    buffer.writeUInt16Le(unk2);
    buffer.writeUInt8(unk3);
    buffer.writeUInt8(cmd);
    buffer.writeUInt16Le(unk4);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ZosungIRTransmitCluster::sendZosungSendIRCode01Command(DeviceManager& deviceManager, uint8_t endpointId, uint8_t zero, uint16_t seq, uint32_t length, uint32_t unk1, uint16_t unk2, uint8_t unk3, uint8_t cmd, uint16_t unk4) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        1
    ).write(buffer);

    buffer.writeUInt8(zero);
    buffer.writeUInt16Le(seq);
    buffer.writeUInt32Le(length);
    buffer.writeUInt32Le(unk1);
    buffer.writeUInt16Le(unk2);
    buffer.writeUInt8(unk3);
    buffer.writeUInt8(cmd);
    buffer.writeUInt16Le(unk4);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ZosungIRTransmitCluster::sendZosungSendIRCode02Command(DeviceManager& deviceManager, uint8_t endpointId, uint16_t seq, uint32_t position, uint8_t maxlen) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        2
    ).write(buffer);

    buffer.writeUInt16Le(seq);
    buffer.writeUInt32Le(position);
    buffer.writeUInt8(maxlen);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ZosungIRTransmitCluster::sendZosungSendIRCode03Command(DeviceManager& deviceManager, uint8_t endpointId, uint8_t zero, uint16_t seq, uint32_t position, Buffer msgpart, uint8_t msgpartcrc) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        3
    ).write(buffer);

    buffer.writeUInt8(zero);
    buffer.writeUInt16Le(seq);
    buffer.writeUInt32Le(position);
    buffer.writeOctstr(msgpart);
    buffer.writeUInt8(msgpartcrc);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ZosungIRTransmitCluster::sendZosungSendIRCode04Command(DeviceManager& deviceManager, uint8_t endpointId, uint8_t zero0, uint16_t seq, uint16_t zero1) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        4
    ).write(buffer);

    buffer.writeUInt8(zero0);
    buffer.writeUInt16Le(seq);
    buffer.writeUInt16Le(zero1);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ZosungIRTransmitCluster::sendZosungSendIRCode05Command(DeviceManager& deviceManager, uint8_t endpointId, uint16_t seq, uint16_t zero) {
    auto buffer = deviceManager.getBuffer();

    Frame(
        FrameControl(FrameType::Cluster, Direction::ToServer, true),
        nextTransactionSequenceNumber++,
        5
    ).write(buffer);

    buffer.writeUInt16Le(seq);
    buffer.writeUInt16Le(zero);

    deviceManager.sendMessage(this, endpointId, buffer);
}

void ZosungIRTransmitCluster::processCommand(uint8_t commandId, Memory& request, Memory& response) {
    switch (commandId) {
        case 0: {
            auto seq = request.readUInt16Le();
            auto length = request.readUInt32Le();
            auto unk1 = request.readUInt32Le();
            auto unk2 = request.readUInt16Le();
            auto unk3 = request.readUInt8();
            auto cmd = request.readUInt8();
            auto unk4 = request.readUInt16Le();
            auto status_ = onZosungSendIRCode00Command(seq, length, unk1, unk2, unk3, cmd, unk4);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 1: {
            auto zero = request.readUInt8();
            auto seq = request.readUInt16Le();
            auto length = request.readUInt32Le();
            auto unk1 = request.readUInt32Le();
            auto unk2 = request.readUInt16Le();
            auto unk3 = request.readUInt8();
            auto cmd = request.readUInt8();
            auto unk4 = request.readUInt16Le();
            auto status_ = onZosungSendIRCode01Command(zero, seq, length, unk1, unk2, unk3, cmd, unk4);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 2: {
            auto seq = request.readUInt16Le();
            auto position = request.readUInt32Le();
            auto maxlen = request.readUInt8();
            auto status_ = onZosungSendIRCode02Command(seq, position, maxlen);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 3: {
            auto zero = request.readUInt8();
            auto seq = request.readUInt16Le();
            auto position = request.readUInt32Le();
            auto msgpart = request.readOctstr();
            auto msgpartcrc = request.readUInt8();
            auto status_ = onZosungSendIRCode03Command(zero, seq, position, msgpart, msgpartcrc);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 4: {
            auto zero0 = request.readUInt8();
            auto seq = request.readUInt16Le();
            auto zero1 = request.readUInt16Le();
            auto status_ = onZosungSendIRCode04Command(zero0, seq, zero1);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        case 5: {
            auto seq = request.readUInt16Le();
            auto zero = request.readUInt16Le();
            auto status_ = onZosungSendIRCode05Command(seq, zero);
            response.writeUInt8((uint8_t)status_);
            return;
        }
        default:
            Cluster::processCommand(commandId, request, response);
            return;
    }
}
