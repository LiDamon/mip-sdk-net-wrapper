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
 * @brief This file contains the Profile class which includes the Profile::Observer and the Profile::Settings classes.
 * 
 * @file profile.h
 */

#ifndef API_MIP_UPE_PROFILE_H_
#define API_MIP_UPE_PROFILE_H_

#include <memory>
#include <string>
#include <vector>

#include "mip/common_types.h"
#include "mip/error.h"
#include "mip/mip_export.h"
#include "mip/upe/policy_engine.h"

namespace mip {

/**
 * @brief Profile class is the root class for using the Microsoft Information Protection operations.
 * A typical application will only need one Profile but it can create multiple profiles if needed.
 */
class Profile {
public:
  /**
   * @brief Observer interface for clients to get notifications for profile related events.
   * 
   * @note If an *Error event occurs, error object holds inside mip::Error class.
   * @note Client should not call the engine back on the thread that calls the observer.
   */
  class Observer {
  public:

    /**
     * @brief Called when profile was loaded successfully.
     * 
     * @param profile the current profile used to start the operation.
     * @param context the context passed to the operation.
     */
    virtual void OnLoadSuccess(
        const std::shared_ptr<Profile>& profile, 
        const std::shared_ptr<void>& context) { UNUSED(profile); UNUSED(context); }

