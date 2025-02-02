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

#ifndef ALEXA_SMART_SCREEN_SDK_APPLICATIONUTILITIES_SMARTSCREENCLIENT_INCLUDE_SMARTSCREENCLIENT_SMARTSCREENCLIENT_H_
#define ALEXA_SMART_SCREEN_SDK_APPLICATIONUTILITIES_SMARTSCREENCLIENT_INCLUDE_SMARTSCREENCLIENT_SMARTSCREENCLIENT_H_

#include <ACL/Transport/MessageRouter.h>
#include <ACL/Transport/MessageRouterFactory.h>
#include <ADSL/DirectiveSequencer.h>
#include <AFML/AudioActivityTracker.h>
#include <AFML/FocusManager.h>
#include <AFML/VisualActivityTracker.h>
#include <AIP/AudioInputProcessor.h>
#include <AIP/AudioProvider.h>
#include <AVSCommon/AVS/AVSDiscoveryEndpointAttributes.h>
#include <AVSCommon/AVS/Attachment/AttachmentManagerInterface.h>
#include <AVSCommon/AVS/DialogUXStateAggregator.h>
#include <AVSCommon/AVS/ExceptionEncounteredSender.h>
#include <AVSCommon/SDKInterfaces/AVSConnectionManagerInterface.h>
#include <AVSCommon/SDKInterfaces/AVSGatewayManagerInterface.h>
#include <AVSCommon/SDKInterfaces/Audio/AudioFactoryInterface.h>
#include <AVSCommon/SDKInterfaces/AuthDelegateInterface.h>
#include <AVSCommon/SDKInterfaces/Bluetooth/BluetoothDeviceConnectionRuleInterface.h>
#include <AVSCommon/SDKInterfaces/CallManagerInterface.h>
#include <AVSCommon/SDKInterfaces/CapabilitiesDelegateInterface.h>
#include <AVSCommon/SDKInterfaces/CapabilitiesObserverInterface.h>
#include <AVSCommon/SDKInterfaces/ConnectionStatusObserverInterface.h>
#include <AVSCommon/SDKInterfaces/Diagnostics/DiagnosticsInterface.h>
#include <AVSCommon/SDKInterfaces/DialogUXStateObserverInterface.h>
#include <AVSCommon/SDKInterfaces/Endpoints/DefaultEndpointAnnotation.h>
#include <AVSCommon/SDKInterfaces/Endpoints/EndpointBuilderInterface.h>
#include <AVSCommon/SDKInterfaces/Endpoints/EndpointIdentifier.h>
#include <AVSCommon/SDKInterfaces/Endpoints/EndpointInterface.h>
#include <AVSCommon/SDKInterfaces/ExpectSpeechTimeoutHandlerInterface.h>
#include <AVSCommon/SDKInterfaces/InternetConnectionMonitorInterface.h>
#include <AVSCommon/SDKInterfaces/LocaleAssetsManagerInterface.h>
#include <AVSCommon/SDKInterfaces/PowerResourceManagerInterface.h>
#include <AVSCommon/SDKInterfaces/SingleSettingObserverInterface.h>
#include <AVSCommon/SDKInterfaces/SpeechInteractionHandlerInterface.h>
#include <AVSCommon/SDKInterfaces/Storage/MiscStorageInterface.h>
#include <AVSCommon/SDKInterfaces/SystemTimeZoneInterface.h>
#include <AVSCommon/SDKInterfaces/TemplateRuntimeObserverInterface.h>
#include <AVSCommon/Utils/DeviceInfo.h>
#include <AVSCommon/Utils/LibcurlUtils/HTTPContentFetcherFactory.h>
#include <AVSCommon/Utils/MediaPlayer/MediaPlayerFactoryInterface.h>
#include <AVSCommon/Utils/MediaPlayer/MediaPlayerInterface.h>
#include <AVSCommon/Utils/Metrics/MetricRecorderInterface.h>
#include <AVSCommon/Utils/Optional.h>
#include <Alexa/AlexaInterfaceCapabilityAgent.h>
#include <Alexa/AlexaInterfaceMessageSender.h>
#include <ApiGateway/ApiGatewayCapabilityAgent.h>
#include <Captions/CaptionManagerInterface.h>
#include <Captions/CaptionPresenterInterface.h>
#include <CertifiedSender/CertifiedSender.h>
#include <CertifiedSender/SQLiteMessageStorage.h>
#include <Endpoints/EndpointRegistrationManager.h>
#include <acsdkAlerts/AlertsCapabilityAgent.h>
#include <acsdkAlerts/Renderer/Renderer.h>
#include <acsdkAlerts/Storage/AlertStorageInterface.h>
#include <acsdkApplicationAudioPipelineFactoryInterfaces/ApplicationAudioPipelineFactoryInterface.h>
#include <acsdkAudioPlayer/AudioPlayer.h>
#include <acsdkAudioPlayerInterfaces/AudioPlayerObserverInterface.h>
#include <acsdkBluetooth/Bluetooth.h>
#include <acsdkBluetoothInterfaces/BluetoothNotifierInterface.h>
#include <acsdkBluetoothInterfaces/BluetoothStorageInterface.h>
#include <acsdkDeviceSetupInterfaces/DeviceSetupInterface.h>
#include <acsdkDeviceSetupInterfaces/DeviceSetupInterface.h>
#include <acsdkDoNotDisturb/DoNotDisturbCapabilityAgent.h>
#include <acsdkEqualizer/EqualizerCapabilityAgent.h>
#include <acsdkEqualizerImplementations/EqualizerController.h>
#include <acsdkEqualizerInterfaces/EqualizerConfigurationInterface.h>
#include <acsdkEqualizerInterfaces/EqualizerModeControllerInterface.h>
#include <acsdkEqualizerInterfaces/EqualizerRuntimeSetupInterface.h>
#include <acsdkEqualizerInterfaces/EqualizerStorageInterface.h>
#include <acsdkExternalMediaPlayer/ExternalMediaPlayer.h>
#include <acsdkExternalMediaPlayerInterfaces/ExternalMediaAdapterHandlerInterface.h>
#include <acsdkExternalMediaPlayerInterfaces/ExternalMediaPlayerInterface.h>
#include <acsdkManufactory/Manufactory.h>
#include <acsdkNotifications/NotificationsCapabilityAgent.h>
#include <acsdkShutdownManagerInterfaces/ShutdownManagerInterface.h>
#include <acsdkStartupManagerInterfaces/StartupManagerInterface.h>
#include <acsdkSystemClockMonitorInterfaces/SystemClockMonitorInterface.h>

#ifdef ENABLE_PCC
#include <AVSCommon/SDKInterfaces/Phone/PhoneCallerInterface.h>
#include <PhoneCallController/PhoneCallController.h>
#endif

#ifdef ENABLE_MCC
#include <AVSCommon/SDKInterfaces/Calendar/CalendarClientInterface.h>
#include <AVSCommon/SDKInterfaces/Meeting/MeetingClientInterface.h>
#include <MeetingClientController/MeetingClientController.h>
#endif

#include <AVSCommon/SDKInterfaces/Endpoints/EndpointInterface.h>
#include <AVSCommon/SDKInterfaces/SystemSoundPlayerInterface.h>
#include <Endpoints/Endpoint.h>
#include <PlaybackController/PlaybackController.h>
#include <PlaybackController/PlaybackRouter.h>
#include <Settings/DeviceSettingsManager.h>
#include <Settings/Storage/DeviceSettingStorageInterface.h>
#include <SoftwareComponentReporter/SoftwareComponentReporterCapabilityAgent.h>
#include <SpeakerManager/DefaultChannelVolumeFactory.h>
#include <SpeakerManager/SpeakerManager.h>
#include <SpeechEncoder/SpeechEncoder.h>
#include <SpeechSynthesizer/SpeechSynthesizer.h>
#include <System/SoftwareInfoSender.h>
#include <System/UserInactivityMonitor.h>

#ifdef ENABLE_REVOKE_AUTH
#include <System/RevokeAuthorizationHandler.h>
#endif

#ifdef ENABLE_RTCSC
#include <LiveViewControllerCapabilityAgent/LiveViewControllerCapabilityAgent.h>
#endif

#include <AlexaPresentation/AlexaPresentation.h>
#include <RegistrationManager/RegistrationManagerInterface.h>
#include <RegistrationManager/RegistrationNotifierInterface.h>
#include <SmartScreenSDKInterfaces/AlexaPresentationObserverInterface.h>
#include <SmartScreenSDKInterfaces/TemplateRuntimeObserverInterface.h>
#include <SmartScreenSDKInterfaces/VisualStateProviderInterface.h>
#include <TemplateRuntimeCapabilityAgent/TemplateRuntime.h>
#include <VisualCharacteristics/VisualCharacteristics.h>
#include <acsdkInteractionModelInterfaces/InteractionModelNotifierInterface.h>
#include <acsdkNotificationsInterfaces/NotificationsNotifierInterface.h>

