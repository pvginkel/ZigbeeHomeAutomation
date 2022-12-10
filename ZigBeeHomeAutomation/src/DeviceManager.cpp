#include <Printers.h>
#include "ZigBeeHomeAutomation.h"

#define IS_COMMAND(c, n) ((c).getCommand()[0] == (n)[0] && (c).getCommand()[1] == (n)[1])

static AtCommandRequest buildResetCommand(uint8_t index);
static AtCommandRequest buildRetrieveConfigurationCommand(uint8_t index);
static AtCommandRequest buildReadDiagnosticsCommand(uint8_t index);
static AtCommandRequest associationIndicationCommand();
static AtCommandRequest serialNumberHighCommand();
static AtCommandRequest serialNumberLowCommand();
static AtCommandRequest networkAddressCommand();
static AtCommandRequest operatingPanIdCommand();

DeviceManager::DeviceManager() :
	_shortAddress(0), _payload{}, _commandBuilder(nullptr), _commandBuilderOffset(0),
	_state(State::Connected), _lastSendMillis(0), _associationIndication(0xff), _associationIndicationMillis(0) {
	//    onResponse(printResponseCb, (uintptr_t) (Print * ) & Serial);
	_device.onZBExplicitRxResponse(
		[](ZBExplicitRxResponse& status, uintptr_t data) { ((DeviceManager*)data)->explicitRxCallback(status); },
		(uintptr_t)this
	);
	_device.onModemStatusResponse(
		[](ModemStatusResponse& status, uintptr_t data) { ((DeviceManager*)data)->modemStatusCallback(status); },
		(uintptr_t)this
	);
	_device.onAtCommandResponse(
		[](AtCommandResponse& command, uintptr_t data) { ((DeviceManager*)data)->atCommandCallback(command); },
		(uintptr_t)this
	);
#if LOG_WARN
	_device.onPacketError(printErrorCb, (uintptr_t)(Print*)&Serial);
	_device.onTxStatusResponse(printErrorCb, (uintptr_t)(Print*)&Serial);
	_device.onZBTxStatusResponse(printErrorCb, (uintptr_t)(Print*)&Serial);
#endif
}

/* Send the device announce command */
void DeviceManager::sendAnnounce() {
	DEBUG(F("Sending announce"));

	auto address = getAddress();

	auto frameId = _device.getNextFrameId();

	uint8_t capability = 0b00001000; /* For now, just receiver on during idle times */
	uint8_t announceCluster = 0x13;

	Memory memory(_payload, 0);
	memory.writeUInt8(frameId);
	memory.writeUInt16Le(_shortAddress);
	memory.writeUInt32Le(address.getLsb());
	memory.writeUInt32Le(address.getMsb());
	memory.writeUInt8(capability);

	auto broadcastAddress = BROADCAST_ADDR64;

	ZBExplicitTxRequest announce(
		broadcastAddress,
		ANNOUNCE_BROADCAST_ADDR16,
		0,
		0,
		memory.getData(),
		memory.getPosition(),
		frameId,
		0,
		0,
		announceCluster,
		0
	);
	_device.send(announce);
}

XBeeAddress64 DeviceManager::getAddress() {
	DEBUG(F("Getting device address"));

	XBeeAddress64 address;

	auto command = serialNumberHighCommand();
	if (_device.sendAndWait(command, 5000) != XBEE_WAIT_TIMEOUT) {
		AtCommandResponse response;
		_device.getResponse(response);

		Memory memory(response.getValue(), response.getValueLength());
		address.setMsb(memory.readUInt32Be());
	}

	command = serialNumberLowCommand();
	if (_device.sendAndWait(command, 5000) != XBEE_WAIT_TIMEOUT) {
		AtCommandResponse response;
		_device.getResponse(response);

		Memory memory(response.getValue(), response.getValueLength());
		address.setLsb(memory.readUInt32Be());
	}

	return address;
}

Device* DeviceManager::getDeviceByEndpoint(uint8_t endpointId) {
	for (auto device : _deviceList) {
		if (device->getEndpointId() == endpointId) {
			return device;
		}
	}
	return nullptr;
}

