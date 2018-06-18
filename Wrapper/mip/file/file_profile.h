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

#ifndef API_MIP_FILE_FILE_PROFILE_H_
#define API_MIP_FILE_FILE_PROFILE_H_

#include <memory>
#include <string>
#include <vector>

#include "mip/common_types.h"
#include "mip/error.h"
#include "mip/file/file_engine.h"
#include "mip/file/file_export.h"

namespace mip {

/**
 * @brief FileProfile class is the root class for using the Microsoft Information Protection operations.
 * 
 * A typical application will only need one Profile but it can create multiple profiles if needed.
 */
class FileProfile {
public:

  /**
   * @brief Observer interface for clients to get notifications for profile related events.
   * 
   * @note If an *Error event occurs, error object holds inside mip::Error class.
   * @note Client should not call the engine back on the thread that calls the observer.
   */
  class Observer {
  public:
    virtual ~Observer() {}

    /**
     * @brief Called when profile was loaded successfully.
     */
    virtual void OnLoadSuccess(
        const std::shared_ptr<mip::FileProfile>& profile, 
        const std::shared_ptr<void>& context) { UNUSED(profile); UNUSED(context); }

    /**
     * @brief Called when loading a profile caused an error.
     */
    virtual void OnLoadFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when list of engines was generated successfully.
     */
    virtual void OnListEnginesSuccess(
        const std::vector<std::string>& engineIds, 
        const std::shared_ptr<void>& context) { UNUSED(engineIds); UNUSED(context); }

    /**
     * @brief Called when listing engines caused an error.
     */
    virtual void OnListEnginesError(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when an engine was unloaded successfully.
     */
    virtual void OnUnloadEngineSuccess(const std::shared_ptr<void>& context) { UNUSED(context); }

    /**
     * @brief Called when unloading an engine caused an error.
     */
    virtual void OnUnloadEngineError(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when a new engine was added successfully.
     */
    virtual void OnAddEngineSuccess(
        const std::shared_ptr<mip::FileEngine>& engine, 
        const std::shared_ptr<void>& context) { UNUSED(engine); UNUSED(context); }

    /**
     * @brief Called when adding a new engine caused an error.
     */
    virtual void OnAddEngineError(const std::exception_ptr& error, const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when an engine was deleted successfully.
     */
    virtual void OnDeleteEngineSuccess(const std::shared_ptr<void>& context) { UNUSED(context); }

    /**
     * @brief Called when deleting an engine caused an error.
     */
    virtual void OnDeleteEngineError(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when the policy has changed for the engine with the given id.
     */
    virtual void OnPolicyChanged(const std::string& engineId) { UNUSED(engineId); }

  protected:
    Observer() {}
  };

  class Settings {
  public:
    /**
     * @brief Interface for configuring the profile.
     * 
     * @param observer A class implementing the FileHandler::Observer interface. Can be nullptr.
     */
    Settings(
        const std::string& path,
        bool useInMemoryStorage,
        std::shared_ptr<AuthDelegate> authDelegate,
        std::shared_ptr<Observer> observer,
        const ApplicationInfo& applicationInfo)
      : mPath(path),
        mUseInMemoryStorage(useInMemoryStorage),
        mAuthDelegate(authDelegate),
        mObserver(observer),
        mApplicationInfo(applicationInfo) {
    }
    ~Settings() {}

    const std::string& GetPath() const { return mPath; }
    bool GetUseInMemoryStorage() const { return mUseInMemoryStorage; }
    std::shared_ptr<AuthDelegate> GetAuthDelegate() const { return mAuthDelegate; }
    std::shared_ptr<Observer> GetObserver() const { return mObserver; }
    const ApplicationInfo GetApplicationInfo() const { return mApplicationInfo; }
    bool GetSkipTelemetryInit() const { return mSkipTelemetryInit; }
    void SetSkipTelemetryInit() { mSkipTelemetryInit = true; }

    /**
    * @brief Sets the profile session id.
    */
    void SetSessionId(const std::string& sessionId) {
      mSessionId = sessionId;
    }

    /**
    * @brief Return the profile session id.
    */
    const std::string& GetSessionId() const {
      return mSessionId;
    }

  private:
    std::string mPath;
    bool mUseInMemoryStorage;
    std::shared_ptr<AuthDelegate> mAuthDelegate;
    std::shared_ptr<Observer> mObserver;
    ApplicationInfo  mApplicationInfo;
    bool mSkipTelemetryInit = false;
    std::string mSessionId;
  };

  /**
   * @brief Starts loading a profile based on the provided |settings|.
   * 
   * @note FileProfile::Observer will be called upon success or failure.
   */
//  FILE_EXPORT static void __CDECL LoadAsync(const Settings& settings, const std::shared_ptr<void>& context);
  FILE_EXPORT static void __cdecl LoadAsync(const Settings& settings, const std::shared_ptr<void>& context);

  /**
   * @brief Gets library version.
   *
   * @return Version string
   */
//  FILE_EXPORT static const char* __CDECL GetVersion();
  FILE_EXPORT static const char* __cdecl GetVersion();

  virtual ~FileProfile() {}

  /**
   * @brief Returns the profile settings.
   */
  virtual const Settings& GetSettings() const = 0;

  /**
   * @brief Starts list engines operation.
   * 
   * @note FileProfile::Observer will be called upon success or failure.
   */
  virtual void ListEnginesAsync(const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Starts unloading the file engine with the given id.
   * 
   * @note FileProfile::Observer will be called upon success or failure.
   */
  virtual void UnloadEngineAsync(const std::string& id, const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Starts adding a new file engine to the profile.
   * 
   * @note FileProfile::Observer will be called upon success or failure.
   */
  virtual void AddEngineAsync(
      const FileEngine::Settings& settings,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Starts deleting the file engine with the given id. All data for the given profile will be completely deleted.
   * 
   * @note FileProfile::Observer will be called upon success or failure.
   */
  virtual void DeleteEngineAsync(const std::string& id, const std::shared_ptr<void>& context) = 0;

protected:
  FileProfile() {}
};

} // namespace mip

#endif  // API_MIP_FILE_FILE_PROFILE_H_