#include "SmartScreenClient/ConnectionRetryTrigger.h"
#include "SmartScreenClient/EqualizerRuntimeSetup.h"
#include "SmartScreenClient/ExternalCapabilitiesBuilderInterface.h"

namespace alexaSmartScreenSDK {
namespace smartScreenClient {

/**
 * This class serves to instantiate each default component with of the SDK with no specializations to provide an
 * "out-of-box" component that users may utilize for AVS interaction.
 */
class SmartScreenClient
        : public alexaClientSDK::avsCommon::sdkInterfaces::SpeechInteractionHandlerInterface
        , public std::enable_shared_from_this<SmartScreenClient>
        , public alexaClientSDK::avsCommon::sdkInterfaces::ChannelObserverInterface {
public:
    using SmartScreenClientManufactory = alexaClientSDK::acsdkManufactory::Manufactory<
        std::shared_ptr<alexaClientSDK::acsdkAlertsInterfaces::AlertsCapabilityAgentInterface>,
        std::shared_ptr<
            alexaClientSDK::acsdkApplicationAudioPipelineFactoryInterfaces::ApplicationAudioPipelineFactoryInterface>,
        std::shared_ptr<alexaClientSDK::acsdkAudioPlayerInterfaces::AudioPlayerInterface>,
        std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothLocalInterface>,
        std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothNotifierInterface>,
        std::shared_ptr<alexaClientSDK::acsdkEqualizerInterfaces::EqualizerRuntimeSetupInterface>,
        std::shared_ptr<alexaClientSDK::acsdkExternalMediaPlayer::ExternalMediaPlayer>,  /// Applications should not use
                                                                                         /// this export.
        std::shared_ptr<alexaClientSDK::acsdkExternalMediaPlayerInterfaces::ExternalMediaPlayerInterface>,
        std::shared_ptr<alexaClientSDK::acsdkShutdownManagerInterfaces::ShutdownManagerInterface>,
        std::shared_ptr<alexaClientSDK::acsdkStartupManagerInterfaces::StartupManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DirectiveSequencerInterface>,
        std::shared_ptr<alexaClientSDK::acsdkSystemClockMonitorInterfaces::SystemClockMonitorInterface>,
        std::shared_ptr<alexaClientSDK::afml::interruptModel::InterruptModel>,
        std::shared_ptr<alexaClientSDK::avsCommon::avs::attachment::AttachmentManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AuthDelegateInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AVSConnectionManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AVSGatewayManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::CapabilitiesDelegateInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeFactoryInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ContextManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExpectSpeechTimeoutHandlerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExceptionEncounteredSenderInterface>,
        alexaClientSDK::acsdkManufactory::Annotated<
            alexaClientSDK::avsCommon::sdkInterfaces::AudioFocusAnnotation,
            alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::HTTPContentFetcherInterfaceFactoryInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::InternetConnectionMonitorInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::LocaleAssetsManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::PlaybackRouterInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::PowerResourceManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::RenderPlayerInfoCardsProviderRegistrarInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerManagerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SystemSoundPlayerInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SystemTimeZoneInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::UserInactivityMonitorInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::audio::AudioFactoryInterface>,
        alexaClientSDK::acsdkManufactory::Annotated<
            alexaClientSDK::avsCommon::sdkInterfaces::endpoints::DefaultEndpointAnnotation,
            alexaClientSDK::avsCommon::sdkInterfaces::endpoints::EndpointBuilderInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::storage::MiscStorageInterface>,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::DeviceInfo>,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::configuration::ConfigurationNode>,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::metrics::MetricRecorderInterface>,
        std::shared_ptr<alexaClientSDK::capabilityAgents::alexa::AlexaInterfaceMessageSender>,
        std::shared_ptr<alexaClientSDK::capabilityAgents::doNotDisturb::DoNotDisturbCapabilityAgent>,
        std::shared_ptr<alexaClientSDK::captions::CaptionManagerInterface>,
        std::shared_ptr<alexaClientSDK::certifiedSender::CertifiedSender>,
        std::shared_ptr<alexaClientSDK::registrationManager::CustomerDataManagerInterface>,
        std::shared_ptr<alexaClientSDK::registrationManager::RegistrationManagerInterface>,
        std::shared_ptr<alexaClientSDK::registrationManager::RegistrationNotifierInterface>,
        std::shared_ptr<alexaClientSDK::settings::DeviceSettingsManager>,
        std::shared_ptr<alexaClientSDK::settings::storage::DeviceSettingStorageInterface>,
        std::shared_ptr<alexaClientSDK::speechencoder::SpeechEncoder>,
        std::shared_ptr<alexaClientSDK::acsdkDeviceSetupInterfaces::DeviceSetupInterface>,
        std::shared_ptr<alexaClientSDK::acsdkNotificationsInterfaces::NotificationsNotifierInterface>,
        std::shared_ptr<alexaClientSDK::acsdkInteractionModelInterfaces::InteractionModelNotifierInterface>>;

    /**
     * Creates and initializes a default AVS SDK client. To connect the client to AVS, users should make a call to
     * connect() after creation.
     *
     * @param manufactory @c Manufactory for creating various instances used by DefaultlClient.
     * @param bluetoothMediaPlayer The media player to play bluetooth content.
     * @param ringtoneMediaPlayer The media player to play Comms ringtones.
     * @param systemSoundMediaPlayer The media player to play system sounds.
     * @param bluetoothSpeaker The speaker to control volume of bluetooth.
     * @param ringtoneSpeaker The speaker to control volume of Comms ringtones.
     * @param systemSoundSpeaker The speaker to control volume of system sounds.
     * @param additionalSpeakers A map of additional speakers to receive volume changes.
#ifdef ENABLE_PCC
     * @param phoneSpeaker Interface to speaker for phone calls.
     * @param phoneCaller Interface for making phone calls.
#endif
#ifdef ENABLE_MCC
     * @param meetingSpeaker Interface to speaker for meetings.
     * @param meetingClient Meeting client for meeting client controller.
     * @param calendarClient Calendar client for meeting client controller.
#endif
#ifdef ENABLE_COMMS_AUDIO_PROXY
     * @param commsMediaPlayer The media player to play Comms calling audio.
     * @param commsSpeaker The speaker to control volume of Comms calling audio.
     * @param sharedDataStream The stream to use which has the audio from microphone.
#endif
     * @param notificationsStorage The storage interface that will be used to store notification indicators.
     * @param bluetoothStorage The storage interface that will be used to store bluetooth data.
     * @param alexaDialogStateObservers Observers that can be used to be notified of Alexa dialog related UX state
     * changes.
     * @param connectionObservers Observers that can be used to be notified of connection status changes.
     * @param enabledConnectionRules The set of @c BluetoothDeviceConnectionRuleInterface instances used to
     * create the Bluetooth CA.
     * @param firmwareVersion The firmware version to report to @c AVS or @c INVALID_FIRMWARE_VERSION.
     * @param sendSoftwareInfoOnConnected Whether to send SoftwareInfo upon connecting to @c AVS.
     * @param softwareInfoSenderObserver Object to receive notifications about sending SoftwareInfo.
     * @param bluetoothDeviceManager The @c BluetoothDeviceManager instance used to create the Bluetooth CA.
     * @param diagnostics Diagnostics interface which provides suite of APIs for diagnostic insight into SDK.
     * @param externalCapabilitiesBuilder Optional object used to build capabilities that are not included in the SDK.
     * @param firstInteractionAudioProvider Optional object used in the first interaction started from
     * the alexa voice service
     * @param visualStateProvider The visual state provider. This should be @C nullptr for non-APL devices.
     * @param APLMaxVersion The maximum APL version supported by the GUI client. This default to empty on headless
     * devices.
     * @return A @c std::unique_ptr to a SmartScreenClient if all went well or @c nullptr otherwise.
     */
    static std::unique_ptr<SmartScreenClient> create(
        const std::shared_ptr<SmartScreenClientManufactory>& manufactory,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> bluetoothMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> ringtoneMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> systemSoundMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> bluetoothSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> ringtoneSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> systemSoundSpeaker,
        const std::multimap<
            alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeInterface::Type,
            std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>> additionalSpeakers,
#ifdef ENABLE_PCC
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> phoneSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::phone::PhoneCallerInterface> phoneCaller,
#endif
#ifdef ENABLE_MCC
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> meetingSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::meeting::MeetingClientInterface> meetingClient,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::calendar::CalendarClientInterface> calendarClient,
#endif
#ifdef ENABLE_COMMS_AUDIO_PROXY
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> commsMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> commsSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream,
#endif
        std::shared_ptr<alexaClientSDK::acsdkNotificationsInterfaces::NotificationsStorageInterface>
            notificationsStorage,
        std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothStorageInterface> bluetoothStorage,
        std::unordered_set<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DialogUXStateObserverInterface>>
            alexaDialogStateObservers,
        std::unordered_set<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ConnectionStatusObserverInterface>>
            connectionObservers,
        std::unordered_set<std::shared_ptr<
            alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceConnectionRuleInterface>>
            enabledConnectionRules = std::unordered_set<std::shared_ptr<
                alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceConnectionRuleInterface>>(),
        alexaClientSDK::avsCommon::sdkInterfaces::softwareInfo::FirmwareVersion firmwareVersion =
            alexaClientSDK::avsCommon::sdkInterfaces::softwareInfo::INVALID_FIRMWARE_VERSION,
        bool sendSoftwareInfoOnConnected = false,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SoftwareInfoSenderObserverInterface>
            softwareInfoSenderObserver = nullptr,
        std::unique_ptr<alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceManagerInterface>
            bluetoothDeviceManager = nullptr,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::diagnostics::DiagnosticsInterface> diagnostics =
            nullptr,
        const std::shared_ptr<ExternalCapabilitiesBuilderInterface>& externalCapabilitiesBuilder = nullptr,
        alexaClientSDK::capabilityAgents::aip::AudioProvider firstInteractionAudioProvider =
            alexaClientSDK::capabilityAgents::aip::AudioProvider::null(),
        std::shared_ptr<smartScreenSDKInterfaces::VisualStateProviderInterface> visualStateProvider = nullptr,
        const std::string& APLMaxVersion = "");

    /**
     * Creates and initializes a default AVS SDK client. To connect the client to AVS, users should make a call to
     * connect() after creation.
     *
     * @deprecated
     * @param deviceInfo DeviceInfo which reflects the device setup credentials.
     * @param customerDataManager CustomerDataManager instance to be used by RegistrationManager and instances of
     * all classes extending CustomDataHandler.
     * @param externalMusicProviderMediaPlayers The map of <players, mediaPlayer> to use to play content from each
     * external music provider.
     * @param externalMusicProviderSpeakers The map of <players, speaker> to use to track volume of each
     * external music provider media player.
     * @param adapterCreationMap The map of <players, adapterCreationMethod> to use when creating the adapters for the
     * different music providers supported by ExternalMediaPlayer.
     * @param speakMediaPlayer The media player to use to play Alexa speech from.
     * @param audioMediaPlayerFactory The media player factory to use to generate players for Alexa audio content.
     * @param alertsMediaPlayer The media player to use to play alerts from.
     * @param notificationsMediaPlayer The media player to play notification indicators.
     * @param bluetoothMediaPlayer The media player to play bluetooth content.
     * @param ringtoneMediaPlayer The media player to play Comms ringtones.
     * @param systemSoundMediaPlayer The media player to play system sounds.
     * @param speakSpeaker The speaker to control volume of Alexa speech.
     * @param audioSpeakers A list of speakers to control volume of Alexa audio content.
     * @param alertsSpeaker The speaker to control volume of alerts.
     * @param notificationsSpeaker The speaker to control volume of notifications.
     * @param bluetoothSpeaker The speaker to control volume of bluetooth.
     * @param ringtoneSpeaker The speaker to control volume of Comms ringtones.
     * @param systemSoundSpeaker The speaker to control volume of system sounds.
     * @param additionalSpeakers A map of additional speakers to receive volume changes.
#ifdef ENABLE_COMMS_AUDIO_PROXY
     * @param commsMediaPlayer The media player to play Comms calling audio.
     * @param commsSpeaker The speaker to control volume of Comms calling audio.
     * @param sharedDataStream The stream to use which has the audio from microphone.
#endif
     * @param equalizerRuntimeSetup Equalizer component runtime setup
     * @param audioFactory The audioFactory is a component that provides unique audio streams.
     * @param authDelegate The component that provides the client with valid LWA authorization.
     * @param alertStorage The storage interface that will be used to store alerts.
     * @param messageStorage The storage interface that will be used to store certified sender messages.
     * @param notificationsStorage The storage interface that will be used to store notification indicators.
     * @param deviceSettingStorage The storage interface that will be used to store device settings.
     * @param bluetoothStorage The storage interface that will be used to store bluetooth data.
     * @param miscStorage The storage interface that will be used to store key / value pairs.
     * @param alexaDialogStateObservers Observers that can be used to be notified of Alexa dialog related UX state
     * changes.
     * @param connectionObservers Observers that can be used to be notified of connection status changes.
     * @param capabilitiesDelegate The component that provides the client with the ability to send messages to the
     * Capabilities API.
     * @param contextManager The @c ContextManager which will provide the context for various components.
     * @param transportFactory The object passed in here will be used whenever a new transport object
     * for AVS communication is needed.
     * @param avsGatewayManager The @c AVSGatewayManager instance used to create the ApiGateway CA.
     * @param localeAssetsManager The device locale assets manager.
     * @param enabledConnectionRules The set of @c BluetoothDeviceConnectionRuleInterface instances used to
     * create the Bluetooth CA.
     * @param systemTimezone Optional object used to set the system timezone.
     * @param firmwareVersion The firmware version to report to @c AVS or @c INVALID_FIRMWARE_VERSION.
     * @param sendSoftwareInfoOnConnected Whether to send SoftwareInfo upon connecting to @c AVS.
     * @param softwareInfoSenderObserver Object to receive notifications about sending SoftwareInfo.
     * @param bluetoothDeviceManager The @c BluetoothDeviceManager instance used to create the Bluetooth CA.
     * @param metricRecorder The metric recorder object used to capture metrics.
     * @param powerResourceManager Object to manage power resource.
     * @param diagnostics Diagnostics interface which provides suite of APIs for diagnostic insight into SDK.
     * @param externalCapabilitiesBuilder Optional object used to build capabilities that are not included in the SDK.
     * @param channelVolumeFactory Optional object used to build @c ChannelVolumeInterface in the SDK.
     * @param startAlertSchedulingOnInitialization Whether to start scheduling alerts after client initialization. If
     * this is set to false, no alert scheduling will occur until onSystemClockSynchronized is called.
     * @param messageRouterFactory Object used to instantiate @c MessageRouter in the SDK.
     * @param expectSpeechTimeoutHandler An optional object that applications may provide to specify external handling
of the @c ExpectSpeech directive's timeout. If provided, this function must remain valid for the lifetime of the @c
AudioInputProcessor.
     * @param firstInteractionAudioProvider Optional object used in the first interaction started from
     * the alexa voice service
     * @param visualStateProvider The visual state provider. This should be @C nullptr for non-APL devices.
     * @param APLMaxVersion The maximum APL version supported by the GUI client. This default to empty on headless
     * devices.
     * @return A @c std::unique_ptr to a SmartScreenClient if all went well or @c nullptr otherwise.
     */
    static std::unique_ptr<SmartScreenClient> create(
        std::shared_ptr<alexaClientSDK::avsCommon::utils::DeviceInfo> deviceInfo,
        std::shared_ptr<alexaClientSDK::registrationManager::CustomerDataManagerInterface> customerDataManager,
        const std::unordered_map<
            std::string,
            std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface>>&
            externalMusicProviderMediaPlayers,
        const std::unordered_map<
            std::string,
            std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>>& externalMusicProviderSpeakers,
        const alexaClientSDK::acsdkExternalMediaPlayer::ExternalMediaPlayer::AdapterCreationMap& adapterCreationMap,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> speakMediaPlayer,
        std::unique_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerFactoryInterface>
            audioMediaPlayerFactory,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> alertsMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> notificationsMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> bluetoothMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> ringtoneMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> systemSoundMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> speakSpeaker,
        std::vector<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>> audioSpeakers,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> alertsSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> notificationsSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> bluetoothSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> ringtoneSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> systemSoundSpeaker,
        const std::multimap<
            alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeInterface::Type,
            std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>> additionalSpeakers,
#ifdef ENABLE_PCC
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> phoneSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::phone::PhoneCallerInterface> phoneCaller,
#endif
#ifdef ENABLE_MCC
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> meetingSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::meeting::MeetingClientInterface> meetingClient,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::calendar::CalendarClientInterface> calendarClient,
#endif
#ifdef ENABLE_COMMS_AUDIO_PROXY
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> commsMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> commsSpeaker,
        std::shared_ptr<alexaClientSDK::alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream,
#endif
        std::shared_ptr<EqualizerRuntimeSetup> equalizerRuntimeSetup,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::audio::AudioFactoryInterface> audioFactory,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AuthDelegateInterface> authDelegate,
        std::shared_ptr<alexaClientSDK::acsdkAlerts::storage::AlertStorageInterface> alertStorage,
        std::shared_ptr<alexaClientSDK::certifiedSender::MessageStorageInterface> messageStorage,
        std::shared_ptr<alexaClientSDK::acsdkNotificationsInterfaces::NotificationsStorageInterface>
            notificationsStorage,
        std::shared_ptr<alexaClientSDK::settings::storage::DeviceSettingStorageInterface> deviceSettingStorage,
        std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothStorageInterface> bluetoothStorage,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::storage::MiscStorageInterface> miscStorage,
        std::unordered_set<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DialogUXStateObserverInterface>>
            alexaDialogStateObservers,
        std::unordered_set<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ConnectionStatusObserverInterface>>
            connectionObservers,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::InternetConnectionMonitorInterface>
            internetConnectionMonitor,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::CapabilitiesDelegateInterface> capabilitiesDelegate,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ContextManagerInterface> contextManager,
        std::shared_ptr<alexaClientSDK::acl::TransportFactoryInterface> transportFactory,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AVSGatewayManagerInterface> avsGatewayManager,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::LocaleAssetsManagerInterface> localeAssetsManager,
        std::unordered_set<std::shared_ptr<
            alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceConnectionRuleInterface>>
            enabledConnectionRules = std::unordered_set<std::shared_ptr<
                alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceConnectionRuleInterface>>(),
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SystemTimeZoneInterface> systemTimezone = nullptr,
        alexaClientSDK::avsCommon::sdkInterfaces::softwareInfo::FirmwareVersion firmwareVersion =
            alexaClientSDK::avsCommon::sdkInterfaces::softwareInfo::INVALID_FIRMWARE_VERSION,
        bool sendSoftwareInfoOnConnected = false,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SoftwareInfoSenderObserverInterface>
            softwareInfoSenderObserver = nullptr,
        std::unique_ptr<alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceManagerInterface>
            bluetoothDeviceManager = nullptr,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::metrics::MetricRecorderInterface> metricRecorder = nullptr,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::PowerResourceManagerInterface> powerResourceManager =
            nullptr,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::diagnostics::DiagnosticsInterface> diagnostics =
            nullptr,
        const std::shared_ptr<ExternalCapabilitiesBuilderInterface>& externalCapabilitiesBuilder = nullptr,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeFactoryInterface> channelVolumeFactory =
            std::make_shared<alexaClientSDK::capabilityAgents::speakerManager::DefaultChannelVolumeFactory>(),
        bool startAlertSchedulingOnInitialization = true,
        std::shared_ptr<alexaClientSDK::acl::MessageRouterFactoryInterface> messageRouterFactory =
            std::make_shared<alexaClientSDK::acl::MessageRouterFactory>(),
        const std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExpectSpeechTimeoutHandlerInterface>&
            expectSpeechTimeoutHandler = nullptr,
        alexaClientSDK::capabilityAgents::aip::AudioProvider firstInteractionAudioProvider =
            alexaClientSDK::capabilityAgents::aip::AudioProvider::null(),
        std::shared_ptr<smartScreenSDKInterfaces::VisualStateProviderInterface> visualStateProvider = nullptr,
        const std::string& APLMaxVersion = "");

    /// @name ChannelObserverInterface Methods
    /// @{
    void onFocusChanged(
        alexaClientSDK::avsCommon::avs::FocusState newFocus,
        alexaClientSDK::avsCommon::avs::MixingBehavior behavior) override;
    /// }

    /**
     * Connects the client to AVS. After this call, users can observe the state of the connection asynchronously by
     * using a connectionObserver that was passed in to the create() function.
     *
     * @param performReset True if the client wishes to reset the AVS gateway and clear the previous user's
     * registration status as well on connection.
     *
     */
    void connect(bool performReset = true);

    /**
     * Disconnects the client from AVS if it is connected. After the call, users can observer the state of the
     * connection asynchronously by using a connectionObserver that was passed in to the create() function.
     */
    void disconnect();

    void onUserEvent(alexaClientSDK::avsCommon::sdkInterfaces::AudioInputProcessorObserverInterface::State state);

    /**
     * Get the gateway URL for the AVS connection.
     *
     * @return The URL for the current AVS gateway.
     */
    std::string getAVSGateway();

    /**
     * This will force clear the DIALOG channel and reset it, allowing for proper cloud-side context when locally
     * stopping DIALOG channel.
     */
    void forceClearDialogChannelFocus();

    /**
     * An exit event that can be used to stop all active audio channels, clear all active UI, and reset DIALOG focus.
     */
    void forceExit();

    /**
     * Clears all displayed presentations.
     * Sends @c Alexa.Presentation.Dismissed event to AVS when clearing APL presentations.
     */
    void clearPresentations();

    /**
     * Clear displaying APL card on screen.
     */
    void clearAPLCard();

    /**
     * Forces display and focus of the active PlayerInfo card if available.
     */
    void forceDisplayPlayerInfoCard();

    /**
     * Clears the active PlayerInfo card (whether it is backgrounded or displayed)
     */
    void clearPlayerInfoCard();

    /**
     * Stops the foreground audio activity if there is one. This acts as a "stop" button that can be used to stop an
     * ongoing activity. This call will block until the foreground activity has stopped all user-observable activities.
     */
    void stopForegroundActivity();

    /**
     * Stops all active channels/activities if there are any(has acquired focus atleast once). This acts as a "stop"
     * button that can be used to stop all ongoing activities. This call will block until all the activities has
     * stopped. There is a possibility of race condition of some activity about to start when this API is invoked.
     */
    void stopAllActivities();

    /**
     * This function provides a way for application code to request this object stop any active alert as the result
     * of a user action, such as pressing a physical 'stop' button on the device.
     */
    void localStopActiveAlert();

    /**
     * Adds an observer to be notified of Alexa dialog related UX state.
     *
     * @param observer The observer to add.
     */
    void addAlexaDialogStateObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DialogUXStateObserverInterface> observer);