void DeviceManager::processZDO(XBeeAddress64 dst64, uint16_t dst16, uint16_t clusterId, uint8_t* frameData, uint8_t frameDataLength) {
#if LOG_DEBUG
	DEBUG(F("ZDO:"));
	DEBUG(F("  Dst64 "), String(dst64.getMsb(), HEX), F(" "), String(dst64.getLsb(), HEX));
	DEBUG(F("  Dst16 "), dst16);
	DEBUG(F("  ClusterId "), clusterId);
	DEBUG(F("  FrameDataLength "), frameDataLength);
#endif

	if (clusterId == (uint16_t)ZdoCommand::SimpleDescriptorRequest) {
		DEBUG(F("ZDO Simple Descriptor Request"));

		Device* dev = getDeviceByEndpoint(frameData[3]);
		if (dev) {
			uint8_t numInClusters = 0;
			uint8_t numOutClusters = 0;

			for (int i = 0; i < dev->getClusterCount(); i++) {
				if (dev->getClusterByIndex(i)->getType() == ClusterType::Input) {
					numInClusters++;
				}
				else {
					numOutClusters++;
				}
			}

			Memory memory(_payload);
			memory.writeUInt8(frameData[0]);
			memory.writeUInt8((uint8_t)Status::Success);
			memory.writeUInt16Le(_shortAddress);
			auto lengthPosition = memory.getPosition();
			memory.writeUInt8(0);
			memory.writeUInt8(dev->getEndpointId());
			memory.writeUInt16Le((uint16_t)0x0104);
			memory.writeUInt16Le(dev->getDeviceId());
			memory.writeUInt8(0x40);
			memory.writeUInt8(numInClusters);

			for (int i = 0; i < dev->getClusterCount(); i++) {
				auto cluster = dev->getClusterByIndex(i);
				if (cluster->getType() == ClusterType::Input) {
					memory.writeUInt16Le(cluster->getClusterId());
				}
			}

			memory.writeUInt8(numOutClusters);

			for (int i = 0; i < dev->getClusterCount(); i++) {
				auto cluster = dev->getClusterByIndex(i);
				if (cluster->getType() == ClusterType::Output) {
					memory.writeUInt16Le(cluster->getClusterId());
				}
			}

			auto length = memory.getPosition();
			memory.setPosition(lengthPosition);
			memory.writeUInt8(length - 5);

			ZBExplicitTxRequest message(
				dst64,
				dst16,
				0,
				0,
				memory.getData(),
				length,
				_device.getNextFrameId(),
				0,
				0,
				(uint16_t)ZdoCommand::SimpleDescriptorResponse,
				0
			);
			_device.send(message);
		}
	}
	else if (clusterId == (uint16_t)ZdoCommand::ActiveEndpointsRequest) {
		DEBUG(F("ZDO Active Endpoints Request"));

		Memory memory(_payload);

		memory.writeUInt8(frameData[0]);
		memory.writeUInt8((uint8_t)Status::Success);
		memory.writeUInt16Le(_shortAddress);
		memory.writeUInt8(_deviceList.size());
		for (auto i = 0; i < _deviceList.size(); i++) {
			memory.writeUInt8(_deviceList[i]->getEndpointId());
		}

		ZBExplicitTxRequest message(
			dst64,
			dst16,
			0,
			0,
			memory.getData(),
			memory.getPosition(),
			_device.getNextFrameId(),
			0,
			0,
			(uint16_t)ZdoCommand::ActiveEndpointsResponse,
			0
		);
		_device.send(message);
	}
	else if (clusterId == (uint16_t)ZdoCommand::MatchDescriptorRequest) {
		DEBUG(F("ZDO Match Descriptor Request"));

		uint16_t profile_id = ((uint16_t)frameData[4] << 8) | frameData[3];
		uint8_t numInClusters = frameData[5];
		for (uint8_t i = 1; i <= numInClusters; i++) {
			uint16_t cluster = ((uint16_t)frameData[5 + 2 * i] << 8) | frameData[4 + (2 * i)];
			Serial.println(cluster, HEX);
		}
		uint8_t numOutClusters = frameData[6 + 2 * numInClusters];
		for (uint8_t i = 1; i <= numOutClusters; i++) {
			uint16_t cluster =
				((uint16_t)frameData[7 + 2 * (i + numInClusters)] << 8) | frameData[6 + 2 * (i + numInClusters)];
			Serial.println(cluster, HEX);
		}

		Memory memory(_payload);

		memory.writeUInt8(frameData[0]);
		memory.writeUInt8((uint8_t)Status::Success);
		memory.writeUInt16Le(_shortAddress);
		memory.writeUInt8(0);

		ZBExplicitTxRequest message(
			dst64,
			dst16,
			0,
			0,
			memory.getData(),
			memory.getPosition(),
			_device.getNextFrameId(),
			0,
			0,
			(uint16_t)ZdoCommand::MatchDescriptorResponse,
			0
		);
		_device.send(message);
	}
}

