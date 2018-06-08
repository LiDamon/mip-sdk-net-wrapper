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
 * @brief Defines GetUserPolicyResultStatus enum and GetUserPolicyResult interface
 * 
 * @file get_user_policy_result.h
 */

#ifndef API_MIP_RMS_GET_USER_POLICY_RESULT_H_
#define API_MIP_RMS_GET_USER_POLICY_RESULT_H_

#include <memory>
#include <string>

namespace mip {
class UserPolicy; // Forward declared because user_policy.h already #includes get_user_policy_result.h

/**
 * @brief Describes status of user policy acquisition request
 */
enum class GetUserPolicyResultStatus {
  Success = 0, /**< Success */
  NoRights = 1, /**< User has no rights to content */
  Expired = 2, /**< Content expired */
};

/**
 * @brief Describes the results of a user policy acquisition request
 */
class GetUserPolicyResult {
public:
  /**
   * @brief Gets the status of the policy acquisition request
   * 
   * @return Status of the policy acquisition request
   */
  virtual GetUserPolicyResultStatus GetResultStatus() = 0;
  
  /**
   * @brief Gets the refererrer address of the policy
   * 
   * @return Referrerer address of the policy
   * 
   * @note The referrer is a URI that can be displayed to the user upon failed policy acquisition that contains
   * information on how that user can gain permission to access the content.
   */
  virtual std::shared_ptr<std::string> GetReferrer() = 0;

  /**
   * @brief Gets a UserPolicy instance
   * 
   * @return UserPolicy instance if acquisition was successful, else nullptr
   */
  virtual std::shared_ptr<UserPolicy> GetPolicy() = 0;

  /** @cond DOXYGEN_HIDE */
  virtual ~GetUserPolicyResult() {}
  
protected:
  GetUserPolicyResult() {}
  /** @endcond */
};
} // namespace mip

#endif // API_MIP_RMS_GET_USER_POLICY_RESULT_H_