    /**
     * Removes an observer to be notified of Alexa dialog related UX state.
     *
     * @note This is a synchronous call which can not be made by an observer callback.  Attempting to call
     *     @c removeObserver() from @c DialogUXStateObserverInterface::onDialogUXStateChanged() will result in a
     *     deadlock.
     *
     * @param observer The observer to remove.
     */
    void removeAlexaDialogStateObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DialogUXStateObserverInterface> observer);

    /**
     * Adds an observer to be notified when a message arrives from AVS.
     *
     * @param observer The observer to add.
     */
    void addMessageObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::MessageObserverInterface> observer);

    /**
     * Removes an observer to be notified when a message arrives from AVS.
     *
     * @param observer The observer to remove.
     */
    void removeMessageObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::MessageObserverInterface> observer);

    /**
     * Adds an observer to be notified of connection status changes.
     *
     * @param observer The observer to add.
     */
    void addConnectionObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ConnectionStatusObserverInterface> observer);

    /**
     * Removes an observer to be notified of connection status changes.
     *
     * @param observer The observer to remove.
     */
    void removeConnectionObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ConnectionStatusObserverInterface> observer);

    /**
     * Adds an observer to be notified of internet connection status changes.
     *
     * @param observer The observer to add.
     */
    void addInternetConnectionObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::InternetConnectionObserverInterface> observer);

    /**
     * Removes an observer to be notified of internet connection status changes.
     *
     * @param observer The observer to remove.
     */
    void removeInternetConnectionObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::InternetConnectionObserverInterface> observer);

    /**
     * Adds an observer to be notified of alert state changes.
     *
     * @param observer The observer to add.
     */
    void addAlertsObserver(std::shared_ptr<alexaClientSDK::acsdkAlertsInterfaces::AlertObserverInterface> observer);

    /**
     * Removes an observer to be notified of alert state changes.
     *
     * @param observer The observer to remove.
     */
    void removeAlertsObserver(std::shared_ptr<alexaClientSDK::acsdkAlertsInterfaces::AlertObserverInterface> observer);

    /**
     * Adds an observer to be notified of @c AudioPlayer state changes. This can be used to be be notified of the @c
     * PlayerActivity of the @c AudioPlayer.
     *
     * @param observer The observer to add.
     */
    void addAudioPlayerObserver(
        std::shared_ptr<alexaClientSDK::acsdkAudioPlayerInterfaces::AudioPlayerObserverInterface> observer);

    /**
     * Removes an observer to be notified of @c AudioPlayer state changes.
     *
     * @param observer The observer to remove.
     */
    void removeAudioPlayerObserver(
        std::shared_ptr<alexaClientSDK::acsdkAudioPlayerInterfaces::AudioPlayerObserverInterface> observer);

    /**
     * Adds an observer to be notified of alexa presentation changes.
     *
     * @param observer The @c AlexaPresentationObserverInterface to add.
     */
    void addAlexaPresentationObserver(
        std::shared_ptr<alexaSmartScreenSDK::smartScreenSDKInterfaces::AlexaPresentationObserverInterface> observer);

    /**
     * Removes an observer to be notified of alexa presentation changes.
     *
     * @param observer The @c AlexaPresentationObserverInterface to remove.
     */
    void removeAlexaPresentationObserver(
        std::shared_ptr<alexaSmartScreenSDK::smartScreenSDKInterfaces::AlexaPresentationObserverInterface> observer);

    /**
     * Adds an observer to be notified of template runtime changes.
     *
     * @param observer The @c TemplateRuntimeObserverInterface to add.
     */
    void addTemplateRuntimeObserver(
        std::shared_ptr<alexaSmartScreenSDK::smartScreenSDKInterfaces::TemplateRuntimeObserverInterface> observer);

    /**
     * Removes an observer to be notified of template runtime changes.
     *
     * @param observer The @c TemplateRuntimeObserverInterface to remove.
     */
    void removeTemplateRuntimeObserver(
        std::shared_ptr<alexaSmartScreenSDK::smartScreenSDKInterfaces::TemplateRuntimeObserverInterface> observer);

    /**
     * Notify the TemplateRuntime Capability Agent that the display card is cleared from the screen.
     */
    void TemplateRuntimeDisplayCardCleared();

    /**
     * Adds an observer to be notified of IndicatorState changes.
     *
     * @param observer The observer to add.
     */
    void addNotificationsObserver(
        std::shared_ptr<alexaClientSDK::acsdkNotificationsInterfaces::NotificationsObserverInterface> observer);

    /**
     * Removes an observer to be notified of IndicatorState changes.
     *
     * @param observer The observer to remove.
     */
    void removeNotificationsObserver(
        std::shared_ptr<alexaClientSDK::acsdkNotificationsInterfaces::NotificationsObserverInterface> observer);

    /**
     * Adds an observer to be notified of ExternalMediaPlayer changes
     *
     * @param observer The observer to add.
     */
    void addExternalMediaPlayerObserver(
        std::shared_ptr<alexaClientSDK::acsdkExternalMediaPlayerInterfaces::ExternalMediaPlayerObserverInterface>
            observer);

    /**
     * Removes an observer to be notified of ExternalMediaPlayer changes.
     *
     * @param observer The observer to remove.
     */
    void removeExternalMediaPlayerObserver(
        std::shared_ptr<alexaClientSDK::acsdkExternalMediaPlayerInterfaces::ExternalMediaPlayerObserverInterface>
            observer);

    /**
     * Adds an observer to be notified of bluetooth device changes.
     *
     * @param observer The @c BluetoothDeviceObserverInterface to add.
     */
    void addBluetoothDeviceObserver(
        std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothDeviceObserverInterface> observer);

    /**
     * Removes an observer to be notified of bluetooth device changes.
     *
     * @param observer The @c BluetoothDeviceObserverInterface to remove.
     */
    void removeBluetoothDeviceObserver(
        std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothDeviceObserverInterface> observer);

    /**
     * Adds a presenter responsible for displaying formatted captions content.
     *
     * @deprecated Applications should use the manufactory to create their CaptionPresenterInterface and
     * inject it with the CaptionManagerInterface. See the SampleApplicationComponent for an example.
     * @param presenter The @c CaptionPresenterInterface to add.
     */
    void addCaptionPresenter(std::shared_ptr<alexaClientSDK::captions::CaptionPresenterInterface> presenter);

    /**
     * Sets the media players that can produce or control captioned content.
     *
     * @deprecated Applications should use an ApplicationAudioPipelineFactoryInterface to instantiate media players
     * and register them with the CaptionManager when they transition to the manufactory (e.g. see
     * GstreamerAudioPipelineFactory).
     * @param mediaPlayers The @c MediaPlayerInterface instances to add.
     */
    void setCaptionMediaPlayers(
        const std::vector<std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface>>&
            mediaPlayers);

    /*
     * Get a reference to the PlaybackRouter
     *
     * @return shared_ptr to the PlaybackRouter.
     */
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::PlaybackRouterInterface> getPlaybackRouter() const;

    /**
     * Get a reference to the Alexa Presentation
     *
     * @return shared_ptr to the Alexa Presentation
     */
    std::shared_ptr<alexaSmartScreenSDK::smartScreenCapabilityAgents::alexaPresentation::AlexaPresentation>
    getAlexaPresentation() const;

    /**
     * Get a reference to the Audio FocusManager
     *
     * @return shared_ptr to the FocusManager
     */
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerInterface> getAudioFocusManager() const;

    /**
     * Get a reference to the Video FocusManager
     *
     * @return shared_ptr to the FocusManager
     */
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerInterface> getVisualFocusManager() const;

    /**
     * Adds a SpeakerManagerObserver to be alerted when the volume and mute changes.
     *
     * @param observer The observer to be notified upon volume and mute changes.
     */
    void addSpeakerManagerObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerManagerObserverInterface> observer);

    /**
     * Removes a SpeakerManagerObserver from being alerted when the volume and mute changes.
     *
     * @param observer The observer to be notified upon volume and mute changes.
     */
    void removeSpeakerManagerObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerManagerObserverInterface> observer);

    /**
     * Get a shared_ptr to the SpeakerManager.
     *
     * @return shared_ptr to the SpeakerManager.
     */
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerManagerInterface> getSpeakerManager();

    /**
     * Adds a SpeechSynthesizerObserver to be alerted on SpeechSynthesizer state changes
     * @param observer  The observer to be notified upon the state change
     */
    void addSpeechSynthesizerObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeechSynthesizerObserverInterface> observer);

    /**
     * Removes a SpeechSynthesizerObserver from being alerted on SpeechSynthesizer state changes
     * @param observer  The observer to be removed
     */
    void removeSpeechSynthesizerObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeechSynthesizerObserverInterface> observer);

    /**
     * Get a shared_ptr to the RegistrationManager.
     *
     * @return shared_ptr to the RegistrationManager.
     */
    std::shared_ptr<alexaClientSDK::registrationManager::RegistrationManagerInterface> getRegistrationManager();

    /**
     * Adds an @c RegistrationObserverInterface to the @c RegistrationNotifier.
     *
     * @param observer - The @c RegistrationObserverInterfaces to be notified of logout events.
     */
    void addRegistrationObserver(
        const std::shared_ptr<alexaClientSDK::registrationManager::RegistrationObserverInterface>& observer);

    /**
     * Removes an @c RegistrationObserverInterface to the @c RegistrationNotifier.
     *
     * @param observer - The @c RegistrationObserverInterfaces to be notified of logout events.
     */
    void removeRegistrationObserver(
        const std::shared_ptr<alexaClientSDK::registrationManager::RegistrationObserverInterface>& observer);

