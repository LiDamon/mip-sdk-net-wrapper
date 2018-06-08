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
 * @brief Defines PolicyDescriptor interface
 * 
 * @file policy_descriptor.h
 */

#ifndef API_MIP_RMS_POLICY_DESCRIPTOR_H_
#define API_MIP_RMS_POLICY_DESCRIPTOR_H_

#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>

#include "mip/mip_export.h"
#include "mip/rms/user_rights.h"
#include "mip/rms/user_roles.h"

namespace mip {

/**
 * @brief Key/Value dictionary of app-specific data
 */
using AppDataHashMap = std::unordered_map<std::string, std::string>;

/**
* @brief Represents an ad-hoc policy associated with protected content
*/
class PolicyDescriptor {
public:
  /**
   * @brief Creates a PolicyDescriptor whose access permissions are defined by users and rights
   * 
   * @param userRightsList Collection of users-to-rights mappings
   * 
   * @return New PolicyDescriptor instance
   */
  MIP_EXPORT static std::shared_ptr<PolicyDescriptor> Create(const std::vector<mip::UserRights>& userRightsList);

  /**
   * @brief Creates a PolicyDescriptor whose access permissions are defined by users and roles
   * 
   * @param userRolesList Collection of users-to-roles mappings
   * 
   * @return New PolicyDescriptor instance
   */
  MIP_EXPORT static std::shared_ptr<PolicyDescriptor> Create(const std::vector<mip::UserRoles>& userRolesList);

  /**
   * @brief Gets policy name
   * 
   * @return Policy name
   */
  virtual const std::string& GetName() = 0;

  /**
   * @brief Sets policy name
   * 
   * @param value Policy name
   */
  virtual void SetName(const std::string& value) = 0;

  /**
   * @brief Gets policy description
   * 
   * @return Policy description
   */
  virtual const std::string& GetDescription() = 0;

  /**
   * @brief Sets policy description
   * 
   * @param value Policy description
   */
  virtual void SetDescription(const std::string& value) = 0;

  /**
  * @brief Gets collection of users-to-rights mappings

  * @return Collection of users-to-rights mappings
  *
  * @note The value of the UserRightsList property will be empty if the current user doesn't have access to the user
  * rights information (i.e. is not the owner and does not have the VIEWRIGHTSDATA right).
  */
  virtual const std::vector<UserRights>& GetUserRightsList() const = 0;

  /**
   * @brief Gets collection of users-to-roles mappings
   * 
   * @return Collection of users-to-roles mappings
   */
  virtual const std::vector<mip::UserRoles>& GetUserRolesList() = 0;

  /**
   * @brief Gets policy expiration time
   * 
   * @return Policy expiration time
   */
  virtual const std::chrono::time_point<std::chrono::system_clock>& GetContentValidUntil() = 0;

  /**
   * @brief Sets policy expiration time
   * 
   * @param value Policy expiration time
   */
  virtual void SetContentValidUntil(const std::chrono::time_point<std::chrono::system_clock>& value) = 0;

  /**
   * @brief Gets whether or not policy allows offline content access
   * 
   * @return Whether or not policy allows offline content access (default = true)
   */
  virtual bool DoesAllowOfflineAccess() = 0;

  /**
   * @brief Sets whether or not policy allows offline content access
   * 
   * @param value Whether or not policy allows offline content access
   */
  virtual void SetAllowOfflineAccess(bool value) = 0;

  /**
   * @brief Gets policy referrer address
   * 
   * @return Policy referrer address
   * 
   * @note The referrer is a URI that can be displayed to the user upon failed policy acquisition that contains
   * information on how that user can gain permission to access the content.
   */
  virtual const std::string& GetReferrer() const = 0;

  /**
   * @brief Sets policy referrer address
   * 
   * @param uri Policy referrer address
   * 
   * @note The referrer is a URI that can be displayed to the user upon failed policy acquisition that contains
   * information on how that user can gain permission to access the content.
   */
  virtual void SetReferrer(const std::string& uri) = 0;

  /**
   * @brief Gets app-specific data that was encrypted
   * 
   * @return App-specific data
   * 
   * @note A UserPolicy may contain a dictionary of app-specific data that was encrypted by the RMS service. This
   * encrypted data is independent of the signed data accessible via PolicyDescriptor::GetSignedAppData
   */
  virtual const AppDataHashMap& GetEncryptedAppData() = 0;

  /**
   * @brief Sets app-specific data that should be encrypted
   * 
   * @param value App-specific data
   * 
   * @note An application can specify a dictionary of app-specific data that will be encrypted by the RMS service. This
   * encrypted data is independent of the signed data set by PolicyDescriptor::SetSignedAppData.
   */
  virtual void SetEncryptedAppData(const AppDataHashMap& value) = 0;

  /**
   * @brief Gets the app-specific data that was signed
   * 
   * @return App-specific data
   * 
   * @note A UserPolicy may contain a dictionary of app-specific data that was signed by the RMS service. This signed
   * data is independent of the encrypted data accessible via PolicyDescriptor::GetEncryptedAppData
   */
  virtual const AppDataHashMap& GetSignedAppData() = 0;

  /**
   * @brief Sets app-specific data that should be signed
   * 
   * @param value App-specific data
   * 
   * @note An application can specify a dictionary of app-specific data that will be signed by the RMS service. This
   * signed data is independent of the encrypted data set by PolicyDescriptor::SetEncryptedAppData.
   */
  virtual void SetSignedAppData(const AppDataHashMap& value) = 0;

  /** @cond DOXYGEN_HIDE */
  virtual ~PolicyDescriptor() {}

protected:
  PolicyDescriptor() {}
  /** @endcond */
};

} // namespace mip

#endif //API_MIP_RMS_POLICY_DESCRIPTOR_H_
