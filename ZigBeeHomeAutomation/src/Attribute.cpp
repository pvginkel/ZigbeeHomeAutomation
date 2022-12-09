#include "ZigBeeHomeAutomation.h"

Attribute::~Attribute() {
	delete _reporting;
}

void Attribute::configureReporting(const XBeeAddress64& destinationAddress, uint16_t destinationShortAddress, uint8_t destinationEndpoint, uint16_t minimumInterval, uint16_t maximumInterval, Memory& memory) {
	if (!_reporting) {
		_reporting = new Reporting();
	}
	_reporting->destinationAddress = destinationAddress;
	_reporting->destinationShortAddress = destinationShortAddress;
	_reporting->destinationEndpoint = destinationEndpoint;
	_reporting->minimumInterval = minimumInterval;
	_reporting->maximumInterval = maximumInterval;

	resetPendingDefaultResponse();

	configureReportableChange(memory);
}

void Attribute::resetPendingDefaultResponse() {
	_reporting->transactionSequenceNumber = 0;
	_reporting->defaultResponseTimeout = 0;
	_reporting->defaultResponseBackoff = 0;
}

AttributeReportStatus Attribute::report(XBee& device, Memory& buffer) {
	if (!_reporting) {
		return AttributeReportStatus::None;
	}

	// Anything to report?

	if (!_dirty) {
		return AttributeReportStatus::None;
	}

	// Reset backoff.

	report(device, buffer, false);

	return AttributeReportStatus::Reported;
}

AttributeReportStatus Attribute::resendReport(XBee& device, Memory& buffer) {
	if (!_reporting) {
		return AttributeReportStatus::None;
	}

	// No resend pending?

	if (_reporting->transactionSequenceNumber == 0) {
		return AttributeReportStatus::None;
	}

	// Too early still?

	if (millis() < _reporting->defaultResponseTimeout) {
		return AttributeReportStatus::Pending;
	}

	DEBUG(F("Resending status report because the default response wasn't received within "), _reporting->defaultResponseBackoff, "ms");

	report(device, buffer, true);

	return AttributeReportStatus::Reported;
}

void Attribute::report(XBee& device, Memory& buffer, bool resend) {
	DEBUG(
		F("Reporting attribute endpoint "), _cluster->getDevice()->getEndpointId(),
		F(" cluster "), _cluster->getClusterId(),
		F(" attribute "), getAttributeId(),
		F(" value "), toString(),
		F(" to "), String(_reporting->destinationAddress.getMsb(), HEX), String(_reporting->destinationAddress.getLsb(), HEX),
		F(" short "), String(_reporting->destinationShortAddress, HEX),
		F(" endpoint "), _reporting->destinationEndpoint);

	buffer.setPosition(0);

	uint8_t transactionSequenceNumber = device.getNextFrameId();

	Frame(
		FrameControl(FrameType::Global, Direction::ToClient, false),
		transactionSequenceNumber,
		(uint8_t)CommandIdentifier::ReportAttributes
	).write(buffer);

	ReportAttributesFrame::writeAttribute(buffer, getAttributeId(), getDataType());
	writeValue(buffer);

	_dirty = false;

	ZBExplicitTxRequest message(
		_reporting->destinationAddress,
		_reporting->destinationShortAddress,
		0, // broadcastRadius
		0, // option
		buffer.getData(),
		buffer.getPosition(),
		transactionSequenceNumber,
		_cluster->getDevice()->getEndpointId(),
		_reporting->destinationEndpoint,
		_cluster->getClusterId(),
		DeviceManager::ZHA_PROFILE_ID
	);
	device.send(message);

	_reporting->transactionSequenceNumber = transactionSequenceNumber;
	// Exponential backoff on resend.
	if (resend) {
		_reporting->defaultResponseBackoff = _reporting->defaultResponseBackoff * 2;
	}
	else {
		_reporting->defaultResponseBackoff = RESEND_DELAY_MS;
	}
	_reporting->defaultResponseTimeout = millis() + _reporting->defaultResponseBackoff;
}

bool Attribute::processDefaultResponse(uint8_t transactionSequenceNumber, uint8_t commandId, Status status) {
	if (transactionSequenceNumber == _reporting->transactionSequenceNumber) {
		DEBUG(
			F("Received default response for attribute "), getAttributeId(),
			F(" status "), (int)status,
			F(" marking as received"));

		resetPendingDefaultResponse();
		return true;
	}

	return false;
}