#ifdef ENABLE_REVOKE_AUTH
    /**
     * Adds a RevokeAuthorizationObserver to be alerted when a revoke authorization request occurs.
     *
     * @param observer The observer to be notified of revoke authorization requests.
     */
    void addRevokeAuthorizationObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::RevokeAuthorizationObserverInterface> observer);

    /**
     * Removes a RevokeAuthorizationObserver from being alerted when a revoke authorization request occurs.
     *
     * @param observer The observer to no longer be notified of revoke authorization requests.
     */
    void removeRevokeAuthorizationObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::RevokeAuthorizationObserverInterface> observer);
#endif

    /**
     * Get a shared_ptr to the EqualizerController.
     *
     * @note Be sure to release all references to the returned @c EqualizerController before releasing the last
     * reference to the @c SmartScreenClient.
     * @return shared_ptr to the EqualizerController.
     */
    std::shared_ptr<alexaClientSDK::acsdkEqualizer::EqualizerController> getEqualizerController();

    /**
     * Adds a EqualizerControllerListener to be notified of Equalizer state changes.
     *
     * @param listener The listener to be notified of Equalizer state changes.
     */
    void addEqualizerControllerListener(
        std::shared_ptr<alexaClientSDK::acsdkEqualizerInterfaces::EqualizerControllerListenerInterface> listener);

    /**
     * Removes a EqualizerControllerListener to be notified of Equalizer state changes.
     *
     * @param listener The listener to no longer be notified of Equalizer state changes.
     */
    void removeEqualizerControllerListener(
        std::shared_ptr<alexaClientSDK::acsdkEqualizerInterfaces::EqualizerControllerListenerInterface> listener);

    /**
     * Adds a ContextManagerObserver to be notified of Context state changes.
     *
     * @param observer The observer to be notified of Context state changes.
     */
    void addContextManagerObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ContextManagerObserverInterface> observer);

    /**
     * Removes a ContextManagerObserver to be notified of Context state changes.
     *
     * @param observer The observer to no longer be notified of Context state changes.
     */
    void removeContextManagerObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ContextManagerObserverInterface> observer);

    /**
     * Update the firmware version.
     *
     * @param firmwareVersion The new firmware version.
     * @return Whether the setting was accepted.
     */
    bool setFirmwareVersion(alexaClientSDK::avsCommon::sdkInterfaces::softwareInfo::FirmwareVersion firmwareVersion);

    /// @name SpeechInteractionHandlerInterface Methods
    /// @{
    std::future<bool> notifyOfWakeWord(
        alexaClientSDK::capabilityAgents::aip::AudioProvider wakeWordAudioProvider,
        alexaClientSDK::avsCommon::avs::AudioInputStream::Index beginIndex,
        alexaClientSDK::avsCommon::avs::AudioInputStream::Index endIndex,
        std::string keyword,
        std::chrono::steady_clock::time_point startOfSpeechTimestamp,
        std::shared_ptr<const std::vector<char>> KWDMetadata = nullptr) override;

    std::future<bool> notifyOfTapToTalk(
        alexaClientSDK::capabilityAgents::aip::AudioProvider tapToTalkAudioProvider,
        alexaClientSDK::avsCommon::avs::AudioInputStream::Index beginIndex =
            alexaClientSDK::capabilityAgents::aip::AudioInputProcessor::INVALID_INDEX,
        std::chrono::steady_clock::time_point startOfSpeechTimestamp = std::chrono::steady_clock::now()) override;

    std::future<bool> notifyOfHoldToTalkStart(
        alexaClientSDK::capabilityAgents::aip::AudioProvider holdToTalkAudioProvider,
        std::chrono::steady_clock::time_point startOfSpeechTimestamp = std::chrono::steady_clock::now(),
        alexaClientSDK::avsCommon::avs::AudioInputStream::Index beginIndex =
            alexaClientSDK::capabilityAgents::aip::AudioInputProcessor::INVALID_INDEX) override;

    std::future<bool> notifyOfHoldToTalkEnd() override;

    std::future<bool> notifyOfTapToTalkEnd() override;
    /// }

    /**
     * Retrieves the device settings manager which can be used to access device settings.
     *
     * @return Pointer to the device settings manager.
     */
    std::shared_ptr<alexaClientSDK::settings::DeviceSettingsManager> getSettingsManager();

    /**
     * Creates an endpoint builder which can be used to configure a new endpoint.
     *
     * @note Endpoints must be registered with the Endpoint Registration Manager to be controlled by the device.
     *
     * @return An endpoint builder.
     */
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::endpoints::EndpointBuilderInterface>
    createEndpointBuilder();

    /**
     * Registers an endpoint with the @c EndpointRegistrationManagerInterface.
     *
     * @param endpoint A pointer to the @c EndpointInterface to be registered.
     * @return A future that will resolve to the @c RegistrationResult for registering this endpoint.
     */
    std::future<alexaClientSDK::endpoints::EndpointRegistrationManager::RegistrationResult> registerEndpoint(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::endpoints::EndpointInterface> endpoint);

    /**
     * Deregisters an endpoint with the @c EndpointRegistrationManagerInterface.
     *
     * @param endpointId The @c EndpointIdentifier of the endpoint to deregister.
     * @return A future that will resolve to the @c DeregistratonResult for deregistering this endpoint.
     */
    std::future<alexaClientSDK::endpoints::EndpointRegistrationManager::DeregistrationResult> deregisterEndpoint(
        alexaClientSDK::avsCommon::sdkInterfaces::endpoints::EndpointIdentifier endpointId);

    /**
     * Retrieves the builder for the default endpoint which contains all capabilities associated with this client.
     *
     * This builder can be used to add extra capabilities to the default endpoint.
     *
     * @return The default endpoint builder.
     * @warning The default endpoint can only be configured before you call @c connect(). Adding new components after
     * the client has been connected will fail.
     */
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::endpoints::EndpointBuilderInterface>
    getDefaultEndpointBuilder();

    /**
     * Adds an @c AudioInputProcessorObserver to be alerted on @c AudioInputProcessor related state changes.
     *
     * @param observer The observer to be notified upon @c AudioInputProcessor related state changes.
     */
    void addAudioInputProcessorObserver(
        const std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AudioInputProcessorObserverInterface>&
            observer);

    /**
     * Removes an @c AudioInputProcessorObserver to be alerted on @c AudioInputProcessor related state changes.
     *
     * @param observer The observer to be removed as an @c AudioInputProcessor observer.
     */
    void removeAudioInputProcessorObserver(
        const std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AudioInputProcessorObserverInterface>&
            observer);

    /**
     * Adds an observer to be notified when the call state has changed.
     *
     * @param observer The observer to add.
     */
    void addCallStateObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::CallStateObserverInterface> observer);

    /**
     * Removes an observer to be notified when the call state has changed.
     *
     * @param observer The observer to remove.
     */
    void removeCallStateObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::CallStateObserverInterface> observer);

    /**
     * Adds an observer to be notified when dtmf tones were sent.
     *
     * @param observer The observer to add.
     */
    void addDtmfObserver(std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DtmfObserverInterface> observer);

    /**
     * Removes an observer to be notified when dtmf tones were sent.
     *
     * @param observer The observer to remove.
     */
    void removeDtmfObserver(std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DtmfObserverInterface> observer);

    /**
     * Adds the provided FocusManagerObserver to be notified of all focus manager changes.
     *
     * @param observer The observer to be notified of focus manager changes.
     */
    void addFocusManagersObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerObserverInterface> observer);

    /**
     * Removes the provided FocusManagerObserver from being notified of focus manager changes.
     *
     * @param observer The observer to be removed from being notified of focus manager changes.
     */
    void removeFocusManagersObserver(
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerObserverInterface> observer);

    /**
     * Lets the caller know if Comms is enabled.
     *
     * @return True if comms is enabled.
     */
    bool isCommsEnabled();

    /**
     * Accepts an incoming phone-call.
     */
    void acceptCommsCall();

    /**
     * Send dtmf tones during the call.
     *
     * @param dtmfTone The signal of the dtmf message.
     */
    void sendDtmf(alexaClientSDK::avsCommon::sdkInterfaces::CallManagerInterface::DTMFTone dtmfTone);

    /**
     * Stops a phone-call.
     */
    void stopCommsCall();

    /**
     * Enables local video during a call.
     */
    void enableLocalVideo();

    /**
     * Disables local video during a call.
     */
    void disableLocalVideo();

    /**
     * Sends an user event.
     * @param payload The input user event.
     */
    void sendUserEvent(const std::string& payload);

    /**
     * Sends a DataSourceFetchRequest event.
     * @param type DataSource type.
     * @param payload event.
     */
    void sendDataSourceFetchRequestEvent(const std::string& type, const std::string& payload);

    /**
     * Sends a RuntimeError event.
     * @param payload event.
     */
    void sendRuntimeErrorEvent(const std::string& payload);

    /**
     * Handle visual context.
     * @param token The visual context token.
     * @param payload The input payload.
     */
    void handleVisualContext(uint64_t token, std::string payload);

    /**
     * Handle render document result.
     * @param token The token.
     * @param result The render document result.
     * @param error The error.
     */
    void handleRenderDocumentResult(const std::string& token, bool result, std::string error);

    /**
     * Handle execute command result.
     * @param token The token.
     * @param result The execute command result.
     * @param error The error.
     */
    void handleExecuteCommandsResult(const std::string& token, bool result, std::string error);

    /**
     * Handle activity event.
     * @param source The source of the activity event.
     * @param event The activity event.
     * @param isAlexaPresentationPresenting Whether the AlexaPresentation agent is presenting or not.
     */
    void handleActivityEvent(
        const std::string& source,
        smartScreenSDKInterfaces::ActivityEvent event,
        bool isAlexaPresentationPresenting);

    /**
     * Set idle timeout for APL documents.
     * @param timeout The timeout.
     */
    void setDocumentIdleTimeout(std::chrono::milliseconds timeout);

    /**
     * Clear all execute commands.
     * @param token The token. This should be passed in if we are clearing execute commands due to APL-specific trigger
     * (eg. Finish command). This should be left empty if we are clearing due to global triggers (eg. back navigation)
     * @param markAsFailed mark cleared command as failed.
     */
    void clearActiveExecuteCommandsDirective(const std::string& token = std::string(), const bool markAsFailed = true);

    /**
     * Set device window state.
     * @param payload The payload for device window state.
     */
    void setDeviceWindowState(const std::string& payload);

    /**
     * Gets Device Time Zone Offset.
     */
    std::chrono::milliseconds getDeviceTimezoneOffset();

    /**
     * handle the renderComplete notification for APL Document
     * @param isAlexaPresentationPresenting Whether the AlexaPresentation agent is presenting or not.
     */
    void handleRenderComplete(bool isAlexaPresentationPresenting);

    /**
     * handle the event raised by APL core engine
     * @param event APL Event in context
     * @param isAlexaPresentationPresenting Whether the AlexaPresentation agent is presenting or not.
     */
    void handleAPLEvent(APLClient::AplRenderingEvent event, bool isAlexaPresentationPresenting);

    /**
     * This function stops playback of the current song in the @c AudioPlayer.
     */
    void audioPlayerLocalStop();

    /**
     * Check if the Comms call is muted.
     *
     * @return Whether the comms call is muted.
     */
    bool isCommsCallMuted();

    /**
     * Mute comms Call.
     */
    void muteCommsCall();

    /**
     * Unmute Comms call.
     */
    void unmuteCommsCall();

    /*
     * To be called when system clock is synchronized.
     */
    void onSystemClockSynchronized();

    /**
     * Register an ExternalMediaPlayerAdapterHandler with the ExternalMediaPlayer CA
     * Multiple adapter handlers can be added to the ExternalMediaPlayer by repeatedly calling this function.
     *
     * @param externalMediaPlayerAdapterHandler Pointer to the EMPAdapterHandler to register
     */
    void registerExternalMediaPlayerAdapterHandler(
        std::shared_ptr<alexaClientSDK::acsdkExternalMediaPlayerInterfaces::ExternalMediaAdapterHandlerInterface>
            externalMediaPlayerAdapterHandler);

    /**
     * Gets the @c ShutdownManagerInterface for when it is time to shut down the SDK.
     *
     * This method is required to support legacy applications that have not transitioned to fully integrating
     * the manufactory.
     * @return A shared_ptr to the @c ShutdownManagerInterface.
     */
    std::shared_ptr<alexaClientSDK::acsdkShutdownManagerInterfaces::ShutdownManagerInterface> getShutdownManager();

    /**
     * Release all observers that are on the alexaClientSDK::afml::FocusManager::DIALOG_CHANNEL_NAME channel
     * This method will be called when there's an user interruption (i.e. click, touch, scroll)
     */
    void releaseAllObserversOnDialogChannel();