void DeviceManager::atCommandCallback(AtCommandResponse& command) {
#if LOG_DEBUG
	printResponseCb(command, (uintptr_t)(Print*)&Serial);
#endif

	Memory memory(command.getValue(), command.getValueLength());

	if (IS_COMMAND(command, "MY")) {
		_shortAddress = memory.readUInt16Be();
	}
	else if (IS_COMMAND(command, "OP")) {
		_operatingPanId.setMsb(memory.readUInt32Be());
		_operatingPanId.setLsb(memory.readUInt32Be());

		DEBUG(F("Operating pan ID is 0x"), String(_operatingPanId.getMsb(), HEX), String(_operatingPanId.getLsb(), HEX));
	}
	else if (IS_COMMAND(command, "AI")) {
		_associationIndication = memory.readUInt8();
		DEBUG(F("Association indication is now: "), getAssociationIndicationDescription(_associationIndication));

		setConnected(_associationIndication == 0 ? ConnectionStatus::Connected : ConnectionStatus::Connecting);

		if (_associationIndication) {
			setStatus(getShortAssociationIndicationDescription(_associationIndication));
		}
		else {
			setStatus(F(""));
		}

		if (_state == State::RetrievingAssociationIndication && _associationIndication == 0) {
			retrieveConfiguration();
			return;
		}
	}

	if (sendNextCommand()) {
		return;
	}

	if (_state == State::Resetting) {
		retrieveAssociationIndication();
	}
	else if (_state == State::RetrievingConfiguration) {
		if (_associationIndication) {
			retrieveAssociationIndication();
		}
		else {
			_state = State::Connected;

			sendAnnounce();
		}
	}
}

void DeviceManager::modemStatusCallback(ModemStatusResponse& status) {
	switch (status.getStatus()) {
		case HARDWARE_RESET:
			DEBUG(F("Modem reset."));
			break;
		case ASSOCIATED:
			DEBUG(F("Joined network."));
			if (_state == State::Connected) {
				setCommandBuilder(buildReadDiagnosticsCommand);
				sendAnnounce();
			}
			break;
		case DISASSOCIATED:
			setStatus(F("Disassociated"));
			break;
		default:
#if LOG_DEBUG
			printResponseCb(status, (uintptr_t)(Print*)&Serial);
#endif
			break;
	}
}

