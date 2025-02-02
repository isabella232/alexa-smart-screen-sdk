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

#ifndef ALEXA_SMART_SCREEN_SDK_SAMPLEAPP_INCLUDE_SAMPLEAPP_KEYWORDOBSERVER_H_
#define ALEXA_SMART_SCREEN_SDK_SAMPLEAPP_INCLUDE_SAMPLEAPP_KEYWORDOBSERVER_H_

#include <memory>
#include <string>

#include <AVSCommon/AVS/AudioInputStream.h>
#include <AVSCommon/SDKInterfaces/KeyWordObserverInterface.h>
#include <SmartScreenClient/SmartScreenClient.h>

#include <acsdkKWDImplementations/AbstractKeywordDetector.h>

namespace alexaSmartScreenSDK {
namespace sampleApp {

/**
 * Observes callbacks from keyword detections and notifies the SmartScreenClient that a wake word has occurred.
 */
class KeywordObserver : public alexaClientSDK::avsCommon::sdkInterfaces::KeyWordObserverInterface {
public:
    /**
     * Creates a KeywordObserver and registers as an observer to a KeywordDetector.
     *
     * @param client The default SDK client.
     * @param audioProvider The audio provider from which to stream audio data from.
     * @param keywordDetector The @c AbstractKeywordDetector to self register to as an observer.
     *
     * @return a @c KeywordObserver.
     */
    static std::shared_ptr<KeywordObserver> create(
        std::shared_ptr<smartScreenClient::SmartScreenClient> client,
        alexaClientSDK::capabilityAgents::aip::AudioProvider audioProvider,
        std::shared_ptr<alexaClientSDK::acsdkKWDImplementations::AbstractKeywordDetector> keywordDetector);

    /**
     * Constructor.
     *
     * @param client The default SDK client.
     * @param audioProvider The audio provider from which to stream audio data from.
     */
    KeywordObserver(
        std::shared_ptr<smartScreenClient::SmartScreenClient> client,
        alexaClientSDK::capabilityAgents::aip::AudioProvider audioProvider);

    /// @name KeyWordObserverInterface Functions
    /// @{
    void onKeyWordDetected(
        std::shared_ptr<alexaClientSDK::avsCommon::avs::AudioInputStream> stream,
        std::string keyword,
        alexaClientSDK::avsCommon::avs::AudioInputStream::Index beginIndex = UNSPECIFIED_INDEX,
        alexaClientSDK::avsCommon::avs::AudioInputStream::Index endIndex = UNSPECIFIED_INDEX,
        std::shared_ptr<const std::vector<char>> KWDMetadata = nullptr) override;
    /// @}

private:
    /// The default SDK client.
    std::shared_ptr<smartScreenClient::SmartScreenClient> m_client;

    /// The audio provider.
    alexaClientSDK::capabilityAgents::aip::AudioProvider m_audioProvider;
};

}  // namespace sampleApp
}  // namespace alexaSmartScreenSDK

#endif  // ALEXA_SMART_SCREEN_SDK_SAMPLEAPP_INCLUDE_SAMPLEAPP_KEYWORDOBSERVER_H_