#ifdef ENABLE_RTCSC
    /**
     * Adds an observer to be notified of LiveViewController changes.
     *
     * @param observer The @c LiveViewControllerCapabilityAgentObserverInterface to add.
     */
    void addLiveViewControllerCapabilityAgentObserver(
        std::shared_ptr<
            alexaSmartScreenSDK::smartScreenSDKInterfaces::LiveViewControllerCapabilityAgentObserverInterface>
            observer);

    /**
     * Removes an observer to be notified of LiveViewController changes.
     *
     * @param observer The @c LiveViewControllerCapabilityAgentObserverInterface to remove.
     */
    void removeLiveViewControllerCapabilityAgentObserver(
        std::shared_ptr<
            alexaSmartScreenSDK::smartScreenSDKInterfaces::LiveViewControllerCapabilityAgentObserverInterface>
            observer);

    /**
     * Set microphone for live view experience.
     * @param enabled whether microphone should be turned on in live view experiences or not.
     */
    void setCameraMicrophoneState(bool enabled);

    /**
     * Clear live view.
     */
    void clearLiveView();
#endif

    /**
     * Destructor.
     */
    ~SmartScreenClient();

    /**
     * Gets the @c BluetoothLocalInterface for local applications that wish to invoke Bluetooth functionality.
     *
     * @return A shared_ptr to the @c BluetoothLocalInterface.
     */
    std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothLocalInterface> getBluetoothLocal();