void DeviceManager::explicitRxCallback(ZBExplicitRxResponse& resp) {
#if LOG_DEBUG
	printResponseCb(resp, (uintptr_t)(Print*)&Serial);
#endif

	uint16_t profileId = resp.getProfileId();
	uint16_t clusterId = resp.getClusterId();
	uint8_t srcEndpoint = resp.getSrcEndpoint();
	uint8_t dstEndpoint = resp.getDstEndpoint();
	uint8_t* frameData = resp.getFrameData() + resp.getDataOffset();
	int frameDataLength = resp.getFrameDataLength() - resp.getDataOffset();

	//DEBUG(F("profileId "), profileId, F(" srcEndpoint "), srcEndpoint, F(" dstEndpoint "), dstEndpoint, F(" clusterId "), clusterId, F(" remote addr "), resp.getRemoteAddress16());

	if (profileId == 0x0000 && srcEndpoint == 0x00 && dstEndpoint == 0x00) {
		/* ZDO command */
		processZDO(resp.getRemoteAddress64(), resp.getRemoteAddress16(), clusterId, frameData,
			frameDataLength);
	}
	else if (profileId == ZHA_PROFILE_ID) {
		auto frameBuffer = Memory(frameData, frameDataLength);
		auto request = Frame::read(frameBuffer);

		Device* device = getDeviceByEndpoint(dstEndpoint);
		if (device) {
			/* Frame layout
		  ---------------------------------------------------------------------
		  |    Bits: 8     |   0/16   |    8     |    8       |   Variable    |
		  |-------------------------------------------------------------------|
		  | Frame Control  | MFR code | Frame ID | Command ID | Frame Payload |
		  Frame Control Field
		  ---------------------------------------------------------------------
		  --------------------------------------------------------------------------------
		  }  Bits: 3  |            1             |     1     |       1      |      2     |
		  |------------------------------------------------------------------------------|
		  | Reserverd | Disable Default Response | Direction | MFR specific | Frame Type |
		  --------------------------------------------------------------------------------
		*/

			if (request.frameControl().frameType() == FrameType::Global) {
		        DEBUG(F("General command"));

				Memory buffer(_payload);

				if (request.commandIdentifier() == (int)CommandIdentifier::DefaultResponse) {
					WARN(F("Received a default response without a recipient"));
					return;
				}

				auto status = device->processGeneralCommand(*this, request, frameBuffer, resp, buffer);
				if (status != Status::Success) {
					buffer.setPosition(0);

					Frame(
						FrameControl(FrameType::Global, Direction::ToClient, true),
						request.transactionSequenceNumber(),
						(uint8_t)CommandIdentifier::DefaultResponse
					).write(buffer);

					DefaultResponseFrame(
						request.commandIdentifier(),
						status
					).write(buffer);
				}

				ZBExplicitTxRequest message(
					resp.getRemoteAddress64(),
					resp.getRemoteAddress16(),
					0, // broadcastRadius
					0, // option
					buffer.getData(),
					buffer.getPosition(),
					_device.getNextFrameId(),
					dstEndpoint,
					srcEndpoint,
					clusterId,
					profileId
				);

				_device.send(message);
			}
			if (request.frameControl().frameType() == FrameType::Cluster) {
				auto cluster = device->getClusterById(clusterId);
				auto commandId = request.commandIdentifier();

				DEBUG(F("Cluster "), clusterId, F(" specific command ID "), commandId);

				if (request.frameControl().disableDefaultResponse()) {
					WARN(F("Sending default response even though disable default response is set"));
				}

				Memory buffer(_payload);

				Frame(
					FrameControl(FrameType::Global, Direction::ToClient),
					request.transactionSequenceNumber(),
					(uint8_t)CommandIdentifier::DefaultResponse
				).write(buffer);

				buffer.writeUInt8(commandId);

				cluster->processCommand(commandId, frameBuffer, buffer);

				ZBExplicitTxRequest message(
					resp.getRemoteAddress64(),
					resp.getRemoteAddress16(),
					0, // broadcastRadius
					0, // option
					buffer.getData(),
					buffer.getPosition(),
					_device.getNextFrameId(),
					dstEndpoint,
					srcEndpoint,
					clusterId,
					profileId
				);

				_device.send(message);
			}
		}
		else {
			Memory buffer(_payload);

			Frame(
				FrameControl(FrameType::Global, Direction::ToClient, true),
				request.transactionSequenceNumber(),
				(uint8_t)CommandIdentifier::DefaultResponse
			).write(buffer);

			DefaultResponseFrame(
				request.commandIdentifier(),
				Status::NotFound
			).write(buffer);

			ZBExplicitTxRequest message(
				resp.getRemoteAddress64(),
				resp.getRemoteAddress16(),
				0, // broadcastRadius
				0, // option
				buffer.getData(),
				buffer.getPosition(),
				_device.getNextFrameId(),
				dstEndpoint,
				srcEndpoint,
				clusterId,
				profileId
			);

			_device.send(message);
		}
	}
}

void DeviceManager::reportAttributes() {
	if (_associationIndication != 0) {
		return;
	}

	for (auto device : _deviceList) {
		for (int i = 0; i < device->getClusterCount(); i++) {
			auto cluster = device->getClusterByIndex(i);
			for (int j = 0; j < cluster->getAttributeCount(); j++) {
				reportAttribute(device, cluster, cluster->getAttributeByIndex(j));
			}
		}
	}
}

void DeviceManager::reportAttribute(Device* device, Cluster* cluster, Attribute* attribute) {
	auto reportingEndpointId = attribute->getReportingEndpointId();

	if (!reportingEndpointId) {
		return;
	}

	// Anything to report?

	if (!attribute->isDirty()) {
		return;
	}

	DEBUG(
		F("Reporting attribute endpoint "), device->getEndpointId(),
		F(" cluster "), cluster->getClusterId(),
		F(" attribute "), attribute->getAttributeId(),
		F(" value "), attribute->toString(),
		F(" to "), (reportingEndpointId == Attribute::REPORT_BROADCAST ? F("broadcast") : F("coordinator")),
		F(" endpoint "), (reportingEndpointId == Attribute::REPORT_BROADCAST ? 1 : reportingEndpointId));

	Memory buffer(_payload);

	Frame(
		FrameControl(FrameType::Global, Direction::ToClient, true),
		0,
		(uint8_t)CommandIdentifier::ReportAttributes
	).write(buffer);

	ReportAttributesFrame::writeAttribute(buffer, attribute->getAttributeId(), attribute->getDataType());
	attribute->writeValue(buffer);

	attribute->markClean();

	XBeeAddress64 destinationAddress;
	uint16_t destinationShortAddress;
	uint8_t destinationEndpoint;

	if (reportingEndpointId == Attribute::REPORT_BROADCAST) {
		destinationAddress = BROADCAST_ADDR64;
		destinationShortAddress = 0;
		destinationEndpoint = 1;
	}
	else {
		destinationAddress = _operatingPanId;
		destinationShortAddress = 0;
		destinationEndpoint = reportingEndpointId;
	}

	ZBExplicitTxRequest message(
		destinationAddress,
		destinationShortAddress,
		0, // broadcastRadius
		0, // option
		buffer.getData(),
		buffer.getPosition(),
		_device.getNextFrameId(),
		device->getEndpointId(),
		destinationEndpoint,
		cluster->getClusterId(),
		DeviceManager::ZHA_PROFILE_ID
	);
	_device.send(message);
}

