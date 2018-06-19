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
 * @brief Defines UserPolicy interface and PolicyAcquisitionOptions, UserPolicyCreationOptions, and UserPolicyType enums
 * 
 * @file user_policy.h
 */

#ifndef API_MIP_RMS_USER_POLICY_H_
#define API_MIP_RMS_USER_POLICY_H_

#include <chrono>

#include "mip/rms/cache_control.h"
#include "mip/rms/consent_callback.h"
#include "mip/rms/get_user_policy_result.h"
#include "mip/rms/policy_descriptor.h"
#include "mip/rms/template_descriptor.h"

namespace rmscore {
namespace core {
class ProtectionPolicy;
} // namespace core
} // namespace rmscore

namespace mip {

/**
 * @brief Describes the mode for acquisition operation
 */
enum PolicyAcquisitionOptions {
  /**
   * @brief Default - Allows UI and network operations
   * 
   * @note The SDK will attempt an offline acquisition but will show a UI (via ConsentCallback) and connect to a network
   * when necessary.
   */
  POL_None = 0x0,

  /**
   * @brief Do not allow UI and network operations.
   * 
   * @note The SDK will only attempt an offline acquisition (i.e. from policy cache). If network connectivity is
   * required, the operation will fail. For example, this option may be used by an application which wishes to open
   * content only if it can be done without a network connection.
   */
  POL_OfflineOnly = 0x1
};

/**
 * @brief Bit flags that dictate additional policy creation behavior
 */
enum UserPolicyCreationOptions {
  USER_None = 0x0, /**< None  */
  USER_AllowAuditedExtraction = 0x1, /**< Content can be opened in a non-RMS-aware app */
  USER_PreferDeprecatedAlgorithms = 0x2, /**< Use deprecated crypto algorithms (ECB) for backwards compatibility */
};

/**
 * @brief UserPolicyCreationOptions bitwise OR operator
 * 
 * @param a Left value
 * @param b Right value
 * 
 * @return Bitwise OR of parameters
 */
inline UserPolicyCreationOptions operator|(UserPolicyCreationOptions a, UserPolicyCreationOptions b) {
  return static_cast<UserPolicyCreationOptions>(static_cast<int>(a) | static_cast<int>(b));
}

/**
 * @brief Origin type of policy
*/
enum class UserPolicyType {
  TemplateBased = 0, /**< Policy was created from a template */
  Custom = 1, /**< Policy was created ad hoc */
};

/**
 * @brief Represents the policy associated with protected content
 */
class UserPolicy {
public:

// TODO: This code depends on the "#include <future>" part of the STL library, which is unsupported in C++/CLI.

  ///**
  // * @brief Acquire a UserPolicy from a serialized publishing license (PL)
  // * 
  // * @param serializedPolicy Serialized publishing license (PL) to be rehydrated into a UserPolicy
  // * @param userId Email address of the user trying to consume the protected content. This id will be used during OAuth
  // *  token acquisition (i.e. it will be the identity used in AuthDelegate::AcquireOAuth2Token()). This id will also be
  // *  checked when loading a policy from the offline cache (if supported by ResponseCacheFlags).
  // * @param authenticationCallback Callback used for the authentication process
  // * @param consentCallback Callback used if SDK requires any user consent during policy acquisition. If null, all
  // *  consents will be granted automatically.
  // * @param options Describes additional acquisition options (e.g. offline-only, etc.)
  // * @param cacheMask Describes whether and how acquisition response is cached to allow future offline acquisitions
  // * @param cancelState Cancellation token to allow application to cancel this operation at any time
  // * 
  // * @return GetUserPolicyResult object 
  // */
  //MIP_EXPORT static std::shared_ptr<mip::GetUserPolicyResult> Acquire(
  //    const std::vector<unsigned char>& serializedPolicy,
  //    const std::string& userId,
  //    mip::AuthDelegate& authenticationCallback,
  //    mip::ConsentCallback* consentCallback,
  //    PolicyAcquisitionOptions options,
  //    mip::ResponseCacheFlags cacheMask,
  //    std::shared_ptr<std::atomic<bool>> cancelState);

  ///**
  // * @brief Creates a new UserPolicy from a template id
  // * 
  // * @param templateId RMS template to be applied to this UserPolicy
  // * @param userId Email address of the user trying to consume the protected content. This id will be used during OAuth
  // *  token acquisition (i.e. it will be the identity used in AuthDelegate::AcquireOAuth2Token()).
  // * @param authenticationCallback Callback used for the authentication process
  // * @param options Describes additional acquisition options (e.g. offline-only, etc.)
  // * @param signedAppData Signed app-specific data
  // * @param cancelState Cancellation token to allow application to cancel this operation at any time
  // * 
  // * @return New UserPolicy instance
  // */
  //MIP_EXPORT static std::shared_ptr<UserPolicy> CreateFromTemplateId(
  //    const std::string& templateId,
  //    const std::string& userId,
  //    mip::AuthDelegate& authenticationCallback,
  //    UserPolicyCreationOptions options,
  //    const mip::AppDataHashMap& signedAppData,
  //    std::shared_ptr<std::atomic<bool>> cancelState);