private:
    /**
     * Initializes the SDK and "glues" all the components together.
     *
     * @param manufactory @c Manufactory for creating various instances used by DefaultlClient.
     * @param bluetoothMediaPlayer The media player to play bluetooth content.
     * @param ringtoneMediaPlayer The media player to play Comms ringtones.
     * @param systemSoundPlayer The media player to play system sounds.
     * @param bluetoothSpeaker The speaker to control bluetooth volume.
     * @param ringtoneSpeaker The speaker to control volume of Comms ringtones.
     * @param systemSoundSpeaker The speaker to control volume of system sounds.
     * @param additionalSpeakers A map of additional speakers to receive volume changes.
     * @param notificationsStorage The storage interface that will be used to store notification indicators.
     * @param bluetoothStorage The storage interface that will be used to store bluetooth data.
     * @param alexaDialogStateObservers Observers that can be used to be notified of Alexa dialog related UX state
     * changes.
     * @param connectionObservers Observers that can be used to be notified of connection status changes.
     * @param enabledConnectionRules The set of @c BluetoothDeviceConnectionRuleInterface instances used to
     * create the Bluetooth CA.
     * @param firmwareVersion The firmware version to report to @c AVS or @c INVALID_FIRMWARE_VERSION.
     * @param sendSoftwareInfoOnConnected Whether to send SoftwareInfo upon connecting to @c AVS.
     * @param softwareInfoSenderObserver Object to receive notifications about sending SoftwareInfo.
     * @param bluetoothDeviceManager The @c BluetoothDeviceManager instance used to create the Bluetooth CA.
     * @param diagnostics Diagnostics interface that provides suite of APIs for insights into SDK.
     * @param externalCapabilitiesBuilder Object used to build capabilities that are not included in the SDK.
     * @param firstInteractionAudioProvider Optional object used in the first interaction started from
     * the alexa voice service
     * @param visualStateProvider The visual state provider. This should be @C nullptr for non-APL devices
     * @param APLMaxVersion The maximum APL version supported by the GUI client. This default to empty on headles
     * devices.
     * @return Whether the SDK was initialized properly.
     */
    bool initialize(
        const std::shared_ptr<SmartScreenClientManufactory>& manufactory,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> bluetoothMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> ringtoneMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> systemSoundMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> bluetoothSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> ringtoneSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> systemSoundSpeaker,
        const std::multimap<
            alexaClientSDK::avsCommon::sdkInterfaces::ChannelVolumeInterface::Type,
            std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface>> additionalSpeakers,
#ifdef ENABLE_PCC
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> phoneSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::phone::PhoneCallerInterface> phoneCaller,
#endif
#ifdef ENABLE_MCC
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> meetingSpeaker,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::meeting::MeetingClientInterface> meetingClient,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::calendar::CalendarClientInterface> calendarClient,
#endif
#ifdef ENABLE_COMMS_AUDIO_PROXY
        std::shared_ptr<alexaClientSDK::avsCommon::utils::mediaPlayer::MediaPlayerInterface> commsMediaPlayer,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerInterface> commsSpeaker,
        std::shared_ptr<alexaClientSDK::alexaClientSDK::avsCommon::avs::AudioInputStream> sharedDataStream,
#endif
        std::shared_ptr<alexaClientSDK::acsdkNotificationsInterfaces::NotificationsStorageInterface>
            notificationsStorage,
        std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothStorageInterface> bluetoothStorage,
        std::unordered_set<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DialogUXStateObserverInterface>>
            alexaDialogStateObservers,
        std::unordered_set<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ConnectionStatusObserverInterface>>
            connectionObservers,
        std::unordered_set<std::shared_ptr<
            alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceConnectionRuleInterface>>
            enabledConnectionRules,
        alexaClientSDK::avsCommon::sdkInterfaces::softwareInfo::FirmwareVersion firmwareVersion,
        bool sendSoftwareInfoOnConnected,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SoftwareInfoSenderObserverInterface>
            softwareInfoSenderObserver,
        std::unique_ptr<alexaClientSDK::avsCommon::sdkInterfaces::bluetooth::BluetoothDeviceManagerInterface>
            bluetoothDeviceManager,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::diagnostics::DiagnosticsInterface> diagnostics,
        const std::shared_ptr<ExternalCapabilitiesBuilderInterface>& externalCapabilitiesBuilder,
        alexaClientSDK::capabilityAgents::aip::AudioProvider firstInteractionAudioProvider,
        std::shared_ptr<alexaSmartScreenSDK::smartScreenSDKInterfaces::VisualStateProviderInterface>
            visualStateProvider = nullptr,
        const std::string& APLMaxVersion = "");
    /**
     * Adds an ChannelObserverInterface to the set of dialogChannelObserverInterface set. This set will be used
     * to clear the alexaClientSDK::afml::FocusManager::DIALOG_CHANNEL_NAME channel
     * @param observer The ChannelObserverInterface that uses the Dialog channel
     */
    void addDialogChannelObserverInterface(const std::shared_ptr<ChannelObserverInterface>& observer);

    /**
     * Removes an ChannelObserverInterface to the set of dialogChannelObserverInterface set. This set will be used
     * to clear the alexaClientSDK::afml::FocusManager::DIALOG_CHANNEL_NAME channel
     * @param observer The ChannelObserverInterface that uses the Dialog channel
     */
    void removeDialogChannelObserverInterface(const std::shared_ptr<ChannelObserverInterface>& observer);

    std::chrono::milliseconds calculateDeviceTimezoneOffset(const std::string& timeZone);

    /// The directive sequencer.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DirectiveSequencerInterface> m_directiveSequencer;

    /// The focus manager for audio channels.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerInterface> m_audioFocusManager;

    /// The focus manager for visual channels.
    std::shared_ptr<alexaClientSDK::afml::FocusManager> m_visualFocusManager;

    /// The visual activity tracker.
    std::shared_ptr<alexaClientSDK::afml::VisualActivityTracker> m_visualActivityTracker;

    /// The message router.
    std::shared_ptr<alexaClientSDK::acl::MessageRouterInterface> m_messageRouter;

    /// The connection manager.
    std::shared_ptr<alexaClientSDK::acl::AVSConnectionManagerInterface> m_connectionManager;

    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::InternetConnectionMonitorInterface>
        m_internetConnectionMonitor;

    /// The captions manager.
    std::shared_ptr<alexaClientSDK::captions::CaptionManagerInterface> m_captionManager;

    /// The exception sender.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExceptionEncounteredSenderInterface> m_exceptionSender;

    /// The certified sender.
    std::shared_ptr<alexaClientSDK::certifiedSender::CertifiedSender> m_certifiedSender;

    /// The audio input processor.
    std::shared_ptr<alexaClientSDK::capabilityAgents::aip::AudioInputProcessor> m_audioInputProcessor;

    /// The speech synthesizer.
    std::shared_ptr<alexaClientSDK::capabilityAgents::speechSynthesizer::SpeechSynthesizer> m_speechSynthesizer;

    /// The audio player.
    std::shared_ptr<alexaClientSDK::acsdkAudioPlayerInterfaces::AudioPlayerInterface> m_audioPlayer;

    /// The external media player.
    std::shared_ptr<alexaClientSDK::acsdkExternalMediaPlayerInterfaces::ExternalMediaPlayerInterface>
        m_externalMediaPlayer;

    /// The alexa interface message sender.
    std::shared_ptr<alexaClientSDK::capabilityAgents::alexa::AlexaInterfaceMessageSender> m_alexaMessageSender;

    /// The api gateway capability agent.
    std::shared_ptr<alexaClientSDK::capabilityAgents::apiGateway::ApiGatewayCapabilityAgent>
        m_apiGatewayCapabilityAgent;

    /// The alerts capability agent.
    std::shared_ptr<alexaClientSDK::acsdkAlertsInterfaces::AlertsCapabilityAgentInterface> m_alertsCapabilityAgent;

    /// The bluetooth capability agent.
    std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothLocalInterface> m_bluetoothLocal;

    /// The bluetooth notifier.
    std::shared_ptr<alexaClientSDK::acsdkBluetoothInterfaces::BluetoothNotifierInterface> m_bluetoothNotifier;

    /// The interaction model notifier.
    std::shared_ptr<alexaClientSDK::acsdkInteractionModelInterfaces::InteractionModelNotifierInterface>
        m_interactionModelNotifier;

    /// The notifications notifier.
    std::shared_ptr<alexaClientSDK::acsdkNotificationsInterfaces::NotificationsNotifierInterface>
        m_notificationsNotifierInterface;