void DeviceManager::addDevice(Device& device) {
	_deviceList.add(&device);
}

void DeviceManager::begin(Stream& stream) {
	_device.begin(stream);

	retrieveConfiguration();
}

void DeviceManager::performReset() {
	_state = State::Resetting;

	setCommandBuilder(buildResetCommand);
}

void DeviceManager::setCommandBuilder(command_builder_t commandBuilder) {
	_commandBuilder = commandBuilder;
	_commandBuilderOffset = 0;

	sendCurrentCommand();
}

void DeviceManager::update() {
	_device.loop();

	reportAttributes();

	esp8266_yield();

	// Retry any pending at command.

	if (_commandBuilder) {
		if (millis() - _lastSendMillis > AT_COMMAND_RETRY_MS) {
			DEBUG(F("Retrying..."));
			sendCurrentCommand();
		}
	}

	// Refresh association indication.

	if (_state == State::RetrievingAssociationIndication) {
		const time_t currentMillis = millis();
		if (!_associationIndicationMillis || currentMillis - _associationIndicationMillis > ASSOCIATION_INDICATION_REFRESH_MS) {
			_associationIndicationMillis = currentMillis;

			auto command = associationIndicationCommand();
			_device.send(command);
		}
	}
}

bool DeviceManager::sendNextCommand() {
	if (!_commandBuilder) {
		return false;
	}

	auto command = _commandBuilder(++_commandBuilderOffset);
	if (!command.getCommand()) {
		_commandBuilder = nullptr;
		_commandBuilderOffset = 0;
		return false;
	}

	sendCurrentCommand();

	return true;
}

void DeviceManager::sendCurrentCommand() {
	auto command = _commandBuilder(_commandBuilderOffset);

	DEBUG(F("Sending command "), (char)command.getCommand()[0], (char)command.getCommand()[1]);

	_lastSendMillis = millis();
	_device.send(command);
}

void DeviceManager::retrieveAssociationIndication() {
	_state = State::RetrievingAssociationIndication;
	_associationIndicationMillis = millis();

	DEBUG(F("Requesting association indication"));

	auto command = associationIndicationCommand();
	_device.send(command);
}

void DeviceManager::retrieveConfiguration() {
	DEBUG(F("Retrieving configuration"));

	_state = State::RetrievingConfiguration;

	setStatus(F("Connecting..."));

	setCommandBuilder(buildRetrieveConfigurationCommand);
}

const __FlashStringHelper* DeviceManager::getAssociationIndicationDescription(uint8_t associationIndication) {
	switch (associationIndication) {
	case 0x00: return F("Successfully formed or joined a network. (Coordinators form a network, routers and end devices join a network.)");
	case 0x21: return F("Scan found no PANs");
	case 0x22: return F("Scan found no valid PANs based on current SC and ID settings");
	case 0x23: return F("Valid Coordinator or Routers found, but they are not allowing joining (NJ expired)");
	case 0x24: return F("No joinable beacons were found");
	case 0x25: return F("Unexpected state, node should not be attempting to join at this time");
	case 0x27: return F("Node Joining attempt failed (typically due to incompatible security settings)");
	case 0x2A: return F("Coordinator Start attempt failed");
	case 0x2B: return F("Checking for an existing coordinator");
	case 0x2C: return F("Attempt to leave the network failed");
	case 0xAB: return F("Attempted to join a device that did not respond.");
	case 0xAC: return F("Secure join error - network security key received unsecured");
	case 0xAD: return F("Secure join error - network security key not received");
	case 0xAF: return F("Secure join error - joining device does not have the right preconfigured link key");
	case 0xFF: return F("Scanning for a ZigBee network (routers and end devices)");
	default: return F("Unknown");
	}
}