    /**
     * @brief Called when loading a profile caused an error.
     * 
     * @param error the error that cause the load operation to fail.
     * @param context the context passed to the operation.
     */
    virtual void OnLoadFailure(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when list of engines was generated successfully.
     * 
     * @param engineIds a list of engine ids the are available.
     * @param context the context passed to the operation.
     */
    virtual void OnListEnginesSuccess(
        const std::vector<std::string>& engineIds, 
        const std::shared_ptr<void>& context) { UNUSED(engineIds); UNUSED(context); }

    /**
     * @brief Called when listing engines caused an error.
     * 
     * @param error the error that cause the list engine operation to fail.
     * @param context the context passed to the operation.
     */
    virtual void OnListEnginesError(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when an engine was unloaded successfully.
     * 
     * @param context the context passed to the operation.
     */
    virtual void OnUnloadEngineSuccess(const std::shared_ptr<void>& context) { UNUSED(context); }

    /**
     * @brief Called when unloading an engine caused an error.
     *  
     * @param error the error that cause the unload engine operation to fail.
     * @param context the context passed to the operation.
     */
    virtual void OnUnloadEngineError(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when a new engine was added successfully.
     */
    virtual void OnAddEngineSuccess(
        const std::shared_ptr<PolicyEngine>& engine, 
        const std::shared_ptr<void>& context) { UNUSED(engine); UNUSED(context); }

    /**
     * @brief Called when adding a new engine caused an error.
     * 
     * @param error the error that cause the add engine operation to fail.
     * @param context the context passed to the operation.
     */
    virtual void OnAddEngineError(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when an engine was deleted successfully.
     * 
     * @param context the context passed to the operation.
     */
    virtual void OnDeleteEngineSuccess(const std::shared_ptr<void>& context) { UNUSED(context); }

    /**
     * @brief Called when deleting an engine caused an error.
     * 
     * @param error the error that cause the delete engine operation to fail.
     * @param context the context passed to the operation.
     */
    virtual void OnDeleteEngineError(
        const std::exception_ptr& error, 
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when the policy has changed for the engine with the given id.
     * 
     * @param engineId the engine
     * @note To load the new policy it is necessary to call AddEngineAsync again 
     * with the engine Id given. 
     */
    virtual void OnPolicyChanged(const std::string& engineId ) { UNUSED(engineId); }
    
    /** @cond DOXYGEN_HIDE */
    virtual ~Observer() { }
  protected:
    Observer() { }
    /** @endcond */
  };

  class Settings {
  public:
    /**
     * @brief Interface for configuring the profile.
     * 
     * @param path The path to a directory in which the sdk will store the profile state.
     * @param useInMemoryStorage A flag indicating whether or not state should be stored on disk.
     * @param authDelegate The authentication delegate used by the SDK to acquire authenitication tokens.
     * @param observer A class implementing the Profile::Observer interface. Can be nullptr.
     * @param applicationInfo The application identifiers used for service access. 
     */
    Settings(
        const std::string& path,
        bool useInMemoryStorage,
        const std::shared_ptr<AuthDelegate>& authDelegate,
        const std::shared_ptr<Profile::Observer>& observer,
        const ApplicationInfo& applicationInfo)
      : mPath(path),
        mUseInMemoryStorage(useInMemoryStorage),
        mAuthDelegate(authDelegate),
        mObserver(observer),
        mApplicationInfo(applicationInfo) {
    }
    /**
     * @brief Get the path to the stored state.
     * 
     * @return path to stored state.
     */
    const std::string& GetPath() const { return mPath; }
    /**
     * @brief Get the Use In Memory Storage flag.
     * 
     * @return true if use in memory is set else false.
     */
    bool GetUseInMemoryStorage() const { return mUseInMemoryStorage; }
    /**
     * @brief Get the Auth Delegate.
     * 
     * @return the Auth Delegate. 
     */
    const std::shared_ptr<AuthDelegate>& GetAuthDelegate() const { return mAuthDelegate; }
    /**
     * @brief Get the event observer.
     * 
     * @return the event observer.
     */
    const std::shared_ptr<Profile::Observer>& GetObserver() const { return mObserver; }
    /**
     * @brief Get the application info.
     * 
     * @return the application info.
     */
    const ApplicationInfo GetApplicationInfo() const { return mApplicationInfo; }

    /** @cond DOXYGEN_HIDE */
    bool GetSkipTelemetryInit() const { return mSkipTelemetryInit; }
    void SetSkipTelemetryInit() { mSkipTelemetryInit = true; }

    void SetSessionId(const std::string& sessionId) {
      mSessionId = sessionId;
    }

    const std::string& GetSessionId() const {
      return mSessionId;
    }
    ~Settings() { }
  private:
    std::string mPath;
    bool mUseInMemoryStorage;
    std::shared_ptr<AuthDelegate> mAuthDelegate;
    std::shared_ptr<Profile::Observer> mObserver;
    ApplicationInfo mApplicationInfo;
    bool mSkipTelemetryInit = false;
    std::string mSessionId;
    /** @endcond */
  };

  /**
   * @brief Starts loading a profile based on the provided settings.
   * 
   * @param settings the profile settings used to load the profile object.
   * @param context a context parameter that will be passed into the observer functions.
   * @note Profile::Observer will be called upon success or failure.
   */
  MIP_EXPORT static void __CDECL LoadAsync(const Settings& settings, const std::shared_ptr<void>& context);

  /**
   * @brief Get the library version.
   *
   * @return a version string,
   */
  MIP_EXPORT static const char* __CDECL GetVersion();

  /**
   * @brief Get the settings set on the profile.
   * 
   * @return settings set on the profile.
   */
  virtual const Settings& GetSettings() const = 0;

  /**
   * @brief Starts list engines operation.
   *
   * @param context a parameter that will be passed into the observer functions.
   * @note Profile::Observer will be called upon success or failure.
   */
  virtual void ListEnginesAsync(const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Starts unloading the policy engine with the given id.
   * 
   * @param id the unique engine id.
   * @param context a parameter that will be passed into the observer functions.
   * @note Profile::Observer will be called upon success or failure.
   */
  virtual void UnloadEngineAsync(const std::string& id, const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Starts adding a new policy engine to the profile.
   * 
   * @param settings the mip::PolicyEngine::Settings objet that specifies the engines parameters.
   * @param context a parameter that will be passed into the observer functions.
   * @note Profile::Observer will be called upon success or failure.
   */
  virtual void AddEngineAsync(
        const PolicyEngine::Settings& settings,
        const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Starts deleting the policy engine with the given id. All data for the given profile will be completely deleted.
   * 
   * @param id the unique engine id.
   * @param context a parameter that will be passed into the observer functions.
   * @note Profile::Observer will be called upon success or failure.
   */
  virtual void DeleteEngineAsync(const std::string& id, const std::shared_ptr<void>& context) = 0;
  
  /** @cond DOXYGEN_HIDE */
  virtual ~Profile() { }
protected:
  Profile() { }
  /** @endcond */
};

}  // namespace mip

#endif  // API_MIP_UPE_PROFILE_H_
