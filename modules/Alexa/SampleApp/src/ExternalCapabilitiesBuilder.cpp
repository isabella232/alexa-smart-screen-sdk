/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "SampleApp/ExternalCapabilitiesBuilder.h"

#include <AVSCommon/Utils/Logger/Logger.h>

#ifdef ENABLE_COMMS
#include <AVSCommon/SDKInterfaces/CallManagerInterface.h>
#include <CallManager/CallManager.h>
#include <CallManager/SipUserAgent.h>
#endif

#ifdef ENABLE_COMMS_AUDIO_PROXY
#include <CallManager/CallAudioDeviceProxy.h>
#endif

#ifdef ENABLE_MRM
#include <acsdkMultiRoomMusic/MRMCapabilityAgent.h>
#ifdef ENABLE_MRM_STANDALONE_APP
#include <MRMHandler/MRMHandlerProxy.h>
#else
#include <MRMHandler/MRMHandler.h>
#endif  // ENABLE_MRM_STANDALONE_APP
#endif  // ENABLE_MRM

#ifdef ENABLE_COMMS
#define COMMS_NAMESPACE "com.amazon.avs-comms-adapter"
#endif

#ifdef ENABLE_RTCSC
#include <RTCSessionController/RtcscCapabilityAgent.h>
#include <RTCSessionController/Interfaces/RtcscCapabilityAgentInterface.h>
#endif