#ifdef ENABLE_PCC
    /// The phoneCallController capability agent.
    std::shared_ptr<alexaClientSDK::capabilityAgents::phoneCallController::PhoneCallController>
        m_phoneCallControllerCapabilityAgent;
#endif

#ifdef ENABLE_MCC
    /// The MeetingClientController capability agent.
    std::shared_ptr<alexaClientSDK::capabilityAgents::meetingClientController::MeetingClientController>
        m_meetingClientControllerCapabilityAgent;
#endif

    /// The call manager capability agent.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::CallManagerInterface> m_callManager;

    /// The Alexa dialog UX aggregator.
    std::shared_ptr<alexaClientSDK::avsCommon::avs::DialogUXStateAggregator> m_dialogUXStateAggregator;

    /// The playbackRouter.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::PlaybackRouterInterface> m_playbackRouter;

    /// The speakerManager. Used for controlling the volume and mute settings of @c SpeakerInterface objects.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SpeakerManagerInterface> m_speakerManager;

    /// The AlexaPresentation capability agent.
    std::shared_ptr<alexaSmartScreenSDK::smartScreenCapabilityAgents::alexaPresentation::AlexaPresentation>
        m_alexaPresentation;

    /// The TemplateRuntime capability agent.
    std::shared_ptr<alexaSmartScreenSDK::smartScreenCapabilityAgents::templateRuntime::TemplateRuntime>
        m_templateRuntime;

    /// The VisualCharacteristics capability agent.
    std::shared_ptr<alexaSmartScreenSDK::smartScreenCapabilityAgents::visualCharacteristics::VisualCharacteristics>
        m_visualCharacteristics;

