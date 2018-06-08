/**
 *
 * Copyright (c) Microsoft Corporation.
 * All rights reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/**
 * @brief Defines ProtectionProfile interface
 * 
 * @file protection_profile.h
 */

#ifndef API_MIP_RMS_PROTECTION_PROFILE_H_
#define API_MIP_RMS_PROTECTION_PROFILE_H_

#include <future>
#include <memory>
#include <string>

#include "mip/common_types.h"
#include "mip/mip_export.h"

namespace mip {

/**
 * @brief ProtectionProfile is the root class for performing protection operations
 * 
 * @note An application need to create a ProtectionProfile prior to performing any protection operations
 */
class ProtectionProfile {
public:
  /**
   * @brief Interface that receives notifications related to ProtectionProfile
   * 
   * @note This interface must by implemented by applications using the protection SDK
   */
  class Observer {
  public:
    /** @cond DOXYGEN_HIDE */
    virtual ~Observer() { }
    /** @endcond */

    /**
     * @brief Called when profile was loaded successfully
     * 
     * @param profile A reference to the newly-created ProtectionProfile
     * @param context The same context that was passed to ProtectionProfile::LoadAsync
     * 
     * @note An application can pass any type of context (e.g. std::promise, std::function, etc.) to
     * ProtectionProfile::LoadAsync and that same context will be forwarded as-is to
     * ProtectionProfile::Observer::OnLoadSuccess or ProtectionProfile::Observer::OnLoadFailure
     */
    virtual void OnLoadSuccess(
        const std::shared_ptr<ProtectionProfile>& profile, 
        const std::shared_ptr<void>& context) { UNUSED(profile); UNUSED(context); }

    /**
     * @brief Called when loading a profile caused an error
     * 
     * @param error Error that occured while loading
     * @param context The same context that was passed to ProtectionProfile::LoadAsync
     * 
     * @note An application can pass any type of context (e.g. std::promise, std::function, etc.) to
     * ProtectionProfile::LoadAsync and that same context will be forwarded as-is to
     * ProtectionProfile::Observer::OnLoadSuccess or ProtectionProfile::Observer::OnLoadFailure
     */
    virtual void OnLoadFailure(
        const std::exception_ptr& error,
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /** @cond DOXYGEN_HIDE */
  protected:
    Observer() { }
    /** @endcond */
  };

  /**
   * @brief Settings used by ProtectionProfile during its creation and throughout its lifetime
   */
  class Settings {
  public:
    /**
     * @brief ProtectionProfile::Settings constructor
     * 
     * @param path File path under which logging, telemetry, and other protection collateral is stored
     * @param observer Observer instance which will receive notifications of events related to ProtectionProfile 
     * @param applicationInfo Info regarding application which is consuming the protection SDK
     */
    Settings(
        const std::string& path,
        const std::shared_ptr<ProtectionProfile::Observer>& observer,
        const ApplicationInfo& applicationInfo)
      : mPath(path),
        mObserver(observer),
        mApplicationInfo(applicationInfo) {
    }

    /** @cond DOXYGEN_HIDE */
    ~Settings() { }
    /** @endcond */

    /**
     * @brief Gets the path under which logging, telemetry, and other protection collateral is stored
     * 
     * @return Path under which logging, telemetry, and other protection collateral is stored
     */
    const std::string& GetPath() const { return mPath; }

    /**
     * @brief Gets the observer which receieves notifications of events related to ProtectionProfile
     * 
     * @return Observer which receieves notifications of events related to ProtectionProfile
     */
    const std::shared_ptr<ProtectionProfile::Observer>& GetObserver() const { return mObserver; }

    /**
     * @brief Gets info regarding application which is consuming the protection SDK
     * 
     * @return Info regarding application which is consuming the protection SDK
     */
    const ApplicationInfo& GetApplicationInfo() const { return mApplicationInfo; }

    /**
     * @brief Gets whether or not telemetry initialization should be skipped
     * 
     * @return Whether or not telemetry initialization should be skipped
     */
    bool GetSkipTelemetryInit() const { return mSkipTelemetryInit; }

    /**
     * @brief Disables telemetry initialization
     * 
     * @note This should not normally be called by client applications, rather it is used by File SDK (which already
     * initializes telemetry) to prevent duplicate initialization
     */
    void SetSkipTelemetryInit() { mSkipTelemetryInit = true; }

    /**
     * @brief Sets the session id
     * 
     * @param sessionId Session id which will be used to correlate logs/telemetry
     */
    void SetSessionId(const std::string& sessionId) { mSessionId = sessionId; }

    /**
     * @brief Gets the session id
     * 
     * @return Session id which will be used to correlate logs/telemetry
     */
    const std::string& GetSessionId() const { return mSessionId; }

  private:
    std::string mPath;
    std::shared_ptr<ProtectionProfile::Observer> mObserver;
    ApplicationInfo mApplicationInfo;
    std::launch mLaunchMode;
    bool mSkipTelemetryInit = false;
    std::string mSessionId;
  };

  /**
   * @brief Starts loading a profile based on the provided settings.
   * 
   * @param settings Settings used by ProtectionProfile during its initialization and throughout its lifetime
   * @param context This same context will be forwarded to ProtectionProfile::Observer::OnLoadSuccess or
   * ProtectionProfile::Observer::OnLoadFailure as-is.
   * 
   * @note ProtectionProfile::Observer will be called upon success or failure.
   */
  MIP_EXPORT static void __CDECL LoadAsync(const Settings& settings, const std::shared_ptr<void>& context);

  /**
   * @brief Gets library version
   *
   * @return Library version
   */
  MIP_EXPORT static const char* __CDECL GetVersion();

  /**
   * @brief Gets settings used by ProtectionProfile during its initialization and throughout its lifetime
   * 
   * @return Settings used by ProtectionProfile during its initialization and throughout its lifetime
   */
  virtual const Settings& GetSettings() const = 0;

  /**
   * @brief Deletes caches (e.g. consent databases, etc.)
   * 
   * @note Useful for debugging/testing
   */
  virtual void ClearCaches() = 0;

  /**
   * @brief Gets the path under which logging, telemetry, and other protection collateral is stored
   * 
   * @return Path under which logging, telemetry, and other protection collateral is stored
   */
  static std::string GetPath();

  /** @cond DOXYGEN_HIDE */
  virtual ~ProtectionProfile() { }
  /** @endcond */
};

} // namespace mip

#endif // API_MIP_RMS_PROTECTION_PROFILE_H_