namespace alexaSmartScreenSDK {
namespace sampleApp {

/// String to identify log entries originating from this file.
static const std::string TAG("ExternalCapabilitiesBuilder");

/**
 * Create a LogEntry using this file's TAG and the specified event string.
 *
 * @param The event string for this @c LogEntry.
 */
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

ExternalCapabilitiesBuilder::ExternalCapabilitiesBuilder(
    std::shared_ptr<alexaClientSDK::avsCommon::utils::DeviceInfo> deviceInfo) :
        m_deviceInfo{deviceInfo} {
    ACSDK_DEBUG5(LX(__func__));
}

ExternalCapabilitiesBuilder& ExternalCapabilitiesBuilder::withVisualFocusManager(
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerInterface> focusManager) {
    ACSDK_DEBUG5(LX(__func__));
    m_visualFocusManager = std::move(focusManager);
    return *this;
}

ExternalCapabilitiesBuilder& ExternalCapabilitiesBuilder::withSettingsStorage(
    std::shared_ptr<alexaClientSDK::settings::storage ::DeviceSettingStorageInterface> settingStorage) {
    // ExternalCapabilitiesBuilder doesn't need the settingStorage to build any object.
    return *this;
}

ExternalCapabilitiesBuilder& ExternalCapabilitiesBuilder::withTemplateRunTime(
    std::shared_ptr<smartScreenCapabilityAgents::templateRuntime::TemplateRuntime> templateRuntime) {
    ACSDK_DEBUG5(LX(__func__));
    m_templateRuntime = std::move(templateRuntime);
    return *this;
}

std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::CallManagerInterface> ExternalCapabilitiesBuilder::
    getCallManager() {
    return m_callManager;
}

ExternalCapabilitiesBuilder& ExternalCapabilitiesBuilder::withInternetConnectionMonitor(
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::InternetConnectionMonitorInterface>
        internetConnectionMonitor) {
    // ExternalCapabilitiesBuilder doesn't need the internetConnectionMonitor to build any object.
    return *this;
}

ExternalCapabilitiesBuilder& ExternalCapabilitiesBuilder::withDialogUXStateAggregator(
    std::shared_ptr<alexaClientSDK::avsCommon::avs::DialogUXStateAggregator> dialogUXStateAggregator) {
    m_dialogUXStateAggregator = std::move(dialogUXStateAggregator);
    return *this;
}

std::pair<
    std::list<ExternalCapabilitiesBuilder::Capability>,
    std::list<std::shared_ptr<alexaClientSDK::avsCommon::utils::RequiresShutdown>>>
ExternalCapabilitiesBuilder::buildCapabilities(
    std::shared_ptr<alexaClientSDK::acsdkExternalMediaPlayer::ExternalMediaPlayer> externalMediaPlayer,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AVSConnectionManagerInterface> connectionManager,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::MessageSenderInterface> messageSender,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExceptionEncounteredSenderInterface> exceptionSender,
    std::shared_ptr<alexaClientSDK::certifiedSender::CertifiedSender> certifiedSender,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerInterface> audioFocusManager,
    std::shared_ptr<alexaClientSDK::registrationManager::CustomerDataManagerInterface> dataManager,
    std::shared_ptr<alexaClientSDK::capabilityAgents::system::ReportStateHandler> stateReportHandler,
    std::shared_ptr<alexaClientSDK::capabilityAgents::aip::AudioInputProcessor> audioInputProcessor,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerManagerInterface> speakerManager,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DirectiveSequencerInterface> directiveSequencer,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::UserInactivityMonitorInterface> userInactivityMonitor,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ContextManagerInterface> contextManager,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AVSGatewayManagerInterface> avsGatewayManager,
    std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> ringtoneMediaPlayer,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::audio::AudioFactoryInterface> audioFactory,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeInterface> ringtoneChannelVolumeInterface,
#ifdef ENABLE_COMMS_AUDIO_PROXY
    std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> commsMediaPlayer,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> commsSpeaker,
    std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream,
#endif
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::PowerResourceManagerInterface> powerResourceManager,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ComponentReporterInterface> softwareComponentReporter,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::PlaybackRouterInterface> playbackRouter,
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::endpoints::EndpointRegistrationManagerInterface>
        endpointRegistrationManager) {
    ACSDK_DEBUG5(LX(__func__));
    std::pair<
        std::list<ExternalCapabilitiesBuilder::Capability>,
        std::list<std::shared_ptr<alexaClientSDK::avsCommon::utils::RequiresShutdown>>>
        retValue;
    std::list<Capability> capabilities;
    std::list<std::shared_ptr<alexaClientSDK::avsCommon::utils::RequiresShutdown>> requireShutdownObjects;

#ifdef ENABLE_COMMS
    if (!ringtoneMediaPlayer) {
        ACSDK_ERROR(LX("initializeFailed").d("reason", "nullRingtoneMediaPlayer"));
        return retValue;
    }

    auto sipUserAgent = std::make_shared<alexaClientSDK::capabilityAgents::callManager::SipUserAgent>();
    std::string avsGatewayURL = avsGatewayManager->getGatewayURL();

    if (!alexaClientSDK::capabilityAgents::callManager::CallManager::create(
            sipUserAgent,
            ringtoneMediaPlayer,
            messageSender,
            contextManager,
            audioFocusManager,
            m_visualFocusManager,
            exceptionSender,
            audioFactory->communications(),
            avsGatewayURL,
            speakerManager,
            ringtoneChannelVolumeInterface)) {
        ACSDK_ERROR(LX("initializeFailed").d("reason", "unableToCreateCallManager"));
        return retValue;
    }

    auto callManager = alexaClientSDK::capabilityAgents::callManager::CallManager::getInstance();

    m_callManager = callManager;

    const std::string commsVersion =
        alexaClientSDK::capabilityAgents::callManager::CallManager::getCommsAdapterVersion();
    std::shared_ptr<alexaClientSDK::avsCommon::avs::ComponentConfiguration> commsConfig =
        alexaClientSDK::avsCommon::avs::ComponentConfiguration::createComponentConfiguration(
            COMMS_NAMESPACE, commsVersion);
    softwareComponentReporter->addConfiguration(commsConfig);
    m_dialogUXStateAggregator->addObserver(callManager);
    connectionManager->addConnectionStatusObserver(callManager);
    avsGatewayManager->addObserver(m_callManager);

    Capability callManagerCapability;
    auto callManagerConfigurations = callManager->getCapabilityConfigurations();
    callManagerCapability.directiveHandler = std::move(callManager);
    for (auto& configurationPtr : callManagerConfigurations) {
        callManagerCapability.configuration = *configurationPtr;
        capabilities.push_back(callManagerCapability);
    }
    requireShutdownObjects.push_back(m_callManager);

#ifdef ENABLE_COMMS_AUDIO_PROXY
    auto acquireAudioInputStream =
        [sharedDataStream]() -> std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> {
        return sharedDataStream;
    };
    auto relinquishAudioInputStream = [](std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> stream) {
        // Nothing to release
    };
    auto callAudioDeviceProxy = alexaClientSDK::capabilityAgents::callManager::CallAudioDeviceProxy::create(
        commsMediaPlayer, commsSpeaker, acquireAudioInputStream, relinquishAudioInputStream);
    m_callManager->addObserver(callAudioDeviceProxy);
#endif
#endif

#ifdef ENABLE_MRM
#ifdef ENABLE_MRM_STANDALONE_APP
    auto mrmHandler = capabilityAgents::mrm::mrmHandler::MRMHandlerProxy::create(
        connectionManager,
        messageSender,
        directiveSequencer,
        userInactivityMonitor,
        contextManager,
        audioFocusManager,
        speakerManager);
#else
    auto mrmHandler = capabilityAgents::mrm::mrmHandler::MRMHandler::create(
        connectionManager,
        messageSender,
        directiveSequencer,
        userInactivityMonitor,
        contextManager,
        audioFocusManager,
        speakerManager,
        m_deviceInfo->getDeviceSerialNumber());

#endif  // ENABLE_MRM_STANDALONE_APP

    if (!mrmHandler) {
        ACSDK_ERROR(LX(__func__).m("Unable to create mrmHandler"));
        return retValue;
    }

    auto mrmCapabilityAgent = capabilityAgents::mrm::MRMCapabilityAgent::create(
        std::move(mrmHandler), speakerManager, userInactivityMonitor, exceptionSender);

    if (!mrmCapabilityAgent) {
        ACSDK_ERROR(LX(__func__).m("Unable to create MRMCapabilityAgent"));
        return retValue;
    }

    if (m_templateRuntime) {
        m_templateRuntime->addRenderPlayerInfoCardsProvider(mrmCapabilityAgent);
    }

    if (m_callManager) {
        m_callManager->addObserver(mrmCapabilityAgent);
    }

    Capability mrmCapability;
    auto mrmConfigurations = mrmCapabilityAgent->getCapabilityConfigurations();
    mrmCapability.directiveHandler = std::move(mrmCapabilityAgent);
    for (auto& configurationPtr : mrmConfigurations) {
        mrmCapability.configuration = *configurationPtr;
        capabilities.push_back(mrmCapability);
    }

    requireShutdownObjects.push_back(mrmCapabilityAgent);

#endif  // // ENABLE_MRM

#ifdef ENABLE_RTCSC
    ACSDK_DEBUG5(LX("RtcscCapabilityAgent being created"));
    if (!alexaClientSDK::capabilityAgents::rtcscCapabilityAgent::RtcscCapabilityAgent::create(
            messageSender, contextManager, exceptionSender)) {
        ACSDK_ERROR(LX("initializeFailed").d("reason", "unableToCreate RtcscCapabilityAgent"));
        return retValue;
    }

    auto rtcscCapabilityAgent =
        alexaClientSDK::capabilityAgents::rtcscCapabilityAgent::RtcscCapabilityAgent::getInstance();

    m_rtcscCapabilityAgent = rtcscCapabilityAgent;

    Capability rtcscCapabilityAgentCapability;
    auto rtcscCapabilityAgentConfigurations = rtcscCapabilityAgent->getCapabilityConfigurations();
    rtcscCapabilityAgentCapability.directiveHandler = std::move(rtcscCapabilityAgent);
    for (auto& configurationPtr : rtcscCapabilityAgentConfigurations) {
        rtcscCapabilityAgentCapability.configuration = *configurationPtr;
        capabilities.push_back(rtcscCapabilityAgentCapability);
    }
    requireShutdownObjects.push_back(m_rtcscCapabilityAgent);
#endif

    retValue.first.swap(capabilities);
    retValue.second.swap(requireShutdownObjects);

    return retValue;
}

}  // namespace sampleApp
}  // namespace alexaSmartScreenSDK