  ///**
  // * @brief Creates a new UserPolicy from a TemplateDescriptor
  // * 
  // * @param templateDescriptor RMS template to be applied to this UserPolicy
  // * @param userId Email address of the user trying to consume the protected content. This id will be used during OAuth
  // *  token acquisition (i.e. it will be the identity used in AuthDelegate::AcquireOAuth2Token()).
  // * @param authenticationCallback Callback used for the authentication process
  // * @param options Describes additional acquisition options (e.g. offline-only, etc.)
  // * @param signedAppData Signed app-specific data
  // * @param cancelState Cancellation token to allow application to cancel this operation at any time
  // * 
  // * @return New UserPolicy instance
  // */
  //MIP_EXPORT static std::shared_ptr<UserPolicy> CreateFromTemplateDescriptor(
  //    const TemplateDescriptor& templateDescriptor,
  //    const std::string& userId,
  //    mip::AuthDelegate& authenticationCallback,
  //    UserPolicyCreationOptions options,
  //    const mip::AppDataHashMap& signedAppData,
  //    std::shared_ptr<std::atomic<bool>> cancelState);

  ///**
  // * @brief Creates a new UserPolicy from a PolicyDescriptor
  // * 
  // * @param policyDescriptor Ad hoc description of policy
  // * @param userId Email address of the user trying to consume the protected content. This id will be used during OAuth
  // *  token acquisition (i.e. it will be the identity used in AuthDelegate::AcquireOAuth2Token()).
  // * @param authenticationCallback Callback used for the authentication process
  // * @param options Describes additional acquisition options (e.g. offline-only, etc.)
  // * @param cancelState Cancellation token to allow application to cancel this operation at any time
  // * 
  // * @return New UserPolicy instance
  // */
  //MIP_EXPORT static std::shared_ptr<UserPolicy> Create(
  //    mip::PolicyDescriptor& policyDescriptor,
  //    const std::string& userId,
  //    mip::AuthDelegate& authenticationCallback,
  //    UserPolicyCreationOptions options,
  //    std::shared_ptr<std::atomic<bool>> cancelState);

  /**
   * @brief Clear protection policy cache
   * 
   * @note Internal only
   */
  MIP_EXPORT static void ClearProtectionPolicyFromCache();

  /**
   * @brief Checks if policy grants user access to specified right
   * 
   * @param right Right to check
   * 
   * @return Whether or not policy grants user access to specified right
   */
  virtual bool AccessCheck(const std::string& right) const = 0;

  /**
   * @brief Gets policy type
   * 
   * @return Policy type
   */
  virtual UserPolicyType GetType() = 0;

  /**
   * @brief Gets policy name
   * 
   * @return Policy name
   */
  virtual std::string GetName() = 0;

  /**
   * @brief Gets policy description
   * 
   * @return Policy description
   */
  virtual std::string GetDescription() = 0;

  /**
   * @brief Gets TemplateDescriptor for a template-based UserPolicy
   * 
   * @return TemplateDescriptor if UserPolicy is template-based, else nullptr
   */
  virtual std::shared_ptr<TemplateDescriptor> GetTemplateDescriptor() = 0;

  /**
   * @brief Gets PolicyDescriptor for an ad hoc UserPolicy
   * 
   * @return PolicyDescriptor if UserPolicy is ad hoc, else nullptr
   */
  virtual std::shared_ptr<PolicyDescriptor> GetPolicyDescriptor() = 0;

  /**
   * @brief Gets email address of content owner
   * 
   * @return Email address of content owner
   */
  virtual std::string GetOwner() = 0;

  /**
   * @brief Gets user associated with the protection policy
   * 
   * @return User associated with protection policy
   */
  virtual std::string GetIssuedTo() = 0;

  /**
   * @brief Gets whether or not the current user is the content owner
   * 
   * @return Whether or not the current user is the content owner
   */
  virtual bool IsIssuedToOwner() = 0;

  /**
   * @brief Gets unique identifier for the document/content
   * 
   * @return Unique content identifier
   */
  virtual std::string GetContentId() = 0;

  /**
   * @brief Gets app-specific data that was encrypted
   * 
   * @note A UserPolicy may contain a dictionary of app-specific data that was encrypted by the RMS service. This
   * encrypted data is independent of the signed data accessible via UserPolicy::GetSignedAppData
   */
  virtual const mip::AppDataHashMap GetEncryptedAppData() = 0;

  /**
   * @brief Gets the app-specific data that was signed
   * 
   * @note A UserPolicy may contain a dictionary of app-specific data that was signed by the RMS service. This signed
   * data is independent of the encrypted data accessible via UserPolicy::GetEncryptedAppData
   */
  virtual const mip::AppDataHashMap GetSignedAppData() = 0;

  /**
   * @brief Gets policy expiration time
   * 
   * @return Policy expiration time
   */
  virtual std::chrono::time_point<std::chrono::system_clock> GetContentValidUntil() = 0;

  /**
   * @brief Gets whether or not policy uses deprecated crypto algorithms (ECB) for backward compatibility
   * 
   * @return Whether or not policy uses deprecated crypto algorithms
   */
  virtual bool DoesUseDeprecatedAlgorithms() = 0;

  /**
   * @brief Gets whether or not policy grants user 'audited extract' right
   * 
   * @return Whether or not policy grants user 'audited extract' right
   */
  virtual bool IsAuditedExtractAllowed() = 0;

  /**
   * @brief Serialize UserPolicy into a publishing license (PL)
   * 
   * @return Serialized UserPolicy
   */
  virtual const std::vector<unsigned char> GetSerializedPolicy() = 0;

  /**
   * @brief Gets internal derived class implementation of UserPolicy
   * 
   * @return Derived class implementation of UserPolicy
   * 
   * @note Internal only
   */
  virtual std::shared_ptr<rmscore::core::ProtectionPolicy> GetImpl() = 0;

  /** @cond DOXYGEN_HIDE */
  virtual ~UserPolicy() {}

protected:
  UserPolicy() {}
  /** @endcond */
};

} // namespace mip

#endif // API_MIP_RMS_USER_POLICY_H_