#ifdef ENABLE_RTCSC
    /// The LiveViewControllerCapabilityAgent capability agent.
    std::shared_ptr<
        alexaSmartScreenSDK::smartScreenCapabilityAgents::liveViewController::LiveViewControllerCapabilityAgent>
        m_liveViewController;
#endif

    /// The Equalizer capability agent.
    std::shared_ptr<alexaClientSDK::acsdkEqualizer::EqualizerCapabilityAgent> m_equalizerCapabilityAgent;

    /// The @c EqualizerController instance.
    std::shared_ptr<alexaClientSDK::acsdkEqualizer::EqualizerController> m_equalizerController;

    /// Equalizer runtime setup to be used in the SDK.
    std::shared_ptr<alexaClientSDK::acsdkEqualizerInterfaces::EqualizerRuntimeSetupInterface> m_equalizerRuntimeSetup;

    /// Mutex to serialize access to m_softwareInfoSender.
    std::mutex m_softwareInfoSenderMutex;

    /// The System.SoftwareInfoSender capability agent.
    std::shared_ptr<alexaClientSDK::capabilityAgents::system::SoftwareInfoSender> m_softwareInfoSender;

#ifdef ENABLE_REVOKE_AUTH
    /// The System.RevokeAuthorizationHandler directive handler.
    std::shared_ptr<alexaClientSDK::capabilityAgents::system::RevokeAuthorizationHandler> m_revokeAuthorizationHandler;
#endif

    /// The @c AuthDelegateInterface used for authorization events.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AuthDelegateInterface> m_authDelegate;

    /// The RegistrationManager used to control customer registration.
    std::shared_ptr<alexaClientSDK::registrationManager::RegistrationManagerInterface> m_registrationManager;

    /// The @c RegistrationNotifier used to notify RegistrationObservers.
    std::shared_ptr<alexaClientSDK::registrationManager::RegistrationNotifierInterface> m_registrationNotifier;

    /// An instance of the system sounds player.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SystemSoundPlayerInterface> m_systemSoundPlayer;

    /// Module responsible for managing device settings.
    std::shared_ptr<alexaClientSDK::settings::DeviceSettingsManager> m_deviceSettingsManager;

    /// DeviceInfo which reflects the device setup credentials.
    std::shared_ptr<alexaClientSDK::avsCommon::utils::DeviceInfo> m_deviceInfo;

    /// The device context manager.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ContextManagerInterface> m_contextManager;

    /// The endpoint registration manager.
    std::shared_ptr<alexaClientSDK::endpoints::EndpointRegistrationManager> m_endpointRegistrationManager;

    /// The endpoint builder for the default endpoint with AVS Capabilities.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::endpoints::EndpointBuilderInterface>
        m_defaultEndpointBuilder;

    /// The @c AVSGatewayManager instance used in the AVS Gateway connection sequence.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::AVSGatewayManagerInterface> m_avsGatewayManager;

    /// The component that provides the client with the ability to send messages to the Capabilities API.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::CapabilitiesDelegateInterface> m_capabilitiesDelegate;

    /// Diagnostic interface.
    std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::diagnostics::DiagnosticsInterface> m_diagnostics;

    /// The system clock monitor.
    std::shared_ptr<alexaClientSDK::acsdkSystemClockMonitorInterfaces::SystemClockMonitorInterface>
        m_systemClockMonitor;

    /// The list of objects to be shutdown. Shutdown will occur in the reverse order of occurrence.
    std::list<std::shared_ptr<alexaClientSDK::avsCommon::utils::RequiresShutdown>> m_shutdownObjects;

    /// Used to wake up connection retries when the user tries to use the client.
    std::shared_ptr<ConnectionRetryTrigger> m_connectionRetryTrigger;

    /// Device Timezone Offset in milliseconds.
    std::chrono::milliseconds m_deviceTimeZoneOffset{};

    /// A set of SoftwareInfoSenderObservers.
    std::unordered_set<std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::SoftwareInfoSenderObserverInterface>>
        m_softwareInfoSenderObservers;

    /// The SoftwareComponentReporter Capability Agent.
    std::shared_ptr<
        alexaClientSDK::capabilityAgents::softwareComponentReporter::SoftwareComponentReporterCapabilityAgent>
        m_softwareReporterCapabilityAgent;

    /// The @c ShutdownManagerInterface for shutting down the SDK.
    std::shared_ptr<alexaClientSDK::acsdkShutdownManagerInterfaces::ShutdownManagerInterface> m_shutdownManager;

    /// Set of dialog channel observers
    std::unordered_set<std::shared_ptr<ChannelObserverInterface>> m_dialogChannelObserverInterfaces;
};

}  // namespace smartScreenClient
}  // namespace alexaSmartScreenSDK

#endif  // ALEXA_SMART_SCREEN_SDK_APPLICATIONUTILITIES_SMARTSCREENCLIENT_INCLUDE_SMARTSCREENCLIENT_SMARTSCREENCLIENT_H_