const __FlashStringHelper* DeviceManager::getShortAssociationIndicationDescription(uint8_t associationIndication) {
	switch (associationIndication) {
	case 0x21: return F("No PANs found");
	case 0x22: return F("No valid PANs found");
	case 0x23: return F("Join time expired");
	case 0x24: return F("No beacons found");
	case 0x25: return F("Unexpected state");
	case 0x27: return F("Join attempt failed");
	case 0x2A: return F("Coordinator start failed");
	case 0x2B: return F("Finding coordinator");
	case 0x2C: return F("Leave network failed");
	case 0xAB: return F("Device not responding");
	case 0xAC:
	case 0xAD:
	case 0xAF:
		return F("Secure join error");
	case 0xFF: return F("Scanning");
	default: return F("Unknown status");
	}
}

#define AT_BUILDER(n, c, ...) \
	static AtCommandRequest n() { \
		static uint8_t value[] = { __VA_ARGS__ }; \
		return AtCommandRequest((uint8_t*)(c), (uint8_t*)value, ARRAY_LENGTH(value)); \
	}

#define AT_BUILDER_STR(n, c, v) \
	static AtCommandRequest n() { \
		return AtCommandRequest((uint8_t*)(c), (uint8_t*)(v), strlen(v)); \
	}

AT_BUILDER(restoreDefaultsCommand, "RE");
AT_BUILDER(apiOptionsCommand, "AO", 3);
AT_BUILDER(networkResetCommand, "NR", 0);
AT_BUILDER_STR(nodeIdentifierCommand, "NI", "TEST LAMP");
AT_BUILDER(zigbeeStackProfileCommand, "ZS", 2);
AT_BUILDER(nodeJoinTimeCommand, "NJ", 0x5A);
AT_BUILDER(encryptionEnableCommand, "EE", 1);
AT_BUILDER(encryptionOptionsCommand, "EO", 1);
AT_BUILDER(linkKeyCommand, "KY", 0x5A, 0x69, 0x67, 0x42, 0x65, 0x65, 0x41, 0x6C, 0x6C, 0x69, 0x61, 0x6E, 0x63, 0x65, 0x30, 0x39);
AT_BUILDER(dio6RtsCommand, "D6", 0);
AT_BUILDER(scanChannelsCommand, "SC", 0xff, 0xff);
AT_BUILDER(writeCommand, "WR");
AT_BUILDER(softwareResetCommand, "FR");
AT_BUILDER(serialNumberHighCommand, "SH");
AT_BUILDER(serialNumberLowCommand, "SL");
AT_BUILDER(networkAddressCommand, "MY");
AT_BUILDER(apiModeCommand, "AP", 2);
AT_BUILDER(sleepModeCommand, "SM", 0);
AT_BUILDER(operatingChannelCommand, "CH");
AT_BUILDER(operatingPanIdCommand, "OP");
AT_BUILDER(operatingPanIdShortCommand, "OI");
AT_BUILDER(associationIndicationCommand, "AI");
AT_BUILDER(parentNetworkAddressCommand, "MP");

AtCommandRequest buildResetCommand(uint8_t index) {
	switch (index) {
	case 0: return restoreDefaultsCommand();
	case 1: return apiOptionsCommand();
	case 2: return networkResetCommand();
	case 3: return nodeIdentifierCommand();
	case 4: return zigbeeStackProfileCommand();
	case 5: return nodeJoinTimeCommand();
	case 6: return encryptionEnableCommand();
	case 7: return encryptionOptionsCommand();
	case 8: return linkKeyCommand();
	case 9: return dio6RtsCommand();
	case 10: return scanChannelsCommand();
	case 11: return apiModeCommand();
	case 12: return sleepModeCommand();
	case 13: return writeCommand();
	case 14: return softwareResetCommand();
	default: return {};
	}
}

AtCommandRequest buildRetrieveConfigurationCommand(uint8_t index) {
	switch (index) {
	case 0: return networkAddressCommand();
	case 1: return operatingPanIdCommand();
	case 2: return associationIndicationCommand();
	default: return {};
	}
}

AtCommandRequest buildReadDiagnosticsCommand(uint8_t index) {
	switch (index) {
	case 0: return associationIndicationCommand();
	case 1: return operatingChannelCommand();
	case 2: return operatingPanIdShortCommand();
	case 3: return parentNetworkAddressCommand();
	default: return {};
	}
}
